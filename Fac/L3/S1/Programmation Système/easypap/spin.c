
#include "easypap.h"

#include <math.h>
#include <omp.h>

static void rotate (void);
static unsigned compute_color (int i, int j);

// If defined, the initialization hook function is called quite early in the
// initialization process, after the size (DIM variable) of images is known.
// This function can typically spawn a team of threads, or allocated additionnal
// OpenCL buffers.
// A function named <kernel>_init_<variant> is search first. If not found, a
// function <kernel>_init is searched in turn.
void spin_init (void)
{
  // check tile size's conformity with respect to CPU vector width
  // easypap_check_vectorization (VEC_TYPE_FLOAT, DIR_HORIZONTAL);

  PRINT_DEBUG ('u', "Image size is %dx%d\n", DIM, DIM);
  PRINT_DEBUG ('u', "Block size is %dx%d\n", TILE_W, TILE_H);
  PRINT_DEBUG ('u', "Press <SPACE> to pause/unpause, <ESC> to quit.\n");
}

// The image is a two-dimension array of size of DIM x DIM. Each pixel is of
// type 'unsigned' and store the color information following a RGBA layout (4
// bytes). Pixel at line 'l' and column 'c' in the current image can be accessed
// using cur_img (l, c).

// The kernel returns 0, or the iteration step at which computation has
// completed (e.g. stabilized).

///////////////////////////// Simple sequential version (seq)
// Suggested cmdline(s):
// ./run --size 1024 --kernel spin --variant seq
// or
// ./run -s 1024 -k spin -v seq
//
unsigned spin_compute_seq (unsigned nb_iter)
{
  for (unsigned it = 1; it <= nb_iter; it++) {

    for (int i = 0; i < DIM; i++)
      for (int j = 0; j < DIM; j++)
        cur_img (i, j) = compute_color (i, j);

    rotate (); // Slightly increase the base angle
  }

  return 0;
}


// Tile computation
int spin_do_tile_default (int x, int y, int width, int height)
{
  for (int i = y; i < y + height; i++)
    for (int j = x; j < x + width; j++)
      cur_img (i, j) = compute_color (i, j);

  return 0;
}


///////////////////////////// Tiled sequential version (tiled)
// Suggested cmdline(s):
// ./run -k spin -v tiled -ts 64 -m
//
unsigned spin_compute_tiled (unsigned nb_iter)
{
  for (unsigned it = 1; it <= nb_iter; it++) {

    for (int y = 0; y < DIM; y += TILE_H)
      for (int x = 0; x < DIM; x += TILE_W)
        do_tile (x, y, TILE_W, TILE_H, 0 /* CPU id */);

    rotate ();
  }

  return 0;
}

///////////////////////////// Multithreaded version (tiled)

static unsigned NB_THREADS;
static unsigned iterations = 1;
static pthread_barrier_t barrier;
static pthread_mutex_t mutex = PTHREAD_MUTEX_INITIALIZER;
static unsigned the_index    = 0;

void spin_init_thr (void)
{
  NB_THREADS = easypap_requested_number_of_threads ();

  pthread_barrier_init (&barrier, NULL, NB_THREADS);
}

int get_index (void)
{
  int i;
  pthread_mutex_lock (&mutex);
  i = the_index++;
  pthread_mutex_unlock (&mutex);
  return i;
}

static void *thread_func_thr (void *arg)
{
  int me = (int)(intptr_t)arg;

  for (unsigned it = 1; it <= iterations; it++) {

    for (;;) {
      int y = get_index ();
      if (y >= DIM)
        break;
      do_tile (0, y, DIM, 1, me);
    }

    pthread_barrier_wait (&barrier);
    if (me == 0) {
      the_index = 0;
      rotate ();
    }
    pthread_barrier_wait (&barrier);
  }

  return NULL;
}

unsigned spin_compute_thr (unsigned nb_iter)
{
  iterations = nb_iter;

  pthread_t pid[NB_THREADS];
  for (int i = 1; i < NB_THREADS; i++)
    pthread_create (&pid[i], NULL, thread_func_thr, (void *)(intptr_t)i);

  thread_func_thr ((void *)(intptr_t)0);

  for (int i = 1; i < NB_THREADS; i++)
    pthread_join (pid[i], NULL);

  return 0;
}

void spin_init_thr_tiled (void)
{
  spin_init_thr ();
}

static void *thread_func_thr_tiled (void *arg)
{
  int me = (int)(intptr_t)arg;

  for (unsigned it = 1; it <= iterations; it++) {

    for (;;) {
      int n = get_index ();
      if (n >= NB_TILES_X * NB_TILES_Y)
        break;
      int y = n / NB_TILES_X;
      int x = n % NB_TILES_X;
      do_tile (x * TILE_W, y * TILE_H, TILE_W, TILE_H, me);
    }

    pthread_barrier_wait (&barrier);
    if (me == 0) {
      the_index = 0;
      rotate ();
    }
    pthread_barrier_wait (&barrier);
  }

  return NULL;
}

unsigned spin_compute_thr_tiled (unsigned nb_iter)
{
  iterations = nb_iter;


  pthread_t pid[NB_THREADS];
  for (int i = 1; i < NB_THREADS; i++)
    pthread_create (&pid[i], NULL, thread_func_thr_tiled, (void *)(intptr_t)i);

  thread_func_thr_tiled ((void *)(intptr_t)0);

  for (int i = 1; i < NB_THREADS; i++)
    pthread_join (pid[i], NULL);

  return 0;
}


//////////////////////////////////////////////////////////////////////////

static float base_angle = 0.0;
static int color_a_r = 255, color_a_g = 255, color_a_b = 0, color_a_a = 255;
static int color_b_r = 0, color_b_g = 0, color_b_b = 255, color_b_a = 255;

static float atanf_approx (float x)
{
  float a = fabsf (x);

  return x * M_PI / 4 + 0.273 * x * (1 - a);
}

static float atan2f_approx (float y, float x)
{
  float ay   = fabsf (y);
  float ax   = fabsf (x);
  int invert = ay > ax;
  float z    = invert ? ax / ay : ay / ax; // [0,1]
  float th   = atanf_approx (z);           // [0,π/4]
  if (invert)
    th = M_PI_2 - th; // [0,π/2]
  if (x < 0)
    th = M_PI - th; // [0,π]
  if (y < 0)
    th = -th;

  return th;
}

// Computation of one pixel
static unsigned compute_color (int i, int j)
{
  float angle =
      atan2f_approx ((int)DIM / 2 - i, j - (int)DIM / 2) + M_PI + base_angle;

  float ratio = fabsf ((fmodf (angle, M_PI / 4.0) - (float)(M_PI / 8.0)) /
                       (float)(M_PI / 8.0));

  int r = color_a_r * ratio + color_b_r * (1.0 - ratio);
  int g = color_a_g * ratio + color_b_g * (1.0 - ratio);
  int b = color_a_b * ratio + color_b_b * (1.0 - ratio);
  int a = color_a_a * ratio + color_b_a * (1.0 - ratio);

  return rgba (r, g, b, a);
}

static void rotate (void)
{
  base_angle = fmodf (base_angle + (1.0 / 180.0) * M_PI, M_PI);
}

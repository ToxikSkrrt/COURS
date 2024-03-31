
#include "easypap.h"

#include <omp.h>


static unsigned compute_one_pixel (int i, int j);
static void zoom (void);


int mandel_do_tile_default (int x, int y, int width, int height)
{
  for (int i = y; i < y + height; i++)
    for (int j = x; j < x + width; j++)
      cur_img (i, j) = compute_one_pixel (i, j);

  return 0;
}

///////////////////////////// Simple sequential version (seq)
// Suggested cmdline:
// ./run --kernel mandel
//
unsigned mandel_compute_seq (unsigned nb_iter)
{
  for (unsigned it = 1; it <= nb_iter; it++) {

    do_tile (0, 0, DIM, DIM, 0);

    zoom ();
  }

  return 0;
}


///////////////////////////// Tiled sequential version (tiled)
// Suggested cmdline:
// ./run -k mandel -v tiled -ts 64
//
unsigned mandel_compute_tiled (unsigned nb_iter)
{
  for (unsigned it = 1; it <= nb_iter; it++) {

    for (int y = 0; y < DIM; y += TILE_H)
      for (int x = 0; x < DIM; x += TILE_W)
        do_tile (x, y, TILE_W, TILE_H, 0);

    zoom ();
  }

  return 0;
}

unsigned mandel_compute_omp (unsigned nb_iter)
{
  for (unsigned it = 1; it <= nb_iter; it++) {

#pragma omp parallel for collapse(2) schedule(runtime)
    for (int y = 0; y < DIM; y += TILE_H)
      for (int x = 0; x < DIM; x += TILE_W)
        do_tile (x, y, TILE_W, TILE_H, omp_get_thread_num ());

    zoom ();
  }

  return 0;
}

///////////////////////////// Multithreaded version (tiled)

static unsigned NB_THREADS;
static unsigned iterations = 1;
static pthread_barrier_t barrier;
static pthread_mutex_t mutex = PTHREAD_MUTEX_INITIALIZER;
static unsigned the_index    = 0;

void mandel_init_thr (void)
{
  NB_THREADS = easypap_requested_number_of_threads ();

  pthread_barrier_init (&barrier, NULL, NB_THREADS);
}

static int get_index (void)
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
      zoom ();
    }
    pthread_barrier_wait (&barrier);
  }

  return NULL;
}

unsigned mandel_compute_thr (unsigned nb_iter)
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

void mandel_init_thr_tiled (void)
{
  mandel_init_thr ();
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
      zoom ();
    }
    pthread_barrier_wait (&barrier);
  }

  return NULL;
}

unsigned mandel_compute_thr_tiled (unsigned nb_iter)
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


/////////////// Mandelbrot basic computation

#define MAX_ITERATIONS 4096
#define ZOOM_SPEED -0.01

static float leftX   = -0.2395;
static float rightX  = -0.2275;
static float topY    = .660;
static float bottomY = .648;

static float xstep;
static float ystep;

void mandel_init ()
{
  // check tile size's conformity with respect to CPU vector width
  // easypap_check_vectorization (VEC_TYPE_FLOAT, DIR_HORIZONTAL);

  xstep = (rightX - leftX) / DIM;
  ystep = (topY - bottomY) / DIM;
}

static unsigned iteration_to_color (unsigned iter)
{
  unsigned r = 0, g = 0, b = 0;

  if (iter < MAX_ITERATIONS) {
    if (iter < 64) {
      r = iter * 2; /* 0x0000 to 0x007E */
    } else if (iter < 128) {
      r = (((iter - 64) * 128) / 126) + 128; /* 0x0080 to 0x00C0 */
    } else if (iter < 256) {
      r = (((iter - 128) * 62) / 127) + 193; /* 0x00C1 to 0x00FF */
    } else if (iter < 512) {
      r = 255;
      g = (((iter - 256) * 62) / 255) + 1; /* 0x01FF to 0x3FFF */
    } else if (iter < 1024) {
      r = 255;
      g = (((iter - 512) * 63) / 511) + 64; /* 0x40FF to 0x7FFF */
    } else if (iter < 2048) {
      r = 255;
      g = (((iter - 1024) * 63) / 1023) + 128; /* 0x80FF to 0xBFFF */
    } else {
      r = 255;
      g = (((iter - 2048) * 63) / 2047) + 192; /* 0xC0FF to 0xFFFF */
    }
  }
  return rgba (r, g, b, 255);
}

static void zoom (void)
{
  float xrange = (rightX - leftX);
  float yrange = (topY - bottomY);

  leftX += ZOOM_SPEED * xrange;
  rightX -= ZOOM_SPEED * xrange;
  topY -= ZOOM_SPEED * yrange;
  bottomY += ZOOM_SPEED * yrange;

  xstep = (rightX - leftX) / DIM;
  ystep = (topY - bottomY) / DIM;
}

static unsigned compute_one_pixel (int i, int j)
{
  float cr = leftX + xstep * j;
  float ci = topY - ystep * i;
  float zr = 0.0, zi = 0.0;

  int iter;

  // Pour chaque pixel, on calcule les termes d'une suite, et on
  // s'arrête lorsque |Z| > 2 ou lorsqu'on atteint MAX_ITERATIONS
  for (iter = 0; iter < MAX_ITERATIONS; iter++) {
    float x2 = zr * zr;
    float y2 = zi * zi;

    /* Stop iterations when |Z| > 2 */
    if (x2 + y2 > 4.0)
      break;

    float twoxy = (float)2.0 * zr * zi;
    /* Z = Z^2 + C */
    zr = x2 - y2 + cr;
    zi = twoxy + ci;
  }

  return iteration_to_color (iter);
}


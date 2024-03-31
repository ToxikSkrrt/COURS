
#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

#include "error.h"

#define MAX_POINTS 6

struct figure
{
  unsigned color;
  float coord[MAX_POINTS];
};

struct info
{
  char id;
  char *name;
  int nb_floats;
  char *format;
} infos[] = {{'L', "Ligne", 4, "%s %06x (%g,%g) (%g,%g)\n"},
                    {'T', "Triangle", 6, "%s %06x (%g,%g) (%g,%g) (%g,%g)\n"},
                    {'R', "Rond", 3, "%s %06x (%g,%g) %g\n"},
                    {'C', "Carre", 3, "%s %06x (%g,%g) %g\n"},
                    {'\0', NULL, 0, NULL}};

static int char2fig (char id)
{
  for (int i = 0; infos[i].id != 0; i++)
    if (infos[i].id == id)
      return i;

  exit_with_error ("Character %c is not a valid Figure ID", id);
}

static int footprint (int figtype)
{
  return sizeof (unsigned) + infos[figtype].nb_floats * sizeof (float);
}

static void print_fig (int fig_rank, struct figure *fig)
{
  struct info *p = infos + fig_rank;

  printf (p->format, p->name, fig->color, fig->coord[0], fig->coord[1],
          fig->coord[2], fig->coord[3], fig->coord[4], fig->coord[5]);
}

void display (char *file, char fig_code)
{
  int fd, fdi;
  char name[16] = "Z.idx";
  int fig_rank = char2fig (fig_code);

  name[0] = fig_code;
  fdi = open (name, O_RDONLY);
  check (fdi, "open");

  fd = open (file, O_RDONLY);
  check (fd, "open");

  for (;;) {
    struct figure fig;
    char id;
    int n;
    off_t pos;

    n = read (fdi, &pos, sizeof (off_t));

    if (n == 0)
      break;
    
    lseek (fd, pos, SEEK_SET);
    n = read (fd, &id, 1);

    int fig_size = footprint (fig_rank);
    n = read (fd, &fig, fig_size);
    print_fig (fig_rank, &fig);
  }
  close (fd); close (fdi);
}

int main (int argc, char *argv[])
{
  if (argc < 3)
    exit_with_error ("Usage: %s <file> <type>", argv[0]);

  display (argv[1], argv[2][0]);

  return 0;
}

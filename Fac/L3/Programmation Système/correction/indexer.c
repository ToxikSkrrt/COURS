
#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

#include "error.h"

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

static int footprint (int fig_rank)
{
  return sizeof (unsigned) + infos[fig_rank].nb_floats * sizeof (float);
}

void gen_indexes (char *file)
{
  int fdi[4];
  off_t pos = 0;
  int fd    = open (file, O_RDONLY);
  check (fd, "open");

  for (int i = 0; infos[i].id != 0; i++) {
    char name[16] = "Z.idx";
    name[0]       = infos[i].id;
    fdi[i]        = open (name, O_CREAT | O_TRUNC | O_WRONLY, 0666);
    check (fdi[i], "open");
  }

  for (;;) {
    char id;
    int n;
    
    n = read (fd, &id, 1);
    check (n, "read");
    if (n == 0)
      break;

    int fig_rank = char2fig (id);
    int size     = footprint (fig_rank);

    write (fdi[fig_rank], &pos, sizeof (off_t));
    pos = lseek (fd, size, SEEK_CUR);
  }

  for (int i = 0; infos[i].id != 0; i++) {
    close (fdi[i]);
  }
  close (fd);
}

int main (int argc, char *argv[])
{
  if (argc < 2)
    exit_with_error ("Usage: %s <file>", argv[0]);

  gen_indexes (argv[1]);

  return 0;
}

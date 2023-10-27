#include <errno.h>
#include <fcntl.h>
#include <sys/types.h>
#include <sys/uio.h>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>

#include "error.h"

#define SUFFIXE ".idx"

int main(int argc, char *argv[])
{
  assert(argc == 3);

  // construire le chemin au fichier index
  int l = strlen(argv[1]);
  char idx_filename[l + strlen(SUFFIXE) + 1];

  strncpy(idx_filename, argv[1], l);
  strcpy(idx_filename + l, SUFFIXE);

  off_t pos = atol(argv[2]);
  off_t val1 = 0;
  off_t val2;
  char c;

  int fd1 = open(argv[1], O_RDONLY);
  check(fd1 != -1, "Cannot open file %s", argv[1]);

  int fd2 = open(idx_filename, O_RDONLY);
  check(fd2 != -1, "Cannot open file %s", idx_filename);

  int l2 = lseek(fd2, pos * sizeof(val2), SEEK_SET);
  check(l2 != -1, "lseek error");

  int rcount = read(fd2, &val2, sizeof(val2));
  check(rcount == sizeof(val2), "Reading error");

  if (pos > 0)
  {
    l2 = lseek(fd2, (pos - 1) * sizeof(val1), SEEK_SET);
    check(l2 != -1, "lseek error");

    rcount = read(fd2, &val1, sizeof(val1));
    val1++;
  }

  int l1 = lseek(fd1, val1 * sizeof(c), SEEK_SET);
  check(l1 != -1, "lseek error");

  for (int i = val1; i < val2; i++)
  {
    rcount = read(fd1, &c, sizeof(c));
    int wcount = write(STDOUT_FILENO, &c, sizeof(c));
    check(wcount == sizeof(c), "Writing error");
  }

  close(fd1);
  close(fd2);

  return EXIT_SUCCESS;
}
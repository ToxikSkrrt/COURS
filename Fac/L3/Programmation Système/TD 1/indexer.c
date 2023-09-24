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
#define BUF_SIZE 2048

int main(int argc, char *argv[])
{
  assert(argc == 2);

  char c;

  // construire le chemin au fichier index
  int l = strlen(argv[1]);
  char idx_filename[l + strlen(SUFFIXE) + 1];
  strncpy(idx_filename, argv[1], l);
  strcpy(idx_filename + l, SUFFIXE);

  int fd1 = open(argv[1], O_RDONLY);
  check(fd1 != -1, "Cannot open file %s", argv[1]);

  int fd2 = open(idx_filename, O_CREAT | O_WRONLY | O_TRUNC, 0640);
  check(fd2 != -1, "Cannot open file %s", idx_filename);

  off_t index = 0;
  while (read(fd1, &c, sizeof(c)))
  {
    if (c == '\n')
    {
      int wcount = write(fd2, &index, sizeof(index));
      check(wcount == sizeof(index), "Writing error");
    }
    index++;
  }

  close(fd1);
  close(fd2);

  return EXIT_SUCCESS;
}

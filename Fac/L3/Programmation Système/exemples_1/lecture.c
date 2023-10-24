#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

#include "error.h"

#define BUFSIZE 4

char *filename = "file.txt";

void lire(int fd)
{
  int n;
  char buffer[BUFSIZE + 1];

  n = read(fd, buffer, BUFSIZE);
  check_syscall(n, "Cannot read from file %s", filename);

  // TODO : read BUFSIZE bytes from file
  buffer[n] = 0;

  printf("%d bytes read: <%s>\n", n, buffer);
}

int main(int argc, char *argv[])
{
  if (argc > 1)
    filename = argv[1];

  int fd = open(filename, O_RDONLY);
  check_syscall(fd, "Cannot open %s file", filename);

  lire(fd);

  close(fd);

  return 0;
}

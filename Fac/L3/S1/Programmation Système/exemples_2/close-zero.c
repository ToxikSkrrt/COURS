#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

#include "error.h"

#define BUFSIZE 4

char *filename = "file.txt";

void lire (int fd)
{
  int n  = 0;
  char buffer[BUFSIZE + 1];

  n = read (fd, buffer, BUFSIZE);
  check_syscall (n, "Cannot read");

  buffer[n] = 0;

  printf ("%d octets lus : <%s>\n", n, buffer);
}

int main (int argc, char *argv[])
{
  if (argc > 1)
    filename = argv[1];

  close (STDIN_FILENO);

  int fd = open (filename, O_RDONLY);
  check_syscall (fd, "Cannot open %s file", filename);

  lire (STDIN_FILENO);

  close (fd);

  return 0;
}
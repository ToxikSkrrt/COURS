#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

#include "error.h"

#define BUFSIZE 4

char *filename = "file.txt";

void ecrire (int fd)
{
  // TODO: write a few bytes into file
  int n = write (fd, "Bonjour", 7);
  check_syscall (n, "write");
}

int main (int argc, char *argv[])
{
  if (argc > 1)
    filename = argv[1];

  int fd = open (filename, O_RDWR);
  check_syscall (fd, "Cannot open %s file", filename);

  ecrire (fd);

  close (fd);

  return 0;
}

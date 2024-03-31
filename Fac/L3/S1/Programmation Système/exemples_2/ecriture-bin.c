#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

#include "error.h"

#define BUFSIZE 4

char *filename = "int.bin";

void ecrire (int fd)
{
  // TODO: write binary representation of 'i' into file
  int i = 31;
  write (fd, &i, sizeof(int));
}

int main (int argc, char *argv[])
{
  if (argc > 1)
    filename = argv[1];

  int fd = open (filename, O_WRONLY | O_CREAT, 0666);
  check_syscall (fd, "Cannot open %s file", filename);

  ecrire (fd);

  close (fd);

  return 0;
}
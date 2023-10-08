#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

#include "error.h"

#define BUFSIZE 4

char *filename = "big.bin";

int main (int argc, char *argv[])
{
  unsigned char c = 255;

  if (argc > 1)
    filename = argv[1];

  int fd = open (filename, O_WRONLY | O_CREAT | O_TRUNC, 0666);
  check_syscall (fd, "Cannot open %s file", filename);

  // TODO: Do a "long" seek here
  off_t pos = lseek (fd, 1000, SEEK_SET);
  check_syscall (pos, "lseek");
  
  int n = write (fd, &c, 1);
  check_syscall (n, "write");

  close (fd);

  return 0;
}
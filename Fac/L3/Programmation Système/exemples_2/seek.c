#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

#include "error.h"

#define BUFSIZE 4

char *filename = "file.txt";

void lire (int fd)
{
  char buffer[BUFSIZE + 1];

  int n = read (fd, buffer, BUFSIZE);
  check_syscall (n, "Failed to read %d bytes", BUFSIZE);

  buffer[n] = '\0';
  printf ("string: [%s], %d bytes\n", buffer, n);
}

int main (int argc, char *argv[])
{
  off_t pos = 0;

  if (argc > 1)
    pos = atol(argv[1]);

  int fd = open (filename, O_RDONLY);
  check_syscall (fd, "Cannot open %s file", filename); 

  // TODO: test various seeks
  pos = lseek (fd, pos, SEEK_SET);
  check_syscall (pos, "problème avec lseek");

  printf ("position = %lld\n", pos);

  lire (fd);

  close (fd);

  return 0;
}
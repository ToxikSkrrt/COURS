#include <sys/mman.h>
#include <fcntl.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <ctype.h>

#include "error.h"

char *FILENAME = "file.txt";

int main (int argc, char *argv[])
{
  if (argc > 1)
    FILENAME = argv[1];

  int fd = open (FILENAME, O_RDWR);
  check_syscall (fd, "Cannot open %s file", FILENAME);

  // TODO: replace each caracter by its uppercase image
  off_t len = lseek (fd, 0, SEEK_END);

  // TODO: replace each caracter by its uppercase image
  char *tab = mmap (NULL, len, PROT_READ | PROT_WRITE, MAP_SHARED, fd, 0);
  check (tab != NULL, "problem with mmap");

  for (int i = 0; i < len; i++)
    tab [i] = toupper (tab [i]);

  munmap (tab, len);
  close (fd);

  return 0;
}

#include <sys/types.h>
#include <unistd.h>
#include <stdlib.h>
#include <fcntl.h>
#include <stdio.h>
#include <assert.h>

#include "error.h"

int main(int argc, char **argv)
{
  assert(argc == 4);

  int bufsize = atoi(argv[3]);
  char buf[bufsize];
  int rcount = 0;

  FILE *fd1 = fopen(argv[1], "r");
  check(fd1 != NULL, "Cannot open file %s", argv[1]);

  FILE *fd2 = fopen(argv[2], "w");
  check(fd2 != NULL, "Cannot open file %s", argv[2]);

  while (rcount = fread(buf, sizeof(char), bufsize, fd1))
  {
    int wcount = fwrite(buf, sizeof(char), rcount, fd2);
    fflush(fd2);
  }

  fclose(fd1);
  fclose(fd2);

  return EXIT_SUCCESS;
}

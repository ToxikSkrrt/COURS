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

  int fd1 = open(argv[1], O_RDONLY);
  check(fd1 != -1, "Cannot open file %s", argv[1]);

  int fd2 = open(argv[2], O_CREAT | O_WRONLY | O_TRUNC, 0666);
  check(fd2 != -1, "Cannot open file %s", argv[2]);

  do
  {
    rcount = read(fd1, buf, sizeof(char));
    int wcount = write(fd2, buf, rcount);
  } while (rcount > 0);

  close(fd1);
  close(fd2);

  return EXIT_SUCCESS;
}

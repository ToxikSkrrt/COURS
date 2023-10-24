#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

int main(int argc, char *argv[])
{
  printf("I am about to become \"ls -l\"");

  execlp("ls", "ls", "-l", NULL);
  perror("execlp");

  return EXIT_FAILURE;
}

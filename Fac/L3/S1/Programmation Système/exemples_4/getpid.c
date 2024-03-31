#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

int main (int argc, char *argv[])
{
  printf ("Hello from %d\n", getpid ());

  return 0;
}
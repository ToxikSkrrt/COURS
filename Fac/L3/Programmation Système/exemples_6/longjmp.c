#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <signal.h>
#include <string.h>
#include <setjmp.h>

jmp_buf buf;

void f (int v)
{
}

int main (int argc, char *argv[])
{
  int r = -1;
  printf ("Main start\n");

  // TODO: setjump

  printf ("setjmp returns %d\n", r);
  sleep (1);

  printf ("Main end\n");

  return 0;
}

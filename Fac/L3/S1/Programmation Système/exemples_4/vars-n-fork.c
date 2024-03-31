#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

#define pprintf(format, ...) printf ("[PID %d] " format, getpid(), ##__VA_ARGS__)

int i = 0;

int main (int argc, char *argv[])
{
  pid_t pid;

  i = 5;
  pid = fork ();
  if (pid) { // father
    i = 6;
    pprintf ("Parent: i = %d\n", i);
    sleep (2);
    pprintf ("Parent: i = %d\n", i);
  } else { // Child
    i = 7;
    pprintf ("Child: i = %d\n", i);
    sleep (2);
    pprintf ("Child: i = %d\n", i);
  }

  return 0;
}

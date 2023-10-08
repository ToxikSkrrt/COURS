#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

#define pprintf(format, ...)                                                   \
  printf ("[PID %d] " format, getpid (), ##__VA_ARGS__)

int main (int argc, char *argv[])
{
  pid_t pid[2];

  pid[0] = fork ();
  if (pid[0]) { // father
    pprintf ("Parent's fork return value: %d\n", pid[0]);
    pid[1] = fork ();
    if (pid[1]) // father
      pprintf ("Parent's fork return value: %d\n", pid[1]);
    else // Child
      pprintf ("Child's fork return value: %d\n", pid[1]);
  } else { // Child
    pprintf ("Child's fork return value: %d\n", pid[0]);
  }

  return 0;
}

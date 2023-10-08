#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

#define pprintf(format, ...) printf ("[PID %d] " format, getpid(), ##__VA_ARGS__)

int main (int argc, char *argv[])
{
  pid_t pid;

  pid = fork ();
  if (pid) { // father
    pprintf ("Parent's fork return value: %d\n", pid);
    int status;
    wait (&status);
    pprintf ("Fils terminé. Code de retour = %d\n", WEXITSTATUS(status));
  } else { // Child
    pprintf ("Child's fork return value: %d\n", pid);
    sleep (2);
    pprintf ("Child is terminating\n");
    return 31;
  }

  return 0;
}

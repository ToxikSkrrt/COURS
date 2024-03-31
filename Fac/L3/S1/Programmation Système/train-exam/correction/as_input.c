#include <ctype.h>
#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

#include "error.h"

#define pprintf(format, ...)                                                   \
  printf ("[PID %d] " format, getpid (), ##__VA_ARGS__)

int tube[2];

enum { R, W };

void left (int argc, char *argv[])
{
  close (tube[R]);
  dup2 (tube[W], STDOUT_FILENO); close (tube[W]);

  argv[1] = "cat";
  execvp ("cat", argv + 1);
  perror ("execlp");
  exit (EXIT_FAILURE);
}

void right (int argc, char *argv[])
{
  close (tube[W]);
  dup2 (tube[R], STDIN_FILENO); close (tube[R]);

  execlp (argv[1], argv[1], NULL);
  perror (argv[1]);
  exit (EXIT_FAILURE);
}

int main (int argc, char *argv[])
{
  pipe (tube);

  if (fork () == 0) // process which will write into pipe
    left (argc, argv);
  
  if (fork() == 0) // process which will read from pipe
    right (argc, argv);

  close (tube[R]); close (tube[W]);
  
  wait (NULL); wait (NULL);

  return 0;
}

#include <ctype.h>
#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

#include "error.h"

enum { R, W };

int pipe3 (char *cmd1, char *arg1, char *cmd2, char *arg2, char *cmd3, char *arg3)
{
  int tube[2][2];
  pid_t child[3];

  for (int t = 0; t < 2; t++)
    pipe (tube[t]);

  child[0] = fork ();
  if (!child[0]) {
    close (tube[0][R]);
    close (tube[1][R]); close (tube[1][W]);

    dup2 (tube[0][W], STDOUT_FILENO); close (tube[0][W]);

    execlp (cmd1, cmd1, arg1, NULL);
    perror (cmd1);
  }

  child[1] = fork ();
  if (!child[1]) {
    close (tube[0][W]);
    close (tube[1][R]);

    dup2 (tube[0][R], STDIN_FILENO); close (tube[0][R]);
    dup2 (tube[1][W], STDOUT_FILENO); close (tube[1][W]);

    execlp (cmd2, cmd2, arg2, NULL);
    perror (cmd2);
  }

  child[2] = fork ();
  if (!child[2]) {
    close (tube[0][R]); close (tube[0][W]);
    close (tube[1][W]);

    dup2 (tube[1][R], STDIN_FILENO); close (tube[1][R]);

    execlp (cmd3, cmd3, arg3, NULL);
    perror (cmd3);
  }

  for (int t = 0; t < 2; t++) {
    close (tube[t][R]);  close (tube[t][W]);
  }

  for (int f = 0; f < 3; f++) {
    int status;
    pid_t p;
    p = wait (&status);
    if (!WIFEXITED(status) || WEXITSTATUS(status) != 0) {
      fprintf (stderr, "Process %d terminated anormaly", p);
    }
  }

  return 0;
}

int main (int argc, char *argv[])
{
  pipe3 ("ls", "-l", "grep", "e", "cat", "-n");
  
  return 0;
}

#include <ctype.h>
#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

#include "error.h"

char *FILENAME = "file.txt";

#define pprintf(format, ...) \
  printf("[PID %d] " format, getpid(), ##__VA_ARGS__)

int tube[2];

enum
{
  R,
  W
};

void child(void)
{
  close(tube[W]);
  dup2(tube[R], STDIN_FILENO);
  close(tube[R]);

  // tr a-z A-Z
  // TODO : exec "tr a-z A-Z"
  execlp("tr", "tr", "a-z", "A-Z", NULL);
  perror("execlp");
  exit(EXIT_FAILURE);
}

void father(void)
{
  close(tube[R]);
  dup2(tube[W], STDOUT_FILENO);
  close(tube[W]);

  // cat -n FILENAME
  // TODO : exec "cat -n FILENAME"
  execlp("cat", "cat", "-n", FILENAME, NULL);
  perror("execlp");
  exit(EXIT_FAILURE);
}

int main(int argc, char *argv[])
{
  if (argc > 1)
    FILENAME = argv[1];

  pipe(tube);

  if (fork() != 0)
  { // father
    father();
  }
  else
  { //child
    child();
  }

  return 0;
}

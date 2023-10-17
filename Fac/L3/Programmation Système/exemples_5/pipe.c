#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

#include "error.h"

char *message = "Ceci est un message qui ne paie pas de mine, mais qui se "
                "révèle redoutablement long en pratique, sans toutefois "
                "atteindre non plus des proportions gigantesques...\n";

enum { R, W };

int main (int argc, char *argv[])
{
  int tube [2];

  pipe (tube);

  printf ("pipe -> %d %d \n", tube[0], tube[1]);

  // TODO: write something into the pipe
  int n = write (tube[W], message, strlen(message));
  check_syscall (n, "write");

  close (tube[W]);

  char buffer;

  for(;;) {
    int n = read (tube[R], &buffer, 1);
    check_syscall (n, "read");

    if (n < 1)
      break;

    write (STDOUT_FILENO, &buffer, 1);
  }


  // TODO: read from pipe

  close (tube[R]);
  
  return 0;
}

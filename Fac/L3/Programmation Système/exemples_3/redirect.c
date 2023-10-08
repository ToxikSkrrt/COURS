#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

#include "error.h"

char *filename = "log.txt";

void afficher (char *msg)
{
  printf ("Hello World! (%s)\n", msg);
}

int main (int argc, char *argv[])
{
  if (argc > 1)
    filename = argv[1];

  afficher ("Avant");
  
  int fd = open (filename, O_WRONLY | O_CREAT | O_TRUNC, 0666);
  check_syscall (fd, "Cannot open file %s", filename);

  int fd_backup = dup(STDOUT_FILENO);

  dup2 (fd, STDOUT_FILENO);
  close (fd);

  // TODO Redirect STDOUT to file

  afficher ("Après");

  // TODO: try to restore "default STDOUT"
  dup2 (fd_backup, STDOUT_FILENO);
  close (fd_backup);

  afficher ("Enfin");

  return 0;
}

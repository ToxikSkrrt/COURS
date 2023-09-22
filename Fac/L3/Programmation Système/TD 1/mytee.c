#include <sys/types.h>
#include <unistd.h>
#include <stdlib.h>
#include <fcntl.h>
#include <stdio.h>
#include <assert.h>

#include "error.h"

int main(int argc, char **argv)
{
  assert(argc == 2); // Nom du fichier de sortie attendu en ligne de commande

  char c;

  int fd = open(argv[1], O_CREAT | O_WRONLY, 0666);
  check(fd != -1, "Cannot open file %s", argv[1]);

  while (1)
  {

    int rcount = read(STDIN_FILENO, &c, sizeof(c)); // STDIN_FILENO -> == 0 -> entrée standard
    printf("%c UwU", c);
    int wcount = write(fd, &c, sizeof(c));
  }

  return EXIT_SUCCESS;
}

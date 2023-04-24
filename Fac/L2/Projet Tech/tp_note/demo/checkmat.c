#include <stdio.h>
#include <stdlib.h>
#include "tsp.h"

int main(int argc, char **argv) {
  if (argc != 2) EXIT_FAILURE;
  FILE *file = fopen(argv[1], "r");
  char c = fgetc(file);
  fclose(file);
  uint size = c;
  uint *dist = distmat_load(argv[1], &size);
  if (distmat_check(size, dist)) {
    printf("SUCCESS\n");
    free(dist);
    return EXIT_SUCCESS;
  } else {
    printf("FAILURE\n");
    free(dist);
    return EXIT_FAILURE;
  }
}
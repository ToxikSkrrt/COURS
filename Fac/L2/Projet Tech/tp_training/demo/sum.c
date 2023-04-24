#include <stdio.h>
#include <stdlib.h>
#include "tree.h"
#include "tree_aux.h"

int main(int argc, char *argv[]) {
  tree *t1 = tree_load_int(argv[1]);
  int result = tree_sum_int(t1);
  printf("tree sum: %d\n", result);

  tree_free_full(t1, free);

  return EXIT_SUCCESS;
}
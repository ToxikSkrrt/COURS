#include <stdlib.h>
#include <stdio.h>
#include <omp.h>

int main()
{
#pragma omp parallel
  printf("Hello world!\n");
  printf("Bye!\n");

  return EXIT_SUCCESS;
}

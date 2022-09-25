#include <stdio.h>
#include <stdlib.h>

int main (int argc, char *argv[])
{
    for (int i = 1; i < argc ; i++)
    {
        int n = atoi(argv[i]);
        printf("%d ", n*n);
    }
    printf("\n");
    return EXIT_SUCCESS;
}
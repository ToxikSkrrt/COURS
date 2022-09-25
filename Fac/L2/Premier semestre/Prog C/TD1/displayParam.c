#include <stdio.h>
#include <stdlib.h>

int main (int argc, char *argv[])
{
    printf("we run %s \n", argv[0]);
    printf("with %d parameters : ", argc -1);
    for (int i = 1; i < argc ; i++)
    {
        printf("%s ", argv[i]);
    }
    printf("\n");
    return EXIT_SUCCESS;
}
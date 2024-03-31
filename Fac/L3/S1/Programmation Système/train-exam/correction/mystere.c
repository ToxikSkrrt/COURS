#include <stdio.h>
#include <unistd.h>

int main(int argc, char *argv[])
{
    printf("Avant\n");
    execl("/bin/echo", "echo", "Milieu", NULL);
    printf("Après\n");
    return 0;
}
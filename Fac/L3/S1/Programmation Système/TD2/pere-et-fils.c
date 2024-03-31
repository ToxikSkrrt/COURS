#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

int main(int argc, char **argv)
{
    pid_t pid;
    pid = fork();
    if (pid)
    { // pere
        sleep(1);
        printf("Je m'appelle %d et je suis le pere de %d\n", getpid(), pid);
    }
    else
    { // fils
        printf("Je m'appelle %d et je suis le fils de %d\n", getpid(), getppid());
    }

    return EXIT_SUCCESS;
}
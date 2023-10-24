#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <signal.h>
#include <string.h>

enum
{
    R,
    W
};

void test_fork()
{
    int pid = fork();

    if (pid)
    {
        printf("I'm the father -> %d\n", getpid());
    }
    else
    {
        printf("I'm the child -> %d\n", getpid());
    }
}

void test_pipe()
{
    int tube[2];
    pipe(tube);

    int pid = fork();

    if (pid)
    {
        close(tube[R]);
        dup2(tube[W], STDOUT_FILENO);
        close(tube[W]);

        execlp("ls", "ls", "-al", NULL);
        perror("execlp");
        exit(EXIT_FAILURE);
    }
    else
    {
        close(tube[W]);
        dup2(tube[R], STDIN_FILENO);
        close(tube[R]);

        execlp("cat", "cat", "-n", NULL);
        perror("execlp");
        exit(EXIT_FAILURE);
    }
}

int main(int argc, char **argv)
{
    if (argc != 2)
    {
        exit(EXIT_FAILURE);
    }

    if (strcmp(argv[1], "fork") == 0)
    {
        test_fork();
    }
    else if (strcmp(argv[1], "pipe") == 0)
    {
        test_pipe();
    }
    else
    {
        fprintf(stderr, "Ton grand-père le processus\n");
    }

    return 0;
}
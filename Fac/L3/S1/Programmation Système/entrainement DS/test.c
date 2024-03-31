#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <signal.h>
#include <string.h>
#include <fcntl.h>

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

void test_wfile()
{
    char c;
    int fdW = open("file", O_WRONLY | O_CREAT | O_TRUNC, 0666);
    while (read(STDIN_FILENO, &c, sizeof(c)) <= 50)
    {
        write(fdW, &c, sizeof(c));
    }
    close(fdW);
}

void test_rfile()
{
    char c;
    int fdR = open("file", O_RDONLY);
    int l = lseek(fdR, -1, SEEK_END);
    while (l != -1)
    {
        read(fdR, &c, sizeof(c));
        write(STDOUT_FILENO, &c, sizeof(c));
        l = lseek(fdR, -2, SEEK_CUR);
    }
    close(fdR);
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
    else if (strcmp(argv[1], "rfile") == 0)
    {
        test_rfile();
    }
    else if (strcmp(argv[1], "wfile") == 0)
    {
        test_wfile();
    }
    else
    {
        fprintf(stderr, "Ton grand-père le processus\n");
    }

    return 0;
}
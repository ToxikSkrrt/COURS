#include <ctype.h>
#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>
#include <signal.h>
#include <sys/wait.h>
#include <unistd.h>

#include "error.h"

int tube[2];

enum
{
    R,
    W
};

void child1(char **argv2)
{
    close(tube[W]);
    dup2(tube[R], STDIN_FILENO);
    close(tube[R]);

    execvp(argv2[0], argv2);
    perror("execlp");
    exit(EXIT_FAILURE);
}

void child2(char *argv1)
{
    close(tube[R]);
    dup2(tube[W], STDOUT_FILENO);
    close(tube[W]);

    execlp(argv1, argv1, NULL);
    perror("execvp");
    exit(EXIT_FAILURE);
}

int main(int argc, char **argv)
{
    pipe(tube);
    int status1, status2;
    int pid = fork();

    if (!pid)
    {
        int pid2 = fork();
        if (!pid2)
        {
            close(tube[R]);
            close(tube[W]);
            waitpid(pid, &status1, 0);
            waitpid(pid2, &status2, 0);
            if (!WIFEXITED(status1))
            {
                return WTERMSIG(status1);
            }
            else
            {
                if (!WIFEXITED(status2))
                {
                    return WTERMSIG(status2);
                }
                else
                {
                    return WEXITSTATUS(status2);
                }
            }
        }
        else
        {
            child2(argv[1]);
        }
    }
    else
    {
        child1(argv + 2);
    }
    return EXIT_FAILURE;
}
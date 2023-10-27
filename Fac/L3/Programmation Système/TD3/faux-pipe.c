#include <stdlib.h>
#include <stdio.h>
#include <assert.h>
#include <unistd.h>
#include <fcntl.h>
#include <string.h>

int main(int argc, char **argv)
{
    assert(argc > 2);
    int pid = fork();

    if (pid)
    {
        int fd = open("temp", O_WRONLY | O_CREAT, 0666);
        assert(fd != -1);

        int backup = dup(STDOUT_FILENO);
        dup2(fd, STDOUT_FILENO);
        close(fd);

        execlp(argv[1], argv[1], NULL);
        perror("execlp");

        dup2(backup, STDOUT_FILENO);
        close(backup);
    }
    else
    {
        int fd = open("temp", O_RDONLY);
        assert(fd != -1);

        int backup = dup(STDIN_FILENO);
        dup2(fd, STDIN_FILENO);
        close(fd);

        execvp(argv[2], argv + 2);
        perror("execvp");

        dup2(backup, STDIN_FILENO);
        close(backup);
    }

    return EXIT_SUCCESS;
}
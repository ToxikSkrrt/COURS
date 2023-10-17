#include <stdlib.h>
#include <stdio.h>
#include <assert.h>
#include <unistd.h>
#include <fcntl.h>
#include <string.h>

int main(int argc, char **argv)
{
    assert(argc > 2);

    if (fork() != 0)
    {
        int fd = open("temp", O_CREAT, 0640);
        assert(fd != -1);

        dup2(fd, STDOUT_FILENO);
        close(fd);

        execvp(argv[1], argv + 1);
    }
    else
    {
        dup2(STDOUT_FILENO, STDIN_FILENO);
        execvp(argv[2], argv + 1);
    }

    return EXIT_SUCCESS;
}
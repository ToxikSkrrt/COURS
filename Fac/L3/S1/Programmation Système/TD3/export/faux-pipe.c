#include <fcntl.h>
#include <signal.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/wait.h>
#include <unistd.h>

int main(int argc, char **argv) {
    pid_t child = fork();
    if (!child)
    {
        int fd1 = open("tmp", O_WRONLY | O_CREAT | O_TRUNC, 0666);
        int backupout = dup(STDOUT_FILENO);
        dup2(fd1, STDOUT_FILENO);
        close(fd1);
        execlp(argv[1], argv[1], NULL);
        dup2(backupout, STDOUT_FILENO);
        close(backupout);
        int fd2 = open("tmp", O_RDONLY);
        int backupin = dup(STDIN_FILENO);
        dup2(fd2, STDIN_FILENO);
        close(fd2);
        execvp(argv[2], argv+3);
        dup2(backupin, STDIN_FILENO);
        close(backupin);
    }
    else
    {
      wait(&child);
    }

    return EXIT_SUCCESS;
}
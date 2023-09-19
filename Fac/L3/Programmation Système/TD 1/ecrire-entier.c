#include <sys/types.h>
#include <unistd.h>
#include <stdlib.h>
#include <fcntl.h>
#include <stdio.h>
#include <assert.h>

#include "error.h"

int main(int argc, char **argv)
{
    assert(argc == 4);

    off_t pos = atol(argv[2]);
    off_t val = atol(argv[3]);

    int fd = open(argv[1], O_CREAT | O_WRONLY, 0640);
    check(fd != -1, "Cannot open file %s", argv[1]);

    int l = lseek(fd, pos * sizeof(val), SEEK_SET);
    check(l != -1, "lseek error");

    int wcount = write(fd, &val, sizeof(val));
    check(wcount == sizeof(val), "Writing error");

    close(fd);

    return EXIT_SUCCESS;
}
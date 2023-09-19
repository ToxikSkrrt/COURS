#include <sys/types.h>
#include <unistd.h>
#include <stdlib.h>
#include <fcntl.h>
#include <stdio.h>
#include <assert.h>

#include "error.h"

int main(int argc, char **argv)
{
    assert(argc == 3);

    off_t pos = atol(argv[2]);
    off_t val;

    int fd = open(argv[1], O_RDONLY);
    check(fd != -1, "Cannot open file %s", argv[1]);

    int l = lseek(fd, pos * sizeof(val), SEEK_SET);
    check(l != -1, "lseek error");

    int rcount = read(fd, &val, sizeof(val));
    check(rcount == sizeof(val), "Reading error");

    printf("%ld\n", val);

    close(fd);

    return EXIT_SUCCESS;
}
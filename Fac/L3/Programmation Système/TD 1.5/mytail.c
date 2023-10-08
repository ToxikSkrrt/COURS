#include <sys/types.h>
#include <unistd.h>
#include <stdlib.h>
#include <fcntl.h>
#include <stdio.h>
#include <sys/mman.h>

#include <assert.h>

int main(int argc, char **argv)
{
    assert(argc == 2 || argc == 3);

    int n = 10;
    int fd;

    if (argc == 3)
    {
        n = atoi(argv[1]);
        fd = open(argv[2], O_RDONLY);
    }
    else
    {
        fd = open(argv[1], O_RDONLY);
    }

    assert(fd != -1);

    off_t filesize = lseek(fd, 0, SEEK_END);
    assert(filesize != -1);

    char *tab = mmap(NULL, filesize, PROT_READ, MAP_SHARED, fd, 0);
    assert(tab != NULL);

    int linecount = 0;
    off_t filesizecpy = filesize;

    for (int i = 0; i < filesize; i++)
    {
        if (tab[filesize - i - 1] == '\n')
        {
            linecount++;
            if (linecount == n)
                break;
        }
        filesizecpy--;
    }
    for (int i = filesizecpy; i < filesize; i++)
    {
        printf("%c", tab[i]);
    }

    munmap(tab, filesize);

    close(fd);

    return EXIT_SUCCESS;
}
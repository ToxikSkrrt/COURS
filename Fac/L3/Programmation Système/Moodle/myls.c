#include <sys/types.h>
#include <unistd.h>
#include <stdlib.h>
#include <fcntl.h>
#include <stdio.h>
#include <assert.h>
#include <dirent.h>
#include <string.h>

int pstrcmp(const void *a, const void *b)
{
    return strcmp(*(const char **)a, *(const char **)b);
}

int main(int argc, char **argv)
{
    assert(argc == 2 || argc == 3);

    struct dirent *entry;
    char *tab[1024];

    if (argv[1] == "-R")
    {
        fprintf(stderr, "A FAIRE");
    }
    else
    {
        DIR *dirpath = opendir(argv[1]);
        assert(dirpath != NULL);

        int count = 0;

        while (entry = readdir(dirpath))
        {
            if (strcmp(entry->d_name, ".") != 0 && strcmp(entry->d_name, "..") != 0)
            {
                // printf("%s\n", entry->d_name);
                tab[count] = entry->d_name;
                count++;
            }
        }

        qsort(tab, count, sizeof(tab[0]), pstrcmp);

        for (int i = 0; i < count; i++)
        {
            printf("%s\n", tab[i]);
        }

        closedir(dirpath);
    }

    return EXIT_SUCCESS;
}
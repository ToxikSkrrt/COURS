#include <sys/types.h>
#include <unistd.h>
#include <stdlib.h>
#include <fcntl.h>
#include <stdio.h>
#include <assert.h>
#include <dirent.h>
#include <string.h>
#include <sys/stat.h>

int str_sort(const void *a, const void *b)
{
    return strcmp(*(const char **)a, *(const char **)b);
}

int main(int argc, char **argv)
{
    assert(argc >= 1);

    struct dirent *entry;
    int status;
    struct stat st_buf;
    char *tab[1024];

    DIR *dirpath;
    if (argc == 1 || argc == 2)
    {
        if (argc == 1)
        {
            dirpath = opendir(".");
        }
        else
        {
            status = stat(argv[1], &st_buf);
            if (status)
            {
                fprintf(stderr, "cannot access '%s' : No such file or directory\n", argv[1]);
                exit(EXIT_FAILURE);
            }
            //assert(!status);

            if (S_ISREG(st_buf.st_mode))
            {
                printf("%s\n", argv[1]);
                return EXIT_SUCCESS;
            }
            else
            {
                dirpath = opendir(argv[1]);
            }
        }

        int count = 0;

        while ((entry = readdir(dirpath)))
        {
            if (strcmp(entry->d_name, ".") != 0 && strcmp(entry->d_name, "..") != 0)
            {
                tab[count] = entry->d_name;
                count++;
            }
        }

        qsort(tab, count, sizeof(tab[0]), str_sort);

        for (int i = 0; i < count; i++)
        {
            printf("%s\n", tab[i]);
        }

        closedir(dirpath);
    }
    else
    {
        int pathcount = argc - 1;
        int fileNumber = 0;
        for (int i = 1; i <= pathcount; i++)
        {
            status = stat(argv[i], &st_buf);
            if (status)
            {
                fprintf(stderr, "cannot access '%s' : No such file or directory, \n", argv[1]);
                exit(EXIT_FAILURE);
            }
            //assert(!status);
            if (S_ISREG(st_buf.st_mode))
            {
                fileNumber++;
                printf("%s\n", argv[i]);
            }
        }

        if (fileNumber >= 1 && fileNumber != pathcount)
        {
            printf("\n");
        }

        for (int i = 1; i <= pathcount; i++)
        {
            status = stat(argv[i], &st_buf);
            assert(!status);
            if (S_ISDIR(st_buf.st_mode))
            {
                dirpath = opendir(argv[i]);
                assert(dirpath != NULL);

                int count = 0;

                while ((entry = readdir(dirpath)) || entry)
                {
                    if (strcmp(entry->d_name, ".") != 0 && strcmp(entry->d_name, "..") != 0)
                    {
                        tab[count] = entry->d_name;
                        count++;
                    }
                }

                qsort(tab, count, sizeof(tab[0]), str_sort);

                printf("%s:\n", argv[i]);

                for (int j = 0; j < count; j++)
                {
                    printf("%s\n", tab[j]);
                }
                if (i < pathcount)
                {

                    printf("\n");
                }
            }
        }

        closedir(dirpath);
    }

    return EXIT_SUCCESS;
}
#include <stdio.h>
#include <stdlib.h>

int *minMax1(int *t, unsigned int n)
{
    int *tab;
    tab = (int*) malloc(sizeof(int));
    if (tab == NULL)
    {
        fprintf(stderr, "not enough memory!\n");
        exit(EXIT_FAILURE);
    }

    int min = t[0];
    int max = t[0];
    for (int i = 1; i < n; i++)
    {
        if (t[i] < min)
        {
            min = t[i];
        }
        if (t[i] > max)
        {
            max = t[i];
        }
    }

    tab[0] = min;
    tab[1] = max;
    
    return tab;
}

typedef struct
{
    int min;
    int max;
}resMinMax;


resMinMax *minMax2(int *t, unsigned int n)
{
    resMinMax *minMax;
    minMax = (resMinMax*) malloc(sizeof(resMinMax));
    if (minMax == NULL)
    {
        fprintf(stderr, "not enough memory!\n");
        exit(EXIT_FAILURE);
    }

    int min = t[0];
    int max = t[0];
    for (int i = 1; i < n; i++)
    {
        if (t[i] < min)
        {
            min = t[i];
        }
        if (t[i] > max)
        {
            max = t[i];
        }
    }

    minMax->min = min;
    minMax->max = max;

    return minMax;
}


int main(void)
{
    int tabTest[5] = {2, 3, 8, 4, 6};
    
    int *tab;
    tab = minMax1(tabTest, 5);

    resMinMax *minMax;
    minMax = minMax2(tabTest, 5);

    printf("tabTest = {2, 3, 8, 4, 6}\nminMax1 -> min : %d / max : %d\nminMax2 -> min : %d / max : %d\n", tab[0], tab[1], minMax->min, minMax->max);
    
    free(tab);
    free(minMax);

    return EXIT_SUCCESS;
}
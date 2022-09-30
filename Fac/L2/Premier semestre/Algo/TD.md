# TD 2

```c
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

typedef struct
{
    int data;
    SCell *next;
} *SCell;

SCell creer_liste(void)
{

}

bool est_dernier(SCell P)
{

}

int valeur(SCell P)
{

}

SCell suivant(SCell P)
{

}


int main(void)
{
    return EXIT_SUCCESS;
}
```

## Exercice 2

1.
```c
bool appartient(Slist L, int x)
{
    Slist Aux = L;
    while (!estVide(Aux))
    {
        if (valeur(Aux) == x)
        {
            return true;
        }
        Aux = suivant(Aux);
    }
    return false;
}
```

2.
```c
int rang(Slist L, int x)
{
    Slist Aux = L;
    rg = 0;
    while (!estVide(Aux))
    {
        if (valeur(Aux) == x)
        {
            return rg;
        }
        Aux = suivant(Aux);
        rg++;
    }
    return -1;
}
```

3.
```c
int element_n(Slist L, int n)
{
    Slist Aux = L;
    count = 1;
    while (!estVide(Aux))
    {
        if (count == n)
        {
            return valeur(Aux);
        }
        Aux = suivant(Aux);
        count++;
    }
    return "ERREUR";
}
```

4.
```c
int dernier(Slist L)
{
    Slist Aux = L;
    while (!estVide(Aux))
    {
        if (estVide(suivant(Aux)))
        {
            return valeur(Aux);
        }
        Aux = suivant(Aux);
    }
    return "ERREUR";
}
```

5.
```c
Slist ajouter_en_queue(Slist L, int x)
{
    Slist Aux = L;
    while (!estVide(Aux))
    {
        if (estVide(suivant(Aux)))
        {
            return insererApres(L, Aux, x);
        }
        Aux = suivant(Aux);
    }
    return insererEnTete(L, x);
}
```

6.
```c
Slist supprimer_dernier(Slist L)
{
    Slist Aux = L;
    PAux = creer_liste();
    while (!estVide(Aux))
    {
        if (estVide(suivant(Aux)))
        {
            if (estVide(PAux))
            {
                return supprimerEnTete(L);
            }
            return supprimerApres(L, PAux);
        }
        PAux = Aux;
        Aux = suivant(Aux);
    }
    return L;
}
```
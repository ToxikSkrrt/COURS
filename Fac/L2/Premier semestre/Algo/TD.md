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

7.
```c
Slist supprimer_occurences(Slist L, int x)
{
    
}
```

8.
```c
void afficher_liste(Slist L)
{
    
}
```

9.
```c
Slist inverser_liste(Slist L)
{
    
}
```

10.
```c
Slist concatener_listes(Slist L1, Slist L2)
{
    
}
```

11.
```c
Slist fusionner_listes(Slist L1, Slist L2)
{
    if (estVide(L2))
    {
        return L1;
    }
    if (estVide(L1))
    {
        return L2;
    }
    Slist Aux2 = L2;
    if (valeur(L2) < valeur(L1))
    {
        L1 = insererEnTete(L1, valeur(L2));
        Aux2 = suivant(Aux2);
    }
    
    // le premier de L1 le plus petit (pitié j'en peux plus)

    Slist Aux1 = L1;

    while (!estVide(Aux2))
    {
        if (estVide(Aux1) || valeur(Aux2) < valeur(suivant(Aux1)))
        {
            L1 = insererApres(L1, Aux1, valeur(Aux2));
            Aux2 = suivant(Aux2);
        }
        Aux1 = suivant(Aux1);
    }
    return L1;
}
```

## Primitive Mystère

C'est la fonction insererApres().

# TD 3

## Exercice 1

```c
int pgcd(int a, int b)
{
    if (a == 1 || b == 1)
    {
        return 1;
    }
    if (a == b)
    {
        return a;
    }
    if (a > b)
    {
        return pgcd(a - b, b);
    }
    if (b > a)
    {
        return pgcd(a, b - a);
    }
}
```

ptet faux en fait

## Exercice 2

Oui.

## Exercice 3

PTDR.

## Activités du TD

1.
```c
bool appartientR(Slist L, int x)
{
    if (estVide(L))
    {
        return false;
    }
    if (valeur(L) == x)
    {
        return true;
    }
    return appartientR(suivant(L), x);
}
```

2.

En recursif terminal
```c
int rangR(Slist L, int x, int rg)
{
    if (estVide(L))
    {
        return -1;
    }
    if (valeur(L) == x)
    {
        return rg;
    }
    return rangR(suivant(L), x, rg + 1)
}

int rang(Slist L, int x)
{
    return rangR(L, x, 0);
}
```

5.
```c
Slist ajouter_en_queueR(Slist L, int x)
{
    if (estVide(L))
    {
        return insererEnTete(L, x):
    }
    if (estVide(suivant(L)))
    {
        return insererApres(L, L, x);
    }
    return ajouter_en_queueR(suivant(L), x);
}
```

6.
```c
Slist supprimer_dernier(Slist L)
{
    if (estVide(L))
    [
        return L;
    ]
    if (estVide(suivant(L)))
    {
        return supprimerEnTete(L, L, x);
    }
    return supprimer_dernierR(suivant(L));
}
```

# TD 4

## Activités du TD

### Exercice 1

Oui

### Exercice 2

1.
```c
void print_reverse(DList L);
```

2.
```c
DList copy_reverse_list(DList L);
```

3.
```c
DList copy_list(DList L);
```

4.
```c
DList swap(DList L, DList p1, DList p2)
{
    if (!estVide(L) && !estVide(p1) && !estVide(p2))
    {
        insererApres(L, p1, valeur(p2));
        insererApres(L, p2, valeur(p1));
        supprimerAvant(L, suivant(p1));
        supprimerAvant(L, suivant(p2));
        
        return L
    }
    fprintf(stderr, "ERROR\n");
    exit(EXIT_FAILURE);
}
```

Version primitive :
```c
DList p_p1 = precedent(p1);
DList n_p1 = suivant(p1);
DList p_p2 = precedent(p2);
DList n_p2 = suivant(p2);

p1->previous = p_p2;
n_p1->previous = p2;
p2->previous = p_p1;
n_p2->previous = p1;

p_p1->next = p2;
p1->next = n_p2;
p_p2->next = p1;
p2->next = n_p1;
```

Alternative :
```c
aux = p1->data;
p1->data = p2->data;
p2->data = aux;
```

5.
```c
DList bubble_sort(DList L);
```

# TD 5

(Pile = LIFO ; File = FIFO)

## Exercice 1

Renvoie "BaB".

## Exercice 2

1.
```c
pile_int P2 = creerPile();
pile_int Aux = creerPile();

while (!pileVide(P1))
{
    if (valeurPile(P1) % 2 == 0)
        P2 = empiler(P2, valeur(P1));
    else
        Aux = empiler(Aux, valeur(P1));
    P1 = depiler(P1);
}
while (!pileVide(Aux))
    P2 = empiler(P2, valeur(Aux))
    Aux = depiler(Aux);

detruirePile(Aux);
return P2;
```

2.
```c
pile_int P2 = creerPile();
pile_int Aux = creerPile();

while(!pileVide(P1))
{
    Aux = empiler(Aux, valeur(P1));
    P1 = depiler(P1);
}
while(!pileVide(Aux))
{
    P1 = empiler(P1, valeur(Aux));
    if (valeur(Aux) % 2 == 0)
        P2 = empiler(P2, valeur(Aux));
    Aux = depiler(Aux;)
}

detruirePile(Aux);
return P2;
```

## Exerice 3

Renvoie "CabB"

## Exercice 4

F -> 123
P -> 
FS -> 321
v -> 1

La fonction renvoie l'inverse de la file en paramètre.
La file n'est pas modifiée à la fin.
Sa complexité est linéaire.
On ne peut pas l'améliorer.

## Exercice 5

Il faut utiliser une pile.

## Exercice 6


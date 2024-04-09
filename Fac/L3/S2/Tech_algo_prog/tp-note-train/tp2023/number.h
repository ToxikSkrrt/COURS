#ifndef TPTOOLS_H_
#define TPTOOLS_H_

#include <assert.h>
#include <ctype.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
// Après stdio.h.
#include <gmp.h>

#include "alloc.h"

//----------------------------//
// NE PAS MODIFIER CE FICHIER //
//----------------------------//

// La base utilisée pour les nombres.
extern short BASE;

// Structure représentant un nombre.
typedef struct {
  int n;        // Taille du tableau digit[].
  short* digit; // Tableau de chiffres. Chaque chiffre est entre 0 et BASE-1.
  // Le chiffre des unités est digit[0].
} number;

// Retourne un pointeur vers une structure de type number allouée dynamiquement.
// Son tableau digit, alloué dynamiquement, a toutes ses cases initialisées à 0.
// Son nombre de cases est n (de même que le champ "n" de la structure).
//
// Exemple d'utilisation :
//   number *X = number_new(10);
//   assert(X->n == 10);
//   for (int i = 0; i < X->n; i++)
//     assert(X->digit[i] == 0);
number* number_new(int n);

// Libère la mémoire prise par le nombre pointé par X.
void number_free(number* X);

// Libère la mémoire (allouée dynamiquement) accessible depuis les nombres
// pointés par les arguments. Les tableaux digit sont aussi désalloués.
// La liste d'arguments est terminée par un pointeur NULL.
//
// Ne pas confondre cette fonction avec la fonction multiple_free() de alloc.h.
//
// Exemple d'utilisation :
//   number *t1 = number_new(10);
//   number *t2 = number_new(20);
//   number *t3 = number_new(30);
//   ...
//   number_multiple_free(t1, t2, t3, NULL);
void number_multiple_free(number* X, ...);

// Retourne une chaîne de caractères représentant le nombre X. Les zéros
// inutiles (ceux en fin de tableau digit) sont ignorés dans la chaîne
// renvoyée (sauf si X est nul, dans ce cas la fonction copie un '0').
char* number_to_string(number* X);

// Renvoie un pointeur vers le nombre représenté par la chaîne s, dont les
// caractères doivent correspondre à des chiffres entre 0 et BASE-1.
number* string_to_number(char* s);

// Renvoie un pointeur vers un nombre à n chiffres aléatoire. Utilisée dans les
// tests automatiques, vous ne devriez pas avoir besoin de l'utiliser.
number* number_random(int n);

#endif // TPTOOLS_H_

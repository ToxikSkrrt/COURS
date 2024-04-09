#ifndef TEST_H_
#define TEST_H_

//----------------------------//
// NE PAS MODIFIER CE FICHIER //
//----------------------------//

#include "alloc.h"
#include "signed.h"
#include "tools.h"
#include "tp.h"

#define OK "\xE2\x9C\x85"
#define KO "\xE2\x9D\x8C"

// Vérifie les résultats en mode interactif ou automatique.
bool check_result(number *X, number *Y, number *R,
                  void (*mpz_f)(mpz_t, const mpz_t, const mpz_t),
                  char **mpz_result);

// Vérifie les résultats d'une comparaison en mode interactif ou automatique.
bool check_comparison(number *X, number *Y, char **sX, char **sY, int *computed,
                      int *expected);

// Affiche le résultat d'une opération non signée en mode interactif ou
// automatique.
number *output_result(number *X, number *Y, number *(*f)(number *X, number *Y),
                      void (*mpz_f)(mpz_t, const mpz_t, const mpz_t));

// Nombres signés.

// Affiche le résultat d'une opération signée en mode interactif ou automatique.
signed_number *
signed_output_result(signed_number *X, signed_number *Y,
                     signed_number *(*f)(signed_number *X, signed_number *Y),
                     void (*mpz_f)(mpz_t, const mpz_t, const mpz_t), char *op);

// Affiche le résultat d'une comparaison en mode interactif.
void comparison(signed_number *X, signed_number *Y, int how);

#endif // TEST_H_

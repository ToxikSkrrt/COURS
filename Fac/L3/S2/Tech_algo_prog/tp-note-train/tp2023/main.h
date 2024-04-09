#ifndef MAIN_H
#define MAIN_H

//----------------------------//
// NE PAS MODIFIER CE FICHIER //
//----------------------------//

#include <assert.h>
#include <getopt.h>
#include <stdarg.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

#include "alloc.h"
#include "test.h"
#include "tools.h"
#include "tp.h"

// Le prompt utilisé en mode interactif.
#define PROMPT ">>> "

// Affiche un message d'aide.
void usage(char *argv[]);

// Parse les arguments de la ligne de commande.
void parse_argv(int argc, char *argv[]);

// Analyse la ligne de commande.
int yyparse(void);

// Retourne la somme d'un nombre variable d'entiers.
// Cette fonction est utilisée dans main.c, et ne devrait pas être utile.
// Le premier argument est le nombre d'entiers à sommer.
// Exemple d'utilisation :
//   int s = vsum(3, 10, 20, 30);
//   assert(s == 60);
int vsum(int n, ...);

#endif /* MAIN_H */

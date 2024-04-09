#ifndef ALLOC_H_
#define ALLOC_H_

//----------------------------//
// NE PAS MODIFIER CE FICHIER //
//----------------------------//

//--------------------------------------------------------------------------//
// Vous pouvez utiliser ces fonctions pour allouer/désallouer de la mémoire //
//--------------------------------------------------------------------------//

#include <stdarg.h>
#include <stdio.h>
#include <stdlib.h>

// Appelle malloc et vérifie que le pointeur renvoyé n'est pas NULL.
void *malloc_wrapper(size_t size);

// Appelle calloc et vérifie que le pointeur renvoyé n'est pas NULL.
void *calloc_wrapper(size_t nmemb, size_t size);

// Appelle realloc et vérifie que le pointeur renvoyé n'est pas NULL.
void *realloc_wrapper(void *ptr, size_t size);

// Appelle free sur un nombre variable d'arguments.
// Le dernier argument doit être NULL.
// Exemple :
// char *p1 = malloc_wrapper(10);
// char *p2 = malloc_wrapper(10);
// char *p3 = malloc_wrapper(10);
// ...
// multiple_free(p1, p2, p3, NULL);
void multiple_free(void *p, ...);

#endif // ALLOC_H_

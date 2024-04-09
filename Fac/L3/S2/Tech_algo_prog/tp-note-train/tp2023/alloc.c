#include "alloc.h"

// // Fonctions de gestion de la mémoire dynamique.

//----------------------------//
// NE PAS MODIFIER CE FICHIER //
//----------------------------//

//-----------------------------------------------//
// Vous pouvez utiliser les fonctions suivantes. //
//                                               //
// Elles sont décrites dans le fichier alloc.h.  //
//-----------------------------------------------//

void *malloc_wrapper(size_t size) {
  void *p = malloc(size);
  if (p == NULL) {
    fprintf(stderr, "Erreur malloc.\n");
    exit(EXIT_FAILURE);
  }
  return p;
}

void *calloc_wrapper(size_t nmemb, size_t size) {
  void *p = calloc(nmemb, size);
  if (p == NULL) {
    fprintf(stderr, "Erreur calloc.\n");
    exit(EXIT_FAILURE);
  }
  return p;
}

void *realloc_wrapper(void *ptr, size_t size) {
  void *p = realloc(ptr, size);
  if (p == NULL) {
    fprintf(stderr, "Erreur realloc.\n");
    exit(EXIT_FAILURE);
  }
  return p;
}

void multiple_free(void *p, ...) {
  va_list ap;
  va_start(ap, p);
  while (p != NULL) {
    free(p);
    p = va_arg(ap, void *);
  }
  va_end(ap);
}

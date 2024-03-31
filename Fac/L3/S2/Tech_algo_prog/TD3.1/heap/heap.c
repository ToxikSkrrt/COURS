#include "heap.h"
#include <stdlib.h>

heap heap_create(int k, int (*f)(const void*, const void*)) {
  heap h = malloc(sizeof(*h));
  h->n = k + 1;
  h->nmax = 2 ^ h->n;
  h->f = f;
  h->array = malloc(h->nmax * sizeof(void*));

  return NULL;
}

void heap_destroy(heap h) {
  ;
  ;
  ;
}

bool heap_empty(heap h) {
  ;
  ;
  ;
  return true;
}

bool heap_add(heap h, void* object) {
  ;
  ;
  ;
  return false;
}

void* heap_top(heap h) {
  ;
  ;
  ;
  return NULL;
}

void* heap_pop(heap h) {
  ;
  ;
  ;
  return NULL;
}

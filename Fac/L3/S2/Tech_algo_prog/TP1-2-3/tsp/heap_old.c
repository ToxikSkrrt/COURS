#include "heap.h"
#include <stdlib.h>
#include <stdio.h>

heap heap_create(int k, int (*f)(const void*, const void*)) {
  heap h = malloc(sizeof(*h));
  h->n = 0;
  h->nmax = k;
  h->f = f;
  h->array = malloc((h->nmax + 1) * sizeof(void*));

  return h;
}

void heap_destroy(heap h) {
  free(h->array);
  free(h);
}

bool heap_empty(heap h) {
  return h->n == 0;
}

bool heap_add(heap h, void* object) {
  bool test = false;

  if (h->n == h->nmax) {
    test = true;
    h->nmax = 2 ^ h->nmax;
    h->array = realloc(h->array, h->nmax * sizeof(void*));
  }

  h->n++;
  h->array[h->n] = object;
  int current = h->n;
  bool swap = true;

  while (swap) {
    int parent = current / 2 == 0 ? 1 : current / 2;

    if (h->f(h->array[current], h->array[parent]) < 0) {
      void* tmp = h->array[current];
      h->array[current] = h->array[parent];
      h->array[parent] = tmp;

      current /= 2;
    }
    else
      swap = false;
  }

  return test;
}

void* heap_top(heap h) {
  if (!heap_empty(h))
    return h->array[1];

  return NULL;
}

void* heap_pop(heap h) {
  if (heap_empty(h)) {
    return NULL;
  }

  void* tmp = h->array[1];
  void* result = h->array[1];
  h->array[1] = h->array[h->n];
  h->array[h->n] = tmp;


  int current = 1;
  bool swap = true;

  h->n--;

  while (swap) {
    bool existsLeft = current * 2 <= h->n;
    bool existsRight = current * 2 + 1 <= h->n;
    int compLeft, compRight;
    if (existsLeft) compLeft = h->f(h->array[current], h->array[current * 2]);
    if (existsRight) compRight = h->f(h->array[current], h->array[current * 2 + 1]);

    if ((existsLeft && compLeft > 0 && compLeft > compRight) || (existsLeft && compLeft > 0 && !existsRight)) {
      tmp = h->array[current];
      h->array[current] = h->array[current * 2];
      h->array[current * 2] = tmp;

      current *= 2;
    }
    else if ((existsRight && compRight > 0) || (existsRight && compRight > 0 && !existsLeft)) {
      tmp = h->array[current];
      h->array[current] = h->array[current * 2 + 1];
      h->array[current * 2 + 1] = tmp;

      current *= 2;
      current++;
    }
    else
      swap = false;
  }

  return result;
}

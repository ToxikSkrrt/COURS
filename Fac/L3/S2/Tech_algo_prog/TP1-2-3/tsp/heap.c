#include "heap.h"
#include <stdlib.h>

#define IS_ROOT(i) ((i) == 1)
#define PARENT(i) ((i) / 2)
#define LEFT(i) ((i)*2)
#define RIGHT(i) ((i)*2 + 1)

heap heap_create(int k, int (*f)(const void *, const void *)) {
  heap h = malloc(sizeof(*h));
  h->f = f;
  h->nmax = k;
  h->n = 0;
  h->array = malloc((k + 1) * (sizeof(void *)));
  return h;
}

void heap_destroy(heap h) {
  free(h->array);
  free(h);
}

bool heap_empty(heap h) { return (h->n == 0); }

bool heap_add(heap h, void *object) {
  if (h->n == h->nmax) {
    return true;
  }
  h->n++;
  h->array[h->n] = object;
  int i = h->n;
  while (1 < i && (0 < h->f(h->array[PARENT(i)], h->array[i]))) {
    h->array[i] = h->array[PARENT(i)];
    h->array[PARENT(i)] = object;
    i = PARENT(i);
  }
  return false;
}

void *heap_top(heap h) {
  if (!heap_empty(h)) {
    return h->array[1];
  }
  return NULL;
}

void *heap_pop(heap h) {
  if (!heap_empty(h)) {
    void *top = h->array[1];
    h->array[1] = h->array[h->n];
    h->n--;
    int i = 1;
    int next = 1;
    while (RIGHT(i) <= h->n && (0 < h->f(h->array[i], h->array[LEFT(i)]) ||
                                0 < h->f(h->array[i], h->array[RIGHT(i)]))) {
      next = LEFT(i);
      if (0 < h->f(h->array[LEFT(i)], h->array[RIGHT(i)])) {
        next = RIGHT(i);
      }
      void *tmp = h->array[i];
      h->array[i] = h->array[next];
      h->array[next] = tmp;
      i = next;
    }
    if (LEFT(i) <= h->n && 0 < (h->f(h->array[i], h->array[LEFT(i)]))) {
      void *tmp = h->array[i];
      h->array[i] = h->array[LEFT(i)];
      h->array[LEFT(i)] = tmp;
    }
    return top;
  }
  return NULL;
}

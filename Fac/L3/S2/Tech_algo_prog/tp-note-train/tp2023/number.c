#include "number.h"

// Fonctions de manipulation de nombres.

//----------------------------//
// NE PAS MODIFIER CE FICHIER //
//----------------------------//

//-----------------------------------------------//
// Vous pouvez utiliser les fonctions suivantes. //
//                                               //
// Elles sont décrites dans le fichier number.h. //
//-----------------------------------------------//

number *number_new(int n) {
  number *t = malloc_wrapper(sizeof(*t));
  t->n      = n;
  t->digit  = calloc_wrapper(n, sizeof(*t->digit));
  return t;
}

void number_free(number *X) {
  if (X) {
    free(X->digit);
    free(X);
  }
}

void number_multiple_free(number *X, ...) {
  va_list ap;
  va_start(ap, X);
  while (X != NULL) {
    number_free(X);
    X = va_arg(ap, number *);
  }
  va_end(ap);
}

char *number_to_string(number *X) {
  int i;

  for (i = X->n - 1; i >= 0 && X->digit[i] == 0; i--)
    ;
  if (i < 0) {
    // Ne pas retourner la constante "0", car la valeur retournée par
    // number_to_string est supposée avoir été allouée dynamiquement.
    char *sX = malloc_wrapper(2 * sizeof(*sX));
    sX[0]    = '0';
    sX[1]    = 0;
    return sX;
  }

  char *sX = malloc_wrapper((i + 2) * sizeof(*sX));

  for (int j = i; j >= 0; j--)
    sX[i - j] = '0' + X->digit[j];

  sX[i + 1] = 0;
  return sX;
}

number *string_to_number(char *s) {
  number *X = malloc_wrapper(sizeof(*X));
  X->n      = strlen(s);
  X->digit  = malloc_wrapper(X->n * sizeof(*(X->digit)));

  for (int i = 0; i < X->n; i++) {
    X->digit[i] = s[X->n - i - 1] - '0';
    assert(X->digit[i] >= 0);
    assert(X->digit[i] < BASE);
  }
  return X;
}

number *number_random(int n) {
  if (n < 1)
    return NULL;

  number *R = number_new(n);

  for (--n; n >= 0; n--)
    R->digit[n] = random() % BASE;

  return R;
}

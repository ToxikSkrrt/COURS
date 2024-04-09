#include "signed.h"

//----------------------------//
// NE PAS MODIFIER CE FICHIER //
//----------------------------//

signed_number *signed_number_new(int n, int s) {
  signed_number *sn = malloc_wrapper(sizeof(*sn));
  sn->number        = number_new(n);
  sn->sign          = s;
  return sn;
}

void signed_number_free(signed_number *n) {
  if (n) {
    number_free(n->number);
    free(n);
  }
}

void signed_number_multiple_free(signed_number *t, ...) {
  va_list ap;
  va_start(ap, t);
  while (t != NULL) {
    signed_number_free(t);
    t = va_arg(ap, signed_number *);
  }
  va_end(ap);
}

signed_number *signed_number_addition(signed_number *X, signed_number *Y) {
  signed_number *R = malloc_wrapper(sizeof(*R));

  int cmp;

  if (X->sign == Y->sign) {
    R->number = number_addition(X->number, Y->number);
    R->sign   = X->sign;
    return R;
  }

  // À partir d'ici, l'un >= 0, l'autre < 0.

  // Si |X| = |Y|, leur somme est nulle.
  cmp       = number_sign(X->number, Y->number);

  // |X| =/= |Y|, cmp = 1 ou -1.
  R->number = number_substraction(X->number, Y->number);
  R->sign   = cmp == 0 ? 1 : cmp * X->sign;

  return R;
}

signed_number *signed_number_substraction(signed_number *X, signed_number *Y) {
  signed_number *Z = malloc_wrapper(sizeof(*Z));
  Z->sign          = -Y->sign;
  Z->number        = number_new(Y->number->n);
  for (int i = 0; i < Z->number->n; i++) {
    Z->number->digit[i] = Y->number->digit[i];
  }
  signed_number *R = signed_number_addition(X, Z);
  signed_number_free(Z); // Z->number est toujours utilisé par Y.
  return R;
}

signed_number *signed_number_multiplication_recursive(signed_number *X,
                                                      signed_number *Y) {
  signed_number *R = malloc_wrapper(sizeof(*R));

  R->number        = number_multiplication_recursive(X->number, Y->number);

  R->sign          = X->sign * Y->sign;

  return R;
}

signed_number *signed_number_multiplication_karatsuba(signed_number *X,
                                                      signed_number *Y) {
  signed_number *R = malloc_wrapper(sizeof(*R));

  R->number        = number_multiplication_karatsuba(X->number, Y->number);

  R->sign          = X->sign * Y->sign;

  return R;
}

short signed_number_sign(signed_number *X, signed_number *Y) {
  if (X->sign == Y->sign) {
    return X->sign * number_sign(X->number, Y->number);
  }
  return X->sign;
}

char *signed_number_to_string(signed_number *X) {
  char *t = number_to_string(X->number);
  char *s =
      malloc_wrapper(sizeof(char) * (strlen(t) + 1 /* \0 */ + (X->sign == -1)));
  if (X->sign == -1) {
    s[0] = '-';
    memcpy(s + 1, t, strlen(t) + 1);
  } else {
    memcpy(s, t, strlen(t) + 1);
  }
  free(t);
  return s;
}

int signed_number_length(signed_number *X) {
  return number_length(X->number) + (X->sign == -1);
}

signed_number *signed_number_negate(signed_number *X) {
  X->sign = -X->sign;
  return X;
}

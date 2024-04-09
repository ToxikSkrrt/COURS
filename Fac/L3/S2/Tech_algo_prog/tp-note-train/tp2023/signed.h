#ifndef SIGNED_H_
#define SIGNED_H_

//----------------------------//
// NE PAS MODIFIER CE FICHIER //
//----------------------------//

#include "alloc.h"
#include "number.h"
#include "tp.h"

typedef struct {
  number *number;
  short sign; // 1 si positif ou nul, -1 si négatif
} signed_number;

signed_number *signed_number_new(int n, int s);

void signed_number_free(signed_number *n);

void signed_number_multiple_free(signed_number *t, ...);

signed_number *signed_number_addition(signed_number *a, signed_number *b);

signed_number *signed_number_substraction(signed_number *a, signed_number *b);

signed_number *signed_number_multiplication_recursive(signed_number *X,
                                                      signed_number *Y);

signed_number *signed_number_multiplication_karatsuba(signed_number *a,
                                                      signed_number *b);

short signed_number_sign(signed_number *X, signed_number *Y);

char *signed_number_to_string(signed_number *X);

int signed_number_length(signed_number *X);

signed_number *signed_number_negate(signed_number *X);

#endif // SIGNED_H_

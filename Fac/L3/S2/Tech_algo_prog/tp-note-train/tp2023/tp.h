#ifndef TP1_H
#define TP1_H

#include "number.h"
#include "tools.h"

//----------------------------//
// NE PAS MODIFIER CE FICHIER //
//----------------------------//

// Base des nombres, entier >= 2 et <= 9.
extern short BASE;

int number_length(number *X) __attribute__((weak));

int number_sign(number *X, number *Y) __attribute__((weak));

void align_numbers(number *X, number *Y) __attribute__((weak));

number *number_addition(number *X, number *Y) __attribute__((weak));

number *number_substraction(number *X, number *Y) __attribute__((weak));

number *shift(number *X, int k) __attribute__((weak));

number *high(number *X, int k) __attribute__((weak));

number *low(number *X, int k) __attribute__((weak));

number *number_multiplication_recursive(number *X, number *Y);

number *number_multiplication_karatsuba(number *X, number *Y);

#endif

#include "test.h"

//----------------------------//
// NE PAS MODIFIER CE FICHIER //
//----------------------------//

bool check_result(number *X, number *Y, number *R,
                  void (*mpz_f)(mpz_t, const mpz_t, const mpz_t),
                  char **mpz_result) {
  assert(X != NULL);
  assert(Y != NULL);
  assert(R != NULL);
  char *sX = number_to_string(X);
  char *sY = number_to_string(Y);
  char *sR = number_to_string(R);

  mpz_t x, y;
  mpz_init_set_str(x, sX, BASE);
  mpz_init_set_str(y, sY, BASE);

  mpz_t r;
  mpz_init(r);
  mpz_f(r, x, y);

  *mpz_result = mpz_get_str(NULL, BASE, r);
  char *start =
      (*mpz_result[0] == '-') ? *mpz_result + 1 : *mpz_result; // skip sign

  bool check = (strcmp(start, sR) == 0);

  multiple_free(sX, sY, sR, NULL);
  mpz_clear(x);
  mpz_clear(y);
  mpz_clear(r);

  return check;
}

bool check_comparison(number *X, number *Y, char **sX, char **sY, int *computed,
                      int *expected) {
  *sX = number_to_string(X);
  *sY = number_to_string(Y);

  mpz_t x, y;
  mpz_init_set_str(x, *sX, BASE);
  mpz_init_set_str(y, *sY, BASE);

  *computed = number_sign(X, Y);
  *expected = mpz_cmp(x, y);

  mpz_clear(x);
  mpz_clear(y);

  return (*computed == *expected || *computed * *expected > 0);
}

number *output_result(number *X, number *Y, number *(*f)(number *X, number *Y),
                      void (*mpz_f)(mpz_t, const mpz_t, const mpz_t)) {
  number *R = f(X, Y);

  char *mpz_r;
  bool test = check_result(X, Y, R, mpz_f, &mpz_r);

  if (test)
    printf("%s ", OK);
  else {
    char *sR = number_to_string(R);
    printf("%s (attendu : %s, calculé %s)\n", KO, mpz_r, sR);
    free(sR);
  }
  free(mpz_r);

  return R;
}

signed_number *
signed_output_result(signed_number *X, signed_number *Y,
                     signed_number *(*f)(signed_number *X, signed_number *Y),
                     void (*mpz_f)(mpz_t, const mpz_t, const mpz_t), char *op) {
  signed_number *R = f(X, Y);

  char *sX         = signed_number_to_string(X);
  char *sY         = signed_number_to_string(Y);
  char *sR         = signed_number_to_string(R);

  mpz_t x, y;
  mpz_init_set_str(x, sX, BASE);
  mpz_init_set_str(y, sY, BASE);

  mpz_t r;
  mpz_init(r);
  mpz_f(r, x, y);

  char *mpz_r = mpz_get_str(NULL, BASE, r);

  if (strcmp(mpz_r, sR) == 0)
    printf("%s %s %s %s = %s\n", OK, sX, op, sY, sR);
  else {
    printf("%s (attendu : %s, calculé %s)\n", KO, mpz_r, sR);
  }

  signed_number_multiple_free(X, Y, NULL);
  multiple_free(sX, sY, sR, mpz_r, NULL);
  mpz_clear(x);
  mpz_clear(y);
  mpz_clear(r);
  return R;
}

void comparison(signed_number *X, signed_number *Y, int how) {
  printf("Résultat de la comparaison : ");
  if (signed_number_sign(X, Y) == how)
    printf("Vrai\n");
  else
    printf("Faux\n");
  signed_number_multiple_free(X, Y, NULL);
}

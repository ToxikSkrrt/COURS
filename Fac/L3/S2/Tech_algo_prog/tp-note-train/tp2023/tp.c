#include "tp.h"

//-------------------------//
// SEUL FICHIER À MODIFIER //
//-------------------------//

//---------------------------------------------------------------------------//
// Une fois une fonction écrite, vous pouvez enlever __attribute__((unused)) //
// pour chacun de ses arguments, de façon que le compilateur indique les     //
// arguments inutilisés.                                                     //
//---------------------------------------------------------------------------//

//---------------------------------------------------------------------------//

// Retourne le nombre de chiffres significatifs dans un nombre,
// c'est-à-dire le nombre de chiffres sans compter les zéros en tête dans
// l'écriture habituelle du nombre.
//
// Exemples en base 10 :
// Si le tableau X->digit vaut {1,2,3,4}, number_length(X) renvoie 4.
// Si le tableau X->digit vaut {0,1,2,3,4}, number_length(X) renvoie 5.
// Si le tableau X->digit vaut {0,1,2,3,4,0,0,0}, number_length(X) renvoie 5
// car les zéros en fin de tableau ne sont pas significatifs.
//
// Par convention, si le tableau X->digit ne contient que des 0,
// number_length(X) renvoie 0.
int number_length(number* X) {
  int cpt = 0;
  for (int i = X->n - 1; i > 0; i--) {
    if (X->digit[i] != 0)
      return X->n - cpt;
    cpt++;
  }
  return 0;
}

// Dans les fonctions suivantes, on suppose que les opérandes X et Y
// représentent des nombres valides (au moins 1 chiffre, pointeur non NULL,
// etc.). C'est donc à l'appellant de s'en assurer, pas à la fonction que vous
// avez à écrire.
//
// Les opérandes X,Y sont toujours considérés positifs.
//
// Attention ! Il est possible que X et Y ne soient pas de la même taille.

// Compare deux entiers. Retourne
// -1 si le nombre représenté par X est < à celui représenté par Y,
// 0 si les nombres représentés par X et Y sont égaux,
// 1 si  le nombre représenté par X est > à celui représenté par Y.
// Attention ! Il est possible que X et Y ne soient pas de la même taille.
// Attention aussi aux zéros inutiles dans X ou Y.
int number_sign(number* X,
  number* Y) {
  int nlX = number_length(X);
  int nlY = number_length(Y);
  if (nlX < nlY)
    return -1;
  else if (nlX > nlY)
    return 1;
  else {
    for (int i = nlX; i > 0; i--) {
      if (X->digit[i] < Y->digit[i]) return -1;
      else if (X->digit[i] > Y->digit[i]) return 1;
    }
    return 0;
  }
}

// Renvoie un nombre représentant la somme X+Y de ceux représentés par X et Y.
// Le calcul doit être en O(n) où n est la taille du plus grand des deux
// nombres.
number* number_addition(number* X,
  number* Y) {
  number* Z = number_new(1 + max(number_length(X), number_length(Y)));
  bool carry = false;
  int length = max(number_length(X), number_length(Y));

  for (int i = 0; i < length; i++) {
    if (number_length(X) < i) {
      Z->digit[i] = carry ? Y->digit[i] + 1 : Y->digit[i];
      carry = false;
    }
    else if (number_length(Y) < i) {
      Z->digit[i] = carry ? X->digit[i] + 1 : X->digit[i];
      carry = false;
    }
    else {
      short sum = carry ? X->digit[i] + Y->digit[i] + 1 : X->digit[i] + Y->digit[i];
      carry = false;
      if (sum >= BASE) {
        carry = true;
        sum %= BASE;
      }
      Z->digit[i] = sum;
    }
  }
  if (carry) Z->digit[max(number_length(X), number_length(Y))] = 1;
  return Z;
}

// Renvoie un nombre représentant |X-Y|, c'est-à-dire la valeur absolue la
// différence des nombres représentés par X et Y.
//
// La fonction positionne la variable globale sign pour son utilisation dans la
// multiplication de Karatsuba (cf. commentaire en début de fichier).
//
// Le calcul doit être en O(n) où n est la taille du plus grand des deux
// nombres.
number* number_substraction(number* X __attribute__((unused)),
  number* Y __attribute__((unused))) {
  return string_to_number("0");
}

// Renvoie un nombre représentant celui représenté par X multiplié par BASE^k.
number* shift(number* X __attribute__((unused)),
  int k __attribute__((unused))) {
  return string_to_number("0");
}

// Renvoie le nombre représenté par les k chiffres de poids faible de X, ie,
// obtenu en ne gardant que les k premiers chiffres de X->digit
// (ce nombre représente X % BASE^k).
number* low(number* X __attribute__((unused)), int m __attribute__((unused))) {
  return string_to_number("0");
}

// Renvoie le nombre représenté par les (X->n - k) chiffres de poids fort de X,
// ie, obtenu en ne conservant que les X->n-k derniers chiffres de X->digit
// (ce nombre représente X/BASE^k).
number* high(number* X __attribute__((unused)), int m __attribute__((unused))) {
  return string_to_number("0");
}

// Ajoute si besoin des zéros inutiles à l'un des deux nombres représentés par X
// et Y pour que les tableaux X->digit et Y->digit soient de même taille.
//
// Après l'appel, X->digit et Y->digit ont donc la même taille, qui est le
// maximum des tailles d'origine, et la valeur des entiers représentés par *X et
// *Y n'est pas changée.
//
// Attention à bien mettre à jour les deux champs du nombre modifié.
//
// Exemple : si X->digit vaut {1,2,3,4} et Y->digit vaut {1,2,3,4,5,6,7,8},
// après appel à align_numbers(X,Y), X->digit vaudra {1,2,3,4,0,0,0,0} et
// Y->digit sera inchangé. X->n vaudra 8 (au lieu de 4 initialement) et Y->n
// vaudra 8 (il est inchangé).
void align_numbers(number* X __attribute__((unused)),
  number* Y __attribute__((unused))) {
  return;
}

// Renvoie un nombre représentant le produit X*Y de ceux représentés par X et Y
// en utilisant l'algorithme de multiplication récursive naïve, en O(n^2) où n
// est la taille du plus grand des deux nombres.
number* number_multiplication_recursive(number* X __attribute__((unused)),
  number* Y __attribute__((unused))) {
  return string_to_number("0");
}

// Renvoie un nombre représentant le produit X*Y de ceux représentés par X et Y
// en utilisant l'algorithme de multiplication récursive Karatsuba, en O(n^1.59)
// ou n est la taille du plus grand des deux nombres.
number* number_multiplication_karatsuba(number* X __attribute__((unused)),
  number* Y __attribute__((unused))) {
  return string_to_number("0");
}

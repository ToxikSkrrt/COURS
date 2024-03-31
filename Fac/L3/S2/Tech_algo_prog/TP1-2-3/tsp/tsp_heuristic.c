#include "tools.h"
#include "tsp_brute_force.h"

//
//  TSP - HEURISTIQUES
//

void reverse(int* T, int p, int q) {
  // Renverse la partie T[p]...T[q] du tableau T avec p<q si
  // T={0,1,2,3,4,5,6} et p=2 et q=5, alors le nouveau tableau T sera
  // {0,1, 5,4,3,2, 6}.

  for (int i, j = p, q; i < j; i++, j--) {
    int tmp = T[i];
    T[i] = T[j];
    T[j] = tmp;
    // SWAP (T[i], T[j], tmp);
  }
}

double first_flip(point* V, int n, int* P) {
  // Renvoie le gain>0 du premier flip réalisable, tout en réalisant
  // le flip, et 0 s'il n'y en a pas.

  for (int i = 0; i < n - 2; i++) {
    for (int j = i + 2; j < n; (j + 1) % n) {
      if (j == n - 1 && i == 0) continue;

      double delta = dist(V[P[i]], V[P[j]]) + dist(V[P[i + 1]], V[P[j + 1]]) - dist(V[P[i]], V[P[i + 1]]) - dist(V[P[j]], V[P[j + 1]]);
      if (delta < 0) {
        reverse(P, i + 1, j);

        return delta;
      }
    }
  }

  return 0;
}

double tsp_flip(point* V, int n, int* P) {
  // La fonction doit renvoyer la valeur de la tournée obtenue. Pensez
  // à initialiser P, par exemple à P[i]=i. Pensez aussi faire
  // drawTour() pour visualiser chaque flip.

  for (int i = 0; i < n; i++)
    P[i] = i;

  double gain;

  while (gain = first_flip(V, n, P))
    drawTour(V, n, P);

  return gain;
}

double tsp_greedy(point* V, int n, int* P) {
  // La fonction doit renvoyer la valeur de la tournée obtenue. Pensez
  // à initialiser P, par exemple à P[i]=i.

  for (int i = 0; i < n; i++)
    P[i] = i;

  for (int i = 0; i < n; i++) {
    double min_d = DBL_MIN;
    for (int j = 0; j < n; j++) {
      double d = dist(V[P[i]], V[P[j]]);
      // A FINIR
    }
  }

  return 0.0;
}

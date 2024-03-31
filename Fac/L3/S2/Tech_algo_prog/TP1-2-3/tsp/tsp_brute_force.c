#include "tools.h"

//
//  TSP - BRUTE-FORCE
//
// -> la structure "point" est définie dans "tools.h"
// -> tsp_main peut être testé dès les 3 premières fonctions codées
//

double dist(point A, point B)
{
  return sqrt(pow(A.x - B.x, 2) + pow(A.y - B.y, 2));
}

double value(point *V, int n, int *P)
{
  double distance = 0;

  for (int i = 0; i < n - 1; i++)
  {
    distance += dist(V[P[i]], V[P[i + 1]]);
  }

  distance += dist(V[P[0]], V[P[n - 1]]);

  return distance;
}

double tsp_brute_force(point *V, int n, int *Q)
{
  int P[n];
  double dmin = DBL_MAX;
  double d = 0;

  for (int i = 0; i < n; i++)
  {
    P[i] = i;
  }

  do
  {
    d = value(V, n, P);
    if (d < dmin)
    {
      dmin = d;
      memcpy(Q, P, n * sizeof(int));
    }
  } while (NextPermutation(P, n) && running);

  return dmin;
}

void MaxPermutation(int *P, int n, int k)
{
  int i = k;
  int j = n - 1;
  int tmp;

  while (i < j && running)
  {
    tmp = P[i];
    P[i] = P[j];
    P[j] = tmp;
    i++;
    j--;
  }
}

double value_opt(point *V, int n, int *P, double w)
{
  double distance = 0;

  for (int i = 0; i < n - 1; i++)
  {
    distance += dist(V[P[i]], V[P[i + 1]]);
    if (distance > w)
      return -(i + 1);
  }
  distance += dist(V[P[0]], V[P[n - 1]]);
  if (distance > w)
    return -(n - 1);

  return distance;
}

double tsp_brute_force_opt(point *V, int n, int *Q)
{
  ;
  ;
  ;
  return 0;
}

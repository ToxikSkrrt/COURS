#include "tp.h"
#include "htable.h"

//
// Paire de Points les Plus Proches
//
// Vous avez 5 fonctions à compléter: dist(), pppp_naive(), map(),
// pppp_random() et pppp_random2(). N'attendez pas la dernière minute pour
// les compiler et les tester.
//
// Chaque fonction du type pppp_xxx() doit renvoyer le couple {i,j}
// d'indices des deux points les plus proches.
//
// -> la structure "point" est définie dans "tools.h"
// -> la structure "couple" est définie dans "tp.h"
//

double dist(point A, point B) {
  return sqrt(pow(A.x - B.x, 2) + pow(A.y - B.y, 2));
}

couple pppp_naive(point* V, int n) {
  couple result = { 0,1 };
  int dmin = dist(V[0], V[1]);

  for (int i = 0; i < n - 1; i++) {
    for (int j = i + 1; j < n; j++) {
      int tmp_dist = dist(V[i], V[j]);
      if (tmp_dist < dmin) {
        dmin = tmp_dist;
        result = (couple){ i, j };
      }
    }
  }

  return result;
}

// clang-format off

// map: N^2 -> N définit pour toute paire d'entiers (i,j) un entier
// unique. Il faut i,j >= 0. Il correspond à la somme des longueurs
// des diagonales montantes de la forme (t,0) -> (0,t), partant de
// (0,0), et jusqu'à atteindre le point (i,j) sans le compter. La
// longueur de la diagonale est le nombre de points qu'elle contient.
//
//       | | | | | |
//     4 .-.-.-.-.-.-
//       | | | | | |
//     3 o-.-.-.-.-.-
//       |\| | | | |
//     2 o-o-.-.-.-.-
//       |\|\| | | |
// j = 1 o-o-o-X-.-.-    Ex: map(i,j) = map(3,1) = (#o) = 11
//       |\|\|\|\| |
//     0 o-o-o-o-o-.-
//       0 1 2 3 4 5
//             i
//

// clang-format on

int map(int i, int j) {
  int sum = 1;
  for (int t = 1; t <= i + j; t++)
    sum += t;

  return sum;
}

// Point de vigilance. Attention à ce que les cellules voisines
// tombent dans le premier quadrant (i,j >= 0), sinon map(i,j) ne
// marchera pas.
couple pppp_random(point* V, int n) {
  // 1.
  int dmin = dist(V[0], V[1]);
  couple R = { 0, 1 };
  // 2.
  htable T = ht_create();
  bool run = true;
  while (run) {
    ht_reset(T);
    int delta = dmin / sqrt(2);
    // 3.
    for (int t = 0; t < n; t++) {
      // a)
      int i = V[t].x / delta;
      int j = V[t].y / delta;
      // b)
      for (int m = -2; m <= 2; m++) {
        for (int n = -2; n <= 2; n++) {

          void* q = ht_read(T, map(m, n));

          // c)
          if (q != NULL && dist(V[t], *(point*)q) < dmin) {
            dmin = dist(V[t], *(point*)q);
            R.i = t;
            R.j = map(i + m, j + n);
            break;break;break;continue;
          }
          // d)
          ht_write(T, map(i, j), &V[t]);
        }
      }

    }
    run = false;
    // 4.

  }
  return R;
}

// Version optimisée de pppp_random() comportant les deux extensions
// suivantes:
//
// . Il est possible de maintenir l'indice du dernier échec, disons tf
// (initialisée à -1), de sorte que les instructions (3b) et (3c)
// doivent être exécutée seulement si t>tf. Faire attention, lors
// d'un échec, de bien chercher le point q le plus proche dans le
// voisinage, sinon il y aura des échecs plusieurs fois au même
// indice.
//
// . Optimisez le nombre de cellules voisines en passant de 25 à 21
// cellules à explorer. Comparez.
//
couple pppp_random2(point* V, int n) {
  couple result = { -1, -1 };
  ;
  ;
  ;
  return result;
}

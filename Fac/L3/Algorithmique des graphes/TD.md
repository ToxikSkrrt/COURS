# TD 1

## Exercice 1

1. 
s0 -> 1 (s6)
s1 -> 3 (s2 / s5)
s2 -> 3 (s1 / s3 / s4)
s3 -> 3 (s1 / s2 / s4)
s4 -> 2 (s2 / s3)
s5 -> 1 (s1)
s6 -> 1 (s0)

2. 
degré min : 1 / degré max : 3

3. 
```
Matrice d'adjacence  
   0  1  2  3  4  5  6  
0  0  0  0  0  0  0  1  
1  0  0  1  1  0  1  0  
2  0  1  0  1  1  0  0  
3  0  1  1  0  1  0  0  
4  0  0  1  1  0  1  1  
5  0  1  0  0  0  0  0  
6  1  0  0  0  0  0  0  

Matrice d'incidence  
   e1 e2 e3 e4 e5 e6 e7  
0  1  0  0  0  0  0  0  
1  0  1  1  1  0  0  0  
2  0  1  0  0  1  1  0  
3  0  0  1  0  1  0  1  
4  0  0  0  0  0  1  1  
5  0  0  0  1  0  0  0  
6  1  0  0  0  0  0  0  
```

4. 
G1 contient un cycle : S1 -> S3 -> S4 -> S2 -> S1 -> ...

5. 
G1 n'est pas connexe, S0 et S1 sont séparés du reste du graphe

## Exercice 2

(image1)

```
Matrice d'adjacence  
   1  2  3  4  5  
1  0  1  1  0  0 
2  1  0  1  1  1  
3  1  1  0  0  1  
4  0  1  0  0  1  
5  0  1  1  1  0  

Matrice d'incidence  
   e1 e2 e3 e4 e5 e6 e7  
1  1  1  0  0  0  0  0  
2  1  0  1  1  1  0  0  
3  0  1  1  0  0  1  0  
4  0  0  0  1  0  0  1  
5  0  0  0  0  1  1  1  
```

## Exercice 3 (a faire a la maison)

1. 
graphe contenant une boucle : (image2)  
graphe sans boucle contenant des arêtes parallèles (image3)
graphe simple : (image4)

## Exercice 4

Preuve 1 : Si on considère la matrice I(G) d'un graphe G, la somme des degrés de G est égale à la somme des valeurs de I(G). Chaque colonne de I(G) contient soit deux 1, soit un 2 (si l'arête est une boucle). Donc la somme des degrés sera 2x le nombre de colonne de I(G), soit 2x le nombre d'arrêtes et donc sera paire.

Preuve 2 : Par récurrence sur le nombre d'arêtes. Soit G un graphe à n sommets (n >= 1) et m arêtes.  
Soit P(n) la propriété : La somme des degrés de G avec m arêtes est paire.  
P(0) est vraie car la somme des degrés est égale à 0.  
Supposons que P(n) est vraoe pour tout m <= M avec M >= 0.  
Soit G ayant m = M + 1 arêtes, G possède au moins une arête e = uv.  
G \ e possède M arêtes, la somme de ses degrés est paire.
Quand on rajoute e, si u =/ v, alors les degrés de u et v augmentent de 1. Si u = v le degré de u augmente de 2.  
Donc la somme des degrés de G est égale à celle de G \ e + 2 et donc reste paire.  
Donc par recurrence, la sommme des degrés de tout graphe est paire.
.........
Comme la somme des degrés est paire, le nombre de sommets de degré impair est forcément pair.

## Exercice 5

Preuve par contradiction : 
Soit G un graphe possédant un isthme uv.  
Supposons que G ne possède que des sommets de degré pair.  
G' = G \ uv. Soit Cu la composanteconnexe de u dans G \ uv. Comme les degrés des sommets de Cu sont les mêmes dans G et dans G' sont sont pour u, Cu a tous les sommets de degré pair.  
Soit u qui est degré impair dans G'. Comme Cu est un graphe, c'est impossible. Donc G n'existe pas.

## Exercice 6

jvois pas ptn

## Exercice 7



## Exercice 8

1. 
Dans G, comme u et v sont dans la même composante annexe, il existe une chaîne reliant u et v. Donc l'arête uv va créer un cycle constitué de cette chaîne + l'arête uv.

2. 
Soit x et y deux sommets de V(G). On va montrer que x et y sont reliés par une chaine dans G ssi ils sont une chaîne dans G'.  
a) si u et v sont reliés par une chaine dans G , ils le sont par la meme chaie dans G'.
b)  si u et v sont chaine dans G' :
    b1) ?

3. 
a.
Soit Cu et Cv les composantes connexes contenant respectivement u et v. On va montrer que dans G' = G + e (e = uv), Cu et Cv sont unifiés et les autres composantes connexes restent les mêmes.  
Soit C un composante connexe de G =/ Cu et Cv. C est connexe. Il reste à montrer que C est maximal dans G'.  
Soit s € G\C. Supposons qu'il existe une chaine reliant s à un sommet t de C. La chaine passe par l'arête uv, sinon s serait déjà dans C dans G. Donc il existe une chaîne reliant t à u ou v dans G et G'. Donc t aurait dû appartenir à Cu ou à Cv. Donc C aurait dû être unifiée dans G à Cu et Cv. Donc s et t n'existent pas et donc C reste maximale dans G'.

b.
Soit Cu U Cv. Montrons que Cu U Cv est connexe dans G.  
Soit x et y deux sommets de Cu U Cv. Si x et y € Cu et x et y € Cv, ils étaient reliés par une chaine dans G et (?). Supposons x € Cu et y € Cv. Il existe dans G (et G') une chaine Pxu reliant x à u. Il existe dans G (et G') une chaine Pvy reliant v à y. Donc dans G', si on (?) Pxu, w, Pvy, on obtient une (?) x à y. Donc Cu U Cv est connexe et est une composante connexe de G'. (?)

4. (?)

---

# TD 2 (les exos sont pas dans l'ordre de la feuille "papier")

## Exercice 1

Soit G un graphe simple à n >= 2 sommets. On veut montrer qu'il existe deux sommets de G ayant le même degré.  
Pour tout x € V(G), 0 <= degG(x) <= n - 1  
Mais les valeurs 0 et n - 1 sont incompatibles : s'il existe un sommet de degré n - 1, il est relié à tous les autres et donc la valeur 0 est impossible.  
Donc pour tout x € V(G) -> Soit 1 <= degG(x) <= n - 1  
                        -> Soit 0 <= defF(x) <= n - 2  
Donc dans les deux cas, on a n - 1 valeurs possibles pour n sommets. Donc au moins 2 d'entre eux ont le même degré.

## Exercice 2

G = (V, E) et G' = (V', E')  
ssi il existe une bijection S  
S : V -> V' telle que e = uv € E(G) <=> e' = S(u)S(v) € E(G')  
S: a -> a | b -> b | c -> d | d -> c

1. 
(imageTD2.2)

2. 
Le degré max dans un arbre à n sommets est n - 1.  
Un sommet dans un arbre ne peut etre relié à plus de n - 1 voisons (sinon il y a un cycle).  
L'étoile à n sommets atteint cette valeur.  
Un arbre possède n - 1 arêtes. Donc la somme de n degrés est 2(n - 1). Si on a 1 sommet de degré n - 1, les autres sommets sont forcément de degré 1. Donc la liste des degrés est n - 1, 1 ... 1 est le seul graphe  possible et l'étoile à n sommets.

3. 
Soit T un arbre, u et v 2 sommets de T tels que la chaine Puv reliant u et v soit de longueur max.  
u n'a pas de voison en dehors de la chaine Puv, sinon on pourrait ralonger Puv. Il n'y a pas d'autre voisin que son seul voisin dans la chaine, sinon on aurait un cycle.  
idem pour v, donc u et v sont de degré 1.  
S'il existe exactement 2 sommets de degré 1, T est une chaine et c'est la seule possibilité car on ne peut pas avoir de sommet de degré > 2.

4. 
Soit s un sommet de degré Delta. s et Delta voisin : v1 ... vDelta. SI on construit une chaine élémentaire ayant une extrémité en s et contenant vi, les successeurs de vi dans la chaine vont aller jusqu'a aboutir a un sommet de degré 1.  
Comme chacune de ces chaines ne peut contenir qu'un seul vi (sinon on aurait un cycle), on a donc au moins Delta sommets de degré 1.  
Pour avoir un nombre min de sommets de degré 1, il faut que le sommet s de degré Delta soit relié uniquement à des chaines (ex : Delta = 4)  
Donc T doit avoir une "structure" en étoile.  
Donc la solution n'est pas unique car les chaines peuvent avoir une longueur quelconque.

## Exercice 8

```
f(n) = O(g(n)) <=> il existe c > O, il existe n0 € R⁺, pour tout n >= n0, 0 <= f(n) <= cg(n)  
f(n) = (1/3)n(n + 1/2)(n + 1)  
f(n) = O(n³) ?  
f(n) = (1/3)n³ + (1/2)n² + (1/6)n  
Si on prend c = 1 et n0 = 1, on a pour tout n >= n0, 0 <= f(n) <= cn³  
n³ - f(n) = (2/3)n³ + (1/2)n² + (1/6)n 
```

1. 
f(n) = O(n¹⁰)  ->  VRAIE  
Pour tout n >= 1, (1/3)n³ + (1/2)n² + (1/6)n <= n³ <= n¹⁰

2. 
f(n) = (1/3)n³ + O(n²)  ->  (?)  
<=> (1/2)n² + (1/6)n = O(n²)

3. 
O(n²) = O(n³)  ->  VRAIE  
car pour tout n >= 0, cn² <= cn³

4. 
O(n³) = O(n²)  ->  FAUSSE  
n³ = O(n³) et n³ =/ O(n²)

5. 
(1/3)n³ + O(n²) = O(n³)  ->  VRAIE  
(?)

## Exercice 3

Liste d'adjacence :  
s1 = s4, s6  
s2 = s1, s3  
s3 = s5  
s4 = s2, s6  
s5 = s4  
s6 = s7  
s7 = s5

```
Matrice d'adjacence
   s1 s2 s3 s4 s5 s6 s7  
s1 0  0  0  1  0  1  1  
s2 1  0  1  0  0  0  0  
s3 0  0  0  0  1  0  0  
s4 0  1  0  0  0  1  0
s5 0  0  0  1  0  0  0
s6 0  0  0  0  0  0  1
s7 0  0  0  0  1  0  0
```

```
Matrice d'incidence
    s1s4 s1s6 s2s1 s2s3 s3s5 s4s2 s4s6 s5s4 s6s7 s7s5
s1   -1   -1    1    0    0    0    0    0    0    0
s2    0    0   -1   -1    0    1    0    0    0    0
s3    0    0    0    1   -1    0    0    0    0    0
s4    1    0    0    0    0   -1   -1    1    0    0
s5    0    0    0    0    1    0    0   -1    0    1
s6    0    1    0    0    0    0    1    0   -1    0
s7    0    0    0    0    0    0    0    0    1   -1
```

## Exercice 5

1. 
```c
// Ma version

bool isIsolated(int **mat, int n) {
   bool zerocount = 0;
   for (int i = 0; i < n; i++) {
      for (int j = 0; j < n; j++) {
         if (mat[i][j] == 0)
            zerocount++;
      }
      if (zerocount == n)
         return true;
   }
   return false;
}

// Version corrigée

bool isIsolated(int **mat, int n) {
   for (int i = 0; i < n; i++) {
      bool doSuccExists = false;
      for (int j = 0; j < n; j++) {
         if (mat[i][j] == 1) {
            doSuccExists = true;
            break;
         }
      }
      if (!doSuccExists)
         return true;
   }
   return false;
}
// O(n²)
```

2. 
```c
int degMax(int **mat, int n) {
   int max = 0;
   int current = 0;
   for (int i = 0; i < n; i++) {
      for (int j = 0; j < n; j++) {
         if (mat[i][j] == 1)
            current++;
      }
      if (current > max)
         max = current;
      current = 0;
   }
   return max;
}
// O(n²)
```

3. 
```c
int degMin(int **mat, int n) {
   int min = -1;
   int current = 0
   for (int i = 0; i < n; i++) {
      for (int j = 0; j < n; j++) {
         if (mat[i][j] == 1)
            current++;
      }
      if (current < min || min == -1)
         min = current;
      current = 0;
   }
   return min;
}
// O(n²)
```

## Exercice 6

1. 
```c
int degMax(int **mat, int n, int m) {
   int max = 0;
   int current = 0;
   for (int i = 0; i < n; i++) {
      for (int j = 0; j < m; j++) {
         current += mat[i][j];
      }
      if (current > max)
         max = current;
      current = 0;
   }
   return max;
}
// O(n x m)
```

2. 
```c
bool isIsolated(int **mat, int n, int m) {
   for (int i = 0; i < n; i++) {
      bool doSuccExists = false;
      for (int j = 0; j < m; j++) {
         if (mat[i][j] == 1) {
            doSuccExists = true;
            break;
         }
      }
      if (!doSuccExists)
         return true;
   }
   return false;
}
```

3. 
```c
int degMin(int **mat, int n, int m) {
   int min = -1;
   int current = 0
   for (int i = 0; i < n; i++) {
      for (int j = 0; j < m; j++) {
         current += mat[i][j];
      }
      if (current < min || min == -1)
         min = current;
      current = 0;
   }
   return min;
}
// O(n x m)
```

## Exercice 7

Besoin d'une structure pour faire en C donc photos sur tel.

1. 
```c
// A FAIRE
```

2. 
```c
// A FAIRE
```

3. 
```c
// A FAIRE
```

## Exercice 10

1. 
???

---

# TD 3

## Exercice 1

1. 
```
file : s1, s2, s3, s5, s6

    s1  s2  s3  s4  s5  s6
d  inf  0   1   1   2  inf
p  nil nil  s1  s1  s2 nil
```

2. 
```
file : s2, s1, s3, s4, s6, s5, s7

    s1  s2  s3  s4  s5  s6  s7
d   1   0   1   2   2   2   3
p   s2 nil  s2  s1  s3  s1  s6
```

## Exercice 2

```

```
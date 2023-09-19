# COURS

https://amuschol.pages.emi.u-bordeaux.fr/mpc

uiuiuiiiiiiiiiiiii

## Expressions rationnelles : exemples (4)

- Mots sur l'alphabet {0, 1} qui ne contiennent ni 00, ni 11 :
  - `(01)*(0 + E) + (10)*(1 + E)`

## Expressions rationnelles : exemples (5)

- Représentations des nombres en base 10 divisibles par 3
  - `ok.`

## Les automates finis

### Automates : un exemple

0, 1, 2 -> états

### Automates : définition

```
A = {a, b}
Q = {0, 1, 2}
S = {(0, a, 1), (1, b, 1), (1, b, 2), (2, a, 0), (2, b, 0)}
S <= Q x A x Q
I = {0}
F = {2}
```

### Fonctionnement d'un automate

Calculs sur aba : `0 -(a)> 1 -(b)> 2 -(a)> 0`   pas accepté  
abc pas accepté : `0 -(a)> 1 -(b)> 1`  
ab est accepté : `0 -(a)> 1 -(b)> 2`  
abb est accepté

Mot :
- accepté -> s'il existe un calcul acceptant
- rejeté -> si TOUS les calculs sont rejetants

### Langage d'un automate

```
L(A) = {w € A* | il existe un calcul acceptant de A sur w}
     = {w € A* | il existe p -(w)> q, p € I, q € F}
```

### Automates : complet, déterministe

```
Q' := Q U {d}
F' := F
S' = S U {(q, a, d) | J ne contient pas (q, a, *)}
```

(image1)

### Automates : exemples (1)

- Ensembles des mots sur {a, b} qui commencent par un a
  - `a(a + b)*` (image2)

- Ensemble des mots sur {a, b} qui contiennent aba
  - `(a + b)*aba(a + b)*`   (image3)
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
    b1) 
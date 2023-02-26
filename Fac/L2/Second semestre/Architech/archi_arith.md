Université de Bordeaux - Licence STS

Architecture des ordinateurs (4TIN304U)

Codage binaire et hexadécimal - Arithmétique des processeurs

Ce document est copiable et distribuable librement et gratuitement à la condition expresse que son contenu ne soit
modifié en aucune façon, et en particulier que le nom de son auteur et de son institution d'origine continuent à y
figurer, de même que le présent texte.

(c) 2014,2020 F. Pellegrini
___

# Notation positionnelle (1)

- La notation positionnelle représente un nombre sous la forme d'une
  séquence de chiffres
    - Chaque chiffre représente le multiple d'une puissance d'un nombre
      appelé base
    - Les puissances croissent à partir de zéro, de la droite vers la
      gauche
- Nous utilisons couramment la base 10, avec les chiffres de `0` à `9`  
  123 = 1 × 10^2 + 2 × 10^1 + 3 × 10^0

# Notation positionnelle (2)

- La notation positionnelle présente de nombreux avantages :
    - Utilise toujours les mêmes chiffres
        - À la différence de l'écriture en chiffres romains :
          I = 1, V = 5, X = 10, L = 50, C = 100, D = 500,
          M = 1000, ...
    - Permet d'écrire facilement de très grands nombres

# Notation binaire (1)

- Les ordinateurs encodent l’information en utilisant les états de
  systèmes physiques 
- Les systèmes physiques les plus simples possèdent deux états :
    - Tension électrique / pas de tension
    - Orientation nord ou sud d’un aimant
    - Etc.
- La notation binaire est naturelle pour représenter les états de la
  mémoire d'un ordinateur

# Notation binaire (2)

- La notation binaire utilise la base 2 et les chiffres `0` et `1`  
  101011 = 1 × 2^5 + 0 × 2^4 + 1 × 2^3 + 0 × 2^2 + 1 × 2^1 + 1 × 2^0
- Pour lever toute ambigüité , on indique parfois la base (en décimal)
  à la fin d'un nombre

    101011_{2} != 101011_{10}  
    101011_{2}  = 43_{10}

# Numération en binaire (1)

- En binaire, on compte comme dans toute autre base
- Lorsque, dans une colonne, on est arrivé au plus grand chiffre :
    - On remet la colonne à zéro
    - On incrémente la puissance supérieure

    0 + 0 =  0  
    0 + 1 =  1  
    1 + 0 =  1  
    1 + 1 = 10

# Numération en binaire (2)

- On énumère les nombres binaires en appliquant ce principe, en
  partant de 0 :

       0  
       1  
      10  
      11  
     100  
     101  
     110  
     111  
    1000  
    1001  
    1010  
    1011  
    1100  
    1101  
    1110  
    1111  
    etc.

# Notation hexadécimale (1)

- La notation binaire est fastidieuse !
    - Même les nombres les plus courants peuvent être longs à écrire
- Il faut trouver une notation plus économe en place

# Notation hexadécimale (2)

- Il faut trouver une base qui :
    - Se convertisse facilement en une écriture binaire
        - Donc une puissance de 2
    - Soit plus grande que 2, mais pas trop grande
        - Retenir 32 chiffres ou plus serait plutôt pénible...
    - Permette d'écrire facilement des octets
        - Donc dont le log2 soit un diviseur de 8 : base 4 ou 16
- Choix : base 16, ou "codage hexadécimal"  
  16 = 2^4 , log2 (16) = 4 = 8 / 2
  On peut coder un octet pile avec deux chiffres hexadécimaux.
- Si on avait choisi la base octale :  
  8 = 2^3  
  log_2(8) = 3

  Pour coder un octet, il faudrait utiliser trois chiffres octaux,
  dont celui le plus à gauche serait mal utilisé, puisque seuls ses
  deux bits de poids le plus faible seraient significatifs, celui de
  poids fort étant toujours à zéro. Ce serait un gaspillage
  d'information.

  Si on représente les 8 positions binaires par puissances de 2 allant
  de 0 à 7, codant trois chiffres octaux A (poids faible), B (poids
  moyen) et C (poids fort) :

    . 7 6 5 4 3 2 1 0
    0 C C B B B A A A

# Notation hexadécimale (3)

- Les chiffres hexadécimaux vont de `0` à `9`, puis de `A` à `F` :

    0000  0  
    0001  1  
    0010  2  
    0011  3  
    0100  4  
    0101  5  
    0110  6  
    0111  7  
    1000  8  
    1001  9  
    1010  A (10)  
    1011  B (11)  
    1100  C (12)  
    1101  D (13)  
    1110  E (14)  
    1111  F (15)
  
  B0A_{16} = 11 × 16^2 + 0 × 16^1 + 10 × 16^0 = 2826_{10}

- Dans de nombreux langages, on préfixe les nombres hexadécimaux par
  "`0x...`" ou "`0X...`"

# Arithmétique entière (1)

- Avec n bits, on dispose de 2^n combinaisons possibles, qui permettent
  de représenter les nombres entiers naturels de 0 à (2^n)–1
- Les règles classiques de l'addition s'appliquent

- Exemple d'une addition binaire : 53 + 148 = 201

       00110101 ( 53)  
    +  10010100 (148)  
    =  11001001 (201)

# Arithmétique entière (2)

- Pour représenter des nombres négatifs, on peut transformer le bit de
  poids le plus fort en bit de signe, pour coder 2^(n-1) nombres
  entiers positifs et 2^(n-1) nombres entiers négatifs.

- Lorsque le bit de signe est à 0, on considère que le nombre est
  positif, et on code les entiers naturels de 0 à (2^(n-1))–1.
    - On code de 0 à 2^(n-1)-1 car on commence à coder à partir de 0

- Bit de signe : le bit de poids le plus fort
    - 0 : positif (ou nul)
    - 1 : négatif (à voir si nul aussi)

- Nombres positifs représentatifs sur un entier signé :

    00000000 (  0)  
    00000001 (  1)  
    01111111 (127)

# Arithmétique entière (3)

- Lorsque le bit de signe est à 1, on considère que le nombre est
  négatif
- Plusieurs moyens sont envisageables pour coder les entiers négatifs
  avec les (n-1) bits restants

# Arithmétique entière (4)

- Codage des nombres négatifs au format naturel : on utilise le même
  codage des n-1 bits restants que pour les nombres positifs.

    10000000 (-0)  
    10000001 (-1)

- Problèmes :
    - On a deux zéros (gaspillage d'une configuration)

    00000000 (+0)  
    10000000 (-0)

    - Nécessité d'un circuit spécifique pour la soustraction

# Arithmétique entière (5)

- Pour éviter les problèmes du codage précédent, il faut un codage des
  nombres négatifs tel que :
    - Le bit de signe soit à 1
    - Il n'y ait qu'un seul zéro
    - On puisse utiliser la méthode d'addition standard pour additionner
      nombres positifs et négatifs

# Arithmétique entière (6)

- En particulier, avec les contraintes précédentes, on veut :

       00000001 (   1)  
    +  1....... (-  1)  
    =  00000000

- La seule solution possible est donc :

       00000001 (   1)  
    +  11111111 (-  1)  
    = 100000000

  qui génère une retenue en sortie ("carry"), perdue car elle ne peut
  pas être stockée

# Arithmétique entière (7)

- Pour représenter l'opposé d'un nombre entier, on prend son
  complément bit à bit, auquel on ajoute 1
- Cette notation est appelée "complément à deux"

       00000101 (   5)  
       11111010 (complément bit à bit de 5)  
    +1 11111011 (-  5)

# Arithmétique entière (8)

- Ajouter un nombre à son opposé en complément à deux donne toujours
  zéro car :
    - Ajouter un nombre à son complément bit à bit donne toujours un
      vecteur constitué uniquement de 1
    - Ajouter 1 à ce vecteur donne un vecteur constitué uniquement de 0,
      après perte de la retenue
    - x + (~(x) + 1) = (x + ~x) + 1 = -1 + 1 = 0

       00000101 (   5)  
    +  11111011 (-  5)  
    = 100000000 (   0)

# Arithmétique entière (9)

- Ce principe s'étend à toute addition entre entiers signés
- Par exemple, pour 46 + (-53) = -7

       00101110 (  46)  
    +  11001011 (- 53)  
    =  11111001 (-  7)

# Arithmétique entière (10)

- Principales valeurs en complément à deux pour un nombre binaire sur
  8 bits :

    00000000 (   0)  
    00000001 (   1)  
    11111111 (-  1)  
    01111111 ( 127)  
    10000000 (-128)

Le domaine de validité d'un nombre entier signé sur n bits est donc :
[-2^(n-1);2^(n-1)-1]. Pour 8 bits, il va bien de -128 à +127.

# Arithmétique entière (11)

- Les nombres non signés sont organisés de façon croissante en deux
  sous-blocs considérés de façon non signée.
- Par exemple, sur 16 bits :
  8000 < FFFF < 0000 < 7FFF

# Arithmétique entière (12)

- Il y a débordement arithmétique ("overflow") lorsque le résultat
  attendu n'est pas représentable dans le système choisi.

       01101110 ( 110)  
    +  00101011 (  43)  
    =  10011001 (-103) et non (+153), supérieur à (+127)

- Il peut y avoir débordement sans perte de retenue, ou perte de
  retenue sans débordement

# Arithmétique flottante

Masse de l'électron : 9*10^(28) grammes.
Masse du soleil : 2*10^(33) grammes.
Le domaine dépasse les 10^(60).

n = f * 10^e

3.14 = 0.314 * 10^1 = 3.140 * 10^0

0.00001 = 0.01 * 10^(-3) = 1.000 * 10^(-5)

La forme normaliéee maximise l'utilisation des chiffres significatifs
de la mantisse, et donc la précision

- f = 0 et l'exposant n'importe pas, ou
- f appartient à [1.0 ; 10.0 [  (intervalle fermé-ouvert)

## Norme IEEE 754

Utilise la base 2 pour les mantisses :

f = [2^0].[2^(-1)] [2^(-2)] [2^(-3)] ...

Les nombres commencent par un bit de signe.

Les exposants sont codés par excès :
- 127 pour la simple précision
- 1023 pour la double précision.

Les valeurs minimum (0) et maximum (255 ou 2047) sont réservées pour
des usages spéciaux.

Simple précision (32 bits) :
- 1 bit de signe
- 8 bits pour l'exposant
- 23 bits pour la mantisse :

SEEEEEEEEMMMMMMMMMMMMMMMMMMMMMMM

Double précision (64 bits) :
- 1 bit de signe
- 11 bits pour l'exposant
- 52 bits pour la mantisse :

SEEEEEEEEEEEMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMM

Une mantisse normalisée est dans [1;2[ (ouvert-fermé)

Comme le chiffre de tête doit toujours être 1, on n'a pas besoin de le
stocker : on gagne 1 bit

Représentation IEEE 754 simple précision du nombre 0.75 :
- 0.75 = 1/2 + 1/4
- 0.75_(10) = 1.1_(2) * 2^(-1)
- Le significande est donc : .10000...0_(2)
- L'exposant par excès est donc : -1 + 126 = 126_(10) = 01111110_(2)
- Le codage du nombre sur 32 bits est donc :

  0 01111110 10000000000000000000000_(2)

  3F400000_(16)

Simple précision : domaine de environ 10^(-38) à 10^(+38)
Double présision : domaine de environ 10^(-308) à 10^(+308)

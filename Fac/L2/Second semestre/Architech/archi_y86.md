# y86 (1)

Environnement pédagogique d'apprentissage :

- De la programmation en langage machine
- De l'impact de l'architecture des processeurs sur l'efficacité d'un programme

Créé par R. E. Bryant et D. R. O'Hallaron dans le cadre de leur livre CS:APP

- Librement téléchargeable (mais pas libre !)

[http://csapp.cs.cmu.edu/](http://csapp.cs.cmu.edu/)

# y86 (2)

Architecture inspirée des processeurs Intel « x86 » (architecture IA32)

- Jeu d'instructions simplifié
- Syntaxe quelque peu modifiée

Architecture évolutive

# Outils disponibles (1)

Assembleur générant un pseudo-code objet exécutable : "yas"

Interpréteur permettant d'exécuter au niveau de la couche ISA le code objet produit par "yas" : "yis"

Simulateurs programmables d'architecture de processeur : "ssim", "ssim+" et "psim"

- Modifiables par l'utilisateur (en langage HCL)

# Outils disponibles (2)

Chaîne logicielle « historique » :

"Fichier source .ys" -> Assemblage -> Fichier binaire .yo"

Exécution par les différents interpréteurs / simulateurs d'architectures :
.yo -> yis
.yo -> ssim
.yo -> ssim+
.yo -> psim


# Outils disponibles (3)

De nombreux outils web ont également été créés par des tiers

- Mis en œuvre à l’université de Bordeaux


# Jeu d'instructions

Le jeu d'instructions du processeur y86 permet d'effectuer :

- Des mouvements de données entre mémoire et registres
- Des opérations arithmétiques et logiques
- Des branchements
- Exécution conditionnelle ou répétitive
- Des appels et retours de sous-programmes
- Des manipulations de pile


# Adressage mémoire (1)

Les mémoires informatiques sont organisées comme un ensemble de cellules pouvant chacune stocker une valeur numérique

Toutes les cellules d'une mémoire contiennent le même nombre de bits

- Par exemple, les "octets" sont des cellules à 8 bits
- Le terme anglais "byte" est plus généraliste
- Une cellule de n bits peut stocker 2^n valeurs numériques différentes


# Adressage mémoire (2)

La cellule est la plus petite unité mémoire pouvant être adressée

- Chaque cellule est identifiée par un numéro unique, appelé adresse, auquel les programmes peuvent se référer

Afin d'être plus efficaces, les unités de traitement ne manipulent plus des octets individuels mais des mots de plusieurs octets

- 4 octets par mot pour une architecture 32 bits
- 8 octets par mot pour une architecture 64 bits


# Adressage mémoire (3)

Les ordinateurs, basés sur le système binaire, représentent également les adresses sous forme binaire
Une adresse sur m bits peut adresser 2^m cellules distinctes, indépendamment du nombre de bits n contenus dans chaque cellule

- Capacité totale de la mémoire : 2^{m+n} bits


# Adressage mémoire (4)

Dans quel ordre stocker les octets, par adresse croissante ?

Exemple d'un mot de 4 octets : HhlL

Big endian : poids fort en premier, des octets d'adresse a à (a+3)

    [H] [h] [l] [L]

Little endian_: poids faible en premier, des octets d'adresse a à (a+3)

    [L] [l] [h] [H]


# Adressage mémoire y86

L'architecture y86 considère la mémoire comme un espace linéaire et continu d'octets

- Cet espace commence à partir de l'adresse 0 et s'arrête à la plus grande adresse non signée représentable sur un mot machine

Les mots machine, sur 32 bits, y sont stockés avec leur poids faible en premier

- Stockage "little endian", ou "petit-boutiste"

Par convention, les programmes débutent leur exécution à l'adresse 0


# Registres

Les registres sont des circuits du processeur capables de mémoriser des mots machine

Ils sont localisés au plus près de l'UAL, afin que les calculs puissent être effectués le plus rapidement possible

Les registres sont identifiés par un nom et/ou un numéro

L'ensemble des registres et de la mémoire représente l'état du processeur

# Registres y86 (3)

Représentation effective sur 4 bits et hexadécimale :

    000 0 eax
    001 1 ecx
    010 2 edx
    011 3 ebx
    100 4 esp
    101 5 ebp
    110 6 esi
    111 7 edi

Instruction : addl rA, rB

    [60] [rA rB]

Instruction : addl %eax, %ebp

    [60] [05]


# Traductions successives

Code C :

    int c = a + b;

Code assembleur :

         mrmovl   4(%esp),%eax
         mrmovl   8(%esp),%ebx
         addl     %ebx,%eax


Correspond à :

    register int eax = a;
    eax += b;

Opérandes :

- a : mémoire, à l'adresse (%esp + 4)
- b : mémoire, à l'adresse (%esp + 8)
- c : registre %eax (variable temporaire ?)

Résultat dans %eax

Code binaire (hexadécimal) :

    50 04 04 00 00 00
    50 34 08 00 00 00
    60 30


# Exemple : programme somme

Calcul de : c = a + b

    0x000:              |          .pos 0
    0x000: 500864000000 | prog:    mrmovl a,%eax
    0x006: 503868000000 |          mrmovl b,%ebx
    0x00c: 6030         |          addl   %ebx,%eax
    0x00e: 40086c000000 |          rmmovl %eax,c
    0x014: 10           |          halt
                        |
                        | # Donnees
    0x064:              |          .pos 100
    0x064: 02000000     | a:       .long 2
    0x068: 03000000     | b:       .long 3
    0x06c: 00000000     | c:       .long 0


# Mouvement de données en y86 (4)

    rrmovl rA,rB
    Reg[rB] = Reg[rA]
    [20] [rA rB]

    irmovl V,rB
    Reg[rB] = V
    [30] [8 rB] [VL] [Vl] [Vh] [VH]

    rmmovl rA,D(rB)
    Mem[Reg[rB] + D] = Reg[rA]
    [40] [rA rB] [DL] [Dl] [Dh] [DH]

    mrmovl D(rB),rA
    Reg[rA] = Mem[Reg[rB] + D]
    [50] [rA rB] [DL] [Dl] [Dh] [DH]


# Opérations arithmétiques en y86 (1)

Codage des instructions arithmétiques :

    (op)l rA,rB
    Reg[rB] op= Reg[rA]
    [6 op] [rA rB]

Codes d'opération :

- 0 : addl
- 1 : subl
- 2 : andl
- 3 : xorl


# Opérations arithmétiques en y86 (2)

Opérations avec des valeurs immédiates :

    i(op)l V,rB
    Reg[rB] op= V
    [6 op] [8 rB] [VL] [Vl] [Vh] [VH]


# Branchements en y86 (2)

    jmp D
    PC = D
    [70] [DL] [Dl] [Dh] [DH]

j(op) D
PC = D si condition vérifiée
[70] [DL] [Dl] [Dh] [DH]

Codes conditionnels j(op) :

- 0  mp
- 1  le
- 2  l
- 3  e
- 4  ne
- 5  ge
- 6  g


# Branchements en y86 (3)

Évaluation des codes de condition :

- jle : (rA <= rB) : (S^O == 1) ou (Z== 1)
- jl : (rA  < rB) : (S^O == 1)
- je : (rA == rB) : (Z == 1) 
- jne : (rA != rB) : (Z == 0)
- jge : (rA >= rB) : (S^O == O) ou (Z == 1)
- jg  : (rA  > rB) : (S^O == 0)


# Branchements en y86 (4)

Réalisation de tests if ... then ... :

    if (eax != 0) {
      ...1
    }
    ...2

              andl     %eax,%eax
              je       apres
              ...1
    apres:    ...2


# Branchements en y86 (5)

Réalisation de tests if ... then ... else ... :

    if (eax != 0) {
      ...1
    }
    else {
      ...2
    }
    ...3

              andl     %eax,%eax
              je       else
              ...1
              jmp apres
    else:     ...2
    apres:    ...3


# Branchements en y86 (5)

Réalisation de boucles :

    while (eax -- > 0) {
      ...1
    }
    ...2

    boucle:   isubl    1,%eax
              jl       fin
              ...1
              jmp      boucle
    fin:      ...2

Transformation du test (eax -- > 0) en (-- eax >= 0).


# Manipulation de tableaux (1)

    for (i = 4; i < n; i ++)
      t[i] = t[i % 4];


# Manipulation de tableaux (2)

Une case mémoire peut être considérée comme la cellule d'un tableau ou
bien être accédée par déréférencement d'un pointeur :

    for (i = 0; i < 10; i ++)
      t[i] = i;

    for (p = t, i = 0; i < 10; p ++, i ++)
      *p = i;


# Manipulation de tableaux (3)

Avec un pointeur, on utilise l'adressage indirect par registre pour
accéder à la case courante :

    for (eax = 0, ecx = 10, ebx = t;
         -- ecx >= 0;
         eax ++, (byte *) ebx += 4)
      *ebx = eax;

              irmovl   t,%ebx
              irmovl   10,%ecx
              xorl     %eax,%eax
    boucle:   isubl    1,%ecx
              jl       fin
              rmmovl   %eax,(%ebx)
              iaddl    4,%ebx
              iaddl    1,%eax
              jmp      boucle
    fin:      halt
              .align 4
    t:        .long 0


# Manipulation de tableaux (4)

&t[i] peut se calculer comme : t + (i * sizeof (int))

    for (eax = 0, ecx = 10, ebx = 0;
         -- ecx >= 0;
         eax ++, ebx += 4 /* octets */)
      t[ebx] = eax;

              irmovl   10,%ecx
              xorl     %eax,%eax
              xorl     %ebx,%ebx
    boucle:   isubl    1,%ecx
              jl       fin
              rmmovl   %eax,t(%ebx)
              iaddl    4,%ebx
              iaddl    1,%eax
              jmp      boucle
    fin:      halt
              .align 4
    t:        .long 0


# Appel de procédures (2)

    main :  code1a
            appel codeA
    ret1:   code1b
            ...
            code2a
            appel codeA
    ret2:   code2b

    codeA :  ...
             jmp ???

Comment A peut-elle savoir où revenir pour reprendre l'exécution du
code principal ? Il faut aller à ret1 la première fois et à ret2 la
suivante.

# Appel de procédures (2)

Avec une variable globale pour la procédure codeA :

    vretA : .long

    main :
            code1a
            vretA = ret1
            appel codeA
    ret1:   code1b
            ...
            code2a
            vretA = ret2
            appel codeA
    ret2:   code2b

    codeA :
            ...
            jmp vretA

Cela marche pour les appels simples, mais si codeA est une fonction
récursive, cela ne marche plus : la dernière valeur de retour écrase
les précédentes. On ne saura plus où revenir.


# Appel de procédures (5)

La pile est une zone mémoire réservée à l'appel de fonctions.
Le pointeur de pile marque la position du "sommet" de la pile.
Il pointe sur la dernière case utilisée (et non la première case
vide).
Tout ce qui se trouve au delà du sommet de pile ne doit pas être
accédé. C'est une erreur de le faire.

On dessinera la pile de façon horizontale, en empilant de gauche à
droite, avec le pointeur de pile représenté par un "|".
Notre modèle est une pile descendante : le pointeur de pile part des
adresses hautes pour décroitre vers les adresses basses lorsqu'on
empile des valeurs.

    FFFF [...] [...] [...] | <contenu invalide> ... 0000


# Appel de procédures (6)

On ne peut manipuler la pile que si l'on a défini son emplacement au
préalable. Il faut réserver une zone mémoire dédiée, qui doit être de
taille suffisante pour éviter d'écraser les zones de code et de
données. On la mettra donc "loin" dans la mémoire.
L'initialisation du pointeur de pile se fait au début du programme.
En faire la première instruction du programme, pour être sûr de ne pas
oublier.

           .pos 0
           irmovl  pile,%esp
           ...

           .pos    0x200
    pile:  .long   0


# Appel de procédures (7)

Instruction "call addr" : empile l'adresse située après l'instruction,
aussi appelée "adresse de retour".

Séquence d'actions :

- Le pointeur de pile est décrémenté
- Le compteur ordinal est écrit à cette adresse
- Place dans le compteur ordinal l'adresse d'appel
- Effectue un jmp à cette adresse 

Exemple de code :

    a:    call   func
    b:    ...

    func: ...

État avant :

    PC = a
    [...] |

État après :

    PC = func
    [...] [b] |


# Appel de procédures (8)

Instruction "ret" : dépile l'adresse située en sommet de pile.

Séquence d'actions :

- Lit la valeur contenue à l'adresse du sommet de pile
- Incrémente le pointeur de pile
- Place dans le compteur ordinal l'adresse obtenue
- Effectue un jmp à cette adresse 

    a:    call   func
    b:    ...

    func: ...
          ...
    c:    ret

État avant :

    PC = c
    [...] [b] |

État après :

    PC = b
    [...] |


# Appel de procédures (9)

On peut passer des paramètres à la fonction appelée en positionnant
les valeurs des registres utilisés par cette fonction.

              .pos 0
              irmovl  pile,%esp
              mrmovl  a,%ebx
              mrmovl  b,%ecx
              call    mult
              rmmovl  %eax,c
              halt

    mult:     xorl    %eax,%eax
    multbcl:  andl    %ebx,%ebx
              je      multfin
              addl    %ecx,%eax
              isubl   1,%ebx
              jmp     multbcl
    multfin:  ret

              .pos    0x100
    a:        .long 3
    b:        .long 5
    c:        .long 0

              .pos    0x200
    pile:     .long   0

On peut noter que l'écriture de la fonction "mult" peut être
optimisée. Par exemple, l'étiquette "multbcl" peut être descendue
d'une instruction, puisque le "isubl 1,%ebx" modifie également
les drapeaux de conditions nécessaire à l'évaluation du branchement
par l'instruction "je". On a donc 5 instructions par tour de boucle au
lieu de 6 :

    mult:     xorl    %eax,%eax
              andl    %ebx,%ebx
    multbcl:  je      multfin
              addl    %ecx,%eax
              isubl   1,%ebx
              jmp     multbcl
    multfin:  ret

On peut encore optimiser ce code, en évitant de brancher sur un
branchement. Dans ce cas, on transforme le branchement inconditionnel
en branchement conditionnel :

    mult:     xorl    %eax,%eax
              andl    %ebx,%ebx
              je      multfin
    multbcl:  addl    %ecx,%eax
              isubl   1,%ebx
              jne     multbcl
    multfin:  ret

On n'a alors que trois instructions par cycle.


# Sauvegarde de variables (2)

Instruction "pushl reg" : empile la valeur contenue dans le registre.
Le pointeur de pile est décrémenté.

          irmovl 42,%eax
          pushl  %eax

État avant :

    eax = 42
    [...] |

État après :

    eax = 42
    [...] [42] |


# Sauvegarde de variables (3)

Instruction "popl reg" : dépile et place dans le registre la valeur
située en sommet de pile.
Séquence d'actions :

- Lit la valeur contenue à l'adresse du sommet de pile
- Incrémente le pointeur de pile

          popl   %eax

État avant :

    eax = ...
    [...] [42] |

État après :

    eax = 42
    [...] |


# Sauvegarde de variables (4)

On dépile habituellement dans l'ordre inverse de celui dans lequel on
a empilé.

          pushl   %ebx
          pushl   %esi
          pushl   %edi
          ...
          popl    %edi
          popl    %esi
          popl    %ebx

Inverser les dépilages permet de réaliser des échanges de valeurs
entre registres ("swap").

          pushl   %eax
          pushl   %ebx
          popl    %eax
          popl    %ebx

État avant :

    eax = 13
    ebx = 42
    [...] |

État après les deux "pushl" :

    eax = 13
    ebx = 42
    [...] [13] [42] |

État après :

    eax = 42
    ebx = 13
    [...] |

Noter que cette solution n'est pas optimale, car il est possible de
réaliser un échange avec juste un registre supplémentaire ou, avec la
pile, un seul empilage/dépilage :

          rrmovl  %ebx,%ecx
          rrmovl  %eax,%ebx
          rrmovl  %ecx,%eax

ou :

          pushl   %eax
          rrmovl  %ebx,%eax
          popl    %ebx


# Passage de paramètres (2)

Avant d'appeler la fonction, l'appelant empile les paramètres dans
l'ordre inverse duquel ils sont nommés. Le dernier est empilé en
premier, et ainsi de suite...

Code C :

    f (a, 12, b);

Code y86 :

          mrmovl b,%eax
          pushl  %eax
          irmovl 12,%eax
          pushl  %eax
          mrmovl a,%eax
          pushl  %eax
          call   f
    aret: ...

    f:    ...

État avant :

    [...] |

État après :

    [...] [b] [12] [a] [aret] |


# Passage de paramètres (3)

La fonction appelée peut récupérer les paramètres en les lisant en
mémoire par rapport à la position du sommet de pile.
Elle peut les lire autant de fois que nécessaire.
Elle peut les modifier (comme les paramètres en C).

    f:    mrmovl 4(%esp),%eax
          mrmovl 8(%esp),%edx
          mrmovl 12(%esp),%ecx
          ...
          ret

Structure de la pile (représentée de façon verticale pour une fois) et
adresses relatives des cases par rapport à %esp :

    [aret] %esp
    [a]    %esp+4
    [12]   %esp+8
    [b]    %esp+12
    [...]


# Passage de paramètres (4)

Une fois revenu de la fonction, l'appelant doit vider la pile des
paramètres qu'il y a placés.
Seul l'appelant sait combien de paramètres il a mis.
On n'a pas besoin de dépiler les valeurs, juste de remettre la pile
dans l'état antérieur. Une modification de la valeur de SP suffit.

          mrmovl b,%eax
          pushl  %eax
          irmovl 12,%eax
          pushl  %eax
          mrmovl a,%eax
          pushl  %eax
          call   f
          iaddl  12,%esp

État avant :

    [...] |

État au moment du "call" :

    [...] [b] [12] [a] [aret] |

État après :

    [...] |


# Passage de paramètres (5)

Le passage des paramètres dans l'ordre inverse permet de mettre en
œuvre des fonctions à nombre d'arguments variables.
On sait toujours où se trouve le premier paramètre.

Code C :

      somme (2, 12, 0);
      somme (13, 4, 3, 0);

Code y86 :

            irmovl 0,%eax
            pushl  %eax
            irmovl 12,%eax
            pushl  %eax
            irmovl 2,%eax
            pushl  %eax
            call   somme
            iaddl  12,%esp

            ...

    somme:  rrmovl %esp,%edx
            xorl   %eax,%eax
    boucle: iaddl  4,%edx
            mrmovl (%edx),%ecx
            andl   %ecx,%ecx
            je     fin
            addl   %ecx,%eax
            jmp    boucle
    fin:    ret

État au moment du "call" :

    [...] [0] [12] [2] |
    [...] [0] [3] [4] [13] |


# Variables locales (2)

C'est à la fonction appelée de gérer ses variables locales.
Elles doivent donc être situées dans la pile au-dessus des paramètres
et de l'adresse de retour placés par la fonction appelante.
Attention : quand on déplace SP, on modifie l'accès aux paramètres !

    int
    f (int a, int b)
    {
      int     i;
      ...

État après réservation des variables locales :

    [...] [b] [a] [aret] [i] |


# Variables locales (3)

Mieux vaut réserver l'ensemble de l'espace nécessaire dès l'entrée
dans la procédure.

Code C :

    int
    f (int a, int b)
    {
      int     i, j;
      i = a + b;
      ...

Code y86 :

    f:    isubl  8,%esp
          mrmovl 12(%esp),%eax
          mrmovl 16(%esp),%edx
          addl   %eax,%edx
          rmmovl %edx,4(%esp)
          ...
          iaddl  8,%esp
          ret

Structure de la pile (représentée de façon verticale pour une fois) et
adresses relatives des cases par rapport à %esp après réservation des
variables locales :

    [j]    %esp
    [i]    %esp+4
    [aret] %esp+8
    [a]    %esp+12
    [b]    %esp+16
    [...]


# Branchement à adresse variable (2)

On peut cependant émuler un branchement à l'adresse contenue dans un
registre en utilisant les branchements par la pile.

           irmovl b,%eax
    a:     pushl  %eax
    c:     ret

    b:     ...

État avant :

    PC = a
    eax = b
    [...] |

État après le "pushl" :

    PC = c
    [...] [b] |

État après :

    PC = b
    [...] |


# Branchement à adresse variable (3)

Pour mettre en œuvre un pointeur de fonction, il faut faire un "call",
pas un "jmp". Il faut donc arriver à placer l'adresse de retour dans
la pile.

           irmovl b,%eax
           call   fcall
    a:     ...

    fcall: pushl  %eax
    c:     ret

    b:     ...
           ret

État avant :

    [...] |

État après le "pushl" dans fcall :

    PC = c
    eax = b
    [a] [b] |

État après le "ret" dans fcall :

    PC = b
    eax = b
    [...] [a] |

On est dans la bonne configuration de pile pour revenir au point "a:"
lors du "ret" de la fonction "b".

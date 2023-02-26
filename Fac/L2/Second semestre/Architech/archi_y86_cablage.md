## Modélisation du câblage du y86

L'environnement pédagogique y86 couvre aussi le câblage du processeur
y86 lui-même.
Câblage modélisé par un langage dédié : HCL ("Hardware Control
Language")
- Simplification de langages tels que Verilog et VHDL
Compilation du HCL en C et intégration du code produit au sein de
l'émulateur y86.
Permet de mettre en œuvre plusieurs câblages du même jeu
d'instructions.


##  Utilisation de HCL

Outils disponibles :
emacs -> fichier x.hcl
x.hcl -> hcl2c -> x.c
(x.c + tty.a) -> gcc -> xsim


## Syntaxe HCL (1)

HCL permet de représenter le câblage des blocs fonctionnels du
processeur y86
- Syntaxe proche du langage C
Types de données supportés :
- Booléens : type "bool"
  - Signaux pilotant le fonctionnement des unités fonctionnelles du
    processeur
- Valeurs entières (au plus 32 bits) : type "int"
  - Servent à coder les opérandes, adresses, etc.


## Syntaxe HCL (2)

Opérations supportées :
- Fonctions logiques sur des valeurs booléennes
- Fonctions logiques sur des valeurs entières
Certains blocs fonctionnels ne font pas partie du périmètre du
langage (pas de valeur ajoutée pédagogique) :
- Banque multi-ports des registres ("register file")
- Mémoire centrale (instructions et données)
- UAL


## Syntaxe HCL (3)

Fonctions logiques sur des valeurs booléennes retournant un booléen :

Test d'égalité : codage de NOT (XOR (a, a))
bool eq = (a && b) || (!a && !b);

Multiplexeur à un bit :
bool out = (s && a) || (!s && b);


## Syntaxe HCL (4)

Fonctions logiques sur des valeurs entières retournant un booléen :

bool eq = (A == B);

Les autres opérateurs utilisables sont :  <, <=, >, >=, !=

Permettent d'exprimer simplement les "blocs de base" que sont les
comparateurs de la taille d'un mot.


## Syntaxe HCL (5)

bool s1 = (code == 2) || (code == 3); # Au cas par cas
bool s0 = (code == 1) || (code == 3);
bool s1 = code in { 2, 3 };	# Notation ensembliste
bool s0 = code in { 1, 3 };


## Syntaxe HCL (6)

Fonctions logiques retournant des mots :
int out = [     # Multiplexeur
 s : A;         # La valeur de sortie est la première
 1 : B;	        # valeur dont l'étiquette soit vraie
];


## Syntaxe HCL (7)

int mult4 = [           # Un multiplexeur multiplexe...
 !s1 && !s0 : A;        # 00
 !s1 :        B;        # 01
 !s0 :        C;        # 10
 1 :          D;        # 11
];

int min3 = [	        # Toute fonction peut s'exprimer
 A <= B && A <= C : A;	# sous la forme d'un multiplexeur
 B <= A && B <= C : B;
 1 : C
];


## Rappels sur l'ISA du y86 (1)

Instruction code : 1 octet. Sa valeur détermine la taille de
l'instruction. Décomposé en deux demi-octets "icode" et "ifun".
Registres : 1 octet optionnel contenant deux numéros de registres
"rA" et "rB".
Valeur immédiate : 4 octets optionnels, en "little endian", formant la
valeur constante "valC".

[icode ifun] [rA rB] [VL] [Vl] [Vh] [VH]


## Rappels sur l'ISA du y86 (2)

[0 0] : nop
[1 0] : halt
[2 0] [rA rB] : rrmovl rA, rB
[3 0] [8 rB] [VL] [Vl] [Vh] [VH] : irmovl V,rB
[4 0] [rA rB] [DL] [Dl] [Dh] [DH] : rmmovl rA,D(rB)
[5 0] [rA rB] [DL] [Dl] [Dh] [DH] : mrmovl D(rB),rA
[6 ifun] [rA rB] : opl rA, rB
[7 ifun] [DL] [Dl] [Dh] [DH] : jxx D
[8 0] [DL] [Dl] [Dh] [DH] : call D
[9 0] : ret
[A 0] [rA 8] : pushl rA
[B 0] [rA 8] : popl rA

Pour op = 6 :
[6 0] : addl
[6 1] : subl
[6 2] : andl
[6 3] : xorl

Pour op = 7 :
[7 0] : jmp
[7 1] : jle
[7 2] : jl
[7 3] : je
[7 4] : jne
[7 5] : jge
[7 6] : jg


## Structure du y86-seq (1)
## Structure du y86-seq (2)

L'exécution d'une instruction est organisée en six étapes principales :
- Fetch
- Decode / Read
- Execute
- Memory
- Write back
- PC update

Le schéma de câblage du processeur y86 séquentiel permet
d'interconnecter les blocs fonctionnels participant à la réalisation
de l'ensemble des tâches ci-dessus.

Les blocs fonctionnels sont reliés par des liaisons de diverses nature : 
- Épaisses : 1 mot
- Fines : 1 octet ou quelques bits
- Pointillées : 1 bit
- Ovales blancs : noms des liaisons (variables des calculs)

L'étape "Fetch" correspond à la récupération de l'instruction à
exécuter à partir de l'adresse contenue dans le compteur ordinal "PC".
Les valeurs qui peuvent en être extraites sont "icode" et "ifun" et,
selon les cas, "rA" et "rB", et/ou "valC", la valeur constante.
L'analyse du premier octet permet de déterminer le type de
l'instruction et donc sa longueur. Celle-ci est utilisée par un circuit
additionneur annexe simplifié, "PC increment", pour calculer l'adresse
"valP" de la prochaine instruction à exécuter.

L'étape "Decode" consiste à interroger la banque de registres pour
extraire les valeurs des registres nécessaires à l'exécution de
l'instruction. Deux valeurs peuvent être extraites en même temps,
appelées "valA" et "valB".

L'étape "Execute" mobilise l'UAL pour effectuer un calcul entre les
valeurs rendues disponibles à l'étape précédente : "valA", "valB",
"valC" et/ou des constantes remarquables (0, -4, +4), pour donner une
valeur résultat "valE".

L'étape "Memory" permet d'activer la mémoire de données en lecture ou
en écriture. L'adresse est fournie par valA ou valE, et les données
à écrire par valA ou valP. Lorsque la mémoire est utilisée en lecture,
les données lues sont chargées dans la valeur résultat "valM".

L'étape "Write back" n'utilise pas de nouveau circuit. Elle consiste à
écrire, si nécessaire, dans la banque de registres (déjà accédée en
lecture à l'étape "Decode"), les valeurs valE et/ou valM issues des
traitements des étapes "Execute" et/ou "Memory".

L'étape "PC update" consiste à mettre à jour la valeur du conpteur
ordinal PC à partir des valeurs valP, valC ou valM, selon les
instructions. Une fois cette dernière étape effectuée, le traitement
d'une nouvelle instruction peut être initié.


## Fonctionnement du y86-seq (1)

OPl rA,rB
Fetch :
icode:ifun = M1[PC]
rA:rB = M1[PC+1]
valP = PC + 2

Decode :
valA = R[rA]
valB = R[rB]

Execute :
valE = valB OP valA
CC = SetCC ()

Memory :

Write back :
R[rB] = valE

PC update :
PC = valP


rrmovl rA,rB
Fetch :
icode:ifun = M1[PC]
rA:rB = M1[PC+1]
valP = PC + 2

Decode :
valA = R[rA]

Execute :
ValE = 0 + valA

Memory :

Write back :
R[rB] = valE

PC update :
PC = valP


irmovl valC,rB
Fetch :
icode:ifun = M1[PC]
rA:rB = M1[PC+1]
valC = M4[PC+2]
valP = PC + 6

Decode :

Execute :
ValE = 0 + valC

Memory :

Write back :
R[rB] = valE

PC update :
PC = valP


## Fonctionnement du y86-seq (2)

rmmovl rA,D(rB)
Fetch :
icode:ifun = M1[PC]
rA:rB = M1[PC+1]
valC = M4[PC+2]
valP = PC + 6

Decode :
valA = R[rA]
valB = R[rB]

Execute :
valE = valB + valC

Memory :
M4[valE] = valA

Write back :

PC update :
PC = valP


mrmovl D(rB),rA
Fetch :
icode:ifun = M1[PC]
rA:rB = M1[PC+1]
valC = M4[PC+2]
valP = PC + 6

Decode :
valB = R[rB]

Execute :
valE = valB + valC

Memory :
ValM = M4[valE]

Write back :
R[rA] = valM

PC update :
PC = valP


## Fonctionnement du y86-seq (3)

pushl rA
Fetch :
icode:ifun = M1[PC]
rA:rB = M1[PC+1]
valP = PC + 2

Decode :
valA = R[rA]
valB = R[%esp]

Execute :
valE = valB + (-4)

Memory :
M4[valE] = valA

Write back :
R[%esp] = valE

PC update :
PC = valP


popl rA
Fetch :
icode:ifun = M1[PC]
rA:rB = M1[PC+1]
valP = PC + 2

Decode :
valA = R[%esp]
valB = R[%esp]

Execute :
valE = valB + 4

Memory :
ValM = M4[valA]

Write back :
R[%esp] = valE
R[rA] = valM

PC update :
PC = valP


## Fonctionnement du y86-seq (4)

jXX valC
Fetch :
icode:ifun = M1[PC]
valC = M4[PC+1]
valP = PC + 5

Decode :

Execute :
bch = Cond (CC, ifun)

Memory :

Write back :

PC update :
PC = bch ? ValC : valP


call valC
Fetch :
icode:ifun = M1[PC]
valC = M4[PC+1]
valP = PC + 5

Decode :
valB = R[%esp]

Execute :
valE = valB + (-4)

Memory :
M4[valE] = valP

Write back :
R[%esp] = valE

PC update :
PC = valC


ret
Fetch :
icode:ifun = M1[PC]
valP = PC + 1

Decode :
valA = R[%esp]
valB = R[%esp]

Execute :
valE = valB + 4

Memory :
ValM = M4[valA]

Write back :
R[%esp] = valE

PC update :
PC = valM


## Câblage du y86-seq (1)

"Fetch" : Récupération de l'instruction courante à exécuter
- De 1 à 6 octets lus à partir de l'adresse contenue dans le compteur
  ordinal (PC)
- Pré-calcul de l'adresse de l'instruction suivante (valP)

Permet de récupérer les valeurs :
- icode
- ifun
- rA
- rB
- valC


## Câblage du y86-seq (2)

"Decode" : Accès éventuel à la banque des registres.

La banque de registres est une mémoire spécialisée possédant :
- deux sorties simultamées en lecture (deux "ports" en lecture),
  valA et valB ;
- deux entrées simultanées en écriture (deux "ports" en écriture),
  valE et valM.
Les adresses (numéros de registres) de ces ports, appelés
respectivement "srcA", "srcB", "dstE" et "dstM", sont commandés par
quatre multiplexeurs pilotés par icode et les valeurs immédiates des
numéros de registre rA et rB issus du registre d'instruction.

## What register should be used as the A source?
int srcA = [
  icode in { IRRMOVL, IRMMOVL, IOPL, IPUSHL } : rA;
  icode in { IPOPL, IRET } : RESP;
  1 : RNONE; # Don't need register ];
## What register should be used as the B source?
int srcB = [
  icode in { IOPL, IRMMOVL, IMRMOVL } : rB;
  icode in { IPUSHL, IPOPL, ICALL, IRET } : RESP;
  1 : RNONE; # Don't need register
];
## What register should be used as the E destination?
int dstE = [
  icode in { IRRMOVL, IIRMOVL, IOPL} : rB;
  icode in { IPUSHL, IPOPL, ICALL, IRET } : RESP;
  1 : RNONE; # Don't need register
];
## What register should be used as the M destination?
int dstM = [
  icode in { IMRMOVL, IPOPL } : rA;
  1 : RNONE; # Don't need register
];


## Câblage du y86-seq (3)

"Execute" : Utilisation de l'UAL

Cet étage fonctionnel contient :
- l'UAL proprement dite ;
- la mémoire de stockage des bits de condition ("condition code" ou
  "CC" ) S, Z et C ;
- la logique de décision d'un branchement, dont le résultat ("pris /
  non pris"), appelé "bcond", sera utilisé à l'étage "PC update".
L'entrée A de l'UAL est précédée d'un multipleur, piloté par icode,
entre valA et valC et des valeurs constantes remarquables.
L'entrée B de l'UAL est précédée d'un multipleur, piloté par icode,
entre valB et des valeurs constantes remarquables.
Les lignes de commande de l'UAL (choix de la fonction) dépendent d'un
multiplexeur piloté par icode et ifun.
L'écriture dans le registre de stockage des codes de condition, des
bits S, Z et C issus de l'UAL, par le fil "set_cc", dépend d'un
multiplexeur piloté par "icode".

## Select input A to ALU
int aluA = [
  icode in { IRRMOVL, IOPL } : valA;
  icode in { IIRMOVL, IRMMOVL, IMRMOVL } : valC;
  icode in { ICALL, IPUSHL } : -4;
  icode in { IRET, IPOPL } : 4;
# Other instructions don't need ALU
];
## Select input B to ALU
  int aluB = [
  icode in { IRMMOVL, IMRMOVL, IOPL,
                 ICALL, IPUSHL, IRET, IPOPL } : valB;
  icode in { IRRMOVL, IIRMOVL } : 0;
# Other instructions don't need ALU
];
## Set the ALU function
int alufun = [
  icode == IOPL : ifun;
  1 : ALUADD;
];
## Should the condition codes be updated?
bool set_cc = icode in { IOPL };


## Câblage du y86-seq (4)

"Memory" : Accès à la mémoire des données

En amont de la mémoire se trouvent deux multiplexeurs, l'un pour les
adresses et l'autre pour les données à injecter dans la mémoire :
- le multiplexeur d'adresses, piloté par icode, entre valA et valE ;
- le mutiplexeur de données, piloté par icode, entre valA et valP.
Deux signaux supplémentaires conditionnent l'activation de la mémoire,
eux aussi pilotés par icode : "mem_read" et "mem_write".

## Set read control signal
bool mem_read = icode in { IMRMOVL, IPOPL, IRET };
## Set write control signal
bool mem_write = icode in { IRMMOVL, IPUSHL,
                                             ICALL };
## Select memory address
int mem_addr = [
  icode in { IRMMOVL, IPUSHL, ICALL,
                  IMRMOVL } : valE;
  icode in { IPOPL, IRET } : valA;
# Other instructions don't need address
];
## Select memory input data
int mem_data = [ # Value from register
  icode in { IRMMOVL, IPUSHL } : valA;
# Return PC
  icode == ICALL : valP;
# Default: Don't write anything
];


## Câblage du y86-seq (5)

"PC update" : Mise à jour du compteur ordinal

Il s'agit en fait d'un grand multiplexeur, piloté par icode, afin que
la prochaine instruction soit décodée à partir de la bonne adresse.

int new_pc = [
# Call. Use instruction constant
  icode == ICALL : valC;
# Taken branch. Use instruction constant
  icode == IJXX && Bch : valC;
# Completion of RET instruction. Use value from stack
  icode == IRET : valM;
# Default: Use incremented PC
  1 : valP;
];


## Analyse de l'architecture y86-seq (1)

Caractéristiques :
- Connecte des blocs fonctionnels prédéfinis au moyen de fonctions
  logiques combinatoires
- Exprime chaque instruction sous la forme d'étapes simples
- Flot de contrôle et de données unique pour chaque instruction


## Analyse de l'architecture y86-seq (2)

Limitations :
- Au cours du cycle, le flot de contrôle doit se propager au sein de
  tous les circuits
  - Chemin critique très long
  - Fréquence d'horloge trop basse pour être compétitive
    (vintage '80s : 1 MHz)
- Les unités fonctionnelles ne sont réellement utiles que pendant une
  fraction du cycle
Ceci conduit naturellement à en dériver une version pipe-linée

#!/usr/bin/python3

### Préliminaires: fonctions du TM1 et autres


# factorielle
def facto(n):
    if n<=0:
        return 1
    return n*facto(n-1)

def binomial(n,k):
    return facto(n)/facto(k)/facto(n-k)

# nombres de Catalan
def Catalan(n):
    return facto(2*n)//facto(n)//facto(n+1)

# Toutes sequences binaires de longueur k (récursive)
def ToutesSequencesBinaires(k):
    if k<=0:
        return [()]
    L = ToutesSequencesBinaires(k-1)
    M = []
    for s in L:
        M.append(s+(0,))
        M.append(s+(1,))
    return M

# Séquences sous-diagonales (fonction récursive)
def ToutesSeqSousDiago(n):
    if n<=0:
        return [()]
    L = ToutesSeqSousDiago(n-1)
    M = []
    for s in L:
        for k in range(1,n+1):
            M.append(s+(k,))
    return M

# Conversion (bijective) entre séquences sous-diagonales
# et permutations
def SeqVersPerm(s):
    n = len(s)
    L = [i for i in range(1,n+1)]
    for j in range(n):
        pos = s[j] -1 # Pour ramener à un indice
        if pos != j:
            temp = L[pos]
            L[pos] = L[j]
            L[j] = temp
    return tuple(L)

# Toutes permutations de taille n
def ToutesPermutations(n):
    L = ToutesSeqSousDiago(n)
    M = []
    for s in L:
        M.append(SeqVersPerm(s))
    return M

# Nombre de points fixe d'une permutation s
# Attention au décalage entre indices et valeurs
def NbPointsFixes(s):
    cpt = 0
    n = len(s)
    for i in range(n):
        if s[i] == i+1:
            cpt += 1
    return cpt


#### Exercice 2.1: permutations

## 2.1.1: cycles de longueur 2

# Nombre de cycles de longueur 2 dans une permutation s.
# la valeur i est la première d'un cycle de longueur 2
# si s(i)>i et s(s(i))=i
# Attention au décalage entre indices et valeurs
def Nb2Cycles(s):
    n = len(s)
    cpt = 0
    for i in range(1,n):
        posi = i-1
        j = s[posi]
        posj = j-1
        if j>i and s[posj]==i:
            cpt += 1
    return cpt

### Code pour compter les 2-cycles dans toutes les permutations
### de longueur n
# for n in range(2,10):
#     L = ToutesPermutations(n)
#     cpt = 0
#     for s in L:
#         cpt += Nb2Cycles(s)
#     print("Longueur %d: %d permutations, %d 2-cycles"%(n,len(L),cpt))
## n!/2

## 2.1.2: cycles de longueur autre

# Longueur du cycle contenant i
# s(i), c'est s[i-1] à cause du décalage des indices
# On itère la fonction représentée par s, jusqu'à revenir en i
def LongueurCycle(s,i):
    k = 1
    x = s[i-1]
    while x!=i:
        k += 1
        x = s[x-1]
    return k

# La liste retournée donne, pour chaque entier de 1 à n (les longueurs
# possibles de cycles), le nombre de permutations de taille n où 1 est
# dans un cycle de cette longueur
def Longueurs(n):
    L = ToutesPermutations(n)
    R = [0 for i in range(n)]
    for s in L:
        k = LongueurCycle(s,1)
        R[k-1] += 1
    return R

## Code pour voir le résultat pour les premières longueurs
# for n in range(1,10):
#     L = Longueurs(n)
#     print(n,L)
## (n-1)!, soit n!/n: la longueur du cycle contenant 1 est uniforme


#### Exercice 2.2: mots de Dyck

## 2.2.1:  EstDyck
# True si s est un mot de Dyck, False sinon
def EstDyck(s):
    h = 0
    n = len(s)
    for i in range(n):
        if s[i]==1:
            h += 1
        elif s[i]==0:
            h -= 1
        else:
            return False
        if h<0:
            return False
    return (h==0)

## 2.2.2: tous les mots de Dyck

def TousMotsDyck(n):
    L = ToutesSequencesBinaires(2*n)
    M = []
    for s in L:
        if EstDyck(s):
            M.append(s)
    return M

## Vérification: il doit y avoir Catalan(n) mots de Dyck de longueur 2n
# for n in range(2,11):
#     nbMots = len(TousMotsDyck(n))
#     C = Catalan(n)
#     print("Longueur %d: %d mots, Catalan: %d"%(2*n,nbMots,C))



## 2.2.3: comptage des pics

# Nombre de pics dans un mot (de Dyck)
def Pics(s):
    n = len(s)
    cpt = 0
    for i in range(1,n):
        if s[i-1]==1 and s[i]==0:
            cpt += 1
    return cpt

## 2.2.4:  nombre moyen de pics dans les mots de Dyck
# On compte le nombre total de pics, on divisera par Catalan(n)
def TotalPics(n):
    L = TousMotsDyck(n)
    total = 0
    for s in L:
        total += Pics(s)
    return total

# for n in range(2,11):
#     print("Longueur %d: %f"%(2*n, TotalPics(n)/Catalan(n)))
# Attention à faire une division flottante (/) et pas entière (//),
# le résultat n'est pas forcément entier



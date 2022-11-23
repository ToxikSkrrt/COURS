#!/usr/bin/python3

# NOM:
# PRENOM:
# GROUPE:


# Probabilités, Statistiques, Combinatoire (Licence 2)
# TM1

# Certaines fonctions sont fournies comme exemples; celles dont le
# corps est seulement "return None" sont celles qu'il faut écrire soi-même.
# Il est possible que pour certains exercices, il soit judicieux d'écrire
# des fonctions en plus!

# pour vérifier qu'une liste ne contient pas de doublons
# (il faut que python arrive à trier... pas des choses trop inhomogènes donc)
# Des listes ou tuples d'entiers sont triés dans l'ordre lexicographique
def TousDifferents(L):
    LL = sorted(L)
    m = len(LL)
    for i in range(m-1):
        if LL[i]==LL[i+1]:
            return False
    return True

# Exercice 1

def EntierVersBinaire(k,n):
    L=[]
    for i in range(k):
        L.append(0)
    for i in range(k-1,-1,-1):
        if (n%2)==1:
            L[i]=1
        n = n//2
    return tuple(L)

def EntierVersBinaireBis(k, n):
    res=()
    for i in range(k):
        res=(n%2,)+res
        n=n//2
    return res

def BinaireVersEntier(t):
    k = len(t)
    v = 0
    for i in range(k):
        v = 2*v+t[i]
    return v

def ToutesSequencesBinaires(k):
    L=[]
    for n in range(2**k):
        L.append(EntierVersBinaire(k,n))
    return L

def ToutesSequencesBinairesBis(k):
    L=[EntierVersBinaire(k,n) for n in range(2**k)]
    return L

def ToutesSequencesBinairesRec(k):
    if k<=0:
        return [()]
    L = ToutesSequencesBinairesRec(k-1)
    M = []
    for s in L:
        M.append(s+(0,))
        M.append(s+(1,))
    return M


def NbConsecutifs(t):
    mx = 0
    v = 0
    for i in range(len(t)):
        if t[i]==0:
            if v>mx:
                mx = v
            v = 0
        else:
            v += 1
    if v>mx: # au cas où la séquence termine par un 1
        mx = v
    return mx

# Nombre de séquences dans L avec au moins l 1 consecutifs
# On donne la liste pour éviter de la calculer une fois pour chaque l
def NbAveclConsecutifs(L,l):
    cpt = 0
    for s in L:
        if NbConsecutifs(s) >= l:
            cpt += 1
    return cpt

# Nombre de séquences dans L sans au moins l 1 consecutifs
# On donne la liste pour éviter de la calculer une fois pour chaque l
def NbSansKConsecutifs(L,l):
    cpt = 0
    for s in L:
        if NbConsecutifs(s)<l:
            cpt += 1
    return cpt

# Pour chaque valeur l de 1 à m: affiche combien de séquences binaires
# de longueur k n'ont pas au moins l 1 consécutifs
# affiche la fonction de repartition F de NbConsecutif
# F(l) := Card{ s | NbC(s) < l}
def Comptages(k,m):
   L = ToutesSequencesBinaires(k)
   for l in range(1,m+1):
       nb = NbSansKConsecutifs(L,l)
       print("Parmi le séquences de longueur %d, %d nont 'pas au moins %d 1 consecutifs"%(k,nb,l))
      
# Nombre de séquences dans L avec au moins l 1 consecutifs
# On donne la liste pour éviter de la calculer une fois pour chaque l
def NbAveclConsecutifs(L,l):
    cpt = 0
    for s in L:
        if NbConsecutifs(s)>=l:
            cpt += 1
    return cpt

# Plus petit l entre 0 et k tel que moins de la moitié des séquences
# de longueur k ait l 1 consécutifs
def MinConsecutifs1(k):
    #pop[l] est la population des sequences t telles que NbConsecutifs(t)=l
    pop=[0]*(k+1)
    for s in ToutesSequencesBinaires(k):
        pop[NbConsecutifs(s)]+=1
    l=k+1
    popl=0        #nb de seq dont le NbC est >= l
    popm=2**(k-1) #moitie de la population de sequences
    while popl <= popm:
        l-=1
        popl+=pop[l]       
    return l+1

# Plus petit l entre 0 et k tel que moins de la moitié des séquences
# de longueur k ait l 1 consécutifs
def MinConsecutifs2(k):
    L= ToutesSequencesBinaires(k)
    l=k+1
    popm=2**(k-1) #moitie de la population de sequences
    while NbAveclConsecutifs(L,l)  <= popm:
        l-=1     
    return l+1

# Plus petit l entre 0 et k tel que moins de la moitié des séquences
# de longueur k ait l 1 consécutifs
#i.e. au moins la moitie des sequences de lg k, a au plus l-1 1 consecutifs
def MinConsecutifs3(k):
    L= ToutesSequencesBinaires(k)
    l=0
    popm=2**(k-1) #moitie de la population de sequences
    while NbSansKConsecutifs(L,l) < popm:
        l+=1
    return l

def test_Minconsecutifs(m):
    for k in range(m):
        N1= MinConsecutifs1(k)
        N2= MinConsecutifs2(k)
        N3= MinConsecutifs3(k)
        assert N1==N2
        assert N2==N3
        
test_Minconsecutifs(11)

# Version récursive de ToutesSequencesBinaires
def ToutesSequencesBinairesRec(n):
    if n<=0:
        return [()]
    L = ToutesSequencesBinairesRec(n-1)
    M = []
    for s in L:
        M.append(s+(0,))
        M.append(s+(1,))
    return M

def ToutesSequencesBinairesRecBis(k):
    if k<=0:
        return [()]
    L = ToutesSequencesBinairesRecBis(k-1)
    # On paie une condaténation de listes en plus
    M = [t+(0,) for t in L] + [t+(1,) for t in L]
    return M



















    
# Exercice 2

# Par exemple: t = (0,0,1,0,0,1,1,1)
# en sortie: (3,6,7,8)

def SequenceVersPartie(t):
    n = len(t)
    L = []
    for indice in range(n):
        if t[indice]==1:
            L.append(indice+1) # Décalage pour l'indexation à partir de 0
    return tuple(L)

# L.append(x): ajoute la valeur x à la fin de la liste L
# (modifie la liste L)
# Evolution de L:
# []
# [3]
# [3,6]
# [3,6,7]
# [3,6,7,8]
# retourne (3,6,7,8)

















def Parties(n,k):
    L = ToutesSequencesBinaires(n)
    M = []
    for t in L:
        s = SequenceVersPartie(t)
        if len(s)==k:
            M.append(s)
    return M

def PremierePartie(n,k):
    L = [i+1 for i in range(k)]
    return tuple(L)

#############################################
# Expliquer ici (en commentaires) comment est calculée la
# partie suivante
#
#
#
#############################################

# Retourne la partie qui suit s dans l'ordre lexicographique; on n'a pas
# besoin de k (longueur de s) mais on a besoin de n
def Suivante(n,s):
    k = len(s)
    i = k-1
    L = list(s)
    while (i>=0 and L[i]==n-k+i+1):
        i -=1
    if i==-1:
        return None
    L[i] += 1
    for j in range(i+1,k):
        L[j] = L[j-1]+1
    return tuple(L)

# Peut-etre un peu plus naturelle? on n'entre dans la boucle que si
# on a une "retenue", comme ça on peut se contenter de comparer
# au suivant
def SuivanteBis(n,s): 
    k = len(s)
    L = list(s)
    if L[k-1] <n:
        L[k-1] += 1
        return tuple(L)
    j = k-2
    while (j>=0 and L[j] == L[j+1]-1):
        j -= 1
    if j==-1:
        return None
    L[j] += 1
    for i in range(j+1,k):
        L[i] = L[i-1] +1
    return tuple(L)

# Comme la fonction Parties, mais avec PremierePartie() et Suivante()
def PartiesBis(n,k):
    L=[]
    s = PremierePartie(n,k)
    while s!=None:
        L.append(s)
        s = Suivante(n,s)
    return L

# Exercice 3
# Permutations

# Toutes les séquences sous-diagonales, version récursive
def ToutesSeqSousDiagoRec(n):
    if n<=0:
        return [()]
    L = ToutesSeqSousDiagoRec(n-1)
    M = []
    for s in L:
        for k in range(1,n+1):
            M.append(s+(k,))
    return M

# Version itérative, à écrire
def ToutesSeqSousDiago(n):
    L = [()]
    for i in range(1,n+1):
        M = []
        for s in L:
            for j in range(1,i+1):
                M.append(s+(j,))
        L = M
    return L

    
# Version plus directe, mais pas facile!
def PremiereSeqSousDiago(n):
    L = [1 for i in range(n)]
    return tuple(L)

def SeqSousDiagoSuivante(s):
    L = list(s)
    n = len(L)
    i = n-1
    while (i>0 and L[i]==i+1):
        i -= 1
    if i==0:
        return None
    L[i] += 1
    for j in range(i+1,n):
        L[j] = 1
    return tuple(L)

def ToutesSeqSousDiagoBis(n):
    s = PremiereSeqSousDiago(n)
    L = []
    while s!=None:
        L.append(s)
        s = SeqSousDiagoSuivante(s)
    return L


# Conversion d'une sequence sous-diagonale en permutation
# S'inspirer de l'ex. 1.8 feuille TD1
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

# Toutes les permutations: par conversion depuis les séquences
# sous-diagonales
def ToutesPermutations(n):
    L = [SeqVersPerm(s) for s in ToutesSeqSousDiago(n)]
    return L

# Nombre de points fixe d'une permutation s
def NbPointsFixes(s):
    cpt = 0
    n = len(s)
    for i in range(n):
        if s[i] == i+1:
            cpt += 1
    return cpt


# Nombre total de points fixes dans toutes les permutations
# de taille n
def ComptePointsFixes(n):
    L = ToutesPermutations(n)
    total = 0
    for s in L:
        total = total + NbPointsFixes(s)
    return total

# Nombre de dérangements parmi les permutations de taille n
def NbDerangements(n):
    L = ToutesPermutations(n)
    cpt = 0
    for s in L:
        if NbPointsFixes(s)==0:
            cpt += 1
    return cpt

# Nombre de records dans une permutation
def NbRecords(s):
    cpt = 1
    record = s[0]
    n = len(s)
    for i in range(1,n):
        if s[i] > record:
            record = s[i]
            cpt += 1
    return cpt


#######
# Mettre ici tous les appels de fonctions et affichages pour
# répondre aux questions posées dans le sujet

#print("Exercice 1: séquences binaires")
#Q6:
def Q61(m,ll):
    L= ToutesSequencesBinaires(m)
    for l in ll:
        print("Nb de seq de longueur",m, "ayant au moins",l,"1 consecutifs : ",NbAveclConsecutifs(L,l))
        
##Q61(20,(1,5,10))
##Nb de seq de longueur 20 ayant au moins 1 1 consecutifs :  1048575
##Nb de seq de longueur 20 ayant au moins 5 1 consecutifs :  262008
##Nb de seq de longueur 20 ayant au moins 10 1 consecutifs :  6144
        
def Q62(m):
    for k in range(1,m+1):
        print("plus petit l tel que une minorite de seq de long", k,
              "ont l 1 consecutifs:", MinConsecutifs1(k))

#Q62(20)   
##Nb de seq de longueur
## 20 ayant au moins 1 1 consecutifs :  1048575
##Nb de seq de longueur 20 ayant au moins 5 1 consecutifs :  262008
##Nb de seq de longueur 20 ayant au moins 10 1 consecutifs :  6144
##plus petit nombre l tel que une minorite de seq de long 1 ont l 1 consecutifs: 1
##plus petit nombre l tel que une minorite de seq de long 2 ont l 1 consecutifs: 2
##plus petit nombre l tel que une minorite de seq de long 3 ont l 1 consecutifs: 2
##plus petit nombre l tel que une minorite de seq de long 4 ont l 1 consecutifs: 2
##plus petit nombre l tel que une minorite de seq de long 5 ont l 1 consecutifs: 3
##plus petit nombre l tel que une minorite de seq de long 6 ont l 1 consecutifs: 3
##plus petit nombre l tel que une minorite de seq de long 7 ont l 1 consecutifs: 3
##plus petit nombre l tel que une minorite de seq de long 8 ont l 1 consecutifs: 3
##plus petit nombre l tel que une minorite de seq de long 9 ont l 1 consecutifs: 3
##plus petit nombre l tel que une minorite de seq de long 10 ont l 1 consecutifs: 4
##plus petit nombre l tel que une minorite de seq de long 11 ont l 1 consecutifs: 4
##plus petit nombre l tel que une minorite de seq de long 12 ont l 1 consecutifs: 4
##plus petit nombre l tel que une minorite de seq de long 13 ont l 1 consecutifs: 4
##plus petit nombre l tel que une minorite de seq de long 14 ont l 1 consecutifs: 4
##plus petit nombre l tel que une minorite de seq de long 15 ont l 1 consecutifs: 4
##plus petit nombre l tel que une minorite de seq de long 16 ont l 1 consecutifs: 4
##plus petit nombre l tel que une minorite de seq de long 17 ont l 1 consecutifs: 4
##plus petit nombre l tel que une minorite de seq de long 18 ont l 1 consecutifs: 4
##plus petit nombre l tel que une minorite de seq de long 19 ont l 1 consecutifs: 4
##plus petit nombre l tel que une minorite de seq de long 20 ont l 1 consecutifs: 4        

        
#print("\n\nExercice 2: parties d'un ensemble")
#pas vu de questions

#print("\n\nExercice 3: permutations")
#
def Q3a(nmax):
    for n in range(1,nmax+1):
        print("n=",n,"nb total de points fixes dans Sn", ComptePointsFixes(n))
#Q3a(11)
##n= 1 nb total de points fixes dans Sn 1
##n= 2 nb total de points fixes dans Sn 2
##n= 3 nb total de points fixes dans Sn 6
##n= 4 nb total de points fixes dans Sn 24
##n= 5 nb total de points fixes dans Sn 120
##n= 6 nb total de points fixes dans Sn 720
##n= 7 nb total de points fixes dans Sn 5040
##n= 8 nb total de points fixes dans Sn 40320
##n= 9 nb total de points fixes dans Sn 362880
##n= 10 nb total de points fixes dans Sn 3628800

def Q3b(nmax):
    for n in range(1,nmax+1):
        print("n=",n,"nb de derangements dans Sn",NbDerangements(n))
#Q3b(11)
##n= 1 nb de derangements dans Sn 0
##n= 2 nb de derangements dans Sn 1
##n= 3 nb de derangements dans Sn 2
##n= 4 nb de derangements dans Sn 9
##n= 5 nb de derangements dans Sn 44
##n= 6 nb de derangements dans Sn 265
##n= 7 nb de derangements dans Sn 1854
##n= 8 nb de derangements dans Sn 14833
##n= 9 nb de derangements dans Sn 133496
##n= 10 nb de derangements dans Sn 1334961
        


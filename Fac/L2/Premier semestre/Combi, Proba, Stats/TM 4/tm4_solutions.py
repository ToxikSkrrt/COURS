#!/usr/bin/python3

# NOM:
# Prenom:
# Groupe:

import random
import math

# Fonction partie fractionnaire
def frac(x):
    return x - math.floor(x)

# factorielle: pour les tests
def facto(n):
    f = 1
    for i in range(1,n+1):
        f *= i
    return f

# coefficients binomiaux: pour les tests
def cbino(n,k):
    return facto(n)//facto(k)//facto(n-k)

# Distance entre deux dictionnaires
# "distance en variation totale", toujours comprise entre 0 et 1
def distance(d1,d2):
    d = 0
    for c in d1:
        if c in d2:
            d += abs(d1[c] - d2[c])
        else:
            d += d1[c]
    for c in d2:
        if not c in d1:
            d += d2[c]
    return d/2

# Lancer d'un dé classique (équilibré, 6 faces)
def simuleDe6():
    return random.randint(1,6)

# Lancer de deux dés
def simule2D6():
    x = simuleDe6()
    y = simuleDe6()
    return (x,y)

# Fréquences empiriques pour un dé
def testeDe6(n):
    freq = {}
    for i in range(n):
        resultat = simuleDe6()
        if resultat in freq:
            freq[resultat] += 1
        else:
            freq[resultat] = 1
    for valeur in freq:
        freq[valeur] = freq[valeur] / n
    return freq

# Affichage d'un dictionnaire
def afficheDictionnaire(d):
    l = list(d.keys())
    l.sort()
    for valeur in l:
        print("Clé ",valeur,": fréquence ",d[valeur])


###########################
# Q1: tester la fonction testeDe6

###f10 = testeDe6(10)
###f100 = testeDe6(100)
###f1000 = testeDe6(1000)
###f1M = testeDe6(1000000)
###fth = {1:1/6,2:1/6,3:1/6,4:1/6,5:1/6,6:1/6}
#### frequences théoriques
#### pour 1000000, on observe typiquement une distance de l'ordre de 0.001 avec fth
#### pour 100, typiquement de l'ordre de 0.1
#### sans surprise, c'est d'ordre n^{-1/2}

# Q2: fonction simulePremierSix

def simulePremierSix():
    return None

def simulePremierSix():
    k = 0
    v = 1
    while v!=6:
        v = simuleDe6()
        k += 1
    return k

# Q3: fonction testePremierSix

def testePremierSix(n):
    return None

def testePremierSix(n):
    freq = {}
    for i in range(n):
        v = simulePremierSix()
        if v in freq:
            freq[v] += 1
        else:
            freq[v] = 1
    for v in freq:
        freq[v] = freq[v] / n
    return freq

# p10 = testePremierSix(10)
# p100 = testePremierSix(100)
# p1000 = testePremierSix(1000)
# p1M = testePremierSix(1000000)

# pour n=10 ou n=100, on ne "voit" pas grand chose
# pour n=1000000, on voit bien la décroisance au début, vers les valeurs
# 60 la suite n'est plus décroissante et commence à avoir des "trous"


# Q4: simulation de trois dés

def simuleTroisDes():
    return None

def simuleTroisDes():
    x = simuleDe6()
    y = simuleDe6()
    z = simuleDe6()
    return (x,y,z)

def testeTroisDes(n):
    return None

def testeTroisDes(n):
    f = {}
    for i in range(n):
        v = simuleTroisDes()
        if v in f:
            f[v] += 1
        else:
            f[v] = 1
    for v in f:
        f[v] /= n
    return f

# t100 = testeTroisDes(100)
# t1000 = testeTroisDes(1000)
# t1M = testeTroisDes(1000000)

# On attend une loi uniforme sur [[1,6]^3 (216 éléments)
# Pour n=1000, typiquement toutes les valeurs n'apparaissent pas
# Pour n=10000, typiquement toutes apparaissent
# Pour n=1000000, les fréquences sont typiquement 1/216 entre 0.004 et 0.005

# Q5: fréquences empiriques

def frequencesEmpiriques(sim,n):
    return None

def frequencesEmpiriques(sim,n):
    d = {}
    for i in range(n):
        v = sim()
        if v in d:
            d[v] += 1
        else:
            d[v] = 1
    for v in d:
        d[v] /= n
    return d

# Par exemple pour simuleDe6
# s10k = frequencesEmpiriques(simuleDe6,10000)
# d10k = testeDe6(10000)
# d10kbis = testeDe6(10000)
# print(distance(s10k,d10k))
# print(distance(d10k,d10kbis))
# print(distance(s10k,d10kbis))
# Les distances devraient être similaires, de l'ordre de 0.01


#### Simulateurs génériques
#

def genereDe(faces):
    def sim():
        return random.randint(1,faces)
    return sim

###print(frequencesEmpiriques(genereDe(10),10000))
###print(frequencesEmpiriques(genereDe(6),10000))
### Pour le d10: fréquences entre 0.09 et 0.11
### Pour les d6: fréquences entre 0.16 et 0.17


# Q6: générateur de Bernoulli

def genereBernoulli(p):
    return None

def genereBernoulli(p):
    def b():
        x = random.random()
        if x<p:
            return 1
        else:
            return 0
    return b

# Q7: génerateur de sommes

def genereSomme(sim1,sim2):
    return None

def genereSomme(sim1,sim2):
    def somme():
        x = sim1()
        y = sim2()
        return x+y
    return somme

def genereSommeListe(L):
    return None

def genereSommeListe(L):
    def somme():
        s = 0
        for sim in L:
            s += sim()
        return s
    return somme

#d6 = genereDe(6)
#s2 = genereSomme(d6,d6)

#f = frequencesEmpiriques(s2,10000)
# 0.028, 0.055, 0.083, 0.11, 0.138, 0.166, 0.138, 0.11, 0.083, 0.055, 0.028
# à +/- 0.01 environ

### somme de trois dés à 6 faces
#de6 = genereDe(6)
#L = (de6,de6,de6)
### Si on écrit L = (de6 for i in range(3)), ça ne marche pas
### mais je ne sais pas pourquoi (à partir du 2e appel ça retourn toujours 0)
#sim = genereSommeListe(L)
#f = frequencesEmpiriques(sim,10000)


# Q8: binomiale

def genereBinomiale(k,p):
    return None

def genereBinomiale(k,p):
    b = genereBernoulli(p)
    def bino():
        somme = 0
        for i in range(k):
            somme += b()
        return somme
    return bino

#g = genereBinomiale(2,0.5)
#print(frequencesEmpiriques(g,10000))
# 0.25, 0.5, 0.25

#g = genereBinomiale(3,0.7)
#print(frequencesEmpiriques(g,10000))
# 0.027, 0.189, 0.441, 0.343

#g = genereBinomiale(20,0.05)
#print(frequencesEmpiriques(g,10000))
# Proche d'une Poisson(1): 0.37, 0.37, 0.18, 0.06, 0.0153...


# Q9: generateur de géométriques

def genereGeometrique(p):
    return None

def genereGeometrique(p):
    b = genereBernoulli(p)
    def geom():
        k = 1
        while b()==0:
            k += 1
        return k
    return geom

#g = genereGeometrique(0.5)
#f = frequencesEmpiriques(g,10000)
# 0.5, 0.25, 0.125, 0.0625, ...


# Q10: Poisson

# Magie noire: Poisson(1)
def simulePoisson1():
    x = math.exp(-1)
    v = random.random()
    k = 0
    while v > x:
        v = v * random.random()
        k = k+1
    return k
## un produit d'uniformes: c'est distribué comme l'exponentielle d'une
## somme de variables exponentielles
## La Poisson(x), c'est le nombre d'exponentielles qu'on peut sommer avant
## de dépasser x

# Q10: Poisson, parametre entier

def generePoissonEntier(n):
    def poisson():
        s = 0
        for i in range(n):
            s += simulePoisson1()
        return s
    return poisson

# Q11: Poisson, parametre fractionnaire

def generePoissonFrac(x):
    b = genereBernoulli(x)
    def poisson():
        n = simulePoisson1()
        s = 0
        for i in range(n):
            s += b()
        return s
    return poisson

# Q12: Poisson, parametre quelconque

def generePoisson(x):
    m = math.floor(x)
    y = frac(x)
    return genereSomme(generePoissonEntier(m),generePoissonFrac(y))

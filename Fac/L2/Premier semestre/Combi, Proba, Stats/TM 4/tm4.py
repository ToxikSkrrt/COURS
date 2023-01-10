#!/usr/bin/python3


import random
import math

x = 1/2
if x==0:
    print("ATTENTION vous utilisez probablement Python2; utiliser Python3")

########## Fonctions fournies diverses #####################
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


############### Debut du TM 4 ##########################
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


# Q2: fonction simulePremierSix

def simulePremierSix():
    return None


# Q3: fonction testePremierSix

def testePremierSix(n):
    return None

# Q4: simulation de trois dés

def simuleTroisDes():
    return None


def testeTroisDes(n):
    return None


# Q5: fréquences empiriques

def frequencesEmpiriques(sim,n):
    return None


#### Simulateurs génériques
#

def genereDe(faces):
    def sim():
        return random.randint(1,faces)
    return sim


# Q6: générateur de Bernoulli

def genereBernoulli(p):
    return None


# Q7: génerateur de sommes

def genereSomme(sim1,sim2):
    return None


def genereSommeListe(L):
    return None


# Q8: binomiale

def genereBinomiale(k,p):
    return None


# Q9: generateur de géométriques

def genereGeometrique(p):
    return None


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

# Q10: Poisson, parametre entier

def generePoissonEntier(n):
    return None
    
# Q11: Poisson, parametre fractionnaire

def generePoissonFrac(x):
    return None

# Q12: Poisson, parametre quelconque

def generePoisson(x):
    return None

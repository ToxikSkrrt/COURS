#!/usr/bin/python3
import matplotlib.pyplot
import random
import math    # pour math.sqrt (racine carree)

def dessinEnsemble(S,res=1):
    S1,S2 = separatePointSet(S)
    matplotlib.pyplot.plot(S1,S2,'.') # petits points pleins
    if res>1:
        drawLines(res)
    matplotlib.pyplot.ion() # show() non bloquant
    matplotlib.pyplot.show()

def separatePointSet(L):
    Lx = []
    Ly = []
    for u,v in L:
        Lx.append(u)
        Ly.append(v)
    return Lx,Ly

def drawLines(k):
    L = []
    for i in range(k+1):
        L.append(i/k)
    matplotlib.pyplot.hlines(L,0,1)
    matplotlib.pyplot.vlines(L,0,1)

def distance_carree(pt1,pt2):
    return (pt1[0]-pt2[0])**2 + (pt1[1]-pt2[1])**2

def distance(pt1,pt2):
    return math.sqrt(distance_carree(pt1,pt2))

def rayon(pt):
    return distance(pt,(0,0))

# Moyenne de la loi définie par un dictionnaire
# (moyenne empirique s'il s'agit d'un dictionnaire de frequences;
# esperance si le dictionnaire decrit une loi)
def moyenne(dic):
    return None

# Moyenne (esperance) des images par f des cles du dictionnaire,
# ponderees par les valeurs (frequences); si le dictionnaire decrit
# la loi d'une variable aleatoire X, calcule en fait E(f(X))
def moyenne_f(f,dic):
    return None

# Plus utile pour des experiences en continu
# Moyenne empirique des valeurs retournees par un simulateur
def moyenne_empirique(sim,n):
    return None

def pointAleatoire():
    return None

def ensembleAleatoire(sim,n):
    return None

def pointAleatoireDisque():
    return None


# Distance entre p et le point le plus proche de p dans E
# Les points de E devraient etre tous distincts
def distancePoint(p,E):
    return None

# Distance entre les deux points les plus proches dans E
# Ne doit retourner 0 que si deux points identiques sont
# dans E
def distanceMin(E):
    return None


# Genere un simulateur pour "la distance au centre d'un ensemble de n
# points"; les points sont donnes par generateur
def simu_rayon(generateur,n):
    def sim():
        E = ensembleAleatoire(generateur,n)
        d = distancePoint((0,0),E)
        return d
    return sim

# Ecrire la meme chose pour la distance minimale entre deux points
# d'un ensemble de points aleatoires; attention lors des tests, le
# calcul de la distance minimale est typiquement quadratique (voir
# le cours de Cyril Gavoille au S6 pour faire ca en n.log(n))
def simu_distance(generateur,n):
    def sim():
        return None
    return sim

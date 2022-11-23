#!/usr/bin/python3

import random

# random.randint(a,b): retourne un entier aléatoire uniforme
#  entre a et b inclus
# random.random(): retourne un flottant (réel) aléatoire uniforme
#  entre 0 et 1 (donc proba. x d'être entre 0 et x, et ce, pour tout x)


# Jeux de ballon

# Convention de retour: 1 pour un point/set/match à A,
# 0 pour un point/set/match à B

def SimuleCoup(x):
    return None

# Versions de base: x représente la probabilité pour A de remporter
# n'importe quel point
def SimuleSetTableSimplifie(x):
    score_joueur=0
    score_adversaire=0
    while score_joueur<11 and score_adversaire<11:
        coup = SimuleCoup(x)
        if coup==1:
            score_joueur += 1
        else:
            score_adversaire += 1
    if score_joueur > score_adversaire:
        return 1
    else:
        return 0

def SimuleSetTable(x):
    return None

def SimuleMatchTable(x):
    return None

def SimuleJeuTennis(x):
    return None

def SimuleSetTennis(x):
    return None

def SimuleMatchTennis(x):
    return None

# Versions bis:
# p représente la probabilité pour A de remporter le point si A sert;
# q représente la probabilité pour A de remporter le point si B sert.
def SimuleSetTableBis(p,q):
    return None

def SimuleMatchTableBis(p,q):
    return None

def SimuleJeuTennisBis(p,q):
    return None

def SimuleSetTennisBis(p,q):
    return None

def SimuleMatchTennisBis(p,q):
    return None

# Monty Hall

def initJeu():
    return random.randint(1,3)

def choixJoueur():
    return None

def animateur(bon,choix):
    return None

def strategieJoueur_tetu(choixInitial,choixAnimateur):
    # Joueur qui ne change pas son choix
    return None

def strategieJoueur_change(choixInitial,choixAnimateur):
    # Joueur "qui change"
    return None

def strategieJoueur_hasard(choixInitial,choixAnimateur):
    # Joueur qui choisit aléatoirement de changer ou de ne pas changer
    return None

def simuleJeu(iJ,cJ,a,sJ):
    # simule le jeu; les parametres sont des fonctions
    return None


##########################################################

# Insérer ici votre code pour faire les simulations et essayer
# de répondre aux questions




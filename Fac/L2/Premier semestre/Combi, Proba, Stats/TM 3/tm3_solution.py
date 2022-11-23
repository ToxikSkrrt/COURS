#!/usr/bin/python3

import random

def SimuleCoup(x):
    y = random.random()
    if y<x:
        return 1
    else:
        return 0

def SimuleSetTableSimplifie(x):
    score_joueur=0
    score_adversaire=0
    while score_joueur<21 and score_adversaire<21:
        coup = SimuleCoup(x)
        if coup==1:
            score_joueur = score_joueur +1
        else:
            score_adversaire = score_adversaire +1
    if score_joueur > score_adversaire:
        return 1
    else:
        return 0

def SimuleSetTable(x):
    score_joueur=0
    score_adversaire=0
    while (score_joueur<11 and score_adversaire<11) or abs(score_joueur-score_adversaire)<2:
        coup = SimuleCoup(x)
        if coup==1:
            score_joueur = score_joueur +1
        else:
            score_adversaire = score_adversaire +1
    if score_joueur > score_adversaire:
        return 1
    else:
        return 0

def SimuleMatchTable(x):
    sets_j = 0
    sets_a = 0
    while sets_j<3 and sets_a<3:
        c = SimuleSetTable(x)
        if c==1:
            sets_j += 1
        else:
            sets_a += 1
    if sets_j==3:
        return 1
    else:
        return 0

def SimuleJeuTennis(x):
    sj = 0
    sa = 0
    while (sj<4 and sa<4) or abs(sj-sa)<2:
        c = SimuleCoup(x)
        sj += c
        sa += (1-c)
    if sj>sa:
        return 1
    else:
        return 0

def SimuleSetTennis(x):
    jj=0
    ja=0
    while (jj<6 and ja<6) or abs(jj-ja)<2:
        c = SimuleJeuTennis(x)
        jj += c
        ja += 1-c
    if jj>ja:
        return 1
    else:
        return 0

def SimuleMatchTennis(x):
    sj=0
    sa=0
    while sa<3 and sj<3:
        c = SimuleSetTennis(x)
        sj += c
        sa += 1-c
    if sj>sa:
        return 1
    else:
        return 0
    
    
def TauxVictoire(n,x,f):
    c = 0
    for i in range(n):
        c += f(x)
    return c/n


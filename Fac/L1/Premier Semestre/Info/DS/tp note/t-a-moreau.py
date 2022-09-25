# -*- coding: utf-8 -*-
"""
Created on Sun Jan  9 21:05:10 2022

@author: blanc
"""

from random import randint as rd

class cellule(object):
    
    def __init__(self,value=0, _next=None):
        self.value = value
        self.next = _next

class liste(object):
    
    def __init__(self,cell=None):
        self.head = cell

    def __str__(self): 
        
        resultat = ""
        ptr = self.head   
        while ptr != None:  
            resultat = resultat + str(ptr.value) + ' -> '
            ptr = ptr.next 
        return resultat
    
    def addFirst(self, cell):
        
        if self.liste_vide():
            self.head = cell
        else:
            _next = self.head
            self.head = cell
            cell.next = _next
    
    def liste_vide(self):
        return self.head == None

def construit_liste(value,l):
    return liste(cellule(value,l.head))

#########################
def compteMultiples(L:liste,x)->int:
    compteur = 0
    ptr = L.head
    while ptr != None:
        if ptr.value % x == 0:
            compteur += 1
        ptr = ptr.next
    return compteur

def sontTousSuperieursARec(L, x):
    ptr = L.head
    while ptr != None:
        if ptr.value > x:
            return False
    return True
    
'''def supprimePairsRec(L, x)->list:
    if L.head == None:
        return liste()
    l = supprimePairsRec(liste(L.head.next), x)
    if L.head.value % x != 0:
        l = supprimePairsRec(L.head.value, l)
    return l'''

def empiler(P,x):
    P.addFirst(x)
    return P

def depiler(P):
    if P.head == None:
        return liste()
    P.head = P.head.next
    return P

def valeurPile(P)->int:
    if P.head == None:
        return liste()
    return P.head.value

    
#Appels pour tester les fonctions
L = liste()
t1 = [rd(0, 25) for i in range(10)]
for i in t1:
    L = construit_liste(i, L) 
print(f"La liste avant : {L}") 
n1 = t1[rd(0,len(t1)-1)]
print(f"sontTousSuperieursARec {n1}: {sontTousSuperieursARec(L,n1)}")
n2= t1[rd(0,len(t1)-1)]
print(f"compteMultiples de  {n2}: {compteMultiples(L,n2)}")
'''Q = supprimePairsRec(L, 2)
print(f"supprimePairsRec : {Q}")'''
P=liste()
P=construit_liste(0,P)
t2= [rd(0, 25) for i in range(5)]
for i in t2:
    P = construit_liste(i, P) 
print(f"La Pile avant  empilement de 10 : {P}") 
P=empiler(P,10)
print(f"La Pile après empilement de 10 : {P}") 
P=depiler(P)
P=depiler(P)
print(f"La Pile après deux dépilement : {P}") 
'''print(f"le somment de la pile est : {valeurPile(P)}")'''
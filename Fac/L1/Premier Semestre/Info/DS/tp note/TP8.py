from liste import *
from liste_sentinelle import *

def inputListRec(L = [], t = None):
    t = list(input('Saisir un nombre : '))
    if t == []:
        return L
    else:
        return inputListRec(L + t)
    
def saisie_liste_ptr():
    l = liste()

    ptr = l.sentinelle   # ptr pointe sur la première cellule de la liste

    val = input("Entrez une valeur : ")

    while val != "":
        cell = cellule(val)  # création de la cellule contenant la valeur saisie
        ptr.suivant = cell   # on chaine la nouvelle cellule à celle pointée par ptr
                             # version courte : ptr.suivant = cellule(val)
                             
        ptr = ptr.suivant    # on avance sur la cellule nouvellement crée
        
        val = input("Entrez une valeur : ")

    return l

print(saisie_liste_ptr())

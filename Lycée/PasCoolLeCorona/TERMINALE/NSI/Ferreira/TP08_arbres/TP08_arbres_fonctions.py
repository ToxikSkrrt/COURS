def arbre_vide():
    return []


def noeud(etiquette, gauche, droit):
    return [etiquette, gauche, droit]


def etiquette(arbre):
    return arbre[0]


def gauche(arbre):
    return arbre[1]


def droit(arbre):
    return arbre[2]


def est_vide(arbre):
    return arbre == arbre_vide()


def represente(arbre, profondeur=0):
    """Affiche l'arbre"""
    if est_vide(arbre):
        print('*')
    else:
        print(etiquette(arbre))
        profondeur += 1
        print('-' * profondeur, end='')
        represente(gauche(arbre), profondeur)
        print('-' * profondeur, end='')
        represente(droit(arbre), profondeur)


# =========================
# Fonctions supplémentaires
# =========================


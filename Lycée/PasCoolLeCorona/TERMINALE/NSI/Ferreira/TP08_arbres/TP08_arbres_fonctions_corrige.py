def arbre_vide():
    """Crée un arbre vide"""
    return []


def noeud(etiquette, gauche, droit):
    """Renvoie un arbre dont la racine contient etiquette
       gauche est le sous-arbre gauche de la racine
       droit est le sous-arbre droit de la racine"""
    return [etiquette, gauche, droit]


def etiquette(arbre):
    """Renvoie le contenu de la racine de l'arbre"""
    return arbre[0]


def gauche(arbre):
    """Renvoie le sous-arbre gauche de l'arbre"""
    return arbre[1]


def droit(arbre):
    """Renvoie le sous-arbre droit de l'arbre"""
    return arbre[2]


def est_vide(arbre):
    """Renvoie un booléen, vrai si l'arbre est vide, faux sinon"""
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


def est_feuille(arbre):
    """Renvoie un booléen, vrai si l'arbre est une feuille, faux sinon"""
    return est_vide(gauche(arbre)) and est_vide(droit(arbre))


def compte_feuilles(arbre):
    """Renvoie un entier, le nombre de feuilles de l'arbre"""
    if est_vide(arbre):
        return 0
    if est_feuille(arbre):
        return 1
    return compte_feuilles(gauche(arbre)) + compte_feuilles(droit(arbre))


def taille(arbre):
    """Renvoie un entier, la taille de l'arbre"""
    if est_vide(arbre):
        return 0
    return 1 + taille(gauche(arbre)) + taille(droit(arbre))


def hauteur(arbre):
    """Renvoie un entier, la hauteur de l'arbre"""
    if est_vide(arbre):
        return -1
    return 1 + max(hauteur(gauche(arbre)), hauteur(droit(arbre)))


if __name__ == '__main__':

    test1 = noeud(3, noeud(1, noeud(1, arbre_vide(), arbre_vide()), arbre_vide()),
                 noeud(4, noeud(5, arbre_vide(), arbre_vide()),
                       noeud(9, arbre_vide(), arbre_vide())))

    test2 = noeud(3, noeud(1, arbre_vide(),
                           noeud(4, noeud(1, arbre_vide(),
                                          noeud(5, arbre_vide(), arbre_vide())),
                                 arbre_vide())), arbre_vide())

    print(test1)
    print("Nombre de feuilles : ", compte_feuilles(test1))
    print("Taille : ", taille(test1))
    print("Hauteur : ", hauteur(test1))
    represente(test1)

    print(test2)
    print("Nombre de feuilles : ", compte_feuilles(test2))
    print("Taille : ", taille(test2))
    print("Hauteur : ", hauteur(test2))
    represente(test2)

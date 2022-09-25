# Implémentation d'un TAD : les piles
def creer_pile():
    """ Créé une pile vide."""
    return []


def est_vide(p):
    """ Teste si une pile p est vide."""
    return p == []


def empile(p, a):
    """ Ajoute l'element a à la pile."""  
    p.append(a)


def depile(p):
    """ Enlève le sommet de la pile p, et le renvoie.
    - Échoue si la pile est vide (renvoie une erreur).
    """
    return p.pop()


def sommet(p):
    """ Renvoie la valeur au sommet de la pile P, sans modifier P.
    - Échoue si la pile est vide (renvoie une erreur).
    """
    top = depile(p)
    empile(p, top)
    return top


def hauteur(p):
    """ Calcule la hauteur n de la pile P. """
    # Ne pas utiliser len() de Python
    n = 0
    # On déplace les valeurs dans p vers p2 une autre pile
    p2 = creer_pile()
    while not est_vide(p):
        x = depile(p)
        empile(p2, x)
        n += 1
    # n = len(p) maintenant, on doit déplacer dans l'autre sens
    while not est_vide(p2):
        x = depile(p2)
        empile(p, x)
    return n


def echange_haut_bas(p):
    """ Échange le sommet et le fond de la pile p (p[-1] <-> p[0])."""
    # On dépile
    top = depile(p)
    p2 = creer_pile()
    while not est_vide(p):
        x = depile(p)
        empile(p2, x)
    bottom = depile(p2)
    # On rempile
    empile(p, top)
    while not est_vide(p2):
        x = depile(p2)
        empile(p, x)  # Ordre inchangé pour ces valeurs là
    empile(p, bottom)


if __name__ == '__main__':
    # tester les fonctions
    p = creer_pile()
    empile(p, 1)
    empile(p, 2)
    empile(p, 3)
    empile(p, 4)
    print(p)
    print('Le sommet de la pile est {}.'.format(sommet(p)))
    print('La hauteur de la pile est {}.'.format(hauteur(p)))
    echange_haut_bas(p)
    print(p)
    print('Le sommet de la pile est {}.'.format(sommet(p)))
    print('La hauteur de la pile est {}.'.format(hauteur(p)))
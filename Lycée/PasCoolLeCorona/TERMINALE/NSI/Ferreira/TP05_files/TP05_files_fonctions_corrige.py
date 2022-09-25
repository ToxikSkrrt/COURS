def creer_file():
    """ Créé une file vide."""
    return []


def est_vide(f):
    """Renvoie True si la file est vide False sinon"""
    return f == []


def enfile(f, x):
    """Ajoute x à la file f"""
    # insert() de Python n'est pas autorisé
    f.append(x)
    

def defile(f):
    """Supprime et renvoie le premier élément de la file f
    - Échoue si la file est vide (renvoie une erreur).
    """
    return f.pop(0)


def tete(f):
    """ Renvoie la valeur à la tête de la file f, sans modifier f."""
    return f[0]


def queue(f):
    """ Renvoie la valeur à la queue de la file f, sans modifier f."""
    return f[-1]


def taille(f):
    """ Calcule la hauteur n de la file f. """
    # Ne pas utiliser len() de Python
    n = 0
    # On déplace les valeurs dans f vers f2 une autre pile
    f2 = creer_file()
    while not est_vide(f):
        x = defile(f)
        enfile(f2, x)
        n += 1
    # n = len(p) maintenant, on doit remettre la file
    while not est_vide(f2):
        x = defile(f2)
        enfile(f, x)
    return n


def echange_tete_queue(f):
    """ Échange la tete et la queue de la file f (f[-1] <-> f[0])."""
    n = taille(f)
    tete = defile(f)
    f2 = creer_file()
    # Eléments qui resteront à la même place
    for _ in range(n - 2):
        x = defile(f)
        enfile(f2, x)
    # f ne contient plus que l'élément qui était en queue, et qui passera en tête
    while not est_vide(f2):
        x = defile(f2)
        enfile(f, x)  # Ordre inchangé pour ces valeurs là
    enfile(f, tete)


if __name__ == '__main__':
    # tester les fonctions
    f = creer_file()
    enfile(f, 3)
    enfile(f, 5)
    enfile(f, 8)
    enfile(f, 1)
    enfile(f, 15)
    print(f)
    print('La hauteur de la pile est {}.'.format(taille(f)))
    defile(f)
    print(f)
    print('La hauteur de la pile est {}.'.format(taille(f)))
    a = defile(f)
    print(f)
    print('Le dernier élément défilé est {}.'.format(a))
    print('La hauteur de la pile est {}.'.format(taille(f)))
    print('L\'élément en tête est {}.'.format(tete(f)))
    print('L\'élément en queue est {}.'.format(queue(f)))
    echange_tete_queue(f)
    print(f)
    print('L\'élément en tête est {}.'.format(tete(f)))
    print('L\'élément en queue est {}.'.format(queue(f)))


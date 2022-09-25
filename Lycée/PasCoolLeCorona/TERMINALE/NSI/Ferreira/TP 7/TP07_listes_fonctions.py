def creer_liste():
    """Crée une liste vide"""
    pass


def est_vide(liste):
    """Renvoie un booléen, vrai si liste est vide, faux sinon"""
    pass


def tete(liste):
    """Renvoie la valeur du premier maillon de la liste,
       ou None si la liste est vide"""
    pass


def queue(liste):
    """Renvoie la liste sans son premier maillon
       ou None si la liste est vide"""
    pass


def ajout_en_tete(valeur, liste):
    """Ajoute valeur dans un maillon ajouté en tête de liste"""
    pass


def supprime_en_tete(liste):
    """Renvoie un tuple composé de la valeur du premier maillon
       et de la liste à laquelle on a enlevé le premier maillon"""
    pass


if __name__ == "__main__":
    print('-' * 14)
    print('Tests du 1.1.')
    print('-' * 14)

    l = creer_liste()
    print(est_vide(l))  # Affiche True
    l = ajout_en_tete(3, l)  # La liste l contient l'élément 3
    print(est_vide(l))  # Affiche False
    l = ajout_en_tete(5, l)  # La tête de la liste l contient l'élément 5, la queue contient l'élément 3
    print(l)  # Affiche [5, [3, []]]
    l = ajout_en_tete(8, l)  # La tête de la liste l contient l'élément 8, la queue contient les éléments 5 et 3
    print(l)  # Affiche [8, [5, [3, []]]]
    t, l = supprime_en_tete(l)  # La variable t vaut 8, la tête de la liste l contient l'élément 5, la queue contient l'élément 3
    print(l)  # Affiche [5, [3, []]]
    print(t)  # Affiche 8
    l1 = creer_liste()
    l2 = ajout_en_tete(8, ajout_en_tete(5, ajout_en_tete(3, l1)))
    print(l2)  # Affiche [8, [5, [3, []]]]


    print('\n' * 2)
    print('-' * 14)
    print('Tests du 1.2.')
    print('-' * 14)

    l = creer_liste()
    print(l)
    l = ajout_en_tete(10, l)
    print(l)
    l = ajout_en_tete(9, l)
    print(l)
    l = ajout_en_tete(7, l)
    print(l)
    l1 = creer_liste()
    l2 = ajout_en_tete(5, ajout_en_tete(3, ajout_en_tete(2, ajout_en_tete(1, ajout_en_tete(0, l1)))))
    print(l2)

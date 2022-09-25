from TP07_listes_fonctions_corrige import *


def str_liste(liste):
    """Renvoie une chaîne de caractère correspondant à la liste sous la forme
       [valeur1] - [valeur2] - ... - [dernière valeur] - X """
    pass


def taille(liste):
    """Renvoie le nombre de maillons de la liste"""
    pass


def ajout_en_fin(valeur, liste):
    """Ajoute valeur dans un maillon en fin de liste"""
    pass 


def valeur_en_fin(liste):
    """Renvoie la valeur du dernier maillon de la liste"""
    pass


def supprime_dernier_maillon(liste):
    """Renvoie la liste sans son dernier maillon"""
    pass


def supprime_en_fin(liste):
    """Renvoie un tuple composé de la valeur du dernier maillon
       et de la liste à laquelle on a enlevé le dernier maillon"""
    pass


def maximum(a, b):
    """Renvoie le max des 2 nombres a et b"""
    pass


def max_liste(liste):
    """Retourne la valeur maximale de la liste"""
    pass


def minimum(a, b):
    """Renvoie le min des 2 nombres a et b"""
    pass


def min_liste(liste):
    """Retourne la valeur minimale de la liste"""
    pass


def enlever_valeur(valeur, liste):
    """Retourne la liste, sans l'éventuel premier maillon contenant valeur"""
    pass


def tri_croissant(liste):
    """Retourne la liste, triée par ordre croissant"""
    pass


def tri_decroissant(liste):
    """Retourne la liste, triée par ordre décroissant"""
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
    print(str_liste(l))  # Affiche [5, [3, []]]
    l = ajout_en_tete(8, l)  # La tête de la liste l contient l'élément 8, la queue contient les éléments 5 et 3
    print(str_liste(l))  # Affiche [8, [5, [3, []]]]
    t, l = supprime_en_tete(l)  # La variable t vaut 8, la tête de la liste l contient l'élément 5, la queue contient l'élément 3
    print(str_liste(l))  # Affiche [5, [3, []]]
    print(t)  # Affiche 8
    l1 = creer_liste()
    l2 = ajout_en_tete(8, ajout_en_tete(5, ajout_en_tete(3, l1)))
    print(str_liste(l2))  # Affiche [8, [5, [3, []]]]


    print('\n' * 2)
    print('-' * 14)
    print('Tests du 1.2.')
    print('-' * 14)

    l = creer_liste()
    print(str_liste(l))
    l = ajout_en_tete(10, l)
    print(str_liste(l))
    l = ajout_en_tete(9, l)
    print(str_liste(l))
    l = ajout_en_tete(7, l)
    print(str_liste(l))
    l1 = creer_liste()
    l2 = ajout_en_tete(5, ajout_en_tete(3, ajout_en_tete(2, ajout_en_tete(1, ajout_en_tete(0, l1)))))
    print(str_liste(l2))


#     print('\n' * 2)
#     print('-' * 14)
#     print('Tests du 2.1.')
#     print('-' * 14)
# 
#     l = creer_liste()
#     print(str_liste(l))
#     l = ajout_en_tete(10, l)
#     print(str_liste(l))
#     l = ajout_en_tete(9, l)
#     print(str_liste(l))
#     l = ajout_en_tete(7, l)
#     print(str_liste(l))
#     l1 = creer_liste()
#     l2 = ajout_en_tete(5, ajout_en_tete(3, ajout_en_tete(2, ajout_en_tete(1, ajout_en_tete(0, l1)))))
#     print(str_liste(l2))
#     t, l2 = supprime_en_tete(l2)
#     print(t, str_liste(l2))
#     t, l2 = supprime_en_tete(l2)
#     print(t, str_liste(l2))
# 
# 
#     print('\n' * 2)
#     print('-' * 14)
#     print('Tests du 2.2.')
#     print('-' * 14)
# 
#     l = creer_liste()
#     print(str_liste(l))
#     print(f'La taille de la liste est {taille(l)}.')
#     print(f'Le maximum de la liste est {max_liste(l)}.')
#     print(f'Le minimum de la liste est {min_liste(l)}.')
#     l = ajout_en_tete(10, l)
#     print(str_liste(l))
#     print(f'La taille de la liste est {taille(l)}.')
#     print(f'Le maximum de la liste est {max_liste(l)}.')
#     print(f'Le minimum de la liste est {min_liste(l)}.')
#     l = ajout_en_fin(9, l)
#     print(str_liste(l))
#     print(f'La taille de la liste est {taille(l)}.')
#     print(f'Le maximum de la liste est {max_liste(l)}.')
#     print(f'Le minimum de la liste est {min_liste(l)}.')
#     l = ajout_en_tete(7, l)
#     print(str_liste(l))
#     print(f'La taille de la liste est {taille(l)}.')
#     print(f'Le maximum de la liste est {max_liste(l)}.')
#     print(f'Le minimum de la liste est {min_liste(l)}.')
#     l1 = creer_liste()
#     l2 = ajout_en_fin(5, ajout_en_tete(3, ajout_en_fin(2, ajout_en_tete(1, ajout_en_tete(0, l1)))))
#     print(str_liste(l2))
#     print(f'La taille de la liste est {taille(l)}.')
#     print(f'Le maximum de la liste est {max_liste(l2)}.')
#     print(f'Le minimum de la liste est {min_liste(l2)}.')
#     t, l2 = supprime_en_fin(l2)
#     print(f'\nOn supprime le dernier élément.\nSa valeur est {t}.\nLa liste est maintenant :\n{str_liste(l2)}.')
#     print(f'Le maximum de la liste est {max_liste(l2)}.')
#     print(f'Le minimum de la liste est {min_liste(l2)}.')
#     t, l2 = supprime_en_fin(l2)
#     print(f'\nOn supprime le dernier élément.\nSa valeur est {t}.\nLa liste est maintenant :\n{str_liste(l2)}.')
#     print(f'Le maximum de la liste est {max_liste(l2)}.')
#     print(f'Le minimum de la liste est {min_liste(l2)}.')
#     l2 = ajout_en_fin(5, ajout_en_tete(2, ajout_en_fin(2, ajout_en_tete(5, ajout_en_tete(0, l1)))))
#     print(str_liste(l2))
#     l2 = enlever_valeur(2, l2)
#     print('On supprime la valeur 2.')
#     print(str_liste(l2))
#     l2 = enlever_valeur(5, l2)
#     print('On supprime la valeur 5.')
#     print(str_liste(l2), '\n')
#     l2 = ajout_en_fin(5, ajout_en_tete(2, ajout_en_fin(2, ajout_en_tete(5, ajout_en_tete(0, l1)))))
#     print(str_liste(l2))
#     l2 = tri_croissant(l2)
#     print('Tri de la liste par ordre croissant.')
#     print(str_liste(l2), '\n')
#     l2 = ajout_en_fin(5, ajout_en_tete(2, ajout_en_fin(2, ajout_en_tete(5, ajout_en_tete(0, l1)))))
#     print(str_liste(l2))
#     l2 = tri_decroissant(l2)
#     print('Tri de la liste par ordre décroissant.')
#     print(str_liste(l2))

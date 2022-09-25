class Maillon:
    def __init__(self, contenu, suivant=None):
        self.contenu = contenu
        self.suivant = suivant
    
    def __str__(self):
        if self.contenu is None:
            return 'X'
        if self.suivant is None:
            return f'[{str(self.contenu)}] - X'
        return f'[{str(self.contenu)}] - {str(self.suivant)}'


class Liste_chainee:                    
    def __init__(self, premier=None):  # Constructeur
        self.premier = Maillon(premier)

    def __str__(self):
        return str(self.premier)

    def affiche_tete(self):
        if self.premier.contenu is None: # Pas de tête dans une chaîne vide
            return None
        return f'La tête de la liste {self} est : {self.premier.contenu}'
    
    def affiche_queue(self):
        if self.premier.contenu is None: # Pas de queue dans une chaîne vide
            return None
        pass

    def ajout_en_tete(self, valeur):  # Ajoute d'un élément en tête de liste
        # self.premier = Maillon(...) # A compléter
        pass

    def supprime_en_tete(self):  # Supprime l'élément en tête de liste
        if self.premier.contenu is None:  # On ne peut pas supprimer dans une chaîne vide
            return None 
        # premiere_valeur = ... # A compléter
        pass

    def taille(self):                          
        if self.premier is None:  # Une liste vide a une taille nulle
            return 0
        pass

    def ajout_en_fin(self, valeur):  # Ajout d'un élément en fin de liste
        pass

    def supprime_en_fin(self):  # Supprime l'élément en tête de liste
        if self.premier == None:  # On ne peut pas supprimer dans une chaîne vide
            return None 
        pass


if __name__ == "__main__":
    print('-' * 28)
    print('Tests de la classe Maillon')
    print('-' * 28)

    l = Maillon(3, Maillon(5, Maillon(1)))
    print(f'Contenu du premier maillon : {l.contenu}')
    print(f'Contenu du second maillon : {l.suivant.contenu}')
    print(f'Contenu du Troisième maillon : {l.suivant.suivant.contenu}')
    print(f'Liste chaînée :\n {l}')


    print('\n' * 2)
    print('-' * 28)
    print('Tests de la classe Liste_chainee')
    print('-' * 28)

#     lc = Liste_chainee()
#     print(f'Liste chaînée :\n {lc}')
#     lc.ajout_en_fin(5)
#     print(f'Ajout de la valeur 5 en fin :\n {lc}')
#     lc.ajout_en_fin(3)
#     lc.ajout_en_fin(2)
#     print(f'Ajout des valeurs 3 puis 2 en fin :\n {lc}')
#     print(f'Taille de la liste : {lc.taille()}\n')
#     lc.supprime_en_fin()
#     print(f'Suppression de la valeur en fin :\n {lc}')
#     print(f'Taille de la liste : {lc.taille()}\n')
#     lc.ajout_en_tete(4)
#     lc.ajout_en_tete(8)
#     print(f'Ajout des valeurs 4 puis 8 en tête :\n {lc}')
#     lc.supprime_en_tete()
#     lc.supprime_en_tete()
#     print(f'Suppression des deux valeurs en tête :\n {lc}')
#     print(lc.affiche_tete())
#     print(lc.affiche_queue())

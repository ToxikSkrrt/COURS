# Implémentation d'un TAD en POO : les piles
class Pile:
    def __init__(self):
        """ Initialisation d’une pile."""
        self.tab1 = []

    def est_vide(self):
        """ Teste si une pile p est vide."""
        pass

    def empile(self, a):
        """ Ajoute l'element x à la pile."""
        pass
   
    def depile (self):
        """ Enlève le sommet de la pile p, et le renvoie.
        - Échoue si la pile est vide (renvoie une erreur).
        """
        pass

    def sommet(self):
        """ Retourne le dernier élément ajouté"""
        pass

    def hauteur(self):
        """ Calcule la hauteur n de la pile p.
        """
        pass
    
    def __str__(self):  # Hors-Programme : pour afficher 
        longueur = len(self.tab1)
        i = 0
        affichage = ''
        for elt in self.tab1[::-1]:
            affichage += '\t' + str (elt) + '\n'
        affichage = '***************\n' +\
                    'Haut de la Pile \n' +\
                    affichage +\
                    'Bas de la Pile \n' +\
                    '***************\n'
        return affichage

if __name__ == '__main__':
    # tester les fonctions
    pass



# Implémentation abstraite de piles
class Pile:
    def __init__(self):
        """ Initialisation d’une pile."""
        self.tab1 = []

    def est_vide(self):
        """ Teste si une pile p est vide."""  
        return self.tab1 == []

    def empile(self, x):
        """ Ajoute l'element x à la pile."""
        self.tab1.append(x)

    def depile(self):
        """ Enlève le sommet de la pile p, et le renvoie.
        - Échoue si la pile est vide (renvoie une erreur).
        """
        assert not (self.est_vide()), 'La pile est vide : on ne peut pas la dépiler.'
        return self.tab1.pop() 

    def sommet(self):
        """ Retourne le dernier élément ajouté."""
        assert not (self.est_vide()), ' La pile est vide : pas de sommet.'
        top = self.depile()
        self.empile(top)
        return top # dernier élément ajouté

    def hauteur(self):
        """ Calcule la hauteur n de la pile p.
        """
        n = 0
        p2 = Pile()
        while not self.est_vide():
            x = p.depile()
            p2.empile(x)
            n += 1
        while not p2.est_vide():
            x = p2.depile()
            self.empile(x)
        return n

    def echange_haut_bas(self):
        """ Échange le sommet et le fond de la pile p (p[-1] <-> p[0])."""
        # On dépile
        top = self.depile()
        p2 = Pile()
        while not self.est_vide():
            x = p.depile()
            p2.empile(x)
        bottom = p2.depile()
        # On rempile
        self.empile(top)
        while not p2.est_vide():
            x = p2.depile()
            self.empile(x)  # Ordre inchangé pour ces valeurs là
        self.empile(bottom)

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
    p = Pile()
    p.empile(3)
    p.empile(5)
    p.empile(10)
    p.empile(12)
    print(p)
    print('La hauteur de la pile est {}\n'.format(p.hauteur()))
    p.echange_haut_bas()
    print("Pile après échange de l'élément du haut avec celui du bas :")
    print(p)
    p.depile()
    print('Pile après que le premier élément soit dépilé :')
    print(p)
    p.depile()
    print('Pile après que le second élément soit dépilé :')
    print(p)
    p.depile()
    print('Pile après que le troisième élément soit dépilé :')
    print(p)
    p.depile()
    print('Pile après que le quatrième élément soit dépilé :')
    print(p)
    #  p.depile()


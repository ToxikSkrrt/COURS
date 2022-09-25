# Implémentation abstraite de piles
class File:
    def __init__(self):
        """ Initialisation d’une file."""
        self.tab1 = []

    def est_vide(self):
        """ Teste si une file f est vide."""  
        return self.tab1 == []

    def enfile(self, x):
        """ Ajoute l'element x à la file."""
        self.tab1.append(x)

    def defile(self):
        """Supprime et renvoie le premier élément de la file f
        - Échoue si la file est vide (renvoie une erreur).
        """
        assert not (self.est_vide()), 'La file est vide : on ne peut pas la défiler.'
        return self.tab1.pop(0) 

    def tete(self):
        """ Renvoie la valeur à la tête de la file f, sans modifier f."""
        assert not (self.est_vide()), 'La file est vide : elle ne contient pas d\'élément.'
        return self.tab1[0]

    def queue(self):
        """ Renvoie la valeur à la queue de la file f, sans modifier f."""
        assert not (self.est_vide()), 'La file est vide : elle ne contient pas d\'élément.'
        return self.tab1[-1]

    def taille(self):
        """ Calcule la hauteur n de la file f. """
        # Ne pas utiliser len() de Python
        n = 0
        # On déplace les valeurs dans f vers f2 une autre pile
        f2 = File()
        while not self.est_vide():
            x = f.defile()
            f2.enfile(x)
            n += 1
        # n = len(p) maintenant, on doit remettre la file
        while not f2.est_vide():
            x = f2.defile()
            self.enfile(x)
        return n

    def echange_tete_queue(self):
        """ Échange la tete et la queue de la file f (f[-1] <-> f[0])."""
        n = self.taille()
        tete = self.defile()
        f2 = File()
        # Eléments qui resteront à la même place
        for _ in range(n - 2):
            x = self.defile()
            f2.enfile(x)
        # f ne contient plus que l'élément qui était en queue, et qui passera en tête
        while not f2.est_vide():
            x = f2.defile()
            self.enfile(x)  # Ordre inchangé pour ces valeurs là
        self.enfile(tete)

    def __str__(self):  # Hors-Programme : pour afficher 
        longueur = len(self.tab1)
        i = 0
        affichage = ''
        for elt in self.tab1:
            affichage += '\t' + str (elt) + '\n'
        affichage = '****************\n' +\
                    'Tête de la File \n' +\
                    affichage +\
                    'Queue de la File \n' +\
                    '****************\n'
        return affichage
        pass


if __name__ == '__main__':
    # tester les fonctions
    f = File()
    f.enfile(3)
    f.enfile(5)
    f.enfile(8)
    print(f)
    print('La hauteur de la file est {}\n'.format(f.taille()))
    print('Element en tête de la file est {}\n'.format(f.tete()))
    print('Element en queue de la file est {}\n'.format(f.queue()))
    f.echange_tete_queue()
    print("File après échange de l'élément de tête avec celui en queue :")
    print(f)
    print('Element en tête de la file est {}\n'.format(f.tete()))
    print('Element en queue de la file est {}\n'.format(f.queue()))
    f.defile()
    print('File après que le premier élément soit défilé :')
    print(f)
    f.defile()
    print('File après que le second élément soit défilé :')
    print(f)
    f.defile()
    print('File après que le troisième élément soit défilé :')
    print(f)
    #  p.depile()


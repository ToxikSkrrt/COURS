class Noeud:
    arbre_vide = None

    def __init__(self, etiquette, gauche, droit):
        """Renvoie un arbre dont la racine contient etiquette
           gauche est le sous-arbre gauche de la racine
           droit est le sous-arbre droit de la racine"""
        self._etiquette = etiquette
        self._gauche = gauche
        self._droit = droit

    def etiquette(self):
        """Renvoie le contenu de la racine de l'arbre"""
        return self._etiquette

    def gauche(self):
        """Renvoie le sous-arbre gauche de l'arbre"""
        return self._gauche

    def droit(self):
        """Renvoie le sous-arbre droit de l'arbre"""
        return self._droit

    def est_vide(arbre):
        """Renvoie un booléen, vrai si l'arbre est vide, faux sinon"""
        return arbre is Noeud.arbre_vide

    def represente(arbre, profondeur=0):
        """Affiche l'arbre"""
        if Noeud.est_vide(arbre):
            print('-' * (profondeur) + '*')
        else:
            print('-' * profondeur + str(arbre.etiquette()))
            Noeud.represente(arbre.gauche(), profondeur + 1)
            Noeud.represente(arbre.droit(), profondeur + 1)

# =========================
# Méthodes supplémentaires
# =========================

    def est_feuille(self):
        """Renvoie un booléen, vrai si l'arbre est une feuille, faux sinon"""
        return Noeud.est_vide(self.gauche()) and Noeud.est_vide(self.droit())
    
    def compte_feuille (self):
        """Renvoie un entier, le nombre de feuilles de l'arbre"""
        if self.est_feuille():
            return 1 
        n = 0
        if not Noeud.est_vide(self.gauche()):
            n += self.gauche().compte_feuille()
        if not Noeud.est_vide(self.droit()):
            n += self.droit().compte_feuille()
        return n
    
    def taille (self):
        """Renvoie un entier, la taille de l'arbre"""
        if self.est_feuille():
            return 1 
        n = 1
        if not Noeud.est_vide(self.gauche()):
            n += self.gauche().taille()
        if not Noeud.est_vide(self.droit()):
            n += self.droit().taille()
        return n
    
    def hauteur (self):
        """Renvoie un entier, la hauteur de l'arbre"""
        if self.est_feuille():
            return 0
        h1 = 0
        h2 = 0
        if not Noeud.est_vide(self.gauche()):
            h1 = 1 + self.gauche().hauteur()
        if not Noeud.est_vide(self.droit()):
            h2 = 1 + self.droit().hauteur()
        return max(h1,h2)

if __name__ == '__main__':
    arbre1 = Noeud(3, Noeud(1, Noeud(1, Noeud.arbre_vide, Noeud.arbre_vide), Noeud.arbre_vide),
                 Noeud(4, Noeud(5, Noeud.arbre_vide, Noeud.arbre_vide),
                       Noeud(9, Noeud.arbre_vide, Noeud.arbre_vide)))
    Noeud.represente(arbre1)
    print("Arbre 1 est une feuille : ", arbre1.est_feuille())
    print("Nombre de feuilles : ", arbre1.compte_feuille())
    print("Taille : ", arbre1.taille())
    print("Hauteur : ", arbre1.hauteur())

    arbre2 = Noeud(8, Noeud.arbre_vide, Noeud.arbre_vide)
    Noeud.represente(arbre2)
    print("Arbre 2 est une feuille : ", arbre2.est_feuille())
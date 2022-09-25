class Noeud:
    arbre_vide = None

    def __init__(self, etiquette, gauche, droit):
        self._etiquette = etiquette
        self._gauche = gauche
        self._droit = droit

    def etiquette(self):
        pass

    def gauche(self):
        pass

    def droit(self):
        pass

    def est_vide(arbre):
        return arbre is Noeud.arbre_vide

# =========================
# Méthodes supplémentaires
# =========================


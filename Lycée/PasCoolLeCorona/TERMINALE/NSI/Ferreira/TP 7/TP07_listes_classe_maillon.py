class Maillon:
    def __init__(self, contenu=None, suivant=None):
        self.contenu = contenu
        self.suivant = suivant
    
    def __str__(self):
        if self.contenu is None:
            return 'X'
        elif self.suivant is None:
            return f'[{str(self.contenu)}] - X'
        return f'[{str(self.contenu)}] - {str(self.suivant)}'


if __name__ == "__main__":
    print('-' * 28)
    print('Tests de la classe Maillon')
    print('-' * 28)

    l = Maillon(3, Maillon(5, Maillon(1)))
    print(f'Contenu du premier maillon : {l.contenu}')
    print(f'Contenu du second maillon : {l.suivant.contenu}')
    print(f'Contenu du Troisième maillon : {l.suivant.suivant.contenu}')
    print(f'Liste chaînée :\n {l}')

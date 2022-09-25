import TP06_piles_classe as pf


class File:
    def __init__(self):
        self.entree = pf.Pile()
        self.sortie = pf.Pile()
   
    def est_vide(self):
        return self.entree.est_vide() and self.sortie.est_vide()

    def enfile(self,x):
        self.entree.empile(x)

    def defile(self):
        if self.est_vide():
            raise IndexError("File vide !")
        if self.sortie.est_vide() == True :
            while not self.entree.est_vide():
                self.sortie.empile(self.entree.depile())
        return self.sortie.depile()
    
    def __str__(self):       # Hors-Programme : pour afficher 
        '''
        s = "|"              # convenablement la file avec print(p)
                
        for elt in self.entree.tab1[::-1]:
                s = s + str(elt) + "|"
        for elt in self.sortie.tab1[::]:
            s = s + str(elt) + "|"
        return s
        '''
        affichage=''
        for elt in self.sortie.tab1[::-1]:
            affichage += '\t'+str(elt)+'\n'
        for elt in self.entree.tab1[::]:
            affichage += '\t'+str(elt)+'\n'    
        
            
        affichage = '***************\n'+\
                    'Début de la File \n'+ \
                     affichage +\
                    'Fin de la File \n'+\
                    '***************\n'
        return affichage

if __name__ == '__main__':

    f = File()
    f.enfile(1)
    f.enfile(2)
    f.enfile(3)
    print(f)
    f.defile()
    f.enfile(4)
    f.enfile(5)
    print(f)
    f.defile()
    f.defile()
    f.enfile(6)
    print(f)

import TP06_piles_fonctions as pf


def verification_syntaxique(expression):
    pile = pf.creer_pile()
    assert expression,"l'expression saisie est vide"
    for car in expression:
        if pf.est_vide(pile) and car == ')':
            return False
        elif car == '(':
            pf.empile(pile, car)
        elif car == ')':
            pf.depile(pile)
    return pf.est_vide(pile)


def verification_syntaxique2(expression):
    pile = pf.creer_pile()
    assert expression,"l'expression saisie est vide"
    for car in expression:
        if pf.est_vide(pile) and (car == ')' or car == ']'):
            return False
        elif car == '(' or car == '[':
            pf.empile(pile, car)
        elif car == ')':
            if pf.sommet(pile) == '(':
                pf.depile(pile)
            else:
                return False
        elif car == ']':
            if pf.sommet(pile) == '[':
                pf.depile(pile)
            else:
                return False
    return pf.est_vide(pile)


if __name__ == '__main__':
    liste_expressions = ['a(b(c(d)e)f', 'a(b(c)d)e)f', 'a(bc(d)e)f']
    liste_reponses = [False, False, True]
    liste_expressions2 = liste_expressions +\
                        ['a(b[c(d)e)f', 'a(b(c]d)e)f', '[a(bc[d]e)f]']
    liste_reponses2 = liste_reponses + [False, False, True]
    
    for i, expression in enumerate(liste_expressions):
        assert verification_syntaxique(expression) == liste_reponses[i],\
               "Le test de verification syntaxique échoue pour l'expression {}"\
               .format(expression)
    print("Les tests de la fonction verification_syntaxique sont bons")

    
    for i, expression in enumerate(liste_expressions2):
        assert verification_syntaxique2(expression) == liste_reponses2[i],\
               "Le test de verification syntaxique2 échoue pour l'expression {}"\
               .format(expression)
    print("Les tests de la fonction verification_syntaxique2 sont bons")
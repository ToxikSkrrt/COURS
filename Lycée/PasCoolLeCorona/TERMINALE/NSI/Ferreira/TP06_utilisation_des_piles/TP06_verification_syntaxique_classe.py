import TP06_piles_classe as pf


def verification_syntaxique(expression):
    pile = pf.Pile()
    assert expression,"l'expression saisie est vide"
    for car in expression:
        if pile.est_vide() and car == ')':
            return False
        elif car == '(':
            pile.empile(car)
        elif car == ')':
            pile.depile()
    return pile.est_vide()


def verification_syntaxique2(expression):
    pile = pf.Pile()
    assert expression,"l'expression saisie est vide"
    for car in expression:
        if pile.est_vide() and (car == ')' or car == ']'):
            return False
        elif car == '(' or car == '[':
            pile.empile(car)
        elif car == ')':
            if pile.sommet() == '(':
                pile.depile()
            else:
                return False
        elif car == ']':
            if pile.sommet() == '[':
                pile.depile()
            else:
                return False
    return pile.est_vide()


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

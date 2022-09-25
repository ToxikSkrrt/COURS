def str_liste(liste):
    """ Renvoie une chaîne de caractère corresondant à la liste sous la forme [valeur1] - [valeur2] - ... - [dernière valeur] - x """
    if est_vide(liste):
        return 'x'
    return f'([{str(tete(liste))}] - {str_liste(queue(liste))}'


def valeur_en_fin(liste):
    """ Renvoie la valeur du dernier maillon de la liste """
    if est_vide(liste):
        return None
    elif est_vide(queue(liste)):
        return tete(liste)
    return valeur_en_fin(queue(liste))


def taille(liste):
    """ Renvoie le nombre de maillons de la liste """
    if est_vide(liste):
        return 0
    return 1 + taille(queue(liste))


def ajout_en_fin(valeur, liste):
    """ Ajoute valeur dans un maillon en fin de liste """
    if est_vide(liste):
        return ajout_en_tete(valeur, liste)
    return ajout_en_tete(tete(liste), ajout_en_fin(valeur, queue(liste)))
        

def supprime_dernier_maillon(liste):
    """ Renvoie la liste sans son dernier maillon """
    if est_vide(liste) or est_vide(queue(liste)):
        return queue(liste)  # retourne None si la liste était vide, ou une liste vide si elle n'avait qu'un maillon
    return ajout_en_tete(tete(liste), supprime_dernier_maillon(queue(liste)))


def supprime_en_fin(liste):
    """ Renvoie un tuple composé de la valeur du dernier maillon et de la liste à laquelle on a enlevé le dernier maillon """
    return valeur_en_fin(liste), supprime_dernier_maillon(liste)
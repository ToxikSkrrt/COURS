def tri_insertion(liste):
    for i in range(1, len(liste)):  # on parcourt la liste du deuxième élément jusqu'au dernier
        k = i    # indice initial de la clef
        clef = liste[i]    # valeur à insérer
        while k > 0 and clef < liste[k - 1]:
            liste[k] = liste[k - 1]    # on décale la valeur vers la droite
            k -= 1   # on diminue de 1 l'indice temporaire de la clef i.e. on la décale d'un cran vers la gauche
        liste[k] = clef   # on sort de la boucle while lorsqu'on a trouvé la bonne position pour la clef
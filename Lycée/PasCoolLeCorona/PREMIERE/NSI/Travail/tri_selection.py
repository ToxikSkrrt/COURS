def tri_selection(liste):
    for i in range(len(liste) - 1):
        i_mini = i  # indice initial du minimum
        mini = liste[i] # valeur initiale du minimum
        for j in range(i + 1, len(liste)):
            if liste[j] < mini:
                i_mini = j # nouvel indice temporaire du minimum
                mini = liste[j] # nouvelle valeur temporaire du minimum
        liste[i], liste[i_mini] = liste[i_mini], liste[i]
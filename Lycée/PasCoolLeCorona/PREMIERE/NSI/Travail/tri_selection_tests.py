def tri_selection(liste):
    for i in range(len(liste) - 1):
        i_mini = i  # indice initial du minimum
        mini = liste[i] # valeur initiale du minimum
        for j in range(i + 1, len(liste)):
            if liste[j] < mini:
                i_mini = j # nouvel indice temporaire du minimum
                mini = liste[j] # nouvelle valeur temporaire du minimum
        liste[i], liste[i_mini] = liste[i_mini], liste[i]

liste1 = [4, 2, 8, 10, 6]
liste2 = [10, 8, 6, 4, 2]
liste3 = []
liste4 = [5, 5, 4, 3, 3]

tri_selection(liste1)
tri_selection(liste2)
tri_selection(liste3)
tri_selection(liste4)
print(liste1, liste2, liste3, liste4)
tab = [2, 4, 3, 5, 9, 6, 8, 9, 9]
def fonction1(tab1):
    r1 = 0
    for i in range(len(tab1)):
        r1 += tab1[i]
    return r1
print(fonction1(tab))
def fonction2(n2):
    r2 = 0
    for j in range(len(n2)):
        r2 += n2[j]
    return r2 / len(n2)
print(fonction2(tab))
def fonction3(n3):
    croissant = list(sorted(n3))  # on classe la liste dans un ordre croissant
    if len(croissant) % 2 == 0:  # on voit si la liste est paire
        r3 = len(croissant) // 2        
        r3 = (croissant[r3] + croissant[r3 - 1]) / 2  # on fait la moyenne entre les 2 nombres du milieu de la liste croissante
        return r3
    else:
        r3 = croissant[len(croissant) // 2]  # on choisit le nombre au milieu de la liste croissante si liste impaire
        return r3
print(fonction3(tab))
        
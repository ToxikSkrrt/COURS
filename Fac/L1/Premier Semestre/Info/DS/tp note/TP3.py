def somme(L):
    s = 0
    for valeur in L:
        s += valeur
    return s

# Exo 1
def sommeRec(L, n):
    if n == 0:
        return 0
    return L[n - 1] + sommeRec(L, n - 1)

#print(f'Exo 1 : {sommeRec([1, 5, 4, 5], 4)}\n')

# Exo 2
def polp(chaine, n):
    if n == 0:
        return ''
    return chaine[n - 1] + polp(chaine, n - 1)

#print(f"Exo 2 : {polp('polp', 4)}\n")

# Exo 3
def binaireRec(chaine, n):
    if n == 0:
        return ''
    if chaine[n - 1] == '0':
        return '1' + binaireRec(chaine, n - 1)
    if chaine[n - 1] == '1':
        return '0' + binaireRec(chaine, n - 1)

#print(f"Exo 3 : {binaireRec('0110', 4)}\n")

# Exo 4
def sommeTabRec(tab, i, n):
    if n - 1 == i and tab[n - 1] >= 0:
        return tab[i]
    elif n - 1 == i and tab[n - 1] < 0:
        return 0
    if tab[n - 1] >= 0:
        return tab[n - 1] + sommeTabRec(tab, i, n - 1)
    else:
        return sommeTabRec(tab, i, n - 1)

#print(f'Exo 4 : {sommeTabRec([2, 3, -1, 4], 0, 4)}\n')

# Exo 5
def tabTrieRec(tab, n):
    if n == 0:
        return True
    if tabTrieRec(tab, n - 1) < tabTrieRec(tab, n):
        return True
    else:
        return False
    
#print(f'Exo 5 :\nTest sur tableau trié : {tabTrieRec([1, 2, 3, 4, 5], 5)}\nTest sur tableau non trié : {tabtrieRec([1, 2, 4, 5, 6], 5)}')///
    
def plop(m, x0, y0, x, y, acc = 0):
    if x0 < x or y0 < y:
        if x0 == x and y0 == y:
            return 1
        if (m[x0][y0 + 1] == 0) or (m[x0 + 1][y0] == 0):
            return 0
        return  acc + plop(m, x0+1, y0, x, y) + plop(m, x0, y0 + 1, x, y)
    else:
        return 0
    
m = [[1, 1, 1, 1],
     [1, 0, 1, 1],
     [0, 1, 1, 1],
     [1, 1, 1, 1]]

print(plop(m, 0, 0, 3, 3))
def insert(t, n, elt, k):
    for i in range(n, k, -1):
        t[i] = t[i - 1]
    t[k] = elt
    return n + 1


def delete(t, n, k):
    for i in range(k, n - 1):
        t[i] = t[i + 1]
    return n - 1

t1 = [1, 2, 3, 4, 5, 6, 7, 8, 9]
print(delete(t1, 9, 0))
print(t1)

def amplitude(t, n):
    minimum = t[0]
    maximum = t[0]
    for i in range(n):
        if t[i] < minimum:
            minimum = t[i]
        if t[i] > maximum:
            maximum = t[i]
    return maximum - minimum

t2 = [0, 2, 8, 9, -2, 5, 70, 6]
print(amplitude(t2, 7))

def max2(t, n):
    maximum1 = t[0]
    maximum2 = t[0]
    for i in range(n):
        if t[i] > maximum1:
            maximum2 = maximum1
            maximum1 = t[i]
    return maximum2

print(max2(t2, 7))

def search(tab, n, p):
    index = -1
    for i in range(n):
        if tab[i] == p:
            index = i
    return index

t3 = [2, 3, 1, 2, 2, 4]
print(search(t3, 5, 2))

def swap(tab, i, j):
    tab[i], tab[j] = tab[j], tab[i]
    return tab

print(swap(t3, 1, 5))

'''def insert_order(t, n, elt):
    for i in range(n-1):
        if elt >= t[i]:'''
            
            
t4 = [2, 4, 7, 10, 15, 20, 25, None, None, None]

def deleteFirstInstance(t, n, elt):
    for i in range(n):
        if t[i] == elt:
            return delete(t, n, i)
    return n

t5 = [0, 2, 6, 8, 9, 7]
print('\ndeleteFirstInstances')
print(deleteFirstInstance(t5, 6, 8))
print(t5)

def deleteInstances(t, n, elt):
    suppr = 0 # Nombre d'élements supprimés
    for i in range(n):
        if t[i] != elt:
            t[i - suppr] = t[i]
        else:
            suppr += 1 # J'ai trouvé un elt de plus
    return n - suppr

t6 = [0, 6, 5, 4, 5, 3, 2, 5]
print('\ndeleteInstances')
print(deleteInstances(t6, 8, 5))
print(t6)
def compteur_rec(n):
    if n == 0:
        print(n) 
    else:
        compteur_rec(n - 1)
        print(n)


def compteur_rec2(n, i = 0):
    if i == n:
        print(i) 
    else:
        print(i)
        compteur_rec2(n, i + 1)


compteur_rec(10)
compteur_rec2(10)



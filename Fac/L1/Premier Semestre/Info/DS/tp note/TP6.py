from random import randint as rd
import time

N = 100000
T = [rd(0, 10) for i in range(N)]


def triInsertion(t, n): 
    for i in range(1, n): 
        k = t[i] 
        j = i-1
        while j >= 0 and k < t[j] : 
            t[j + 1] = t[j] 
            j -= 1
        t[j + 1] = k
        
def triFusion(T, g, n):
    if n < 2:
        return
    else:
        m = n//2
        triFusion(T, g, m)
        triFusion(T, g + m, n - m)
        fusion(T, g, n)

def fusion (T, g, n):
    tmp = [None for i in range(n)]
    i1 = g
    i2 = g + n//2
    k = 0
    while i1 < g + n//2 and i2 < g + n:
        if T[i1] < T[i2]:
            tmp[k] = T[i1]
            i1 += 1
        else:
            tmp[k] = T[i2] 
            i2 += 1
        k += 1
    while (i1 < g + n//2):
        tmp[k] = T[i1]
        i1 += 1
        k += 1
    while (i2 < g + n):
        tmp[k] = T[i2]
        i2 += 1
        k += 1
    for i in range(n):
        T[g+i] = tmp[i]

def triRapide(T, i, j):
    if i < j:   
        pivot = pivoter(T, i, j)
        triRapide(T, i, pivot)
        triRapide(T, pivot+1, j)

def pivoter(T, i, j):
    p = i
    pivot = T[i]
    g, d = i + 1, j + 1
    for k in range(g, d):
        if T[k] <= pivot:
            p += 1
            echanger(T, p, k)
    echanger(T, i, p)
    return p

def runTime(f, t, n):
    debut = time.process_time()
    f(t, n)
    fin = time.process_time()
    return round((fin - debut) * 1e3)

        
print(runTime(triInsertion, T, N))
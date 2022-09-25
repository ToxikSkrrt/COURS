from random import randint
import numpy as np

def rollDiceString(n):
    a=""
    for i in range (n):
        a += str(randint(1,6)) + ' '
    return a
        


def rollDice(n):
    a=[0]*n
    for i in range (n):
        a[i] = randint(1,6)
    return a
        


def sumValues(t,n):
    v=0
    for i in range (n):
        v += t[i]
    return v

tabDice = rollDice(5)
print(sumValues(tabDice, 5))


def oneSameSide(t, n, value):
    acc = 0
    for i in range(n):
        if t[i] == value:
            acc += 1
    return acc

print(tabDice)
print(oneSameSide(tabDice, 5, 3))

def histogram(t,n):
    histo=[0]*7
    histo[0]=n
    for i in range (n):
        histo[t[i]] += 1
    return histo

        
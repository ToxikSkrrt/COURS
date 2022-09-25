import os
import matplotlib
import time

os.getcwd()


# 1.
def readLines(filename, n):
    tab = []
    try:
        reader = open(filename, 'r')
        for i in range(n):
            tab.append(reader.readline())
    finally:
        reader.close()
        return tab

# 2.
print(f"2. {readLines('france.csv', 3)}\n")

# 3.
def readLinesBis(filename, n):
    tab = []
    try:
        reader = open(filename, 'r')
        for i in range(1, n + 1):
            tab.append(reader.readline())
    finally:
        reader.close()
        return tab
    
print(f"3. {readLinesBis('france.csv', 3)}\n")

# 4.
def runTime(f, filename, n):
    debut = time.process_time()
    f(filename, n)
    fin = time.process_time()
    return round((fin - debut) * 1e3)

print(f"4. issou {runTime(readLines, 'france.csv', 3)}\n")


# Tri

def readSeveralLines(filename, n):
    t = [''] * n
    try:
        reader = open(filename)
        # reader.readline()
        for i in range(n):
            t[i] = reader.readline()
    finally:
        reader.close()
    return t

def transforme(t, n, delimiter = ','):
    for i in range(n):
        t[i] = t[i].split(delimiter)
        



#1  number : c = 2

def triSelection(t, n):
    for i in range(1, n):
        min = i
        for j in range(i + 1, n):
            if int(t[min][2]) > int(t[j][2]):
                min = j
        temp = t[i]
        t[i] = t[min]
        t[min] = temp

def selectSort2D(t, n, c):
    transforme(t, n)
    triSelection(t, n)
    for k in range(n):
        print(t[k][c])

print(f"test : {readSeveralLines('france.csv', 6)}")
print(f"5. {selectSort2D(readSeveralLines('france.csv', 6), 6, 2)}")
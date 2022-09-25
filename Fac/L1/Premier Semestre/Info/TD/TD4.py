# EXERCICE 1


# EXERCICE 2
def checkNumbersTwo(L1, n1, L2, n2, acc = 0):
    if n1 == 0:
        return L2
    else:
        elt = L1[n1 - 1]
        if elt not in L2:
            L2[acc] = elt
            acc += 1
    return checkNumbersTwo(L1, n1 - 1, L2, n2, acc)
    

if __name__ == '__main__':
    L1 = [3, 5, 3, 4, 2, 1, 1, 3, 9]
    L2 = [None] * len(L1)
    print(f'Exercice 2 : {checkNumbersTwo(L1, len(L1), L2, len(L2))}')
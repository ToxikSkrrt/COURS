def length(L):
    acc = 0
    while L.isEmpty() == False:
        acc += 1
        L = L.next()
    return acc

def occurences(L, element):
    acc = 0
    while L.empty() == False:
        if element == L.value():
            acc += 1
        L = L.next()
    return acc

def isSorted(L):
    elt = L.value()
    L = L.next()
    while L.empty() == False:
        if elt > L.value():
            return False
        else:
            elt = L.value()
            L = L.next()
    return True

def deleteOccurence(L, element):
    pass

def reverse(L):
    pass
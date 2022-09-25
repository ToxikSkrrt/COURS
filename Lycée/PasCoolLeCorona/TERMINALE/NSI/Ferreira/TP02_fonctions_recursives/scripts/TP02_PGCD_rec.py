def pgcd_rec(a, b):
    if b == 0:
        return a
    else:
        return pgcd_rec(b, a % b)

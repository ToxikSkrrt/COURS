# EXPONENTIATION RAPIDE
# 1.
def puissanceIt(x, n):
    p = 1
    while n > 0:
        if n % 2 == 1:
            p *= x
        x *= x
        n = n // 2
    return p

def puissanceRec(x, n, p = 1):
    if n > 0:
        if n % 2 == 1:
            return puissanceRec(x * x, n // 2, p * x)
        else:
            return puissanceRec(x * x, n // 2, p)
    return p


if __name__ == '__main__':
    print(puissanceIt(2, 5))
    print(puissanceRec(2, 5))
def pgcd(a, b):
    if b == 0:
        return a
    while b != 0:
        a, b = b, a % b
    return a

def puissance2(x, n):
    if n == 0:
        return 1
    elif n % 2 == 0:
        return puissance2(x * x, n // 2)
    else:
        return x * puissance2(x * x, n // 2)

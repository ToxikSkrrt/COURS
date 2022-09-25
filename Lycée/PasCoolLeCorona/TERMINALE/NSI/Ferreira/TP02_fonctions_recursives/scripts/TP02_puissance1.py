def puissance1(x, n):
    if n == 0:
        return 1
    else:
        return x * puissance1(x, n - 1)

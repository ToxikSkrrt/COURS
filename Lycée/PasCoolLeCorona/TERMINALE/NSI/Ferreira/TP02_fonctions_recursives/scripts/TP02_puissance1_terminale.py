def puissance1_term(x, n, acc = 1):
    if n == 0:
        return acc
    else:
        return puissance1_term(x, n - 1, x * acc)

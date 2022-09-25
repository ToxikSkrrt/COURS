def puissance2_term(x, n, acc = 1):
    if n == 0:
        return acc
    elif n % 2 == 0:
        return puissance2_term(x * x, n // 2, acc)
    else:
        return puissance2_term(x * x, n // 2, x * acc)

def puissance2_iter(x, n):
    acc = 1
    while n > 0:
        if n % 2:
            acc *= x
        x, n = x * x, n // 2
    return acc

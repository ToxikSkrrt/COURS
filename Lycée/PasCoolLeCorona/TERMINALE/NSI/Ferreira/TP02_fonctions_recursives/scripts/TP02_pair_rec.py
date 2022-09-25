def pair_rec(n):
    if n <= 0:
        return n == 0
    else:
        return pair_rec(n - 2)

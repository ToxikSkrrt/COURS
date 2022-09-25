def fibo(n):
    """ retourne le nème élément de la suite de fibonacci
        programmation itérative
    """
    f0 = 0
    f1 = 1
    fn = None
    if (n == 0):
        fn = f0
    if (n == 1):
        fn = f1
    for k in range(2, n+1):
        fn = f1 + f0
        f0, f1 = f1, fn
    return fn


def fibo_rec(n):
    """ retourne le nème élément de la suite de fibonacci
        programmation récursive
    """
    if n == 0:
        return 0
    elif n == 1:
        return 1 
    else:
        return fibo_rec(n - 1) + fibo_rec(n - 2)

def fibo_terminal(n, a=0, b=1):
    """ retourne le nème élément de la suite de fibonacci
        programmation terminale
    """
    if n==0:
        return a
    return fibo_terminal(n - 1, b, a + b)


if __name__ == "__main__":
    print(fibo(10))
    print(fibo_rec(10))
    print(fibo_terminal(10))

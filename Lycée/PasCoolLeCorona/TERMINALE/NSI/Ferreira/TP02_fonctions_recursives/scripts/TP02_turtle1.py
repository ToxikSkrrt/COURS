import turtle as tu


def dessine(n):
    if n > 0:
        tu.forward(n)
        tu.right(90)
        dessine(n - 5)


dessine(200)
tu.ht()
tu.mainloop()

import turtle as tu


def dessin(taille):
    for i in (-1, 1):
        tu.up()
        tu.goto(- taille // 2, i * taille)
        tu.down()
        tu.forward(taille)


def trace(taille):
    if taille > 0:
        dessin(taille)
        trace(taille - 10)


trace(200)
tu.ht()
tu.mainloop()

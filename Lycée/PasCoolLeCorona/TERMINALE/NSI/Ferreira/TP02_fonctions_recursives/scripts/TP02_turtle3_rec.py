import turtle as tu

couleurs = ['purple', 'blue', 'cyan', 'green', 'yellow', 'orange', 'red']
tu.bgcolor('black')


def dessin_rec(i = 0):
    if i >= 210:
        tu.ht()
        tu.mainloop()
    else:
        tu.color(couleurs[i % 7])
        tu.forward(i)
        tu.right(50.8)
        dessin_rec(i + 1)
    

dessin_rec()

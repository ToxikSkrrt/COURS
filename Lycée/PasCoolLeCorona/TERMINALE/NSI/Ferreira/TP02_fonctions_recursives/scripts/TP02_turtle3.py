import turtle as tu

couleurs = ['purple', 'blue', 'cyan', 'green', 'yellow', 'orange', 'red']
tu.bgcolor('black')


def dessin():
    for i in range(210):
        tu.color(couleurs[i % 7])
        tu.forward(i)
        tu.right(50.8)
    tu.ht()
    tu.mainloop()


dessin()

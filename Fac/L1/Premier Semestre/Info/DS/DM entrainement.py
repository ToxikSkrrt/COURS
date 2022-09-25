from PIL import Image

# Exercice 1
'''
mystere(3)
    -> i = 0 : x = 3 est impair => x = 3 // 2 - 1 = 0
    -> i = 1 : x = 0 est pair => x = 0 + 2 * 1 + 1 = 3
    -> i = 2 : x = 3 est impair => x = 3 // 2 - 1 = 0
    -> return x = 0
'''

# Exercice 2
# 1.
def enlever_impair(L):
    index = 0
    tab = L
    for i in tab:
        if i % 2 == 1:
            tab[index] = 0
        index += 1
    return tab

print('Exo 1 : ', enlever_impair([1, 6, 4, 3]), '\n')

# 2.
'''
Sa complexité dans le pire comme dans le meilleur des cas est de Theta(n) car dans tous les cas, que tous les nombres soient
impairs ou bien pairs, on parcourt tout le tableau pour effectuer les comparaisons.
'''

# Exercice 3
# 1.
def double_voyelle(s):
    chaine = ''
    voyelles = ['a', 'e', 'i', 'o', 'u', 'y']
    for i in s:
        if i in voyelles:
            chaine += 2 * i
        else:
            chaine += i
    return chaine

print('Exo 2 : ', double_voyelle('python'), '\n')

# Exercice 4
# 1.
def neige(img):
    for i in range(img.size[0]):
        for j in range(img.size[1]):
            if (i + j) % 2 == 1:
                img.putpixel((i, j), (255, 255, 255))
    img.show()
          
img1 = Image.open('test.jpg')

print('Exo 4 1. :', neige(img1))

# 2.
'''
Dans le cas où l'image est en 2D, sa complexité sera en O(n²) tandis que si l'image est en 1D, sa complexité sera en O(n).
'''

# 3.
def croix(img):
    mid_x = img.size[0] // 2
    mid_y = img.size[1] // 2
    if mid_x % 2 == 1:
        for j in range(img.size[1]):
            img.putpixel((mid_x, j), (0, 0, 0))
    else:
        for j in range(img.size[1]):
            for i in range(2):
                img.putpixel((mid_x + i, j), (0, 0, 0))
    if mid_y % 2 == 1:
        for k in range(img.size[0]):
            img.putpixel((k, mid_y), (0, 0, 0))
    else:
        for k in range(img.size[0]):
            for l in range(2):
                img.putpixel((k, mid_y + l), (0, 0, 0))
    img.show()

img2 = Image.open('test.jpg')

print('Exo 4 3. :', croix(img2))

# 4.
'''
Si la longueur et la largeur de l'image sont impaires, sa complexité sera en O(n²), cependant si elles sont paires, dans ce cas
sa complexité sera en O(n^4). (pas certain pour le pire cas mdr)
'''
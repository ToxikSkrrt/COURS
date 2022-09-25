from PIL.Image import * # importer la bibliotheque PIL, module Image

def contour(im, seuil):
    (largeur, hauteur)=im.size
    for i in range(largeur - 1):
        for j in range(hauteur - 1):
            # on récupère les composantes r, g et b sur im aux coordonnées données
            r, g, b = im.getpixel((i, j))
            r_l, g_l, b_l =  im.getpixel((i + 1,j))
            r_h, g_h, b_h =  im.getpixel((i,j + 1))
            
            # on calcule la somme des variations des composantes r, g et b
            # entre un pixel et le pixel à sa droite
            # puis entr el pixel et celui en dessous
            delta_l = abs(r - r_l) + abs(g - g_l) + abs(b - b_l)
            delta_h = abs(r - r_h) + abs(g - g_h) + abs(b - b_h)
            
            # si l'écart est trop important, le pixel devient noir
            # sinon il devient blanc
            if delta_h > seuil or delta_l > 50 :
                im.putpixel((i, j), (0, 0, 0))
            else:
                im.putpixel((i, j), (255, 255, 255))
          
im = open("42fdf6c811b8c30b305e0b719d68937a.jpg") # on stocke dans im l'image puppy.jpg
im.show() # affiche l'image non modifiée
for seuil in range(10, 80, 10):
    contour(im, 50)
    im.show() # affiche l'image modifiée

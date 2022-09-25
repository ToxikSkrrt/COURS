from PIL import Image
from random import randint

def read(name):
    img=Image.open(name)
    print(img.format, img.size, img.mode)
    img.show()
    
def create(name, length, width):
    newImage=Image.new(name, (length, width))
    newImage.show()
    
#img1 = create('RGB', 300, 300)
#divide(img1, 3)
#newImage=Image.new('RGB', (300,300))
#newImage.show()
#divide(newImage, 3)
                
YELLOW=(255,255,0)
RED=(255,0,0)
BLACK=(0,0,0)
img1=Image.new("RGB",(1600,400))
coing = (img1.size[0] // 2, img1.size[1] // 2)
j=100
#for i in range(img1.size[0]):
#    img1.putpixel((i,j),YELLOW)
    
'''for k in range(0,coing[0]):
    for l in range(0,coing[1]):
        img1.putpixel((k,l),RED)
for k in range(1,coing[0] - 1):
    for l in range(1,coing[1] - 1):
        img1.putpixel((k,l),BLACK)
img1.show()'''

def rectangle(x, y, width, height, color):
    img = Image.new('RGB', (300, 300))
    for i in range(x, width + 1):
        for j in range(y, height + 1):
            img.putpixel((i, j), color)
    img.show()
    
def divide(img, n):
    (l, h) = img.size
    for k in range(n):
        rectangle(10, 20, 100, 70, (120, 0, 230))
    img.show()

def blur(img):
    for x in range (1,img.size[0]-1):
        for y in range(1, img.size[1]-1):
            r1,g1,b1 = img.getpixel((x-1,y-1))
            r2,g2,b2 = img.getpixel((x,y-1))
            r3,g3,b3 = img.getpixel((x+1,y-1))
            r4,g4,b4 = img.getpixel((x-1,y))
            r5,g5,b5 = img.getpixel((x,y-1))
            r6,g6,b6 = img.getpixel((x-1,y+1))
            r7,g7,b7 = img.getpixel((x,y+1))
            r8,g8,b8 = img.getpixel((x+1,y+1))
            r = (r1 + r2 + r3 + r4 + r5 + r6 + r7 + r8) // 8
            g = (g1 + g2 + g3 + g4 + g5 + g6 + g7 + g8) // 8
            b = (b1 + b2 + b3 + b4 + b5 + b6 + b7 + b8) // 8
            img.putpixel((x, y), (r, g, b))
    img.show()
img = Image.open("bouh.png")
print(blur(img))

    
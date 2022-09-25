from PIL import Image

def minimumR(img):
    min = 255
    max = 0
    for x in range (1,img.size[0]):
        for y in range(1, img.size[1]):
            (r,g,b) = img.getpixel((x,y))
            if r > max:
                max = r
            elif r < min:
                min = r
    return (min,max)
    
img1 = open("index (autre copie).png")
print(minimumR(img1))
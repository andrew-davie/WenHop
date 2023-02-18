from PIL import Image
import sys
from gimpformats.gimpXcfDocument import GimpDocument

def build(pix, im, y, start, stop, step):

    r = 0
    b = 0
    g = 0

    for cx in range(start, stop, step):

        p = pix[cx, y]
        r = (r << 1) | (p & 1)
        g = (g << 1) | ((p & 2) >> 1)
        b = (b << 1) | ((p & 4) >> 2)

    if start-stop == 4:
        r <<= 4
        g <<= 4
        b <<= 4

    return r, g, b


project = GimpDocument(sys.argv[1])

frame = []
max_frame_number = -1

layers = project.layers
for l in layers:
    layer_name = l.name.split()
    if layer_name[0] == 'FRAME':
        if int(layer_name[1]) > max_frame_number:
            max_frame_number = int(layer_name[1])

for frame in range(0, max_frame_number):






front = sys.argv[1]
back = sys.argv[2]

imFront = Image.open(front)
imBack = Image.open(back)
pixFront = imFront.load()
pixBack = imBack.load()

f = open('../' + front + '.asm', 'w')

RedLines = []
GreenLines = []
BlueLines = []
maskLines = []

for y in range(0, imFront.size[1]):

    chary = imFront.size[1] - 1 - y

    R = []
    G = []
    B = []
    mask = []

    (r, g, b) = build(pixFront, imFront, chary, 0, 8, 1)
    R.append(r)
    B.append(b)
    G.append(g)

    (r, g, b) = build(pixFront, imFront, chary, 15, 7, -1)
    R.append(r)
    B.append(b)
    G.append(g)

    (r, g, b) = build(pixFront, imFront, chary, 16, 24, 1)
    R.append(r)
    B.append(b)
    G.append(g)

    (r, g, b) = build(pixFront, imFront, chary, 31, 23, -1)
    R.append(r)
    B.append(b)
    G.append(g)

    RedLines.append(R)
    GreenLines.append(G)
    BlueLines.append(B)

    maskLines.append(mask)


for bytepos in range(0, 4):
    f.write('unsigned char' + str(bytepos) + '\n')
    for line in range(im.size[1]-1, -1, -1):
        f.write(' .byte ' + str(RedLines[line][bytepos]) + ' ;R (' + str(line) + ')\n')
        f.write(' .byte ' + str(GreenLines[line][bytepos]) + ' ;G\n')
        f.write(' .byte ' + str(BlueLines[line][bytepos]) + ' ;B\n')

f.close()
#print(im.size)

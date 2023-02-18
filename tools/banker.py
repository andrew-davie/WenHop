from PIL import Image


def process(out, source):

    im = Image.open(source)
    pix = im.load()

    out.write(' ALIGN 256\n')
    out.write('CopyrightNotice\n')

    for x in range(0, im.size[0],8):

        for y in range(im.size[1]-1, -1, -1):

            b8 = 0
            for subpix in range(0, 8):
                p = 0
                if pix[x + subpix, y] != 0:
                    p = 1
                b8 = (b8 << 1) | p

            out.write(' .byte ' + str(b8) + '\n')
        out.write('\n')

    im.close()


f = open('./Copyright.asm', 'w')
process(f, 'copyright.png')
f.close()

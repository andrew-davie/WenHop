from PIL import Image
import sys


def process(out, source):

    im = Image.open(source)
    pix = im.load()

    out.write('; created by logo.py\n')
    out.write('; converted from image \'' + source + '\'\n')
    out.write('; size = 6 columns x '+ str(im.size[1]) + ' rows\n')


    out.write('\n')

    out.write('__COPYRIGHT_ROWS = ' + str(im.size[1]) + '\n')

    for x in range(0, im.size[0],8):

        out.write('__BBG' + str(int(x/8)) + '\n')
        for y in range(0, im.size[1]):

            b8 = 0
            for subpix in range(0, 8):
                p = 0
                if pix[x + subpix, y] != 0:
                    p = 1
                b8 = (b8 << 1) | p

            out.write(' .byte ' + str(b8) + '\n')
        out.write('\n')
    out.write('\n')

    # for x in range(0, im.size[0],8):

    #     for y in range(im.size[1]-2, -1, -2):
    #     out.write('FSSlogoB' + str(int(x/8)) + '\n')

    #         b8 = 0
    #         for subpix in range(0, 8):
    #             p = 0
    #             if pix[x + subpix, y] != 0:
    #                 p = 1
    #             b8 = (b8 << 1) | p

    #         out.write(' .byte ' + str(b8) + '\n')
    #     out.write('\n')

    out.write('; EOF')
    im.close()


f = open('./copyright.asm', 'w')
process(f, sys.argv[1])
f.close()

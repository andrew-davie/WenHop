from PIL import Image


def colour_distance(a,b):

    mean_red = (a[0] + b[0]) / 2.0
    delta_red = a[0] - b[0]
    delta_red = delta_red * delta_red

    delta_green = a[1] - b[1]
    delta_green = delta_green * delta_green

    delta_blue = a[2] - b[2]
    delta_blue = delta_blue * delta_blue

    distance = (2.0 + mean_red / 256.0) * delta_red + 4.0 * delta_green + (2.0 + ((255.0 - mean_red) / 256.0)) * delta_blue
    return distance


im = Image.open('./sample.jpeg')
pix = im.load()

imResized = im.resize((40, 192), Image.LANCZOS)

palette = [
    (  0,   0,   0),
    ( 64,  64,  64),
    (108, 108, 108),
    (144, 144, 144),
    (176, 176, 176),
    (200, 200, 200),
    (220, 220, 220),
    (236, 236, 236),
    ( 68,  68,   0),
    (100, 100,  16),
    (132, 132,  36),
    (160, 160,  52),
    (184, 184,  64),
    (208, 208,  80),
    (232, 232,  92),
    (252, 252, 104),
    (112,  40,   0),
    (132,  68,  20),
    (152,  92,  40),
    (172, 120,  60),
    (188, 140,  76),
    (204, 160,  92),
    (220, 180, 104),
    (236, 200, 120),
    (132,  24,   0),
    (152,  52,  24),
    (172,  80,  48),
    (192, 104,  72),
    (208, 128,  92),
    (224, 148, 112),
    (236, 168, 128),
    (252, 188, 148),
    (136,   0,   0),
    (156,  32,  32),
    (176,  60,  60),
    (192,  88,  88),
    (208, 112, 112),
    (224, 136, 136),
    (236, 160, 160),
    (252, 180, 180),
    (120,   0,  92),
    (140,  32, 116),
    (160,  60, 136),
    (176,  88, 156),
    (192, 112, 176),
    (208, 132, 192),
    (220, 156, 208),
    (236, 176, 224),
    ( 72,   0, 120),
    ( 96,  32, 144),
    (120,  60, 164),
    (140,  88, 184),
    (160, 112, 204),
    (180, 132, 220),
    (196, 156, 236),
    (212, 176, 252),
    ( 20,   0, 132),
    ( 48,  32, 152),
    ( 76,  60, 172),
    (104,  88, 192),
    (124, 112, 208),
    (148, 136, 224),
    (168, 160, 236),
    (188, 180, 252),
    (  0,   0, 136),
    ( 28,  32, 156),
    ( 56,  64, 176),
    ( 80,  92, 192),
    (104, 116, 208),
    (124, 140, 224),
    (144, 164, 236),
    (164, 184, 252),
    (  0,  24, 124),
    ( 28,  56, 144),
    ( 56,  84, 168),
    ( 80, 112, 188),
    (104, 136, 204),
    (124, 156, 220),
    (144, 180, 236),
    (164, 200, 252),
    (  0,  44,  92),
    ( 28,  76, 120),
    ( 56, 104, 144),
    ( 80, 132, 172),
    (104, 156, 192),
    (124, 180, 212),
    (144, 204, 232),
    (164, 224, 252),
    (  0,  60,  44),
    ( 28,  92,  72),
    ( 56, 124, 100),
    ( 80, 156, 128),
    (104, 180, 148),
    (124, 208, 172),
    (144, 228, 192),
    (164, 252, 212),
    (  0,  60,   0),
    ( 32,  92,  32),
    ( 64, 124,  64),
    ( 92, 156,  92),
    (116, 180, 116),
    (140, 208, 140),
    (164, 228, 164),
    (184, 252, 184),
    ( 20,  56,   0),
    ( 52,  92,  28),
    ( 80, 124,  56),
    (108, 152,  80),
    (132, 180, 104),
    (156, 204, 124),
    (180, 228, 144),
    (200, 252, 164),
    ( 44,  48,   0),
    ( 76,  80,  28),
    (104, 112,  52),
    (132, 140,  76),
    (156, 168, 100),
    (180, 192, 120),
    (204, 212, 136),
    (224, 236, 156),
    ( 68,  40,   0),
    (100,  72,  24),
    (132, 104,  48),
    (160, 132,  68),
    (184, 156,  88),
    (208, 180, 108),
    (232, 204, 124),
    (252, 224, 140),
]

black = (0, 0, 0)

pix = imResized.load()

delta_colour = [(0, 0, 0)] * imResized.size[0]
best_delta = [1e10] * imResized.size[1]
best_colour = [0] * imResized.size[1]

for y in range(0, imResized.size[1]):

    for colour_number in range(0, len(palette)):

        colour = palette[colour_number]
        colour_delta = 0.0

        for x in range(0, imResized.size[0]):

            pixel = (
                pix[x, y][0] + delta_colour[x][0],
                pix[x, y][1] + delta_colour[x][1],
                pix[x, y][2] + delta_colour[x][2] )

            distance_black = colour_distance(pixel, black)
            distance_colour = colour_distance(pixel, colour)

            if distance_black < distance_colour:
                new_colour = black
                colour_delta = colour_delta + distance_black
            else:
                new_colour = colour
                colour_delta = colour_delta + distance_colour

        if colour_delta < best_delta[y]:
            best_delta[y] = colour_delta
            best_colour[y] = colour_number

    # now we have the best colour, we redo the line to choose pixels on/off and get a delta to add to next line

    for x in range(0, imResized.size[0]):

        pixel = pix[x, y]
        distance_black = colour_distance(pixel, black)
        distance_colour = colour_distance(pixel, palette[best_colour[y]])

        if distance_black < distance_colour:
            new_colour = 0
        else:
            new_colour = best_colour[y]

        colour = palette[new_colour]
        delta_colour[x] = (pixel[0] - colour[0], pixel[1] - colour[1], pixel[2] - colour[2])








#    print("line", y, " best colour", best_colour, " delta ", best_delta)












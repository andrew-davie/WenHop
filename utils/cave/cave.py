import random

random_seed1 = 0
random_seed2 = 0


att = dict()

att['CH_BLANK']=  { 0, '  ' }
att['CH_DIRT']=  { 1, '░░' }
att['DIRT'] = {  1, '  ' }
att['CH_BRICKWALL']= {   2, '  ' }
att['CH_MAGICWALL']= {   3, '  ' }
att['CH_DOORCLOSED']= {   4, '  ' }
att['OUTBOX'] = {  4, '  ' }
att['CH_DOOROPEN_0']= {   5, '  ' }
att['CH_EXITBLANK']= {   6, '  ' }
att['CH_STEELWALL']= {   7, '  ' }
att['STEEL'] = {  7, '  ' }
att['CH_FIREFLY_0']= {   8, '  ' }
att['CH_FIREFLY_1']= {   9, '  ' }
att['CH_FIREFLY_2']= {   10, '  ' }
att['CH_FIREFLY_3']= {   11, '  ' }
att['CH_PEBBLE1']= {   12, '  ' }
att['CH_PEBBLE2']= {   13, '  ' }
att['CH_BLANK_DUMMY']= {   14, '  ' }
att['CH_EASTEREGG']= {   15, '  ' }
att['CH_BOULDER']= {   16, '  ' }
att['BOULDER'] = {  16, '  ' }
att['CH_BOULDER_FALLING']= {   17, '  ' }
att['CH_DIAMOND']= {   18, '  ' }
att['DIAMOND'] = {  18, '  ' }
att['CH_DOGE_FALLING']= {   19, '  ' }
att['CH_EXPLODETODIAMOND_0']= {   20, '  ' }
att['CH_EXPLODETODIAMOND_1']= {   21, '  ' }
att['CH_EXPLODETODIAMOND_2']= {   22, '  ' }
att['CH_EXPLODETODIAMOND_3']= {   23, '  ' }
att['CH_EXPLODETODIAMOND_4']= {   24, '  ' }
att['CH_ROCKFORD_BIRTH']= {   25, '  ' }
att['INBOX'] = {  25, '  ' }
att['CH_MAGICWALL_1']= {   26, '  ' }
att['CH_MAGICWALL_2']= {   27, '  ' }
att['CH_MAGICWALL_3']= {   28, '  ' }
att['CH_BUTTERFLY_0']= {   29, '  ' }
att['BUTTERFLY'] = {  29, '  ' }
att['CH_BUTTERFLY_1']= {   30, '  ' }
att['CH_BUTTERFLY_2']= {   31, '  ' }
att['CH_BUTTERFLY_3']= {   32, '  ' }
att['CH_AMOEBA_0']= {   33, '  ' }
att['AMOEBA'] = {  33, '  ' }
att['CH_AMOEBA_1']= {   34, '  ' }
att['CH_AMOEBA_2']= {   35, '  ' }
att['CH_AMOEBA_3']= {   36, '  ' }
att['CH_ROCKFORD']= {   37, '  ' }
att['CH_DIAMOND_PULSE_0']= {   38, '  ' }
att['CH_DIAMOND_PULSE_1']= {   39, '  ' }
att['CH_DIAMOND_PULSE_2']= {   40, '  ' }
att['CH_DIAMOND_PULSE_3']= {   41, '  ' }
att['CH_DIAMOND_PULSE_4']= {   42, '  ' }
att['CH_DIAMOND_PULSE_5']= {   43, '  ' }
att['CH_DIAMOND_PULSE_6']= {   44, '  ' }
att['CH_DIAMOND_PULSE_7']= {   45, '  ' }
#att['CH_DIAMOND_PULSE_8']= {   46, '  ' }
#att['CH_DIAMOND_PULSE_9']= {   47, '  ' }
att['CH_DIAMOND_STATIC']= {   48, '  ' }
att['CH_SPARKLE_0']= {   49, '  ' }
att['CH_SPARKLE_1']= {   50, '  ' }
att['CH_SPARKLE_2']= {   51, '  ' }
att['CH_SPARKLE_3']= {   52, '  ' }
att['CH_EXPLODETOBLANK_0']= {   53, '  ' }
att['CH_EXPLODETOBLANK_1']= {   54, '  ' }
att['CH_EXPLODETOBLANK_2']= {   55, '  ' }
att['CH_EXPLODETOBLANK_3']= {   56, '  ' }
att['CH_EXPLODETOBLANK_4']= {   57, '  ' }
att['CH_DOGE_GRAB']= {   58, '  ' }
att['CH_DIRT_GRAB']= {   59, '  ' }
att['CH_DUST_0']= {   60, '  ' }
att['CH_DUST_1']= {   61, '  ' }
att['CH_DUST_2']= {   62, '  ' }
att['CH_BOULDER_SHAKE']= {   63, '  ' }
att['CH_DUST_LEFT_0']= {   64, '  ' }
att['CH_DUST_LEFT_1']= {   65, '  ' }
att['CH_DUST_RIGHT_0']= {   66, '  ' }
att['CH_DUST_RIGHT_1']= {   67, '  ' }

att['RIGHT'] = {  2, '  ' }
att['DOWN'] = {  4, '  ' }
att['LINE_E'] = {  2, '  ' }
att['LINE_SE'] = {  3, '  ' }
att['LINE'] = {  64, '  ' }
att['RECT'] = {  192, '  ' }
att['FILLRECT'] = {  128, '  ' }


visual = dict()
visual[0] = '  '
visual[1] = '░░'
visual[2] = '▒▒'
visual[3] = '▞▞'
visual[4] = 'X '
visual[5] = 'X '
visual[6] = '..'
visual[7] = '▓▓'
visual[8] = 'F '
visual[9] = 'F '
visual[10] = 'F '
visual[11] = 'F '
visual[12] = '. '
visual[13] = 'o '
visual[14] = '  '
visual[15] = 'E '
visual[16] = '● '
visual[17] = '● '
visual[18] = '▲ '
visual[18] = '▲ '
visual[32] = '  '
visual[33] = '  '
visual[34] = '  '
visual[35] = '  '
visual[36] = '  '
visual[37] = 'R '
visual[44] = '% '
visual[45] = '% '
visual[46] = '% '
visual[48] = 'B '
visual[49] = 'B '
visual[50] = 'B '
visual[51] = 'B '
visual[58] = 'o '
visual[59] = 'o '
visual[60] = 'o '
visual[61] = 'o '

class parse:

    def __init__(self):

        self.parsed = []
        defs = """


    20,       // milling
    20,100,  // diamond $, extra $
    1,          // rain

    10,11,12,13,14,       // randomiser[level]
    20,12,12,12,12,             // diamonds required
    100,0x6E,0x46,0x28,30,      // time


    CAVEDEF_PARALLAX,
    STEEL,DIRT,

    CH_BLANK,CH_BOULDER,DIAMOND,CH_BLANK,
    0x3C,50,15,0,

    LINE + CH_BRICKWALL,13,1,4,15,
    LINE + CH_BRICKWALL,26,20,0,15,

    CH_DOORCLOSED,38,16,
    CH_ROCKFORD_BIRTH,3,2,

    0xFF,

     """

        lines = defs.split('\n')
        self.idx = 0

        for line in lines:
            sub_line = line.upper().split(',')

            for sub in sub_line:
                num = -1
                sub = sub.strip()

                if sub.find('+') >= 0:
                    com = sub.split('+')
                    com[0] = com[0].strip()
                    com[1] = com[1].strip()

                    if com[0] in att:
                        com[0] = att[com[0]]
                    elif com[0].find('0x') >= 0:
                        com[0] = int(com[0], 16)

                    if com[1] in att:
                        com[1] = att[com[1]]
                    elif com[1].find('0x') >= 0:
                        com[1] = int(com[1], 16)

                    num = eval(str(com[0]) + '+' + str(com[1]))

                elif sub.find('0X') >= 0:
                    num = int(sub, 16)

                elif sub.isnumeric():
                    num = int(sub)

                elif sub in att:
                    num = att[sub]

                if num >= 0:
                    self.parsed.append(num)

    def get(self):
        num = self.parsed[self.idx]
        self.idx = self.idx + 1
        return num

    def reset(self):
        self.idx = 29

    def getSeed(self, level):
        return self.parsed[level + 3]


def draw_line(obj, x1, y1, length, direction):

    #print('horiz', obj, x1, y1, length, direction)

    if direction == 1:
        for counter in range(0, length):
            board[y1 - counter][x1 + counter] = obj

    if direction == 2:
        for counter in range(x1, x1 + length):
            board[y1][counter] = obj

    if direction == 3:
        for counter in range(0, length):
            board[y1 + counter][x1 + counter] = obj

    if direction == 4:
        #print('vert', y1, length)
        for counter in range(y1, y1 + length):
            board[counter][x1] = obj

    if direction == 5:
        for counter in range(0, length):
            board[y1 + counter][x1 - counter] = obj


def draw_vertical_line(obj, x1, y1, height):
    for counter in range(y1, y1 + height):
        # print('vert',x1, counter)
        board[counter][x1] = obj


def draw_rect(obj, x1, y1, width, height):
    #print('draw_rect', obj, x1, y1, width, height)
    draw_line(obj, x1, y1, width, 2)
    draw_line(obj, x1, y1 + height - 1, width, 2)
    draw_line(obj, x1, y1, height, 4)
    draw_line(obj, x1 + width - 1, y1, height, 4)


def draw_filled_rect(obj, x1, y1, width, height, fill):
    #print("dfr", obj, x1, y1, width, height, fill)
    for counter in range(y1, y1 + height):
        draw_line(fill, x1, counter, width, 2)
    draw_rect(obj, x1, y1, width, height)
    print('efr')


def do_board(level):

    global random_seed1
    global random_seed2
    global filler_random
    global filler_name


    #print("board ", level)
    test.reset()

    random_seed1 = 0
    random_seed2 = test.getSeed(level)

    board.append([border for col in range(0, 40)])
    for row in range(1, 21):
        board.append([border for col in range(0, 40)])
        for col in range(1, 39):
            next_random()
            board[row][col] = interior
            for obj in range(0, 4):
                if random_seed1 < filler_random[obj]:
                    board[row][col] = filler_name[obj]
    board.append([border for col in range(0, 40)])


    cmd = test.get()
    while cmd != 255:
        #print('cmd=', cmd)
        obj = cmd & 0x3F

        if cmd & 0xC0 == 0xC0:

            a = test.get()
            b = test.get()
            c = test.get()
            d = test.get()

            #print('drawrect', a, b, c, d)

            draw_rect(cmd & 0x3F, a, b, c, d)

        elif cmd & 0x80 == 0x80:

            a = test.get()
            b = test.get()
            c = test.get()
            d = test.get()
            e = test.get()

            #print('drawfilledrect', a, b, c, d, e)
            draw_filled_rect(obj, a, b, c, d, e)

        elif cmd & 0x40 == 0x40:
            a = test.get()
            b = test.get()
            c = test.get()
            d = test.get()

            #print('line', obj, a, b, c, d)
            draw_line(obj, a, b, c, d)

        else:
            x = test.get()
            y = test.get()
            #print('x=', x, 'y=', y)
            board[y][x] = cmd

        cmd = test.get()


def next_random():

    global random_seed1
    global random_seed2

    temp_random1 = (random_seed1 & 0x0001) * 0x0080
    temp_random2 = (random_seed2 >> 1) & 0x007F
    result = random_seed2 + (random_seed2 & 0x0001) * 0x0080
    carry = 0
    if result > 0x00FF:
        carry = 1
    result = result & 0x00FF
    result = result + carry + 0x13
    carry = 0
    if result > 0x00FF:
        carry = 1
    random_seed2 = result & 0x00FF
    result = random_seed1 + carry + temp_random1
    carry = 0
    if result > 0x00FF:
        carry = 1
    result = result & 0x00FF
    result = result + carry + temp_random2
    random_seed1 = result & 0x00FF


board = []
test = parse()

print("milling", test.get())
print("diamond vals", test.get(), test.get())
print("randomisers")
for line in range(0, 3):
    for val in range(0, 5):
        print(test.get())

print("flags", test.get())

border = test.get()
print("border", border)
interior = test.get()
print("interior", interior)

filler_name = []
filler_random = []

for filler in range(0,4):
    filler_name.append(test.get())
for filler in range(0,4):
    filler_random.append(test.get())


# print("fillers")
# print(filler_name)
# print(filler_random)

for level in range(0, 1):
    do_board(level)

    for row in range(0, 22):
        for col in range(0,40):
            print(visual[board[row][col]], end='')
        print()


#include "defines.h"
#include "defines_cdfj.h"
#include "defines_from_dasm_for_c.h"

#include <stdbool.h>

#include "main.h"

#include "animations.h"
#include "attribute.h"
#include "cavedata.h"
#include "characterset.h"
#include "colour.h"
#include "decodecaves.h"
#include "drawplayer.h"
#include "drawscreen.h"
#include "menu.h"
#include "player.h"
#include "random.h"
#include "score.h"
#include "scroll.h"
#include "sound.h"

extern int roller;

const unsigned char *img[5];
const unsigned char *corner[5];
const unsigned char *p;

unsigned char revectorChar[128];

void initCharVector() {

    for (int i = 0; i < 128; i++)
        revectorChar[i] = i;
}

const unsigned char _CHAR_INNER_CORNER_RU[] = {

    // up + right soil

    0b00011, // 00 <
    0b00000, // 01
    0b00000, // 02
    0b00001, // 03 <
    0b00000, // 04
    0b00000, // 05
    0b00000, // 06 <
    0b00000, // 07
    0b00000, // 08
    0b00000, // 09 <
    0b00000, // 10
    0b00000, // 11
    0b00000, // 12 <
    0b00000, // 13
    0b00000, // 14
    0b00000, // 15 <
    0b00000, // 16
    0b00000, // 17
    0b00000, // 18 <
    0b00000, // 19
    0b00000, // 20
    0b00000, // 21 <
    0b00000, // 22
    0b00000, // 23
    0b00000, // 24 <
    0b00000, // 25
    0b00000, // 26
    0b00000, // 27 <
    0b00000, // 28
    0b00000, // 29
};

const unsigned char _CHAR_INNER_CORNER_6[] = {

    // right+down soil

    0b00000, // 00 <
    0b00000, // 01
    0b00000, // 02
    0b00000, // 03 <
    0b00000, // 04
    0b00000, // 05
    0b00000, // 06 <
    0b00000, // 07
    0b00000, // 08
    0b00000, // 09 <
    0b00000, // 10
    0b00000, // 11
    0b00000, // 12 <
    0b00000, // 13
    0b00000, // 14
    0b00000, // 15 <
    0b00000, // 16
    0b00000, // 17
    0b00000, // 18 <
    0b00000, // 19
    0b00000, // 20
    0b00000, // 21 <
    0b00000, // 22
    0b00000, // 23
    0b00001, // 24 <
    0b00000, // 25
    0b00000, // 26
    0b00011, // 27 <
    0b00000, // 28
    0b00000, // 29
};

const unsigned char _CHAR_INNER_CORNER_7[] = {

    // up+right+down soil

    0b00001, // 00 <
    0b00000, // 01
    0b00000, // 02
    0b00001, // 03 <
    0b00000, // 04
    0b00000, // 05
    0b00000, // 06 <
    0b00000, // 07
    0b00000, // 08
    0b00000, // 09 <
    0b00000, // 10
    0b00000, // 11
    0b00000, // 12 <
    0b00000, // 13
    0b00000, // 14
    0b00000, // 15 <
    0b00000, // 16
    0b00000, // 17
    0b00000, // 18 <
    0b00000, // 19
    0b00000, // 20
    0b00000, // 21 <
    0b00000, // 22
    0b00000, // 23
    0b00001, // 24 <
    0b00000, // 25
    0b00000, // 26
    0b00011, // 27 <
    0b00000, // 28
    0b00000, // 29
};

const unsigned char _CHAR_INNER_CORNER_9[] = {
    // ul

    0b11000, // 00 <
    0b00000, // 01
    0b00000, // 02
    0b10000, // 03 <
    0b00000, // 04
    0b00000, // 05
    0b10000, // 06 <
    0b00000, // 07
    0b00000, // 08
    0b00000, // 09 <
    0b00000, // 10
    0b00000, // 11
    0b00000, // 12 <
    0b00000, // 13
    0b00000, // 14
    0b00000, // 15 <
    0b00000, // 16
    0b00000, // 17
    0b00000, // 18 <
    0b00000, // 19
    0b00000, // 20
    0b00000, // 21 <
    0b00000, // 22
    0b00000, // 23
    0b00000, // 24 <
    0b00000, // 25
    0b00000, // 26
    0b00000, // 27 <
    0b00000, // 28
    0b00000, // 29
};

const unsigned char _CHAR_INNER_CORNER_11[] = {

    // up+left+right soil

    0b11001, // 00 <
    0b00000, // 01
    0b00000, // 02
    0b10001, // 03 <
    0b00000, // 04
    0b00000, // 05
    0b10000, // 06 <
    0b00000, // 07
    0b00000, // 08
    0b00000, // 09 <
    0b00000, // 10
    0b00000, // 11
    0b00000, // 12 <
    0b00000, // 13
    0b00000, // 14
    0b00000, // 15 <
    0b00000, // 16
    0b00000, // 17
    0b00000, // 18 <
    0b00000, // 19
    0b00000, // 20
    0b00000, // 21 <
    0b00000, // 22
    0b00000, // 23
    0b00000, // 24 <
    0b00000, // 25
    0b00000, // 26
    0b00000, // 27 <
    0b00000, // 28
    0b00000, // 29
};

const unsigned char _CHAR_INNER_CORNER_12[] = {

    // ld

    0b00000, // 00 <
    0b00000, // 01
    0b00000, // 02
    0b00000, // 03 <
    0b00000, // 04
    0b00000, // 05
    0b00000, // 06 <
    0b00000, // 07
    0b00000, // 08
    0b00000, // 09 <
    0b00000, // 10
    0b00000, // 11
    0b00000, // 12 <
    0b00000, // 13
    0b00000, // 14
    0b00000, // 15 <
    0b00000, // 16
    0b00000, // 17
    0b00000, // 18 <
    0b00000, // 19
    0b00000, // 20
    0b00000, // 21 <
    0b00000, // 22
    0b00000, // 23
    0b00000, // 24 <
    0b00000, // 25
    0b00000, // 26
    0b10000, // 27 <
    0b00000, // 28
    0b00000, // 29
};

const unsigned char _CHAR_INNER_CORNER_13[] = {

    // uld

    0b11000, // 00 <
    0b00000, // 01
    0b00000, // 02
    0b10000, // 03 <
    0b00000, // 04
    0b00000, // 05
    0b10000, // 06 <
    0b00000, // 07
    0b00000, // 08
    0b00000, // 09 <
    0b00000, // 10
    0b00000, // 11
    0b00000, // 12 <
    0b00000, // 13
    0b00000, // 14
    0b00000, // 15 <
    0b00000, // 16
    0b00000, // 17
    0b00000, // 18 <
    0b00000, // 19
    0b00000, // 20
    0b00000, // 21 <
    0b00000, // 22
    0b00000, // 23
    0b00000, // 24 <
    0b00000, // 25
    0b00000, // 26
    0b10000, // 27 <
    0b00000, // 28
    0b00000, // 29
};

const unsigned char _CHAR_INNER_CORNER_14[] = {

    // lrd

    0b00000, // 00 <
    0b00000, // 01
    0b00000, // 02
    0b00000, // 03 <
    0b00000, // 04
    0b00000, // 05
    0b00000, // 06 <
    0b00000, // 07
    0b00000, // 08
    0b00000, // 09 <
    0b00000, // 10
    0b00000, // 11
    0b00000, // 12 <
    0b00000, // 13
    0b00000, // 14
    0b00000, // 15 <
    0b00000, // 16
    0b00000, // 17
    0b00000, // 18 <
    0b00000, // 19
    0b00000, // 20
    0b00000, // 21 <
    0b00000, // 22
    0b00000, // 23
    0b00001, // 24 <
    0b00000, // 25
    0b00000, // 26
    0b10011, // 27 <
    0b00000, // 28
    0b00000, // 29
};

const unsigned char _CHAR_INNER_CORNER_15[] = {

    // udlr

    0b11011, // 00 <
    0b00000, // 01
    0b00000, // 02
    0b10001, // 03 <
    0b00000, // 04
    0b00000, // 05
    0b10001, // 06 <
    0b00000, // 07
    0b00000, // 08
    0b00000, // 09 <
    0b00000, // 10
    0b00000, // 11
    0b00000, // 12 <
    0b00000, // 13
    0b00000, // 14
    0b00000, // 15 <
    0b00000, // 16
    0b00000, // 17
    0b00000, // 18 <
    0b00000, // 19
    0b00000, // 20
    0b00000, // 21 <
    0b00000, // 22
    0b00000, // 23
    0b00001, // 24 <
    0b00000, // 25
    0b00000, // 26
    0b10011, // 27 <
    0b00000, // 28
    0b00000, // 29
};

extern const unsigned char shape_FRAME_BLANK[];
#define _CHAR_BLANK (shape_FRAME_BLANK + 3)

const unsigned char *const roundedCorner[] = {

    _CHAR_BLANK,           // 00
    _CHAR_BLANK,           // 01 U
    _CHAR_BLANK,           // 02 R
    _CHAR_INNER_CORNER_RU, // 03 RU
    _CHAR_BLANK,           // 04 D
    _CHAR_BLANK,           // 05 DU
    _CHAR_INNER_CORNER_6,  // 06 RD
    _CHAR_INNER_CORNER_7,  // 07 URD
    _CHAR_BLANK,           // 08 L
    _CHAR_INNER_CORNER_9,  // 09 LU
    _CHAR_BLANK,           // 10 LR
    _CHAR_INNER_CORNER_11, // 11 LUR
    _CHAR_INNER_CORNER_12, // 12 LD
    _CHAR_INNER_CORNER_13, // 13 LDU
    _CHAR_INNER_CORNER_14, // 14 LRD
    _CHAR_INNER_CORNER_15, // 15 LURD
};

void grabCharacters() {

    unsigned char p2;
    unsigned char type;
    unsigned char udlr;

    for (int col = 0; col < 5; col++) {

        p2 = GET(p[col]);
        type = CharToType[p2];

        if (Animate[type])
            img[col] = charSet[revectorChar[*Animate[type]]];
        else
            img[col] = charSet[revectorChar[p2]];

        if (Attribute[type] & ATT_PAD) {

            udlr = ((Attribute[CharToType[GET(p[col - _1ROW])]] & ATT_CORNER) >> 31) |
                   ((Attribute[CharToType[GET(p[col + 1])]] & ATT_CORNER) >> 30) |
                   ((Attribute[CharToType[GET(p[col + _1ROW])]] & ATT_CORNER) >> 29) |
                   ((Attribute[CharToType[GET(p[col - 1])]] & ATT_CORNER) >> 28);

            corner[col] = roundedCorner[udlr];
        }

        else
            corner[col] = _CHAR_BLANK;
    }

    p += 4;
}

const unsigned char rollDirect[3][PIECE_DEPTH] = {

    {2,  0,  1,  5,  3,  4,  8,  6,  7,  11, 9,  10, 14, 12, 13,
     17, 15, 16, 20, 18, 19, 23, 21, 22, 26, 24, 25, 29, 27, 28},

    {0,  1,  2,  3,  4,  5,  6,  7,  8,  9,  10, 11, 12, 13, 14,
     15, 16, 17, 18, 19, 20, 21, 22, 23, 24, 25, 26, 27, 28, 29},

    {1,  2,  0,  4,  5,  3,  7,  8,  6,  10, 11, 9,  13, 14, 12,
     16, 17, 15, 19, 20, 18, 22, 23, 21, 25, 26, 24, 28, 29, 27},
};

static unsigned char *const arenas[] = {
    RAM + _BUF_PF0_LEFT,
    RAM + _BUF_PF0_RIGHT,
};

void drawScreen() { // --> cycles 62870 (@20230616)

    extern int shakeX, shakeY;
    int lcount = -((scrollY + shakeY) >> 16) * 3;

    int subBlockPixel = (((scrollX + shakeX) & 0xFFFF) * 5) >> 16;
    int shift = 5 - subBlockPixel;

    int startRow = (-lcount * (0x10000 / PIECE_DEPTH)) >> 16;
    lcount += startRow * PIECE_DEPTH;

    int characterX = (scrollX + shakeX) >> 16;

    int scanline = 0;
    for (int row = startRow; scanline < SCANLINES; row++) {

        const int height = SCANLINES - scanline < PIECE_DEPTH ? SCANLINES - scanline : PIECE_DEPTH;

        p = RAM + _BOARD + row * _1ROW + characterX;

        for (int half = 0; half < 2; half++) {

            grabCharacters();

            unsigned char *pf0 = arenas[half] + scanline;

            for (int y = -lcount; y < height; y++) {

                int lineColour = rollDirect[roller][y];

                int px = ((unsigned int)(img[0][lineColour] | corner[0][lineColour]) << 27 >> 7) |
                         ((unsigned int)(img[1][lineColour] | corner[1][lineColour]) << 27 >> 12) |
                         ((unsigned int)(img[2][lineColour] | corner[2][lineColour]) << 27 >> 17) |
                         ((unsigned int)(img[3][lineColour] | corner[3][lineColour]) << 27 >> 22) |
                         ((unsigned int)(img[4][lineColour] | corner[4][lineColour]) << 27 >> 27);

                px >>= shift;

                *(pf0 + (_ARENA_SCANLINES << 1)) = reverseBits[(unsigned char)px];
                *(pf0 + _ARENA_SCANLINES) = px >> 8;
                *pf0++ = reverseBits[px >> 16];
            }
        }

        scanline += height + lcount;
        lcount = 0;
    }
}

bool drawBit(int x, int y) {

    int line = (y - ((scrollY) >> 16)) * 3;
    if (line < 0 || line >= _ARENA_SCANLINES - 3)
        return false;

    int col = x - ((scrollX * 5) >> 16);
    if (col < 0 || col > _BOARD_COLS - 1)
        return false;

    unsigned char *base = _BUF_PF0_LEFT + RAM + line;

    if (col >= 20) {
        col -= 20;
        base += 3 * _ARENA_SCANLINES;
    }

    base += ((col + 4) >> 3) * _ARENA_SCANLINES;

    int shift;
    if (col < 4)
        shift = col + 4;

    else if (col < 12)
        shift = 11 - col;

    else
        shift = (col - 12);

    int bit = 1 << shift;

    base[0] |= bit;
    base[1] |= bit;
    base[2] |= bit;

    return true;
}

unsigned char rainType[RAINHAILSHINE];
unsigned char rainAge[RAINHAILSHINE];

int rainX[RAINHAILSHINE];
int rainY[RAINHAILSHINE], /*rainSpeed[RAINHAILSHINE],*/ rainSpeedX[RAINHAILSHINE];
int rainSpeedY[RAINHAILSHINE];

#define RAINTYPE_BUBBLE 1
// #define RAINTYPE_DOT 2

void drawParticles() {

    for (int i = 0; i < RAINHAILSHINE; i++) {
        if (rainAge[i]) {

            --rainAge[i];

            rainX[i] += rainSpeedX[i];
            rainY[i] += rainSpeedY[i];

            int y = rainY[i] >> 16;
            int x = rainX[i] >> 8;

            if (rainType[i] == RAINTYPE_BUBBLE) {

                if ((rainY[i] >> 16) < lavaSurfaceTrixel) {
                    rainAge[i] = 0;
                    continue;
                }

                x += rangeRandom(2) - 1;
                rainSpeedX[i] = (rainSpeedX[i] * 15) >> 4;
            }

            if (!drawBit(x, y))
                rainAge[i] = 0;
        }
    }
}

// EOF

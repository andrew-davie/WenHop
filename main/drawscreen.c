#include <stdbool.h>

#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Wunused-function"

#include "defines_from_dasm_for_c.h"
#define CDFJ_NO_MUSIC #must be before defines_cdfjplus.h
#define CDFJ_NO_PITCH_TABLE #must be before defines_cdfjplus.h
#define CDFJ_NO_MEMCOPY_INT #must be before defines_cdfjplus.h
#include "defines.h"
#include "defines_cdfjplus.h"

#pragma GCC diagnostic pop

// #include "defines.h"
// #include "defines_cdfjplus.h"

#include "main.h"

#include "animations.h"
#include "attribute.h"
#include "bitpatterns.h"
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

#undef RAM
#define RAM (void *)0x40000800ULL

extern int roller;

const unsigned char *img[5];
const unsigned char *corner[5];
const unsigned char *p;

void grab(int frac, int size) {

    for (int col = 0; col < size; col++) {

        int base = frac + col;
        while (base >= _BOARD_COLS)
            base -= _BOARD_COLS;

        unsigned char p2 = GET2(p[base]);
        int type = CharToType[p2];
        if (Animate[type])
            p2 = *Animate[type];
        img[col] = charSet[p2];

        int udlr = 0;

        if (ATTRIBUTE_BIT(p[base], ATT_PAD)) {

            if (ATTRIBUTE_BIT(p[base - _BOARD_COLS], ATT_CORNER))
                udlr |= DIR_U;
            if (ATTRIBUTE_BIT(p[base + 1], ATT_CORNER))
                udlr |= DIR_R;
            if (ATTRIBUTE_BIT(p[base + _BOARD_COLS], ATT_CORNER))
                udlr |= DIR_D;
            if (ATTRIBUTE_BIT(p[base - 1], ATT_CORNER))
                udlr |= DIR_L;
        }

        static const unsigned char blank[] = {
            CH_BLANK,     // 00
            CH_BLANK,     // 01 U
            CH_BLANK,     // 02 R
            CH_CORNER_3,  // 03 RU
            CH_BLANK,     // 04 D
            CH_BLANK,     // 05
            CH_CORNER_6,  // 06 RD
            CH_CORNER_7,  // 07 URD
            CH_BLANK,     // 08 L
            CH_CORNER_9,  // 09 LU
            CH_BLANK,     // 10 LR
            CH_CORNER_11, // 11 LUR
            CH_CORNER_12, // 12 LD
            CH_CORNER_13, // 13 L
            CH_CORNER_14, // 14 LRD
            CH_CORNER_15, // 15 LURD
        };

        corner[col] = charSet[blank[udlr]];
    }

    p += size;
}

static unsigned char rollDirect[3][PIECE_DEPTH] = {
    {2,  0,  1,  5,  3,  4,  8,  6,  7,  11, 9,  10, 14, 12, 13,
     17, 15, 16, 20, 18, 19, 23, 21, 22, 26, 24, 25, 29, 27, 28},
    {0,  1,  2,  3,  4,  5,  6,  7,  8,  9,  10, 11, 12, 13, 14,
     15, 16, 17, 18, 19, 20, 21, 22, 23, 24, 25, 26, 27, 28, 29},
    {1,  2,  0,  4,  5,  3,  7,  8,  6,  10, 11, 9,  13, 14, 12,
     16, 17, 15, 19, 20, 18, 22, 23, 21, 25, 26, 24, 28, 29, 27},
};

void drawScreen(int side) { // --> cycles 44743 (@20221216)

    return; // tmp

    static unsigned char *const arenas[] = {
        RAM + _BUF_PF0_LEFT,
        RAM + _BUF_PF0_RIGHT,
    };

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

        for (int half = side; half < side + 1; half++) {

            p = RAM + _BOARD + row * _BOARD_COLS + half * 4;
            grab(characterX, 5);

            unsigned char *pf0 = arenas[half] + scanline;

            for (int y = -lcount; y < height; y++) {

                int lineColour = rollDirect[roller][y];

                int p = ((unsigned int)(img[0][lineColour] | corner[0][lineColour]) << 27 >> 7) |
                        ((unsigned int)(img[1][lineColour] | corner[1][lineColour]) << 27 >> 12) |
                        ((unsigned int)(img[2][lineColour] | corner[2][lineColour]) << 27 >> 17) |
                        ((unsigned int)(img[3][lineColour] | corner[3][lineColour]) << 27 >> 22) |
                        ((unsigned int)(img[4][lineColour] | corner[4][lineColour]) << 27 >> 27);

                p >>= shift;

                *(pf0 + (_ARENA_SCANLINES << 1)) = BitRev[(unsigned char)p];
                *(pf0 + _ARENA_SCANLINES) = p >> 8;
                *pf0++ = BitRev[p >> 16];
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

void rain() {

    for (int i = 0; i < RAINHAILSHINE; i++) {
        if (rainX[i] != -1) {

            if (rainAge[i])
                if (!--rainAge[i]) {
                    rainX[i] = -1;
                    continue;
                }

            rainX[i] += rainSpeedX[i];
            rainY[i] += rainSpeedY[i];

            int y = rainY[i] >> 16;
            int x = rainX[i] >> 8;

            if (rainType[i] == RAINTYPE_BUBBLE) {

                if ((rainY[i] >> 16) < lavaSurface) {
                    rainX[i] = -1;
                    continue;
                }

                x += rangeRandom(2) - 1;
                rainSpeedX[i] = (rainSpeedX[i] * 3) >> 2;
            }

            if (!drawBit(x, y))
                rainX[i] = -1;
        }
    }
}

// EOF
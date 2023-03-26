#include <stdbool.h>
#include "defines.h"
#include "defines_cdfj.h"

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
#include "scroll.h"
#include "sound.h"
#include "score.h"

extern int roller;

const unsigned char *img[5];
const unsigned char *corner[5];
const unsigned char *p;


void rain();


void grab(int frac, int size) {

    for (int col = 0; col < size; col++) {

        int base = frac + col;
        if (base >= 40)
            base -= 40;

        unsigned char p2 = GET2(p[base]);
        int type = CharToType[p2];
        if (Animate[type])
            p2 = *Animate[type];
        img[col] = charSet[p2];


        int udlr = 0;

        if (Attribute[CharToType[GET(p[base])]] & ATT_PAD) {

            if (Attribute[CharToType[GET(p[base - 40])]] & ATT_CORNER)
                udlr |= 1;
            if (Attribute[CharToType[GET(p[base + 1])]] & ATT_CORNER)
                udlr |= 2;
            if (Attribute[CharToType[GET(p[base + 40])]] & ATT_CORNER)
                udlr |= 4;
            if (Attribute[CharToType[GET(p[base - 1])]] & ATT_CORNER)
                udlr |= 8;
        }

        static const unsigned char blank[] = {
            CH_BLANK,       // 00
            CH_BLANK,       // 01 U
            CH_BLANK,       // 02 R
            CH_CORNER_3,    // 03 RU
            CH_BLANK,       // 04 D
            CH_BLANK,       // 05
            CH_CORNER_6,    // 06 RD
            CH_CORNER_7,    // 07 URD
            CH_BLANK,       // 08 L
            CH_CORNER_9,    // 09 LU
            CH_BLANK,       // 10 LR
            CH_CORNER_11,   // 11 LUR
            CH_CORNER_12,   // 12 LD
            CH_CORNER_13,   // 13 L
            CH_CORNER_14,   // 14 LRD
            CH_CORNER_15,   // 15 LURD
        };

        corner[col] = charSet[blank[udlr]];
    }


    p += size;
}


static unsigned char rollDirect[3][PIECE_DEPTH] = {
    {2, 0, 1, 5, 3, 4, 8, 6, 7, 11, 9, 10, 14, 12, 13, 17, 15, 16, 20, 18, 19, 23, 21, 22, 26, 24, 25, 29, 27, 28 },
    {0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15, 16, 17, 18, 19, 20, 21, 22, 23, 24, 25, 26, 27, 28, 29 },
    {1, 2, 0, 4, 5, 3, 7, 8, 6, 10, 11, 9, 13, 14, 12, 16, 17, 15, 19, 20, 18, 22, 23, 21, 25, 26, 24, 28, 29, 27 },
};

void drawScreen(int side) { // --> cycles 44743 (@20221216)

    static unsigned char *const arenas[] = {
        RAM + _BUF_PF0_LEFT, // + SCORE_SCANLINES,
        RAM + _BUF_PF0_RIGHT, // + SCORE_SCANLINES,
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

        const int height = SCANLINES - scanline < PIECE_DEPTH
            ? SCANLINES - scanline
            : PIECE_DEPTH;

        for (int half = side; half < side+1; half++) {

            p = RAM + _BOARD + row * 40 + half * 4;
            grab(characterX, 5);

            unsigned char *pf0 = arenas[half] + scanline;

            for (int y = -lcount; y < height; y++) {

                int lineColour = rollDirect[roller][y];

                int p = ((unsigned int)(img[0][lineColour] | corner[0][lineColour]) << 27 >> 7)
                      | ((unsigned int)(img[1][lineColour] | corner[1][lineColour]) << 27 >> 12)
                      | ((unsigned int)(img[2][lineColour] | corner[2][lineColour]) << 27 >> 17)
                      | ((unsigned int)(img[3][lineColour] | corner[3][lineColour]) << 27 >> 22)
                      | ((unsigned int)(img[4][lineColour] | corner[4][lineColour]) << 27 >> 27);

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



// #define ICON_BASE 100

// void initIconPalette() {

//     if (rainbow) {
//         rollRainbow();
//         doRainbowBackground();
//     }

//     unsigned char rollColours[5];

//     // rollColours[0] = bgPalette[0];
//     rollColours[1] = fgPalette[0];
//     rollColours[2] = fgPalette[1];

//     int baseRoller = roller;

//     if (interleavedColour)
//         if (++baseRoller > 2)
//             baseRoller = 0;

//     unsigned char *pal0 = RAM + _BUF_MENU_COLUP0 + ICON_BASE - 1;

//     for (int j = 0; j < 22; j++) {
//         rollColours[0] = bgPalette[j];
//         for (int i = 0; i < 3; i++) {
//             *pal0++ = rollColours[baseRoller];
//             if (++baseRoller > 2)
//                 baseRoller = 0;
//         }
//     }
// }



// void drawIconScreen(int startRow, int endRow) { // --> 113431 cycles

//     p = RAM + _BOARD + startRow * 40;

//     int stepper = 40 * 65536 / 48;

//     unsigned int cc[48];
//     for (int i = 0; i < 48; i++)
//         cc[i] = (i * stepper) >> 16;

//     int m1 = 4 + (startRow & 1);
//     int m2 = m1 ^ 1;


//     for (int row = startRow; row < endRow; row++) {

//         int br = roller;

//         if (!interleavedColour)
//             br--;

//         for (int col = 0; col < 40; col++) {
//             unsigned char p2 = GET(p[col]);
//            int type = CharToType[p2];
//            if (Animate[type])
//                p2 = *Animate[type];
//             img[col] = charSet[p2];
//         }

//         p += 40;

//         unsigned char *ppf = RAM + ICON_BASE + row * 3 + _BUF_MENU_GRP0A;

//         for (int col = 0; col < 6; col++) {

//             unsigned int *p = cc + (col << 3);

//             for (int segment = 0; segment < 3; segment++) {

//                 if (++br > 2)
//                     br = 0;

//                 int roll = segment * 3 + br;

//                 ppf[segment] = (unsigned int)(img[p[0]][roll] >> m2 << 31) >> 24
//                              | (unsigned int)(img[p[1]][roll] >> m1 << 31) >> 25
//                              | (unsigned int)(img[p[2]][roll] >> m2 << 31) >> 26
//                              | (unsigned int)(img[p[3]][roll] >> m1 << 31) >> 27
//                              | (unsigned int)(img[p[4]][roll] >> m2 << 31) >> 28
//                              | (unsigned int)(img[p[5]][roll] >> m1 << 31) >> 29
//                              | (unsigned int)(img[p[6]][roll] >> m2 << 31) >> 30
//                              | (unsigned int)(img[p[7]][roll] >> m1 << 31) >> 31;
//             }

//             ppf += _ARENA_SCANLINES;
//         }

//         m1 ^= 1;
//         m2 ^= 1;
//     }
// }



bool drawBit(int x, int y) {


    int line = (y - ((scrollY) >> 16)) * 3;
    if (line < 0 || line >= _ARENA_SCANLINES - 3) // || line < SCORE_SCANLINES)
        return false;

    int col = x - ((scrollX * 5) >> 16);
//    int col = x - (scrollX >> 14);
    if (col < 0 || col > 39)
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
char rainRow[RAINHAILSHINE];


void rain() {

    for (int i = 0; i < RAINHAILSHINE; i++) {
        if (rainX[i] != -1) {


// 0 fire
// 1 death
// 2 boulder

            if (rainType[i] < 3) {     //bullet

                if (rainType[i] == 2 && rainAge[i] && !--rainAge[i]) {
                    rainX[i] = -1;
                    continue;
                }

                rainX[i] += rainSpeedX[i];
                rainY[i] += rainSpeedY[i];


#define CBLOCK ((PIECE_DEPTH/3) << 16)

                // if (rainY[i] > CBLOCK) {
                //     rainRow[i]++;
                //     rainY[i] -= CBLOCK;
                // }

                // else if (rainY[i] < 0) {
                //     rainRow[i]--;
                //     rainY[i] += CBLOCK;

                // }

                if (rainAge[i])
                    if (!--rainAge[i]) {
                        rainX[i] = -1;
                        continue;
                    }

                if (!drawBit((rainX[i] >> 8), (/*rainRow[i] * CBLOCK +*/ rainY[i]) >> 16))
                    rainX[i] = -1;
            }


        }
    }

}

// EOF
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
            
        const unsigned char blank[] = {
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

    rain();
}



// void drawHalfScreen() { // 66151


//     static unsigned char *const arenas[] = {
//         RAM + _BUF_PF0_LEFT, // + SCORE_SCANLINES,
//         RAM + _BUF_PF0_RIGHT, // + SCORE_SCANLINES,
//     };

// #if ENABLE_SHAKE
//     extern int shakeX, shakeY;
//     int lcount = -((scrollY + shakeY) >> 17) * 3;
//     int shift = 2 - (((scrollX + shakeX) >> 15) & 1);
//     int frac = (scrollX + shakeX) >> 16;
// #else
//     int lcount = -(scrollY >> 17) * 3;
//     int shift = 2 - ((scrollX >> 15) & 1);
//     int frac = scrollX >> 16;
// #endif


//     int rowOffset = (-lcount * (0x10000/15)) >> 16;
//     lcount += rowOffset * HALF_DEPTH;

//     for (int row = 0, scanline = 0; scanline < SCANLINES; row++) {

//         int height = SCANLINES - scanline;
//         if (height > HALF_DEPTH)
//             height = HALF_DEPTH;

//         for (int half = 0; half < 2; half++) {

//             p = RAM + _BOARD + (row + rowOffset) * 40 + half * 10;
//             grab(frac, 11);

//             unsigned char *pf0 = arenas[half] + scanline;

//             for (int y = -lcount; y < height; y++) {

//                 int lineColour = rollDirect[roller][y];

//                 int p = ((img[0][lineColour] >> 6 << 20)
//                        | (img[1][lineColour] >> 6 << 18)
//                        | (img[2][lineColour] >> 6 << 16)
//                        | (img[3][lineColour] >> 6 << 14)
//                        | (img[4][lineColour] >> 6 << 12)
//                        | (img[5][lineColour] >> 6 << 10)
//                        | (img[6][lineColour] >> 6 << 8)
//                        | (img[7][lineColour] >> 6 << 6)
//                        | (img[8][lineColour] >> 6 << 4)
//                        | (img[9][lineColour] >> 6 << 2)
//                        | (img[10][lineColour] >> 6))
    
//                         >> shift;

//                 *(pf0 + (_ARENA_SCANLINES << 1)) = BitRev[(unsigned char)p];
//                 *(pf0 + _ARENA_SCANLINES) = p >> 8;
//                 *pf0++ = BitRev[p >> 16];
//             }
//         }

//         scanline += height + lcount;
//         lcount = 0;
//     }

// }



// void drawOverviewScreen(int startRow, int endRow) { // 137110

//     unsigned char *rDirect = rollDirect[roller];

//     unsigned char *ppf0 = RAM + _BUF_PF0_LEFT + startRow * 9;
//     unsigned char *ppf1 = ppf0 + _ARENA_SCANLINES;
//     unsigned char *ppf2 = ppf1 + _ARENA_SCANLINES;
//     unsigned char *ppf3 = ppf2 + _ARENA_SCANLINES;
//     unsigned char *ppf4 = ppf3 + _ARENA_SCANLINES;
//     unsigned char *ppf5 = ppf4 + _ARENA_SCANLINES;

//     p = RAM + _BOARD + startRow * 40;

//     for (int row = startRow; row < endRow; row++) {

//         for (int col = 0; col < 40; col++) {
//             unsigned char p2 = GET2(p[col]);
//             unsigned char type = CharToType[p2];
//             img[col] = charSet[Animate[type] ? *Animate[type] : p2];
//         }

//         p += 40;


//         for (int iccLine = 0; iccLine < 9; iccLine++) {

//             int rollColour = rDirect[iccLine];
            
//             ppf0[iccLine] = (unsigned int)img[ 0][rollColour] >> 5 << 31 >> 27
//                           | (unsigned int)img[ 1][rollColour] >> 4 << 31 >> 26
//                           | (unsigned int)img[ 2][rollColour] >> 5 << 31 >> 25
//                           | (unsigned int)img[ 3][rollColour] >> 4 << 7;

//             ppf1[iccLine] = (unsigned int)img[ 4][rollColour] >> 5 << 7
//                           | (unsigned int)img[ 5][rollColour] >> 4 << 31 >> 25
//                           | (unsigned int)img[ 6][rollColour] >> 5 << 31 >> 26
//                           | (unsigned int)img[ 7][rollColour] >> 4 << 31 >> 27
//                           | (unsigned int)img[ 8][rollColour] >> 5 << 31 >> 28
//                           | (unsigned int)img[ 9][rollColour] >> 4 << 31 >> 29
//                           | (unsigned int)img[10][rollColour] >> 5 << 31 >> 30
//                           | (unsigned int)img[11][rollColour] >> 4 << 31 >> 31;

//             ppf2[iccLine] = (unsigned int)img[12][rollColour] >> 5 << 31 >> 31
//                           | (unsigned int)img[13][rollColour] >> 4 << 31 >> 30
//                           | (unsigned int)img[14][rollColour] >> 5 << 31 >> 29
//                           | (unsigned int)img[15][rollColour] >> 4 << 31 >> 28
//                           | (unsigned int)img[16][rollColour] >> 5 << 31 >> 27
//                           | (unsigned int)img[17][rollColour] >> 4 << 31 >> 26
//                           | (unsigned int)img[18][rollColour] >> 5 << 31 >> 25
//                           | (unsigned int)img[19][rollColour] >> 4 << 7;

//             ppf3[iccLine] = (unsigned int)img[20][rollColour] >> 5 << 31 >> 27
//                           | (unsigned int)img[21][rollColour] >> 4 << 31 >> 26
//                           | (unsigned int)img[22][rollColour] >> 5 << 31 >> 25
//                           | (unsigned int)img[23][rollColour] >> 4 << 7;
  
//             ppf4[iccLine] = (unsigned int)img[24][rollColour] >> 5 << 7
//                           | (unsigned int)img[25][rollColour] >> 4 << 31 >> 25
//                           | (unsigned int)img[26][rollColour] >> 5 << 31 >> 26
//                           | (unsigned int)img[27][rollColour] >> 4 << 31 >> 27
//                           | (unsigned int)img[28][rollColour] >> 5 << 31 >> 28
//                           | (unsigned int)img[29][rollColour] >> 4 << 31 >> 29
//                           | (unsigned int)img[30][rollColour] >> 5 << 31 >> 30
//                           | (unsigned int)img[31][rollColour] >> 4 << 31 >> 31;


//             // ppf5[iccLine] = (unsigned int)img[32][rollColour] >> 5 << 31 >> 31
//             //               | (unsigned int)img[33][rollColour] >> 4 << 31 >> 30
//             //               | (unsigned int)img[34][rollColour] >> 5 << 31 >> 29
//             //               | (unsigned int)img[35][rollColour] >> 4 << 31 >> 28
//             //               | (unsigned int)img[36][rollColour] >> 5 << 31 >> 27
//             //               | (unsigned int)img[37][rollColour] >> 4 << 31 >> 26
//             //               | (unsigned int)img[38][rollColour] >> 5 << 31 >> 25
//             //               | (unsigned int)img[39][rollColour] >> 4 << 7;

//             // strange, but this "less efficient" version is faster...                          

//             ppf5[iccLine] =
//                   ((((unsigned char)(img[32][rollColour] << 2)) >> 7))
//                 | ((((unsigned char)(img[33][rollColour] << 3)) >> 7) << 1)
//                 | ((((unsigned char)(img[34][rollColour] << 2)) >> 7) << 2)
//                 | ((((unsigned char)(img[35][rollColour] << 3)) >> 7) << 3)
//                 | ((((unsigned char)(img[36][rollColour] << 2)) >> 7) << 4)
//                 | ((((unsigned char)(img[37][rollColour] << 3)) >> 7) << 5)
//                 | ((((unsigned char)(img[38][rollColour] << 2)) >> 7) << 6)
//                 | ((((unsigned char)(img[39][rollColour] << 3)) >> 7) << 7);

//         }

//         ppf0 += 9;
//         ppf1 += 9;
//         ppf2 += 9;
//         ppf3 += 9;
//         ppf4 += 9;
//         ppf5 += 9;
//     }
// }



#define ICON_BASE 100

void initIconPalette() {

    if (rainbow) {
        rollRainbow();
        doRainbowBackground();
    }

    unsigned char rollColours[5];

    // rollColours[0] = bgPalette[0];
    rollColours[1] = fgPalette[0];
    rollColours[2] = fgPalette[1];

    int baseRoller = roller;

    if (interleavedColour)
        if (++baseRoller > 2)
            baseRoller = 0;

    unsigned char *pal0 = RAM + _BUF_MENU_COLUP0 + ICON_BASE - 1;

    for (int j = 0; j < 22; j++) {
        rollColours[0] = bgPalette[j];
        for (int i = 0; i < 3; i++) {
            *pal0++ = rollColours[baseRoller];
            if (++baseRoller > 2)
                baseRoller = 0;
        }
    }
}



void drawIconScreen(int startRow, int endRow) { // --> 113431 cycles

    p = RAM + _BOARD + startRow * 40;

    int stepper = 40 * 65536 / 48;

    unsigned int cc[48];
    for (int i = 0; i < 48; i++)
        cc[i] = (i * stepper) >> 16;

    int m1 = 4 + (startRow & 1);
    int m2 = m1 ^ 1;


    for (int row = startRow; row < endRow; row++) {

        int br = roller;

        if (!interleavedColour)
            br--;

        for (int col = 0; col < 40; col++) {
            unsigned char p2 = GET(p[col]);
           int type = CharToType[p2];
           if (Animate[type])
               p2 = *Animate[type];
            img[col] = charSet[p2];
        }

        p += 40;

        unsigned char *ppf = RAM + ICON_BASE + row * 3 + _BUF_MENU_GRP0A;

        for (int col = 0; col < 6; col++) {

            unsigned int *p = cc + (col << 3);

            for (int segment = 0; segment < 3; segment++) {

                if (++br > 2)
                    br = 0;

                int roll = segment * 3 + br;

                ppf[segment] = (unsigned int)(img[p[0]][roll] >> m2 << 31) >> 24
                             | (unsigned int)(img[p[1]][roll] >> m1 << 31) >> 25
                             | (unsigned int)(img[p[2]][roll] >> m2 << 31) >> 26
                             | (unsigned int)(img[p[3]][roll] >> m1 << 31) >> 27
                             | (unsigned int)(img[p[4]][roll] >> m2 << 31) >> 28
                             | (unsigned int)(img[p[5]][roll] >> m1 << 31) >> 29
                             | (unsigned int)(img[p[6]][roll] >> m2 << 31) >> 30
                             | (unsigned int)(img[p[7]][roll] >> m1 << 31) >> 31;
            }

            ppf += _ARENA_SCANLINES;
        }

        m1 ^= 1;
        m2 ^= 1;
    }
}



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

short rainType[RAINHAILSHINE];
short rainAge[RAINHAILSHINE];

int rainX[RAINHAILSHINE];
int rainY[RAINHAILSHINE], /*rainSpeed[RAINHAILSHINE],*/ rainSpeedX[RAINHAILSHINE];
int rainSpeedY[RAINHAILSHINE];
char rainRow[RAINHAILSHINE];


void rain() {

    for (int i = 0; i < RAINHAILSHINE; i++) {
        if (rainX[i] != -1) {

            // unsigned char *cell = RAM + _BOARD + rainRow[i] * 40 + (rainX[i] >> 8);
            // int type = CharToType[GET2(*cell) & 0x7F];

            // bool halt = false;

            // if (type == TYPE_ROCKFORD) {
            //     if ((rainX[i] + 1) & 2) {                   // col 0 or 3?
            //         if (playerAnimationID == ID_Stand)
            //             startPlayerAnimation(ID_Drip);
            //         halt = true;
            //     }
            //     else {
            //         if (playerAnimationID == ID_Stand)
            //             startPlayerAnimation(ID_Talk2);
            //     }
            // }

            // else 

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

//    rainX[i] = 0xA00;
//    rainRow[i] = 3;

                // if (rainAge[i] == 2)
                //     rainSpeedY[i] += 0x500;         // gravity


#define CBLOCK ((PIECE_DEPTH/3) << 16)

                if (rainY[i] > CBLOCK) {
                    rainRow[i]++;
                    rainY[i] -= CBLOCK;
                }

                else if (rainY[i] < 0) {
                    rainRow[i]--;
                    rainY[i] += CBLOCK;

                }

                if (rainAge[i])
                    if (!--rainAge[i]) {
                        rainX[i] = -1;
                        continue;
                    }

        //         if (rainAge[i] == 0 ) {
        //             cell = RAM + _BOARD + rainRow[i] * 40 + (rainX[i] >> 8);
        //             type = CharToType[GET2(*cell) & 0x7F];


        //             if (Attribute[type] & (ATT_DIRT | ATT_GRAB)) {
        //                 *cell = CH_DUST_0;
        //                 rainX[i] = -1;
        //                 ADDAUDIO(SFX_DRIP);
        //                 continue;
        //             }

        //             if (Attribute[type] != ATT_GRAB)
        //                 if (type != TYPE_SPACE && type != TYPE_ROCKFORD) {

        // //                if (Attribute[type] != ATT_ROCKFORDYBLANK) {
        //                     rainX[i] = -1;
        //                     continue;
        //                 }
        //         }


                if (!drawBit((rainX[i] >> 8), (rainRow[i] * CBLOCK + rainY[i]) >> 16))
                    rainX[i] = -1;
            }

            // else {
                
            //     if (type == TYPE_DOGE) {
            //         *cell = CH_DUST_0;
            //         rainX[i] = -1;
            //         ADDAUDIO(SFX_DRIP);
            //         continue;
            //     }

            //     if (halt || !(Attribute[type] & ATT_ROCKFORDYBLANK)) {


            //         if (rainSpeed[i] > 0) {
            //             rainSpeed[i] = RAIN_RESET_AFTER_IMPACT;
            //             ADDAUDIO(SFX_DRIP2);
            //         }

            //         else if (rainSpeed[i] > RAIN_DEAD) {
            //             rainX[i] = -1;
            //             continue;
            //         }
            //     }

            //     rainSpeed[i] += RAIN_ACCEL;


            //     if (rainSpeed[i] > 0) {
            //         rainY[i] += rainSpeed[i];

            //         if (rainY[i] > 0xA0000) {
            //             rainRow[i]++;
            //             rainY[i] -= 0xA0000;
            //         }
            //     }
            // }

            // if ((rainSpeed[i] & 0x2000) || rainSpeed[i] > 0)
            //     if (!drawBit(rainX[i]>>8, (rainRow[i] * 10) + (rainY[i] >> 16) ))
            //         rainX[i] = -1;
        }
    }

}

// EOF
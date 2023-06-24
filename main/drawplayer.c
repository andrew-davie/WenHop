// #include "defines_from_dasm_for_c.h"
#include <stdbool.h>

#include "main.h"

#include "attribute.h"
#include "colour.h"
#include "defines.h"
#include "defines_cdfj.h"
#include "drawplayer.h"
#include "mellon.h"
#include "player.h"
#include "random.h"
#include "scroll.h"
#include "sound.h"
#include "swipeCircle.h"

static int playerSpriteY;

unsigned char dynamicPlayerColours[16];
unsigned char playerBaseColour[16];
unsigned char postProcessPlayerColours[16];

void initSprites() {

    playerSpriteY = -1;

    int rcol = getRandom32() & 0xF0;

    static const unsigned char playerColour[] = {

        0x28, // 00 HAIR
        0x34, // 01 SKIN
        0x06, // 02 TOP1
        0x06, // 03 TOP2
        0x44, // 04 BOOT
        0x44, // 05 PANT
        0x58, // 06 BELT
        0x08, // 07 SOLE
        0x08, // 08 BONE
        0x2C, // 09 HMT0
        0x28, // 10 HMT1
        0x26, // 11 HMT2
        0x22, // 12 HMT3
        0x4A, // 13 BDY0
        0x46, // 14 BDY1
        0x44, // 15 BDY2
    };

    for (int i = 0; i < 16; i++) {
        playerBaseColour[i] = dynamicPlayerColours[i] = convertColour(playerColour[i]) + rcol;
        postProcessPlayerColours[i] = dynamicPlayerColours[i] & 0xF0;
    }
}

// const unsigned char tinyDigit[][7] = {
// {
//     0b111,
//     0b101,
//     0b101,
//     0b101,
//     0b101,
//     0b101,
//     0b111,
// },

// {
//     0b010,
//     0b010,
//     0b010,
//     0b010,
//     0b010,
//     0b010,
//     0b010,
// },

// {
//     0b111,
//     0b001,
//     0b001,
//     0b111,
//     0b100,
//     0b100,
//     0b111,
// },

// {
//     0b111,
//     0b001,
//     0b001,
//     0b111,
//     0b001,
//     0b001,
//     0b111,
// },

// {
//     0b100,
//     0b101,
//     0b101,
//     0b111,
//     0b001,
//     0b001,
//     0b001,
// },

// {
//     0b111,
//     0b100,
//     0b100,
//     0b111,
//     0b001,
//     0b001,
//     0b111,
// },

// {
//     0b111,
//     0b100,
//     0b100,
//     0b111,
//     0b101,
//     0b101,
//     0b111,
// },

// {
//     0b111,
//     0b001,
//     0b001,
//     0b001,
//     0b001,
//     0b001,
//     0b001,
// },

// {
//     0b111,
//     0b101,
//     0b101,
//     0b111,
//     0b101,
//     0b101,
//     0b111,
// },

// {
//     0b111,
//     0b101,
//     0b101,
//     0b111,
//     0b001,
//     0b001,
//     0b111,
// },
// };

const unsigned char cx[][4] = {
    {0x40, 0x40, 0x40, 0x40},
    {0x20, 0x30, 0x40, 0x50},
};

void drawPlayerSprite() { // --> 3171 cycles

    static int root = 0;
    root++;

    int rooted = cx[1][(root >> 3) & 3];

    if (pulsePlayerColour) {
        if (!(--pulsePlayerColour & 7)) {
            int cswitch = getRandom32() & 0xF0;
            for (int i = 9; i < 13; i++)
                postProcessPlayerColours[i] = cswitch;
        }
    }

    else {
        rooted = cx[0][(root >> 3) & 3];
        for (int i = 0; i < 16; i++)
            postProcessPlayerColours[i] = playerBaseColour[i] & 0xF0;
    }

#if ENABLE_SHAKE
    extern int shakeX, shakeY;

    int x = ((scrollX + shakeX) * 5) >> 16;
    int y = (scrollY + shakeY) >> 16;
#else
    int x = scrollX >> 14;
    int y = scrollY >> 16;

#endif

    int ypos = (playerY + 1) * PIECE_DEPTH - y * 3 - frameAdjustY * gravity - 8 + autoMoveY -
               SCORE_SCANLINES;
    int xpos = playerX * 5 - x;

    if (((frameAdjustY || frameAdjustX || autoMoveX || autoMoveY)) ||
        (xpos >= 0 && xpos < _BOARD_COLS - 1 && ypos >= 0 &&
         ypos < _ARENA_SCANLINES - PIECE_DEPTH)) {

        const unsigned char *spr = spriteShape[*playerAnimation];
        if (!spr)
            spr = spriteShape[1];

        int shapeHeight = *spr++;

        ypos += 30 - (shapeHeight & 0x3f);

        int frameOffset = *(const signed char *)spr++;
        int frameYOffset = *(const signed char *)spr++;

        int lavaLine = (lavaSurfaceTrixel - (scrollY >> 16)) * 3;
        playerSpriteY = ypos - frameYOffset - 1;

        int pX = (xpos)*4 + (faceDirection * (frameOffset + frameAdjustX + autoMoveX)) + 2;

        if (playerSpriteY < 0 || playerSpriteY >= _ARENA_SCANLINES - SPRITE_DEPTH || pX > 159)
            return;

        P0_X = pX;
        if (faceDirection == FACE_LEFT) {
            P1_X = P0_X;
            P0_X += 8;
        } else
            P1_X = P0_X + 8;

        extern int gravity;
        int destLine = -1;

        if (gravity < 0)
            destLine = (shapeHeight & 0x3F) - 4;

        if (shapeHeight & SPRITE_DOUBLE) {

            unsigned char *p0Colour = RAM + _BUF_COLUP0 + playerSpriteY + 1;
            unsigned char *p0 = RAM + _BUF_GRP0A + playerSpriteY;

            unsigned char *p1Colour = p0Colour + _ARENA_SCANLINES;
            unsigned char *p1 = p0 + _ARENA_SCANLINES;

            for (int line = 0; line < (shapeHeight & 0x3f); line++) {

                if (faceDirection == FACE_RIGHT) {
                    p0[destLine] = *spr++;
                    p1[destLine] = *spr++;
                }

                else {
                    p0[destLine] = reverseBits[(unsigned char)*spr++];
                    p1[destLine] = reverseBits[(unsigned char)*spr++];
                }

                int c1 = *spr >> 4;
                int c2 = *spr++ & 0xF;

                if (shapeHeight & SPRITE_ABSCOLOUR) {
                    p0Colour[destLine] = c1;
                    p1Colour[destLine] = c2;
                }

                else {

                    p0Colour[destLine] =
                        (dynamicPlayerColours[c1] & 0xF) ^ postProcessPlayerColours[c1];
                    p1Colour[destLine] =
                        (dynamicPlayerColours[c2] & 0xF) ^ postProcessPlayerColours[c2];

                    if (playerSpriteY++ >= lavaLine) {
                        p0Colour[destLine] = ((p0Colour[destLine] & 0x0f) - 2) ^ (rooted & 0xF0);
                        p1Colour[destLine] = ((p1Colour[destLine] & 0x0f) - 2) ^ (rooted & 0xF0);
                    }
                }

                destLine += gravity;
            }

        }

        else {

            unsigned char *p0Colour = RAM + _BUF_COLUP0 + playerSpriteY + 1;
            unsigned char *p0 = RAM + _BUF_GRP0A + playerSpriteY;

            for (int line = 0; line < (shapeHeight & 0x3F); line++) {

                if (faceDirection == FACE_RIGHT)
                    p0[destLine] = *spr++;
                else
                    p0[destLine] = reverseBits[(unsigned char)*spr++];

                int c1 = *spr++ >> 4;

                if (shapeHeight & SPRITE_ABSCOLOUR)
                    p0Colour[destLine] = c1;

                else {

                    p0Colour[destLine] =
                        (dynamicPlayerColours[c1] & 0xF) ^ postProcessPlayerColours[c1];

                    if (playerSpriteY++ >= lavaLine) {
                        p0Colour[destLine] = ((p0Colour[destLine] & 0x0f) - 2) ^ (rooted & 0xF0);
                    }
                }

                destLine += gravity;
            }
        }
    }
}

// EOF
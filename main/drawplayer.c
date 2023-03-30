#include <stdbool.h>
#include "defines_cdfj.h"
#include "defines.h"
#include "main.h"
#include "drawplayer.h"
#include "bitpatterns.h"
#include "swipeCircle.h"
#include "colour.h"
#include "attribute.h"
#include "player.h"
#include "random.h"
#include "rockford.h"
#include "scroll.h"


static int playerSpriteY;


extern const unsigned char playerColour[];
unsigned char dynamicPlayerColours[16];
unsigned char playerBaseColour[16];
unsigned char postProcessPlayerColours[16];


void initSprites() {

    playerSpriteY = -1;

    int rcol = getRandom32() & 0xF0;

    for (int i = 0; i < 16; i++) {
        playerBaseColour[i] =
        dynamicPlayerColours[i] = convertColour(playerColour[i]) + rcol;
    }

    // for (int i = 9; i < 16; i++)
    //     dynamicPlayerColours[i] += rcol;


    for (int i = 0; i < 16; i++)
        postProcessPlayerColours[i] = dynamicPlayerColours[i] & 0xF0;
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




void drawPlayerSprite() {  // --> 3171 cycles


    static int root = 0;
    root++;

    const unsigned char c[] = { 0x20, 0x30, 0x40, 0x50 };
    int rooted = c[(root >> 3) & 3];



    if (cpulse) {
        if (!(--cpulse & 7)) {
            int cswitch = getRandom32() & 0xF0;
            for (int i = 9; i < 13; i++)
                postProcessPlayerColours[i] = cswitch;
        }
    }

    else {
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

    int ypos = (rockfordY  + 1) * PIECE_DEPTH - y * 3 - frameAdjustY - 8 + autoMoveY - SCORE_SCANLINES;
    int xpos = rockfordX * 5 - x;


    if (((frameAdjustY || frameAdjustX || autoMoveX || autoMoveY )) || (xpos >= 0 && xpos < 39
        && ypos >= 0 && ypos < _ARENA_SCANLINES-PIECE_DEPTH)) {

        const unsigned char *spr = spriteShape[*playerAnimation];
        if (!spr)
            spr = spriteShape[1];

        int shapeHeight = *spr++;

        ypos += 30 - (shapeHeight & 0x3f);


        int frameOffset = *(const signed char *)spr++;
        int frameYOffset = *(const signed char *)spr++;

        int lavaLine = (lavaSurface - (scrollY >> 16)) * 3;
        playerSpriteY = ypos - frameYOffset - 1;

        int pX = (xpos) * 4 + (rockfordFaceDirection * (frameOffset + frameAdjustX + autoMoveX)) + 2;

        if (playerSpriteY < 0 || playerSpriteY >= _ARENA_SCANLINES - SPRITE_DEPTH
            || pX > 159)
            return;


        P0_X = pX;
        if (rockfordFaceDirection == FACE_LEFT) {
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

                if (rockfordFaceDirection == FACE_RIGHT) {
                    p0[destLine] = *spr++;
                    p1[destLine] = *spr++;
                }

                else {
                    p0[destLine] = BitRev[(unsigned char) *spr++];
                    p1[destLine] = BitRev[(unsigned char) *spr++];
                }

                int c1 = *spr >> 4;
                int c2 = *spr++ & 0xF;

                if (shapeHeight & SPRITE_ABSCOLOUR) {
                    p0Colour[destLine] = c1;
                    p1Colour[destLine] = c2;
                }

                else {


                    p0Colour[destLine] = (dynamicPlayerColours[c1] & 0xF) ^ postProcessPlayerColours[c1];
                    p1Colour[destLine] = (dynamicPlayerColours[c2] & 0xF) ^ postProcessPlayerColours[c2];

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

                if (rockfordFaceDirection == FACE_RIGHT)
                    p0[destLine] = *spr++;
                else
                    p0[destLine] = BitRev[(unsigned char) *spr++];

                int c1 = *spr++ >> 4;

                if (shapeHeight & SPRITE_ABSCOLOUR)
                    p0Colour[destLine] = c1;

                else {

                    p0Colour[destLine] = (dynamicPlayerColours[c1] & 0xF) ^ postProcessPlayerColours[c1];

                    if (playerSpriteY++ >= lavaLine) {
                        p0Colour[destLine] = ((p0Colour[destLine] & 0x0f) - 2) ^ (rooted & 0xF0);
                    }
                }

                destLine += gravity;
            }
        }




        // p1Colour = RAM + _BUF_COLUP1 + playerSpriteY - 11;
        // p1 = RAM + _BUF_GRP1A + playerSpriteY - 11;
        // p0Colour = RAM + _BUF_COLUP0 + playerSpriteY - 10;
        // p0 = RAM + _BUF_GRP0A + playerSpriteY - 10;

        // for (int i = 0; i < 7; i++) {
        //     *p0++ = /*(tinyDigit[0][i] << 4) | */(tinyDigit[5][i]);
        //     *p1++ = (tinyDigit[0][i] << 4) | (tinyDigit[0][i]);
        //     *p0Colour++ = 0x08;
        //     *p1Colour++ = 0x08;
        // }


        // const unsigned char drill[] = {

        //     0b10100,
        //     0b01110,
        //     0b00101,
        //     0b00100,
        //     0b00100,
        //     0b00100,
        //     0b00100,


        // };


        // int drillDepth = 30;
        // static int drillofset = 0;

        // drillofset++;

        // p1Colour = RAM + _BUF_COLUP1 + playerSpriteY + 20;
        // p1 = RAM + _BUF_GRP1A + playerSpriteY + 20;

        // for (int i = 0; i < drillDepth; i++) {
        //     *p1++ = drill[(i + (drillofset >> 1)) & 7];
        //     *p1Colour++ = 0x8;
        // }

    }


}


//EOF
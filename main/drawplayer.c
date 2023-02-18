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
static int playerHalfSpriteY;
static int playerSmallSpriteY;



void initSprites() {

    playerSpriteY =
    playerHalfSpriteY =
    playerSmallSpriteY -1;
}



extern const unsigned char playerColour[][4];


void drawPlayerSprite() {  // --> 3171 cycles

    // if (time < 0xA00 && (time & 2))
    //     return;


#if ENABLE_SHAKE
    extern int shakeX, shakeY;

    int x = (scrollX + shakeX) >> 14;
    int y = (scrollY + shakeY) >> 16;
#else
    int x = scrollX >> 14;
    int y = scrollY >> 16;

#endif

    // removeSprite();

    // if (rockfordDeadRelease)
    //     return;


    int ypos = (rockfordY  + 1) * PIECE_DEPTH - y * 3 - frameAdjustY -1 + autoMoveY - SCORE_SCANLINES;
    int xpos = rockfordX * 4 - x;


    if ((/*rockfordDead &&*/ (frameAdjustY || frameAdjustX || autoMoveX || autoMoveY )) || (/*(type == TYPE_ROCKFORD)
        &&*/ xpos >= 0 && xpos < 39
        && ypos >= 0 && ypos < _ARENA_SCANLINES-PIECE_DEPTH)) {

        const unsigned char *spr = (const unsigned char *)playerBigSprite[*playerAnimation];


        int frameOffset = *(const signed char *)spr++;
        int frameYOffset = *(const signed char *)spr++;
    

        playerSpriteY = ypos + frameYOffset - 1;

        int pX = ((rockfordX * 4)- x) * 4 + (rockfordFaceDirection * (frameOffset + frameAdjustX + autoMoveX));

        if (playerSpriteY < 0 || playerSpriteY >= _ARENA_SCANLINES - SPRITE_DEPTH
            || pX > 159)
            return;


        P0_X = pX;            
        if (rockfordFaceDirection == FACE_LEFT) {
            P1_X = P0_X;
            P0_X += 8;
        } else
            P1_X = P0_X + 8;


        unsigned char *p0Colour = RAM + _BUF_COLUP0 + playerSpriteY;
        unsigned char *p1Colour = p0Colour + _ARENA_SCANLINES;

        unsigned char *p0 = RAM + _BUF_GRP0A + playerSpriteY;
        unsigned char *p1 = p0 + _ARENA_SCANLINES;
        
#if __FADE
        unsigned int theFade = mm_tv_type == SECAM ? 0x10000 : fade;
#endif

        for (int line = 0; line < SPRITE_DEPTH; line++) {
            
            if (rockfordFaceDirection == FACE_RIGHT) {
                p0[line] = *spr++;
                p1[line] = *spr++;
            }

            else {
                p0[line] = BitRev[(unsigned char) *spr++];
                p1[line] = BitRev[(unsigned char) *spr++];
            }

            int col = *spr >> 4;
            int hueLum = playerColour[col][mm_tv_type];

#if __FADE
            p0Colour[line] = (hueLum & 0xF0) | (((hueLum & 0xF) * theFade) >> 16);
#else
            p0Colour[line] = hueLum;
#endif
            col = *spr++ & 0xF;
            hueLum = playerColour[col][mm_tv_type];

#if __FADE
            p1Colour[line] = (hueLum & 0xF0) | (((hueLum & 0xF) * theFade) >> 16);
#else
            p1Colour[line] = hueLum;
#endif
        }
    }
}


#define Fifteen21 ((int)(((int)0xF000)/((int)PIECE_DEPTH)))


void drawHalfSprite() { // --> 3960 cycles


#if CIRCLE
     if (!checkSwipeFinished())
        return;
#endif

    const signed char *spr = playerBigSprite[*playerAnimation];
    int frameXOffset = *spr++;
    int frameYOffset = *spr++;

    playerHalfSpriteY = SCORE_SCANLINES + 1
        + rockfordY * HALF_DEPTH
        - ((scrollY * 3) >> 17)
        + ((frameYOffset * 3) >> 2)
        - ((frameAdjustY * 3) >> 5)
        + ((autoMoveY * Fifteen21) >> 12);

    int x = scrollX >> 15;
    x = (((rockfordX << 1) - x) << 2)
        + (rockfordFaceDirection * ((frameXOffset + frameAdjustX + autoMoveX) >> 1));

    P0_X = x;
    P1_X = 10;

    if (playerHalfSpriteY < 0 || playerHalfSpriteY > _ARENA_SCANLINES - 15)
        return;

    unsigned char *p0Colour = RAM + _BUF_COLUP0 + playerHalfSpriteY;
    unsigned char *p0 = RAM + _BUF_GRP0A + playerHalfSpriteY;
    unsigned int newSp;

    for (int line = 0; line < HALF_DEPTH; line++) {

        const unsigned char *spr = (const unsigned char *) playerBigSprite[*playerAnimation]
            + (((line * (0x1700 / HALF_DEPTH) >> 8) * 3) + 5);

        int combined = (spr[0] << 8) | spr[1];

        newSp = 0;
        for (int bit = 0; bit < 8; bit++)
            if (combined & (1 << ((bit << 1) + 1)))
                newSp |= 1 << bit;

        p0[line] = (rockfordFaceDirection == FACE_RIGHT) ? newSp : BitRev[newSp];
        p0Colour[line] = playerColour[(spr[2] & 0xF)][mm_tv_type];
    }
}



void drawPlayerSmallSprite() { // --> 2132 cycles

#define Nine21 ((int)(((int)0x9000)/((int)PIECE_DEPTH)))

    const signed char *spr = playerBigSprite[*playerAnimation];
    int frameOffset = *spr++;
    int frameYOffset = *spr++ >> 1;

    playerSmallSpriteY = rockfordY * 9
                           + frameYOffset
                           - (frameAdjustY >> 3)
                           + ((autoMoveY * Nine21) >> 12)
                           - 1;

    if (playerSmallSpriteY < 0
        || playerSmallSpriteY > _ARENA_SCANLINES - 10)
        return;

    P0_X = (rockfordX << 2)
           + (rockfordFaceDirection * ((frameOffset + frameAdjustX + autoMoveX) >> 2) + 1)
           - 3;
    P1_X = 10;



    unsigned char *p0Colour = RAM + _BUF_COLUP0 + playerSmallSpriteY;
    unsigned char *p0 = RAM + _BUF_GRP0A + playerSmallSpriteY;
    
    {
        const unsigned char *spr = (const unsigned char *) (playerBigSprite[*playerAnimation] + 8);

        unsigned int newSp;
        for (int line = 0; line < 11; line++) {

            int combined = (spr[0] << 8) | spr[1];

            newSp = 0;
            for (int bit = 0; bit < 6; bit++)
                if (combined & (3 << (3 * bit)))
                    newSp |= 1 << bit;

            p0[line] = (rockfordFaceDirection == FACE_RIGHT) ? newSp : BitRev[newSp];
            p0Colour[line] = playerColour[(spr[2] >> 4)/* + easterEggColour*/][mm_tv_type];

            spr += 6;
        }
    }
}

//EOF
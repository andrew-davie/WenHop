#include "scroll.h"
#include "cavedata.h"
#include "decodecaves.h"
#include "defines_cdfj.h"
#include "main.h"
#include "mellon.h"
#include "player.h"

int scrollX, scrollY;
// int scrollLimitXLeft,scrollLimitXRight;
// int scrollLimitYTop, scrollLimitYButtom;

static int scrollSpeedX, scrollSpeedY;
static int targetScrollSpeed, targetYScrollSpeed;

#define accel 4096
#define accelY (accel * 16)
#define decel (accel * 8 / 8)
#define decelY (decel * 8)

int isScrolling() {
    return (/*displayMode == DISPLAY_NORMAL && */ (scrollSpeedX | scrollSpeedY));
}

void Scroll() {

    // if (lockDisplay && displayMode ==m DISPLAY_HALF) {
    //     scrollX = 40 << 14;
    //     scrollY = 53 << 16;
    //     return;
    // }

#if 0
    else if (theCave->flags & CAVEDEF_LEARN) {
        scrollX = 0;
        scrollY = 0;

        return;
    }
#endif

    if (playerDead && !waitRelease && *playerAnimation == FRAME_BLANK) {

        int speedFactor = 1; // displayMode == DISPLAY_NORMAL ? 1 : 2;

        for (int dir = 0; dir < 4; dir++) {
            if (!(swcha & (joyDirectBit[dir] << 4))) {
                scrollX += ((int)xInc[joyDirectBit[dir]] * speedFactor) << 13;
                scrollY += ((int)yInc[joyDirectBit[dir]] * speedFactor) << 16;
            }
        }
    }

    else {

#define PIXELS_PER_CHAR2 4

        int recip = reciprocal[0];
        ; // gameSpeed - SPEED_BASE];
        int rockx = playerX * PIXELS_PER_CHAR2 + (PIXELS_PER_CHAR2 >> 1);
        int rocky = playerY * TRILINES + (TRILINES >> 1);

        int max = (SCROLLSPEED_MAXIMUM_X * recip) >> 8;

        int halfwayPix = (scrollX >> 14) + HALFWAYX;
        int triggerEdgePix = SCROLL_TRIGGEREDGE_HORIZONTAL;

        // if (displayMode == DISPLAY_HALF) {
        //     halfwayPix += HALFWAYX;
        //     triggerEdgePix *= 4;
        // }

        if (rockx < halfwayPix - triggerEdgePix)
            targetScrollSpeed = -max;
        else if (rockx > halfwayPix + triggerEdgePix)
            targetScrollSpeed = max;

        // Y...

        halfwayPix = (scrollY >> 16) + HALFWAYY;
        max = (SCROLLSPEED_MAXIMUM_Y * recip) >> 8;

        triggerEdgePix = SCROLL_TRIGGEREDGE_VERTICAL;

        //        if (displayMode == DISPLAY_HALF) {
        //            max *= 2;
        //            halfwayPix += HALFWAYY;
        //            triggerEdgePix *= 2;
        //        }

        if ((halfwayPix - triggerEdgePix) - rocky > 0)
            targetYScrollSpeed = -max;
        else if (rocky - (halfwayPix + triggerEdgePix) > 0)
            targetYScrollSpeed = max;

        int adjustedAccel = (accel * recip) >> 16;

        if (scrollSpeedX < targetScrollSpeed) {
            scrollSpeedX += adjustedAccel;
            if (scrollSpeedX > targetScrollSpeed)
                scrollSpeedX = targetScrollSpeed;
        }

        if (scrollSpeedX > targetScrollSpeed) {
            scrollSpeedX -= adjustedAccel;
            if (scrollSpeedX < targetScrollSpeed)
                scrollSpeedX = targetScrollSpeed;
        }

        adjustedAccel = (accelY * recip) >> 16;

        if (scrollSpeedY < targetYScrollSpeed) {
            scrollSpeedY += adjustedAccel;
            if (scrollSpeedY > targetYScrollSpeed)
                scrollSpeedY = targetYScrollSpeed;
        }

        if (scrollSpeedY > targetYScrollSpeed) {
            scrollSpeedY -= adjustedAccel;
            if (scrollSpeedY < targetYScrollSpeed)
                scrollSpeedY = targetYScrollSpeed;
        }

        adjustedAccel = (decel * recip) >> 16;
        // if (displayMode == DISPLAY_HALF)
        //     adjustedAccel *= 4;

        if (targetScrollSpeed < 0) {
            targetScrollSpeed += adjustedAccel;
            if (targetScrollSpeed > 0)
                targetScrollSpeed = 0;
        }

        if (targetScrollSpeed > 0) {
            targetScrollSpeed -= adjustedAccel;
            if (targetScrollSpeed < 0)
                targetScrollSpeed = 0;
        }

        adjustedAccel = (decelY * recip) >> 16;
        // if (displayMode == DISPLAY_HALF)
        //     adjustedAccel *= 4;

        if (targetYScrollSpeed < 0) {
            targetYScrollSpeed += adjustedAccel;
            if (targetYScrollSpeed > 0)
                targetYScrollSpeed = 0;
        }

        if (targetYScrollSpeed > 0) {
            targetYScrollSpeed -= adjustedAccel;
            if (targetYScrollSpeed < 0)
                targetYScrollSpeed = 0;
        }

        scrollX += scrollSpeedX;
        scrollY += scrollSpeedY;
    }

    int maxX, maxY;
    // if (displayMode == DISPLAY_HALF) {

    //     maxX = 0x140000;
    //     maxY = 0x660000 - 0x100000;
    // }
    // else {
    maxX = SCROLL_MAXIMUM_X;
    maxY = (16 * PIECE_DEPTH / 3 - 6) << 16;
    // }

    if (scrollX >= maxX) {
        scrollX = maxX;
        targetScrollSpeed = 0;
        scrollSpeedX = 0;
    }

    else if (scrollX < SCROLL_MINIMUM) {
        scrollX = SCROLL_MINIMUM;
        scrollSpeedX = 0;
        targetScrollSpeed = 0;
    }

    if (scrollY > maxY) {
        scrollY = maxY;
        scrollSpeedY = 0;
        targetYScrollSpeed = 0;
    }

    else if (scrollY < SCROLL_MINIMUM) {
        scrollY = SCROLL_MINIMUM;
        scrollSpeedY = 0;
        targetYScrollSpeed = 0;
    }
}

void resetTracking() {

    // if (displayMode == DISPLAY_NORMAL)
    scrollX = (playerX - (HALFWAYX / 5)) << 16;

    // else if (displayMode == DISPLAY_HALF)
    //     scrollX = (playerX - (HALFWAYX >> 1)) << 16;

    scrollY = ((playerY - 4) * TRILINES) << 16;

    if (scrollX < 0)
        scrollX = 0;
    if (scrollY < 0)
        scrollY = 0;

    scrollSpeedX =
        scrollSpeedY =
            targetScrollSpeed =
                targetYScrollSpeed = 0;
}

// EOF
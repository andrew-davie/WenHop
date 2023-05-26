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

#include "main.h"

#include "swipeCircle.h"

#include "colour.h"
#include "sound.h"

#if CIRCLE

#define CIRCLE_CENTER_X 20
#define CIRCLE_CENTER_Y (_ARENA_SCANLINES / 2)
#define CIRCLE_RADIUS_MAX (255 * 32)
#define CIRCLE_RADIUS_MIN 256

static int circleZoom;
static int radius;

unsigned char *p0;
unsigned char *p1;
unsigned char *p2;
unsigned char *p3;
unsigned char *p4;
unsigned char *p5;

unsigned char *p0b;
unsigned char *p1b;
unsigned char *p2b;
unsigned char *p3b;
unsigned char *p4b;
unsigned char *p5b;

void writeMask(unsigned char *bit) {

    unsigned char mask;

    mask = (bit[0] << 4) | (bit[1] << 5) | (bit[2] << 6) | (bit[3] << 7);

    *p0++ &= mask;
    *p0b-- &= mask;

    mask = (bit[4] << 7) | (bit[5] << 6) | (bit[6] << 5) | (bit[7] << 4) | (bit[8] << 3) |
           (bit[9] << 2) | (bit[10] << 1) | (bit[11]);

    *p1++ &= mask;
    *p1b-- &= mask;

    mask = (bit[12]) | (bit[13] << 1) | (bit[14] << 2) | (bit[15] << 3) | (bit[16] << 4) |
           (bit[17] << 5) | (bit[18] << 6) | (bit[19] << 7);

    *p2++ &= mask;
    *p2b-- &= mask;

    mask = (bit[20 + 0] << 4) | (bit[20 + 1] << 5) | (bit[20 + 2] << 6) | (bit[20 + 3] << 7);

    *p3++ &= mask;
    *p3b-- &= mask;

    mask = (bit[20 + 4] << 7) | (bit[20 + 5] << 6) | (bit[20 + 6] << 5) | (bit[20 + 7] << 4) |
           (bit[20 + 8] << 3) | (bit[20 + 9] << 2) | (bit[20 + 10] << 1) | (bit[20 + 11]);

    *p4++ &= mask;
    *p4b-- &= mask;

    mask = (bit[20 + 12]) | (bit[20 + 13] << 1) | (bit[20 + 14] << 2) | (bit[20 + 15] << 3) |
           (bit[20 + 16] << 4) | (bit[20 + 17] << 5) | (bit[20 + 18] << 6) | (bit[20 + 19] << 7);

    *p5++ &= mask;
    *p5b-- &= mask;
}

void drawCircle(int leftX, int rightX, int r2) {

    unsigned char bit[40];
    for (int i = 0; i < 40; i++)
        bit[i] = 0;

    p0 = RAM + _BUF_PF0_LEFT;
    p1 = RAM + _BUF_PF1_LEFT;
    p2 = RAM + _BUF_PF2_LEFT;
    p3 = RAM + _BUF_PF0_RIGHT;
    p4 = RAM + _BUF_PF1_RIGHT;
    p5 = RAM + _BUF_PF2_RIGHT;

    p0b = RAM + _BUF_PF0_LEFT + _ARENA_SCANLINES - 1;
    p1b = RAM + _BUF_PF1_LEFT + _ARENA_SCANLINES - 1;
    p2b = RAM + _BUF_PF2_LEFT + _ARENA_SCANLINES - 1;
    p3b = RAM + _BUF_PF0_RIGHT + _ARENA_SCANLINES - 1;
    p4b = RAM + _BUF_PF1_RIGHT + _ARENA_SCANLINES - 1;
    p5b = RAM + _BUF_PF2_RIGHT + _ARENA_SCANLINES - 1;

    for (int y = 0; y < CIRCLE_CENTER_Y; y++) {

        int distance = (CIRCLE_CENTER_X - leftX) * 7 * (CIRCLE_CENTER_X - leftX) * 7 +
                       ((CIRCLE_CENTER_Y - y)) * ((CIRCLE_CENTER_Y - y));

        while (distance < r2 && leftX >= 0) {
            bit[leftX--] = bit[rightX++] = 1;
            distance += 49;
        }

        writeMask(bit);
    }
}

bool checkSwipeFinished() { return (radius > CIRCLE_RADIUS_MAX || !radius); }

void initSwipeCircle(int zoom) {

    // ADDAUDIO(SFX_WHOOSH);
    circleZoom = zoom;
    radius = zoom < CIRCLE_ZOOM_ZERO ? CIRCLE_RADIUS_MAX : CIRCLE_RADIUS_MIN;
}

void swipeCircle() {

    if (!checkSwipeFinished()) {
        //        displayMode = DISPLAY_NORMAL;
        drawCircle(CIRCLE_CENTER_X, CIRCLE_CENTER_X, (radius >> 5) * (radius >> 5));

        //        if (!roller)
        radius = radius + 128; //(radius * circleZoom) >> CIRCLE_RESOLUTION;
    }
}

bool checkInCircle(int x, int y) {

    int rad = (x - (CIRCLE_CENTER_X)) * (x - (CIRCLE_CENTER_X)) * 12 +
              (y - CIRCLE_CENTER_Y) * (y - CIRCLE_CENTER_Y);

    return rad < (((radius >> 5) * (radius >> 5)) * 4) >> 4;
}

#endif

// EOF
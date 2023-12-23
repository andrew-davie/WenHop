#include "defines_cdfj.h"

#include "main.h"
#include "wyrm.h"

#include "attribute.h"
#include "colour.h"
#include "particle.h"
#include "random.h"

const unsigned char wyrmChar[] = {

    0,                 // 0
    CH_WYRM_VERT_BODY, // 1   U
    CH_WYRM_BODY,      // 2   R
    CH_WYRM_CORNER_RU, // 3   RU
    CH_WYRM_VERT_BODY, // 4   D
    CH_WYRM_VERT_BODY, // 5   UD
    CH_WYRM_CORNER_RD, // 6   RD
    0,                 // 7
    CH_WYRM_BODY,      // 8   L
    CH_WYRM_CORNER_LU, // 9   LU
    CH_WYRM_BODY,      // 10  LR
    0,                 // 11
    CH_WYRM_CORNER_LD, // 12  LD
    0,                 // 13
    0,                 // 14
    0,                 // 15
};

struct wyrmDetails wyrms[WYRM_POP];

void initWyrms() {
    for (int i = 0; i < WYRM_POP; i++)
        wyrms[i].head = -1;
}

void newWyrm(int x, int y) {

    for (int i = 0; i < WYRM_POP; i++) {
        if (wyrms[i].head < 0) {
            struct wyrmDetails *thisWyrm = &wyrms[i];

            thisWyrm->head = 0;
            thisWyrm->dir = getRandom32() & 3;
            thisWyrm->x[0] = x;
            thisWyrm->y[0] = y;
            thisWyrm->length = 2;

            break;
        }
    }
}

void processWyrms() {

    for (int i = gameFrame & 1; i < WYRM_POP; i += 2) {
        // for (int i = 0; i < WYRM_POP; i++) {

        // if (rangeRandom(110))
        //     continue;

        struct wyrmDetails *wyrm = &wyrms[i];

        int headPos = wyrm->head;
        if (headPos < 0)
            continue;

        bool belowSurface = (wyrm->y[0] * TRILINES > lavaSurfaceTrixel);

        int x = wyrm->x[headPos];
        int y = wyrm->y[headPos];

        int candidateX = x + xdir[wyrm->dir];
        int candidateY = y + ydir[wyrm->dir];

        unsigned char *newHead = RAM + _BOARD + candidateY * 40 + candidateX;

        int mask = ATT_BLANK | ATT_GRAB;
        int whatsThere = CharToType[GET(*newHead)];
        int moveable = Attribute[whatsThere] & mask;

        if (!moveable || !(getRandom32() & 3)) {

            int rdir = getRandom32() & 3;

            for (int dir = 0; dir < 4; dir++) {

                candidateX = x + xdir[rdir];
                candidateY = y + ydir[rdir];

                newHead = RAM + _BOARD + candidateY * 40 + candidateX;
                whatsThere = CharToType[GET(*newHead)];
                if (Attribute[whatsThere] & mask) {
                    wyrm->dir = rdir;
                    moveable = true;
                    break;
                }

                rdir = (rdir + 1) & 3;
            }
        }

        bool candidateBelowSurface = (candidateY * TRILINES > lavaSurfaceTrixel);
        if (!candidateBelowSurface && candidateBelowSurface != belowSurface)
            moveable = false;

        if (!moveable) {

            if (wyrm->head > 2 /* && (gameFrame & 1)*/) {

                unsigned char *segment = RAM + _BOARD + wyrm->y[0] * 40 + wyrm->x[0];
                *segment = CH_DUST_ROCK_0;

                for (int i = 0; i < WYRM_MAX - 1; i++) {
                    wyrm->x[i] = wyrm->x[i + 1];
                    wyrm->y[i] = wyrm->y[i + 1];
                }
                wyrm->head--;
                wyrm->length--;
            }

            // if (!rangeRandom(5)) {
            //  reverse wyrm

            unsigned char tempX2[WYRM_MAX], tempY2[WYRM_MAX];
            for (int i = 0; i <= wyrm->head; i++) {
                tempX2[i] = wyrm->x[i];
                tempY2[i] = wyrm->y[i];
            }

            for (int i = 0; i <= wyrm->head; i++) {
                wyrm->x[i] = tempX2[wyrm->head - i];
                wyrm->y[i] = tempY2[wyrm->head - i];
            }

            wyrm->dir = (wyrm->dir + 2) & 3;
            //}
        }

        else {

            unsigned char *segment;
            if (headPos > 0) {
                int dir =
                    dirFromCoords(candidateX, candidateY, wyrm->x[headPos], wyrm->y[headPos]) |

                    dirFromCoords(wyrm->x[headPos - 1], wyrm->y[headPos - 1], wyrm->x[headPos],
                                  wyrm->y[headPos]);

                segment = RAM + _BOARD + wyrm->y[headPos] * _1ROW + wyrm->x[headPos];
                *segment = wyrmChar[dir];
            }

            if (headPos >= wyrm->length) {

                if (true /*tmp*/ || !(Attribute[whatsThere] & (ATT_WATERFLOW | ATT_GRAB)) ||
                    wyrm->length > WYRM_MAX - 2) {
                    unsigned char *tailPos = RAM + _BOARD + wyrm->y[0] * _1ROW + wyrm->x[0];

                    *tailPos = CH_DUST_ROCK_0;

                    for (int i = 0; i < WYRM_MAX - 1; i++) {
                        wyrm->x[i] = wyrm->x[i + 1];
                        wyrm->y[i] = wyrm->y[i + 1];
                    }

                    headPos--;
                }

                else {
                    wyrm->length++;
                }

                if (wyrm->y[0] * TRILINES > lavaSurfaceTrixel) {
                    if (!rangeRandom(500)) {
                        newWyrm(wyrm->x[0], wyrm->y[0]);
                    }
                }
            }

            wyrm->x[++headPos] = candidateX;
            wyrm->y[headPos] = candidateY;

            wyrm->head = headPos;

            segment = RAM + _BOARD + candidateY * 40 + candidateX;

            if (TYPEOF(*segment) == TYPE_DOGE)
                nDots(8, candidateX, candidateY, PT_TWO, 50, 3, 0, 100);

            *segment = wyrm->dir + CH_WYRM_HEAD_U;
        }

        if (headPos) {
            unsigned char *tailPos = RAM + _BOARD + wyrm->y[0] * _1ROW + wyrm->x[0];

            unsigned char tail = CH_WYRM_TAIL_R;
            if (wyrm->y[1] > wyrm->y[0])
                tail = CH_WYRM_TAIL_U;

            else if (wyrm->y[1] < wyrm->y[0])
                tail = CH_WYRM_TAIL_D;

            else if (wyrm->x[1] > wyrm->x[0])
                tail = CH_WYRM_TAIL_L;
            // else
            //     tail = CH_WYRM_TAIL_R;

            *tailPos = tail;

            unsigned char headChar = CH_WYRM_HEAD_U;
            if (wyrm->x[headPos] < wyrm->x[headPos - 1])
                headChar = CH_WYRM_HEAD_L;
            else if (wyrm->x[headPos] > wyrm->x[headPos - 1])
                headChar = CH_WYRM_HEAD_R;
            else if (wyrm->y[headPos] > wyrm->y[headPos - 1])
                headChar = CH_WYRM_HEAD_D;

            unsigned char *head = RAM + _BOARD + wyrm->y[headPos] * _1ROW + wyrm->x[headPos];
            *head = headChar;
        }

        nDots(4, wyrm->x[0], wyrm->y[0], PT_SPIRAL, 30, 2, 5, 100);
    }
}

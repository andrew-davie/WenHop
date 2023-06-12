#include "cavedata.h"
#include "attribute.h"
#include "main.h"

// clang-format off

// #define LINE 0b01000000
// #define FILLRECT 0b10000000
// #define RECT 0b11000000

#define DIRT CH_DIRT
#define STEEL CH_STEELWALL

// #define XY(x,y) (x),(y)
// #define CAVEHEADER(milling, doge, dollar, rain) (milling), (doge), (dollar), (rain)

#define R 2
// #define L 6
//  #define U 0
//  #define D 4

#define LINER(char, x, y, length, direction) 0x40 + char, x, y, direction, length,

// #define RECTR(char, fill, x, y, width, height) 0x80 + char, x, y, width, height, fill,
// #define RECTE(char, x, y, width, height) 0xC0 + char, x, y, width, height,

// #define LINE_N 0
// #define LINE_NE 1
// #define LINE_E 2
// #define LINE_SE 3
// #define LINE_S 4
// #define LINE_SW 5
// #define LINE_W 6
// #define LINE_NW 7

// #define DRAW_LINE(character, x, y, length, direction) (LINE + (character)), (x), (y),
// (direction), (length) #define SIZE(x, y) (x), (y) #define DRAW_SOLID_RECTANGLE(character, x, y,
// width, height, interior) (FILLRECT + (character)), (x), (y), (width), (height), (interior)

// #define UP 0
// #define UPRIGHT 1
//  #define RIGHT 2
// #define DOWNRIGHT 3
//  #define DOWN 4
// #define DOWNLEFT 5
//  #define LEFT 6
// #define UPLEFT 7

const unsigned char caveA[] = {

    20,     // milling
    10, 15, // doge $
    5,      //              ,          // rain

    10, 11, 50, 56, 8, // randomiser[level]
    25, 12, 12, 12, 12, 200, 200, 200, 200, 200,
    // 70,65,60,55,50,

    CAVEDEF_PARALLAX, STEEL, DIRT,

    4,
    CH_BLANK, 60, 255, 0, 255, 10,
    CH_PEBBLE1, 150, 0, 240, 0, 20,
    CH_PEBBLE2, 150, 0, 240, 0, 20,
    CH_ROCK, 10, 0, 240, 0, 20,

    0xFE, CH_FLIP_GRAVITY_0, 16, 8,
    0xFE, CH_FLIP_GRAVITY_0, 8, 12,


    // CH_FLIP_GRAVITY_0,   100, 10, 10, 10, 10,
    // CH_GEODOGE, 80, 80, 80, 80, 80,
    //        CH_WYRM_HEAD_U, 50, 60, 70, 80, 90,

    // CH_PUSH_LEFT,    0,  10,   5,   0,  20,
    // CH_PUSH_RIGHT,   0,  10,   5,   0,  20,
    // CH_PUSH_UP,      0,  10,   5,   0,  20,
    // CH_PUSH_DOWN,    0,  10,   5,   0,  20,

    // CH_DOGE_00, 4, 2,

    // LINE + CH_LADDER_0, 4,2,4,10,

    // FILLRECT+CH_ROCK,5,5,21,10,CH_DIRT,

    // #define VS 3
    // #define HS 3

    //     0xFE,CH_PUSH_DOWN,6,9,
    // //    0xFE,CH_PUSH_DOWN,7,1,
    //     0xFE,CH_PUSH_RIGHT,7,8,
    //   //  0xFE,CH_PUSH_DOWN,9,1,
    //     0xFE,CH_PUSH_LEFT,5,8,
    //     //0xFE,CH_PUSH_DOWN,11,1,
    //     0xFE,CH_PUSH_UP,6,7,
    //     //0xFE,CH_PUSH_DOWN,13,1,
    //     0xFE, CH_HUB, 6,8,

    //     0xFE,CH_PUSH_DOWN,6+HS,9+VS,
    // //    0xFE,CH_PUSH_DOWN,7,1,
    //     0xFE,CH_PUSH_RIGHT,7+HS,8+VS,
    //   //  0xFE,CH_PUSH_DOWN,9,1,
    //     0xFE,CH_PUSH_LEFT,5+HS,8+VS,
    //     //0xFE,CH_PUSH_DOWN,11,1,
    //     0xFE,CH_PUSH_UP,6+HS,7+VS,
    //     //0xFE,CH_PUSH_DOWN,13,1,
    //     0xFE, CH_HUB, 6+HS,8+VS,

    //     0xFE,CH_PUSH_DOWN,6+HS*3,9+VS*2,
    // //    0xFE,CH_PUSH_DOWN,7,1,
    //     0xFE,CH_PUSH_RIGHT,7+HS*3,8+VS*2,
    //   //  0xFE,CH_PUSH_DOWN,9,1,
    //     0xFE,CH_PUSH_LEFT,5+HS*3,8+VS*2,
    //     //0xFE,CH_PUSH_DOWN,11,1,
    //     0xFE,CH_PUSH_UP,6+HS*3,7+VS*2,
    //     //0xFE,CH_PUSH_DOWN,13,1,
    //     0xFE, CH_HUB, 6+HS*3,8+VS*2,

    //     0xFE, CH_HUB, 1,4+VS*2,
    //     0xFE, CH_HUB, 2,4+VS*2,
    //     0xFE, CH_HUB, 3,4+VS*2,
    //     0xFE, CH_HUB, 1,5+VS*2,
    // //    0xFE, CH_HUB, 2+HS*3,5+VS*2,
    //     0xFE, CH_HUB, 3,5+VS*2,
    //     0xFE, CH_HUB, 1,6+VS*2,
    //     0xFE, CH_HUB, 2,6+VS*2,
    //     0xFE, CH_HUB, 3,6+VS*2,

       0xFE, CH_WYRM_HEAD_U, 3, 6,

    // LINE + CH_BRICKWALL,1,7,2,31,
    // LINE + CH_BRICKWALL,8,14,2,31,

    // LINE+CH_BLANK,30,1,4,6,

    // LINE+CH_BLANK,10,1,4,6,

    // LINE+CH_BLANK,5,8,4,7,

    // LINE+CH_BLANK,30,15,4,5,

    0xFE, CH_DOORCLOSED, 38, 16, 0xFE, CH_MELLON_HUSK_BIRTH, 2, 9,

    // 0xFE, CH_GRINDER_0, 4, 9,
    // 0xFE, CH_GRINDER_0, 5, 8,
    // 0xFE, CH_GRINDER_0, 6, 6,
    // 0xFE, CH_GRINDER_0, 7, 6,
    // 0xFE, CH_GRINDER_0, 8, 5,

    // 0xFE, CH_GRINDER_0, 8, 9,
    // 0xFE, CH_GRINDER_1, 9, 9,
    // 0xFE, CH_GRINDER_0, 9, 8,
    // 0xFE, CH_GRINDER_1, 10, 8,
    // 0xFE, CH_GRINDER_0, 10, 7,

    // 0xFE, CH_GRINDER_1, 11, 12,
    // 0xFE, CH_BELT_0, 12, 12,
    // 0xFE, CH_BELT_1, 13, 12,
    // 0xFE, CH_GRINDER_1, 14, 12,
    // 0xFE, CH_BELT_1, 15, 12,
    // 0xFE, CH_BELT_0, 16, 12,
    // 0xFE, CH_GRINDER_1, 17, 12,
    // 0xFE, CH_BELT_1, 18, 12,
    // 0xFE, CH_BELT_0, 19, 12,
    // 0xFE, CH_GRINDER_1, 20, 12,

    // 0xFE, CH_HUB_1, 20, 8,
    //  0xFE, CH_PUSH_DOWN, 20, 9,

    // 0xFE, CH_GRINDER_0, 15, 15,
    // 0xFE, CH_BELT_0, 16, 15,
    // 0xFE, CH_BELT_1, 17, 15,
    // 0xFE, CH_BELT_0, 18, 15,
    // 0xFE, CH_BELT_1, 19, 15,
    // 0xFE, CH_BELT_0, 20, 15,
    // 0xFE, CH_BELT_1, 21, 15,
    // 0xFE, CH_GRINDER_0, 22, 15,

    // 0xFE, CH_HORIZONTAL_BAR, 1, 13,
    // 0xFE, CH_HORIZONTAL_BAR, 2, 13,
    // 0xFE, CH_HORIZONTAL_BAR, 3, 13,
    // 0xFE, CH_TAP_0, 4, 12,
    // 0xFE, CH_HUB_1, 4, 13,
    // 0xFE, CH_OUTLET, 4, 14,

    // 0xFE, CH_WATERFLOW_0, 4, 12,
    // 0xFE, CH_WATERFLOW_0, 4, 13,
    // 0xFE, CH_WATERFLOW_0, 4, 14,
    // 0xFE, CH_WATERFLOW_0, 4, 15,
    // 0xFE, CH_WATERFLOW_0, 4, 16,
    // 0xFE, CH_WATERFLOW_0, 4, 17,
    // 0xFE, CH_WATERFLOW_0, 4, 18,
    // 0xFE, CH_WATERFLOW_0, 4, 19,

    // 0xFE, CH_HORIZ_ZAP_3, 3,7,
    // 0xFE, CH_HORIZ_ZAP_3, 3,8,
    // 0xFE, CH_HORIZ_ZAP_3, 3,9,

    // LINER(CH_LAVA_0, 1,20,10,R)

    //    0xFE, CH_WATER_0, 1, 20,

    0xFE, CH_LAVA_0, 1, 20,

    // 0xFE, CH_BRICKWALL, 20,10,
    // 0xFE, CH_BRICKWALL, 21,10,
    // 0xFE, CH_BRICKWALL, 22,10,
    // 0xFE, CH_BRICKWALL, 23,10,
    // 0xFE, CH_BRICKWALL, 24,10,
    // 0xFE, CH_BRICKWALL, 25,10,
    // 0xFE, CH_BRICKWALL, 26,10,
    // 0xFE, CH_BRICKWALL, 27,10,
    // 0xFE, CH_BRICKWALL, 28,10,
    // 0xFE, CH_BRICKWALL, 29,10,
    // 0xFE, CH_BRICKWALL, 30,10,

    // 0xFE, CH_SWITCH_LEFT_OFF, 1, 19,

    // 0xFE, CH_WYRM_BODY, 6, 4,
    //    0xFE, CH_WYRM_BODY, 16, 10,

    // 0xFE, CH_WYRM_BODY, 12, 2,
    // 0xFE, CH_WYRM_BODY, 16, 14,
    // 0xFE, CH_WYRM_BODY, 16, 18,
    // 0xFE, CH_WYRM_BODY, 11, 12,
    // 0xFE, CH_WYRM_BODY, 16, 4,
    // 0xFE, CH_WYRM_BODY, 16, 8,
    // 0xFE, CH_WYRM_BODY, 12, 12,
    // 0xFE, CH_WYRM_BODY, 2, 12,

    0xFF,

    // EXTRAS
    // LEVEL 0
    0xFF, // LEVEL 1
    0xFF, // LEVEL 2
    0xFF, // LEVEL 3
    0xFF, // LEVEL 4
    0xFF,

    'M', 'E', 'R', 'C', 'U', 'R', 'Y', END_STRING};

const unsigned char caveA2[] = {

    20,     // milling
    10, 15, // doge $
    5,      //              ,          // rain

    10, 11, 50, 56, 8, // randomiser[level]
    25, 12, 12, 12, 12, 200, 200, 200, 200, 200,
    // 70,65,60,55,50,

    CAVEDEF_PARALLAX, STEEL, CH_BLANK,

    4, CH_PUSH_LEFT, 0, 10, 5, 0, 20, CH_PUSH_RIGHT, 0, 10, 5, 0, 20, CH_PUSH_UP, 0, 10, 5, 0, 20,
    CH_PUSH_DOWN, 0, 10, 5, 0, 20,
    //   CH_BLANK,       60, 255,   0, 255,  10,
    //     CH_ROCK,     90,   0, 240,   0,  20,

    0x80 + CH_STEELWALL, 10, 5, 20, 12, CH_DIRT,

    //    0xFE, CH_DOORCLOSED,38,16,
    0xFE, CH_MELLON_HUSK_BIRTH, 16, 6,

    0xFE, CH_WYRM_HEAD_U, 11, 6, 0xFE, CH_WYRM_HEAD_U, 12, 6, 0xFE, CH_WYRM_HEAD_U, 13, 6, 0xFE,
    CH_WYRM_HEAD_U, 14, 6, 0xFE, CH_WYRM_HEAD_U, 15, 6,

    // 0xFE, CH_WYRM_HEAD_U, 11, 9,
    // 0xFE, CH_WYRM_HEAD_U, 12, 9,
    // 0xFE, CH_WYRM_HEAD_U, 13, 9,
    // 0xFE, CH_WYRM_HEAD_U, 14, 9,
    // 0xFE, CH_WYRM_HEAD_U, 15, 9,

    0xFF,

    // EXTRAS
    // LEVEL 0
    0xFF, // LEVEL 1
    0xFF, // LEVEL 2
    0xFF, // LEVEL 3
    0xFF, // LEVEL 4
    0xFF,

    'M', 'E', 'R', 'C', 'U', 'R', 'Y', END_STRING};

const unsigned char caveA3[] = {

    20,    // milling
    1, 15, // doge $
    5,     //              ,          // rain

    10, 11, 50, 56, 8, // randomiser[level]
    8, 8, 8, 8, 8, 20, 200, 200, 200, 200,
    // 70,65,60,55,50,

    CAVEDEF_PARALLAX, STEEL, CH_BLANK,

    0,

    0x80 + CH_STEELWALL, 10, 5, 20, 5, CH_BLANK,

    //    LINER(CH_HORIZ_ZAP_0, 13,7,10,R)
    LINER(CH_DOGE_00, 13, 8, 9, R)
    //    0xFE, CH_FLIP_GRAVITY_0, 16,6,
    // 0xFE, CH_FLIP_GRAVITY_0, 22,8,
    // 0xFE, CH_FLIP_GRAVITY_0, 11,8,
    0xFE,
    CH_DOGE_00, 16, 8, 0xFE, CH_ROCK, 1, 6, 0xFE, CH_STEELWALL, 12, 7,

    // 0xFE, CH_FLIP_GRAVITY_0, 16,6,
    //    0xFE, CH_FLIP_GRAVITY_0, 16,6,
    //    0xFE, CH_FLIP_GRAVITY_0, 17,8,
    //  0xFE, CH_FLIP_GRAVITY_0, 12,6,

    // 0xFE, CH_STEELWALL, 16,7,
    0xFE, CH_DOORCLOSED, 16, 5, 0xFE, CH_BLOCK, 16, 6, 0xFE, CH_BLOCK, 16, 7, 0xFE, CH_ROCK, 16, 9,

    0xFE, CH_ROCK, 16, 9, 0xFE, CH_ROCK, 16, 10, 0xFE, CH_ROCK, 16, 11, 0xFE, CH_ROCK, 16, 12, 0xFE,
    CH_ROCK, 16, 13, 0xFE, CH_ROCK, 16, 14, 0xFE, CH_ROCK, 16, 15, 0xFE, CH_ROCK, 16, 16, 0xFE,
    CH_ROCK, 16, 17, 0xFE, CH_ROCK, 16, 18,
    // 0xFE, CH_DOGE_00, 16,18,
    0xFE, CH_FLIP_GRAVITY_0, 16, 18, 0xFE, CH_FLIP_GRAVITY_0, 16, 19, 0xFE, CH_BLOCK, 16, 20,

    //    0xFE, CH_ROCK, 16,9,
    0xFE, CH_FLIP_GRAVITY_0, 16, 8,

    // LINER(CH_PUSH_DOWN,11,6,18,R)
    // LINER(CH_PUSH_UP,11,11,18,R)
    /*
        0xFE, CH_PUSH_DOWN, 11, 6,
    //    0xFE, CH_PUSH_DOWN, 13, 6,
        0xFE, CH_PUSH_DOWN, 15, 6,
    //    0xFE, CH_PUSH_DOWN, 17, 6,
        0xFE, CH_PUSH_DOWN, 19, 6,
    //    0xFE, CH_PUSH_DOWN, 21, 6,
        0xFE, CH_PUSH_DOWN, 23, 6,
    //    0xFE, CH_PUSH_DOWN, 25, 6,


        0xFE, CH_PUSH_UP, 11, 12,
    //    0xFE, CH_PUSH_UP, 13, 12,
        0xFE, CH_PUSH_UP, 15, 12,
    //    0xFE, CH_PUSH_UP, 17, 12,
        0xFE, CH_PUSH_UP, 19, 12,
    //    0xFE, CH_PUSH_UP, 21, 12,
        0xFE, CH_PUSH_UP, 23, 12,
    //    0xFE, CH_PUSH_UP, 25, 12,
    */

    //    0xFE, CH_DOORCLOSED,38,16,
    0xFE, CH_MELLON_HUSK_BIRTH, 11, 7,
    // 0xFE, CH_PACMAN_DOT, 11, 8,

    //    0xFE, CH_WYRM_HEAD_U, 16, 9,

    // 0xFE, CH_WYRM_HEAD_U, 11, 9,
    // 0xFE, CH_WYRM_HEAD_U, 12, 9,
    // 0xFE, CH_WYRM_HEAD_U, 13, 9,
    // 0xFE, CH_WYRM_HEAD_U, 14, 9,
    // 0xFE, CH_WYRM_HEAD_U, 15, 9,

    0xFF,

    // EXTRAS
    // LEVEL 0
    0xFF, // LEVEL 1
    0xFF, // LEVEL 2
    0xFF, // LEVEL 3
    0xFF, // LEVEL 4
    0xFF,

    'M', 'E', 'R', 'C', 'U', 'R', 'Y', END_STRING};

const unsigned char caveA4[] = {

    20,    // milling
    1, 15, // doge $
    5,     //              ,          // rain

    10, 11, 50, 56, 8, // randomiser[level]
    17, 17, 17, 17, 17, 20, 200, 200, 200, 200,
    // 70,65,60,55,50,

    CAVEDEF_PARALLAX, STEEL, CH_BLANK,

    0,

    0x80 + CH_STEELWALL, 10, 5, 20, 5, CH_DIRT,

    //    LINER(CH_HORIZ_ZAP_0, 13,7,10,R)
    // LINER(CH_DOGE_00, 13,8,16,R)
    // LINER(CH_DOGE_00, 13,7,16,R)
    LINER(CH_DOGE_00, 13, 6, 16, R)
    //    0xFE, CH_FLIP_GRAVITY_0, 16,6,
    // 0xFE, CH_FLIP_GRAVITY_0, 22,8,
    // 0xFE, CH_FLIP_GRAVITY_0, 11,8,
    //    0xFE, CH_DOGE_00, 16,8,
    0xFE,
    CH_ROCK, 1, 6, 0xFE, CH_STEELWALL, 12, 6, 0xFE, CH_STEELWALL, 12, 7,

    0xFE, CH_STEELWALL, 14, 7, 0xFE, CH_STEELWALL, 14, 8,

    0xFE, CH_PEBBLE1, 13, 7,
    // 0xFE, CH_DIRT, 11,6,
    // 0xFE, CH_DIRT, 11,8,

    // 0xFE, CH_FLIP_GRAVITY_0, 16,6,
    //    0xFE, CH_FLIP_GRAVITY_0, 16,6,
    //    0xFE, CH_FLIP_GRAVITY_0, 17,8,
    //  0xFE, CH_FLIP_GRAVITY_0, 12,6,

    // 0xFE, CH_STEELWALL, 16,7,
    0xFE, CH_DOORCLOSED, 16, 5,
    // 0xFE, CH_BLOCK, 16,6,
    // 0xFE, CH_BLOCK, 16,7,
    // 0xFE, CH_ROCK, 16,9,

    0xFE, CH_MELLON_HUSK_BIRTH, 11, 6,

    0xFF,

    // EXTRAS
    // LEVEL 0
    0xFF, // LEVEL 1
    0xFF, // LEVEL 2
    0xFF, // LEVEL 3
    0xFF, // LEVEL 4
    0xFF,

    'M', 'E', 'R', 'C', 'U', 'R', 'Y', END_STRING};

const unsigned char *caveList[] = {

    caveA
    //, caveA4,

    //caveA3,
    // caveA2,
};

const unsigned int caveCount = sizeof(caveList) / sizeof(unsigned char *);

// clang-format on
// EOF

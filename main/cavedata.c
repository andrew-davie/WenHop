
#include "main.h"
#include "cavedata.h"
#include "attribute.h"


#define LINE 0b01000000
#define FILLRECT 0b10000000
#define RECT 0b11000000

#define DIRT        CH_DIRT
#define STEEL       CH_STEELWALL
#define BOULDER     CH_BOULDER
#define INBOX       CH_ROCKFORD_BIRTH


#define XY(x,y) (x),(y)
#define CAVEHEADER(milling, diamonds, dollar, rain) (milling), (diamonds), (dollar), (rain)

#define R 2
//#define L 6
#define U 0
#define D 4

#define LINER(char,x,y,length,direction) 0x40 + char, x, y, direction, length,
#define RECTR(char, fill, x, y, width, height) 0x80 + char, x, y, width, height, fill,
#define ROCKY(startx, starty, doorx, doory) CH_DOORCLOSED, doorx, doory, CH_ROCKFORD_BIRTH, startx, starty,
#define RECTE(char, x, y, width, height) 0xC0 + char, x, y, width, height,

// #define LINE_N 0
// #define LINE_NE 1
#define LINE_E 2
#define LINE_SE 3
// #define LINE_S 4
// #define LINE_SW 5
// #define LINE_W 6
// #define LINE_NW 7

#define DRAW_LINE(character, x, y, length, direction) (LINE + (character)), (x), (y), (direction), (length)
#define SIZE(x, y) (x), (y)
#define DRAW_SOLID_RECTANGLE(character, x, y, width, height, interior) (FILLRECT + (character)), (x), (y), (width), (height), (interior)



//#define UP 0
//#define UPRIGHT 1
#define RIGHT 2
//#define DOWNRIGHT 3
#define DOWN 4
//#define DOWNLEFT 5
// #define LEFT 6
//#define UPLEFT 7




const unsigned char caveA[]= {


    20,       // milling
    10,15,  // diamond $
    5, //              ,          // rain

    10,11,50,56,8,       // randomiser[level]
    25,12,12,12,12,
    200,200,200,200,200,
    //70,65,60,55,50,


    CAVEDEF_PARALLAX,
    STEEL,DIRT,

    4,  CH_BLANK,       60, 255,   0, 255,  10,
        CH_PEBBLE1,     50,   0, 240,   0,  20,
        CH_PEBBLE2,     50,   0, 240,   0,  20,
        CH_BOULDER,     10,   0, 240,   0,  20,

//        CH_WYRM_HEAD_U, 50, 60, 70, 80, 90,

        // CH_PUSH_LEFT,    0,  10,   5,   0,  20,
        // CH_PUSH_RIGHT,   0,  10,   5,   0,  20,
        // CH_PUSH_UP,      0,  10,   5,   0,  20,
        // CH_PUSH_DOWN,    0,  10,   5,   0,  20,

        // DIAMOND,    9,9,9,9,200,

    //CH_DOGE_00, 4, 2,

    //LINE + CH_LADDER_0, 4,2,4,10,


    //FILLRECT+CH_BOULDER,5,5,21,10,CH_DIRT,



#define VS 3
#define HS 3

    0xFE,CH_PUSH_DOWN,6,9,
//    0xFE,CH_PUSH_DOWN,7,1,
    0xFE,CH_PUSH_RIGHT,7,8,
  //  0xFE,CH_PUSH_DOWN,9,1,
    0xFE,CH_PUSH_LEFT,5,8,
    //0xFE,CH_PUSH_DOWN,11,1,
    0xFE,CH_PUSH_UP,6,7,
    //0xFE,CH_PUSH_DOWN,13,1,
    0xFE, CH_STEELWALL, 6,8,



    0xFE,CH_PUSH_DOWN,6+HS,9+VS,
//    0xFE,CH_PUSH_DOWN,7,1,
    0xFE,CH_PUSH_RIGHT,7+HS,8+VS,
  //  0xFE,CH_PUSH_DOWN,9,1,
    0xFE,CH_PUSH_LEFT,5+HS,8+VS,
    //0xFE,CH_PUSH_DOWN,11,1,
    0xFE,CH_PUSH_UP,6+HS,7+VS,
    //0xFE,CH_PUSH_DOWN,13,1,
    0xFE, CH_STEELWALL, 6+HS,8+VS,


    0xFE,CH_PUSH_DOWN,6+HS*3,9+VS*2,
//    0xFE,CH_PUSH_DOWN,7,1,
    0xFE,CH_PUSH_RIGHT,7+HS*3,8+VS*2,
  //  0xFE,CH_PUSH_DOWN,9,1,
    0xFE,CH_PUSH_LEFT,5+HS*3,8+VS*2,
    //0xFE,CH_PUSH_DOWN,11,1,
    0xFE,CH_PUSH_UP,6+HS*3,7+VS*2,
    //0xFE,CH_PUSH_DOWN,13,1,
    0xFE, CH_STEELWALL, 6+HS*3,8+VS*2,


//    0xFE, CH_WYRM_HEAD_U, 11, 16,


    //0xFE,CH_BUTTERFLY_0, 9,7,


    // LINE + CH_BRICKWALL,1,7,2,31,
    // LINE + CH_BRICKWALL,8,14,2,31,

    // LINE+CH_BLANK,30,1,4,6,
    // LINE+CH_BUTTERFLY_0,30,1,4,4,

    // LINE+CH_BLANK,10,1,4,6,
    // LINE+CH_FIREFLY_0,10,1,4,2,

    // LINE+CH_BLANK,5,8,4,7,
    // LINE+CH_BUTTERFLY_0,5,8,4,4,

    // LINE+CH_BLANK,30,15,4,5,
    // LINE+CH_BUTTERFLY_0,30,15,4,4,

    0xFE, CH_DOORCLOSED,38,16,
    0xFE, CH_ROCKFORD_BIRTH,3,10,

    LINER(CH_LAVA_0, 1,20,10,R)




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
    0xFF,   // LEVEL 1
    0xFF,   // LEVEL 2
    0xFF,   // LEVEL 3
    0xFF,   // LEVEL 4
    0xFF,

    'M','E','R','C','U','R','Y',END_STRING
};



const unsigned char caveA2[]= {


    20,       // milling
    10,15,  // diamond $
    5, //              ,          // rain

    10,11,50,56,8,       // randomiser[level]
    25,12,12,12,12,
    200,200,200,200,200,
    //70,65,60,55,50,


    CAVEDEF_PARALLAX,
    STEEL,CH_BLANK,

    4,
        CH_PUSH_LEFT,    0,  10,   5,   0,  20,
        CH_PUSH_RIGHT,   0,  10,   5,   0,  20,
        CH_PUSH_UP,      0,  10,   5,   0,  20,
        CH_PUSH_DOWN,    0,  10,   5,   0,  20,
    //   CH_BLANK,       60, 255,   0, 255,  10,
    //     CH_BOULDER,     90,   0, 240,   0,  20,

    0x80+ CH_STEELWALL,10,5,20,12,CH_DIRT,

//    0xFE, CH_DOORCLOSED,38,16,
    0xFE, CH_ROCKFORD_BIRTH,16,6,

    0xFE, CH_WYRM_HEAD_U, 11, 6,
    0xFE, CH_WYRM_HEAD_U, 12, 6,
    0xFE, CH_WYRM_HEAD_U, 13, 6,
    0xFE, CH_WYRM_HEAD_U, 14, 6,
    0xFE, CH_WYRM_HEAD_U, 15, 6,

    // 0xFE, CH_WYRM_HEAD_U, 11, 9,
    // 0xFE, CH_WYRM_HEAD_U, 12, 9,
    // 0xFE, CH_WYRM_HEAD_U, 13, 9,
    // 0xFE, CH_WYRM_HEAD_U, 14, 9,
    // 0xFE, CH_WYRM_HEAD_U, 15, 9,

    0xFF,

    // EXTRAS
            // LEVEL 0
    0xFF,   // LEVEL 1
    0xFF,   // LEVEL 2
    0xFF,   // LEVEL 3
    0xFF,   // LEVEL 4
    0xFF,

    'M','E','R','C','U','R','Y',END_STRING
};



const unsigned char caveA3[]= {


    20,       // milling
    10,15,  // diamond $
    5, //              ,          // rain

    10,11,50,56,8,       // randomiser[level]
    25,12,12,12,12,
    200,200,200,200,200,
    //70,65,60,55,50,


    CAVEDEF_PARALLAX,
    STEEL,CH_BLANK,

    0,


    0x80+ CH_STEELWALL,10,5,20,9,CH_DIRT,

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
    0xFE, CH_ROCKFORD_BIRTH,19,9,

//    0xFE, CH_WYRM_HEAD_U, 16, 9,


    // 0xFE, CH_WYRM_HEAD_U, 11, 9,
    // 0xFE, CH_WYRM_HEAD_U, 12, 9,
    // 0xFE, CH_WYRM_HEAD_U, 13, 9,
    // 0xFE, CH_WYRM_HEAD_U, 14, 9,
    // 0xFE, CH_WYRM_HEAD_U, 15, 9,

    0xFF,

    // EXTRAS
            // LEVEL 0
    0xFF,   // LEVEL 1
    0xFF,   // LEVEL 2
    0xFF,   // LEVEL 3
    0xFF,   // LEVEL 4
    0xFF,

    'M','E','R','C','U','R','Y',END_STRING
};





const unsigned char *caveList[] = {

    caveA,
    caveA3,
    caveA2,
};

const int caveCount = sizeof(caveList) / sizeof(unsigned char *);


//EOF
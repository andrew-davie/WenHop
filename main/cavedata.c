
#include "main.h"
#include "cavedata.h"
#include "attribute.h"


#define LINE 0b01000000
#define FILLRECT 0b10000000
#define RECT 0b11000000

#define DIRT        CH_DIRT
#define DIAMOND     CH_DOGE_00
//#define WALL        CH_BRICKWALL
// #define MAGIC       CH_MAGICWALL
#define STEEL       CH_STEELWALL
#define FIREFLY     CH_FIREFLY_0
#define BOULDER     CH_BOULDER
#define INBOX       CH_ROCKFORD_BIRTH
#define AMOEBA      CH_AMOEBA_0
#define BUTTERFLY   CH_BUTTERFLY_2


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





const unsigned char caveF[] = { //tetris

/*

▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓
▓●  ●●●●●●●●●●●●●●●●●●●●●●●●●●●●●●●●  ●▓
▓░  ░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░  ░▓
▓░  ░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░  ░▓
▓▓  ▒▒▒▓o●●▓▒▒▒▒▒▓o●●▓▒▒▒▒▒▓●o●▓▒▒▒▒  ▓▓
▓▓  ▒▒▒▓●●o▓▒▒▒▒▒▓●●o▓▒▒▒▒▒▓o●●▓▒▒▒▒  ▓▓
▓▓  ▒▒▒▓●●o▓▒▒▒▒▒▓●●o▓▒▒▒▒▒▓o●o▓▒▒▒▒  ▓▓
▓▓  ▒▒▒▓●oo▓▒▒▒▒▒▓●●●▓▒▒▒▒▒▓ooo▓▒▒▒▒  ▓▓
▓▓  ▒▒▒▓o●●▓▒▒▒▒▒▓●●o▓▒▒▒▒▒▓o●o▓▒▒▒▒  ▓▓
▓▓  ▒▒▒▓●●●▓▒▒▒▒▒▓o●o▓▒▒▒▒▒▓●o●▓▒▒▒▒  ▓▓
▓▓  ▒▒▒▓oo●▓▒▒▒▒▒▓o●●▓▒▒▒▒▒▓o●o▓▒▒▒▒  ▓▓
▓▓  ▒▒▒▓●●●▓▒▒▒▒▒▓o●●▓▒▒▒▒▒▓o●●▓▒▒▒▒  ▓▓
▓▓  ▒▒▒▓●o●▓▒▒▒▒▒▓●o●▓▒▒▒▒▒▓oo●▓▒▒▒▒  ▓▓
▓▓  ▒▒▒▓●o●▓▒▒▒▒▒▓ooo▓▒▒▒▒▒▓oo●▓▒▒▒▒  ▓▓
▓▓ R▒▒▒▓●●●▓▒▒▒▒▒▓●●●▓▒▒▒▒▒▓o●o▓▒▒▒▒  X▓
▓▓  ▓▓▓▓▓░▓▓▓▓▓▓▓▓▓░▓▓▓▓▓▓▓▓▓░▓▓▓▓▓▓  ▓▓
▓                                      ▓
▓                                      ▓
▓                                      ▓
▓                                      ▓
▓                                      ▓
▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓


*/

    CAVEHEADER(30,3,10,0),

    100,137,140,251,51,             // randomiser[level]
    75,80,85,90,95,                 // diamonds[level]
    200, 190, 180, 170, 160,        // time[level]

    CAVEDEF_PARALLAX,
    STEEL,DIRT,                     // wall/fill

    // RandomFill

    2,  CH_BOULDER,     254,254,254,254,254,
        CH_AMOEBA_0,    127,127,127,127,127,

    //FillRect=1 16 38 20 SPACE
    FILLRECT+CH_BLANK,1,+16,38,5,CH_BLANK,


    //Line=1 15 30 15 STEELWALL
    LINE+CH_STEELWALL,8,+15,RIGHT, 23,

    //FillRect=1 0 7 15 STEELWALL
    FILLRECT+CH_STEELWALL,1,0, 7,16, CH_STEELWALL,

    //FillRect=11 0 17 15 STEELWALL
    FILLRECT+CH_STEELWALL,11,0, 7,16, CH_STEELWALL,

    //FillRect=21 0 27 15 STEELWALL
    FILLRECT+CH_STEELWALL,21,0,7,16,CH_STEELWALL,

    //FillRect=31 0 38 15 STEELWALL
    FILLRECT+CH_STEELWALL,31,0,8,16,CH_STEELWALL,

    CH_BOULDER, XY(9, 14),
    CH_BOULDER, XY(19, 14),
    CH_BOULDER, XY(29, 14),

    CH_DIRT, XY(9, 15),
    CH_DIRT, XY(19, 15),
    CH_DIRT, XY(29, 15),



    // LINE+BOULDER,9,OFF+14,1,RIGHT,
    // LINE+BOULDER,19,OFF+14,1,RIGHT,
    // LINE+BOULDER,29,OFF+14,1,RIGHT,

    // LINE+DIRT,9,OFF+15,1,RIGHT,
    // LINE+DIRT,19,OFF+15,1,RIGHT,
    // LINE+DIRT,29,OFF+15,1,RIGHT,


    //Line=1 1 38 1 BOULDER
    LINE+CH_BOULDER,1,+1,RIGHT,38,

    RECT+CH_DIRT,1,+2,38,2,
    //Line=1 2 38 2 DIRT
    //LINE+DIRT,1,OFF+2,38,RIGHT,

    //Line=1 3 38 3 DIRT
    //LINE+DIRT,1,OFF+3,38,RIGHT,

    //Rectangle=2 1 3 15 SPACE
    RECT+CH_BLANK,2,+1,2,15,

    //Rectangle=36 1 37 15 SPACE
    RECT+CH_BLANK,36,+1,2,15,


    CH_DOORCLOSED,38,14,
    CH_ROCKFORD_BIRTH,3,14,


    0xFF,


    // EXTRAS
            // LEVEL 0
    0xFF,   // LEVEL 1
    0xFF,   // LEVEL 2
    0xFF,   // LEVEL 3
    0xFF,   // LEVEL 4
    0xFF,

    // 'T','I','M','E',' ','O','U','T',0xFF,
    // 'F','O','R',0xFF,
    'S','E','R','I','O','U','S',NEW_LINE,
    'F','U','N',END_STRING

};




const unsigned char caveE[] = {

/*

▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓
▓R░░●░●░░░░░░●░●░░●░░●●░●░●░●●░░░●░●░●░▓
▓●●●░░░░●░░░░░░░░░●░░●░░░●░░░●●●░░●●░░░▓
▓●░░░░░░░░░░░░░●░●░░░░░░░░░░░░░░░●●░░░░▓
▓░●░░░░●░●░░░░░●░●●░●░░░░░░░░●░●░●░░░░░▓
▓░●░░●░BBBBBBBBBBBBBBBBBBBBBBBBBBBBBB░░▓
▓░●●●░░BBBBBBBBBBBBBBBBBBBBBBBBBBBBBB░░▓
▓░░░░●░BBBBBBBBBBBBBBBBBBBBBBBBBBBBBB░●▓
▓░●░░░░BBBBBBBBBBBBBBBBBBBBBBBBBBBBBB░░▓
▓░░░░░░BBBBBBBBBBBBBBBBBBBBBBBBBBBBBB░░▓
▓●░●●░░BBBBBBBBBBBBBBBBBBBBBBBBBBBBBB░░▓
▓░░░░░░●░░░░░●░░●●●░░●░░●●░●●░░░░░░●░░●▓
▓░░░●░░░░●░░░●●░●░░░░●░░●●●░░●░●░●░░░░●▓
▓░●░░●░░░░░●●░░░●●░░●●░●░░░●░●░●░░░░░░░▓
▓░░░░░░░░░░░░░░●●●░░░░░░●░░░●░░●░░░●░●░▓
▓░●░░●░░░●●●░░░░░●░●░░░░░░░░●░░░░░░░░░░▓
▓░●░●░●░░●░●●░●●░░░●░░░░●░●●●●░░░●●●●░░▓
▓░●░░●░●░●●░░●●░░░░░░░░●░░░░░●░░░░●░░●●▓
▓░░●░░●●░░░●░●●░░●●░░░●░░░●░░░●░●●░░░░░▓
▓●░░░░░●░░●●░●●░░●░░░░░░●░●░░●░░●░░░░░●▓
▓░░●░░░░░░░░░░●░●░●●●░░░░░░●░░░●●░░●░░X▓
▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓

*/



    //4,       // cave
    20,       // milling
    5,20,    // diamond $
    4,          // rain

//  LEVEL
//    0    1    2    3    4

      20,   201,   120,   220,   22,        // randomiser[level]
     75,  80,  85,  90,  95,        // diamonds needed
     50,  50,  50,  50,  50,        // cave time


    CAVEDEF_PARALLAX,
    STEEL,DIRT,

    3,  CH_BOULDER, 50,60,70,80,90,
        CH_BLANK,   20,20,20,20,20,
        DIAMOND,    30,25,20,15,10,



    // LINE + CH_BRICKWALL,13,1,4,15,
    // LINE + CH_BRICKWALL,26,20,0,15,

    // CH_DOORCLOSED,38,16,
    // CH_ROCKFORD_BIRTH,3,2,

    // 0xFF,



    // CAVEDEF_PARALLAX,
    // STEEL,DIAMOND,

    // CH_BOULDER,0,0x0,0x0,        // random objects
    // 76,0,0,0x0,        // probability
    // 76,0,0,0x0,        // probability
    // 76,0,0,0x0,        // probability
    // 76,0,0,0x0,        // probability
    // 76,0,0,0x0,        // probability


    0x80+CH_BUTTERFLY_2, 7, 5, 31, 6, CH_BUTTERFLY_2,

//    FILLRECT+CH_BUTTERFLY_2, 7, 5, 31., 6, CH_BUTTERFLY_2,

    CH_DOORCLOSED, XY(38,20),
    CH_ROCKFORD_BIRTH, XY(1,1),
    0xFF,

    // EXTRAS
            // LEVEL 0
    0xFF,   // LEVEL 1
    0xFF,   // LEVEL 2
    0xFF,   // LEVEL 3
    0xFF,   // LEVEL 4
    0xFF,

    'F','L','U','T','T','E','R',END_STRING

};





const unsigned char caveV[] = {


/*

▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓
▓░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░▓
▓░░░░░░░░░░░░░░░░oooooo░░░░░░░░░░░░░░░░▓
▓░░░░░░░░░░░░░░●●●●●●●●●●░░░░░░░░░░░░░░▓
▓░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░▓
▓░░░░░░░░░░░░░░          ░░░░░░░░░░░░░░▓
▓░░░░░▒▒░░▒░▒░░          ░░●●●░░●●░░░░░▓
▓░░░░░░▒░░▒▒▒░░          ░░●●●░░●░░░░░░▓
▓░░░░░░▒░░▒▒F▒░BBBBBB    ░●X●●░░●░░░░░░▓
▓░░░░░░▒░░▒▒▒▒░BBBBBB    ░●●●●░░●░░░░░░▓
▓░░░░░░▒░▒▒▒▒░░          ░░●●●●░●░░░░░░▓
▓░░░░░░▒░▒▒▒▒░░          ░░●●●●░●░░░░░░▓
▓░░░░░▒▒░▒▒▒▒▒░          ░●●●●●░●●░░░░░▓
▓░░░░░▒▒░▒▒▒▒▒░          ░●●●●●░●●░░░░░▓
▓░░░░░▒▒▒▒▒▒▒▒░          ░●●●●●●●●░░░░░▓
▓░░░░░░▒▒▒▒▒▒▒▒░░░░░░░░░░●●●●●●●●░░░░░░▓
▓░▓▓▓▓▓▓▓▓▓▓▓▓▓▓●●●●●●●●▓▓▓▓▓▓▓▓▓▓▓▓▓▓░▓
▓░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░▓
▓░░░░░░░░░░R░░░░░░░░░░░░░░░░░░░░░░░░░░░▓
▓░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░▓
▓░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░▓
▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓

*/

    //0,       // cave
    20,       // milling
    10,15,  // diamond $
    1,          // rain

    0xFA,11,12,13,14,       // randomiser[level]
    12,12,12,12,12,       // diamonds[level]
    0x96,0x6E,0x46,0x28,30,       // time[level]

    CAVEDEF_PARALLAX,
    STEEL,DIRT,

    0,
    
    LINE+7,2,16,RIGHT,36,
    LINE+16,16,16,RIGHT,8,

    // left cat

    FILLRECT+CH_BRICKWALL, 6, 6, 9, 10, CH_BRICKWALL,
    LINE+CH_DIRT, 6, 7, DOWN, 5,
    CH_DIRT, 6, 15,
    LINE+CH_DIRT, 8, 6, DOWN, 8,
    LINE+CH_DIRT, 9, 6, DOWN, 4,
    CH_DIRT, 11, 6,
    LINE+CH_DIRT, 13, 6, DOWN, 2,
    LINE+CH_DIRT, 13, 10, DOWN, 2,
    LINE+CH_DIRT, 14, 6, DOWN, 9,
    CH_FIREFLY_0, 12, 8,


    // right cat

    FILLRECT+CH_BOULDER, 25, 6, 9, 10, CH_BOULDER,
    LINE+CH_DIRT, 25+(14-6), 7, DOWN, 5,
    CH_DIRT, 25+(14-6), 15,
    LINE+CH_DIRT, 25+(14-8), 6, DOWN, 8,
    LINE+CH_DIRT, 25+(14-9), 6, DOWN, 4,
    CH_DIRT, 25+(14-11), 6,
    LINE+CH_DIRT, 25+(14-13), 6, DOWN,2,
    LINE+CH_DIRT, 25+(14-13), 10, DOWN, 2,
    LINE+CH_DIRT, 25+(14-14), 6, DOWN, 9,


    LINE+CH_BOULDER,15,3,RIGHT, 10,
    FILLRECT, 15,5,10,10,0,
    FILLRECT+BUTTERFLY,22-7,8,6,2,CH_BUTTERFLY_0,

    LINE+CH_AMOEBA_0, 17, +2, RIGHT, 6,

    CH_DOORCLOSED,27,8,             // pre-outbox
    CH_ROCKFORD_BIRTH,0xB,18,              // player/inbox


    0xFF,

    // EXTRAS
            // LEVEL 0
    0xFF,   // LEVEL 1
    0xFF,   // LEVEL 2
    0xFF,   // LEVEL 3
    0xFF,   // LEVEL 4
    0xFF,

    'Z','P','H',END_STRING
};



const unsigned char caveZPH0[]= {


    20,       // milling
    10,15,  // diamond $
    1,          // rain

    10,11,50,56,8,       // randomiser[level]
    5,9,9,9,9,
    40,50,60,55,50,


    CAVEDEF_PARALLAX,
    STEEL,CH_DIRT,

    2,  CH_BOULDER, 50,75,80,85,20,
        DIAMOND,    9,9,9,9,200,

    RECT + CH_STEELWALL, 10, 5, 20, 11,

    CH_DOORCLOSED,10,14,
    CH_ROCKFORD_BIRTH,11,7,

    0xFF,

    // EXTRAS
            // LEVEL 0
    0xFF,   // LEVEL 1
    0xFF,   // LEVEL 2
    0xFF,   // LEVEL 3
    0xFF,   // LEVEL 4
    0xFF,

    'T','A','N','Y','A','S',NEW_LINE,
    'C','A','V','E','R','N',END_STRING
};



const unsigned char caveZPH1[]= {


    20,       // milling
    10,15,  // diamond $
    1,          // rain

    22,11,50,56,8,       // randomiser[level]
    10,9,9,9,9,
    40,50,60,55,50,


    CAVEDEF_PARALLAX,
    STEEL,CH_DIRT,

    2,  CH_BOULDER, 190,75,80,85,20,
        DIAMOND,    40,9,9,9,200,

    RECT + CH_STEELWALL, 10, 5, 20, 11,

    CH_DOORCLOSED,16,7,
    CH_ROCKFORD_BIRTH,12,14,

    0xFF,

    // EXTRAS
            // LEVEL 0
    0xFF,   // LEVEL 1
    0xFF,   // LEVEL 2
    0xFF,   // LEVEL 3
    0xFF,   // LEVEL 4
    0xFF,

    'T','O','O',NEW_LINE,
    'M','U','C','H',END_STRING
};


const unsigned char caveZPH2[]= {


    20,       // milling
    10,15,  // diamond $
    1,          // rain

    22,11,50,56,8,       // randomiser[level]
    10,9,9,9,9,
    60,50,60,55,50,


    CAVEDEF_PARALLAX,
    STEEL,DIRT,

    0,

//    RECT + CH_STEELWALL, 10, 5, 20, 11,
    RECTR(CH_BRICKWALL, CH_DIRT, 11, 9, 10, 5)


    CH_DOORCLOSED,16,7,
    CH_ROCKFORD_BIRTH,12,14,

    CH_DIRT,16,9,
    CH_BOULDER, 17,8,
    CH_BOULDER, 16,11,
    CH_BOULDER, 16,12,
    CH_AMOEBA_0, 13,12,
    CH_AMOEBA_0, 14,12,

    0xFF,

    // EXTRAS
            // LEVEL 0
    0xFF,   // LEVEL 1
    0xFF,   // LEVEL 2
    0xFF,   // LEVEL 3
    0xFF,   // LEVEL 4
    0xFF,

    'T','R','A','P',NEW_LINE,
    'A','M','O','E','B','A',END_STRING
};



const unsigned char caveZPH3[]= {


    20,       // milling
    10,15,  // diamond $
    1,          // rain

    22,11,50,56,8,       // randomiser[level]
    9,9,9,9,9,
    60,50,60,55,50,


    CAVEDEF_PARALLAX,
    STEEL,DIRT,

    0,

//    RECT + CH_STEELWALL, 10, 5, 20, 11,
    RECTR(CH_BLANK, CH_BLANK, 11, 9, 8, 5)

    CH_BOULDER, 17,7,
    CH_DOORCLOSED,15,7,
    CH_ROCKFORD_BIRTH,12,7,

    CH_BUTTERFLY_0, 11,9,

    0xFF,

    // EXTRAS
            // LEVEL 0
    0xFF,   // LEVEL 1
    0xFF,   // LEVEL 2
    0xFF,   // LEVEL 3
    0xFF,   // LEVEL 4
    0xFF,

    'S','Q','U','I','S','H',NEW_LINE,
    'I','N','S','E','C','T',END_STRING
};


const unsigned char caveZPH4[]= {


    20,       // milling
    10,15,  // diamond $
    1,          // rain

    22,11,50,56,8,       // randomiser[level]
    0,9,9,9,9,
    20,50,60,55,50,


    CAVEDEF_PARALLAX,
    STEEL,DIRT,

    0,

//    RECT + CH_STEELWALL, 10, 5, 20, 11,
    RECT+CH_FIREFLY_0, 11, 9, 3, 3,
    CH_DOORCLOSED,12,10,
    CH_ROCKFORD_BIRTH,10,7,


    CH_BOULDER,13,12,

    0xFF,

    // EXTRAS
            // LEVEL 0
    0xFF,   // LEVEL 1
    0xFF,   // LEVEL 2
    0xFF,   // LEVEL 3
    0xFF,   // LEVEL 4
    0xFF,

    'G','U','A','R','D','E','D',NEW_LINE,
    'E','X','I','T',END_STRING
};



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

    3,  CH_BLANK,       60, 255,   0, 255,  10,
        CH_BOULDER,     30,   0, 240,   0,  20,
        CH_BOULDER_DOGE,     80,   0, 240,   0,  20,

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

    
    0xFE, CH_WYRM_HEAD_U, 11, 16,


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
    0xFE, CH_ROCKFORD_BIRTH,3,2,

    // 0xFE, CH_SWITCH_LEFT_OFF, 1, 19,

    // 0xFE, CH_WYRM_BODY, 6, 4,
    0xFE, CH_WYRM_BODY, 16, 10,

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

//    0xFE, CH_DOORCLOSED,38,16,
    0xFE, CH_ROCKFORD_BIRTH,11,9,

    0xFE, CH_WYRM_HEAD_U, 16, 9,



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


// const unsigned char caveLife[]= {


//     20,       // milling
//     10,15,  // diamond $
//     5, //              ,          // rain

//     10,11,50,56,8,       // randomiser[level]
//     25,12,12,12,12,
//     200,200,200,200,200,
//     //70,65,60,55,50,


//     CAVEDEF_PARALLAX,
//     STEEL,CH_DIRT,

//     0,

//     0xFE, CH_ROCKFORD_BIRTH,11,9,


//     0xFF,

//     // EXTRAS
//             // LEVEL 0
//     0xFF,   // LEVEL 1
//     0xFF,   // LEVEL 2
//     0xFF,   // LEVEL 3
//     0xFF,   // LEVEL 4
//     0xFF,

//     'M','E','R','C','U','R','Y',END_STRING
// };

const unsigned char newCaveA[]= {

    20,       // milling
    10,5,  // diamond $, extra $
    1,          // rain

    221,111,112,113,118,       // randomiser[level]
    10,15,20,25,30,             // diamonds required
    150,140,130,120,110,      // time


    CAVEDEF_PARALLAX,
    STEEL,DIRT,

//  #   CHARACTER       L0   L1   L2   L3   L4

    3,  CH_BOULDER,     50,  60,  70,  80,  90,
        CH_BLANK,       20,  20,  20,  20,  20,
        DIAMOND,        30,  25,  20,  15,  30,

    LINER(CH_BRICKWALL,13,1,15,D)
    LINER(CH_BRICKWALL,26,20,15,U)

    ROCKY(3,2,38,16)
    0xFF,

    // EXTRAS
            // LEVEL 0
    0xFF,   // LEVEL 1
    0xFF,   // LEVEL 2
    0xFF,   // LEVEL 3
    0xFF,   // LEVEL 4
    0xFF,

    'R','U','N',NEW_LINE,
    'R','O','C','K','Y',NEW_LINE,
    'R','U','N',END_STRING

};


const unsigned char newCaveAX[]= {

    20,       // milling
    10,5,  // diamond $, extra $
    1,          // rain

    221,111,112,113,118,       // randomiser[level]
    60,15,20,25,30,             // diamonds required
    150,140,130,120,110,      // time


    CAVEDEF_PARALLAX,
    STEEL,CH_BOULDER,

//  #   CHARACTER       L0   L1   L2   L3   L4

    1,
    // 3,  CH_BOULDER,     50,  60,  70,  80,  90,
    //     CH_BLANK,       20,  20,  20,  20,  20,
         FIREFLY,   2,  5,  7,  9,  11,


    LINER(DIRT, 3, 3, 21, D)
    LINER(DIRT, 3, 3, 15, R)

    LINER(DIRT, 3, 6, 15, R)
    LINER(DIRT, 18, 7, 15, R)


    LINER(DIRT, 3, 9, 15, R)
    LINER(DIRT, 3, 10, 15, R)

    LINER(DIRT, 3, 13, 15, R)
    LINER(DIRT, 3, 14, 15, R)


    LINER(DIRT, 3, 17, 15, R)
    LINER(DIRT, 3, 18, 15, R)

    CH_DOGE_00, 8, 7,
    CH_DOGE_00, 8, 12,

    RECTR(CH_DIRT, CH_BLANK, 25, 5, 10, 14)

    CH_AMOEBA_0, 26,18,

    ROCKY(3,2,38,2)
    0xFF,





    // EXTRAS
            // LEVEL 0
    0xFF,   // LEVEL 1
    0xFF,   // LEVEL 2
    0xFF,   // LEVEL 3
    0xFF,   // LEVEL 4
    0xFF,

    'R','E','A','L',NEW_LINE,
    'B','U','S','T','E','D',END_STRING
};


const unsigned char newCaveC[]= {

    20,       // milling
    20,1,  // diamond $, extra $
    1,          // rain

    10,11,12,13,14,       // randomiser[level]
    1,1,1,10,30,             // diamonds required
    15,20,20,40,30,      // time


    CAVEDEF_PARALLAX|CAVEDEF_OVERVIEW|CAVEDEF_BOULDER_GENERATE,
    STEEL,CH_DOGE_00,

    // Random populate...
    
    // Obj for random #x

    0,

    //1,  CH_AMOEBA_0, 0, 1, 2, 3, 4,


    RECTR(CH_STEELWALL, CH_BLANK, 10, 5, 20, 12)
    RECTE(CH_BOULDER, 19, 1, 2, 5)
    // CH_BOULDER,20, 11-5,
    // CH_BOULDER,18, 12-5,


    CH_DOGE_00, 11, 10,

    LINER(CH_BRICKWALL, 18, 8, 3, R)
    LINER(CH_BRICKWALL, 20, 11, 3, R)


    CH_DOORCLOSED,24,20-5,
    CH_ROCKFORD_BIRTH,11,8,

    0xFF,

    // EXTRAS
    // LEVEL 0

    0xFF, 
    // LEVEL 1
    CH_STEELWALL, 17,6,
    CH_STEELWALL, 22,6,
        
    0xFF,
    // LEVEL 2
    LINER(CH_BRICKWALL, 20, 14, 3, R)

    0xFF,
    // LEVEL 3
    LINER(CH_AMOEBA_0, 18,15, 4, R)


    0xFF,
    // LEVEL 4
    RECTR(BUTTERFLY, BUTTERFLY, 26, 12, 3, 4)
    0xFF,

    'R','O','C','K',NEW_LINE,
    'T','U','M','B','L','E',END_STRING
};


const unsigned char newCaveB[]= {

    20,       // milling
    20,1,  // diamond $, extra $
    1,          // rain

    67,211,212,223,26,       // randomiser[level]
    0,0,0,0,0,             // diamonds required
    150,150,150,150,150,      // time


    CAVEDEF_PARALLAX,
    STEEL,DIRT,

    3,  CH_BLANK,   60, 60, 60, 60, 60,
        CH_BOULDER, 50, 60, 70, 80, 90,
        DIAMOND,    15,15,15,15,15,


    FILLRECT+CH_BOULDER,18,1,21,10,CH_BOULDER,


    LINE + CH_BRICKWALL,23,2,5,17,
    LINE + CH_BRICKWALL,16,9,3,10,


    CH_DOORCLOSED,38,1,
    CH_ROCKFORD_BIRTH,3,2,

    0xFF,

    // EXTRAS
            // LEVEL 0
    0xFF,   // LEVEL 1
    0xFF,   // LEVEL 2
    0xFF,   // LEVEL 3
    0xFF,   // LEVEL 4
    0xFF,

    'N','O','P','E',NEW_LINE,
    'P','A','S','S',END_STRING
};



const unsigned char caveN[]= {

/*

▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓
▓▓  ● ░░░░● ░░░░▒▒░░░░░░● ● ░░  ▒▒░░  ●   ░░░░  ▒▒● ● ░░● ░░░░▲ ▒▒  ░░░░░░░░░░▓▓
▓▓░░░░  ░░░░░░  ▒▒● ● ░░● ░░● ░░▒▒● ● ░░  ░░░░░░▒▒● ░░  ░░░░● ● ▒▒░░▲ ● ░░░░░░▓▓
▓▓                                                                            ▓▓
▓▓  ● ░░░░F   ░░▒▒░░● ░░░░░░░░░░▒▒  ░░F   ░░░░● ▒▒● ░░░░  ● ░░░░▒▒░░░░● ● ░░░░▓▓
▓▓░░  ░░● ░░░░░░▒▒░░░░░░▲   ░░░░▒▒● ░░░░  ░░░░░░▒▒░░░░▲ ░░░░░░░░▒▒░░  ●   ░░░░▓▓
▓▓▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒  ▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▓▓
▓▓● ░░░░░░░░░░░░▒▒░░░░░░░░░░░░░░▒▒░░░░░░  ░░░░░░▒▒░░░░  ░░░░░░░░▒▒░░  ░░░░  ░░▓▓
▓▓▲ ░░  ░░● ░░  ▒▒●       ● ░░░░▒▒░░● ░░  ░░░░● ▒▒▲ ░░░░● ░░░░░░▒▒░░░░░░▲ ░░  ▓▓
▓▓                                                                            ▓▓
▓▓░░░░░░░░░░░░░░▒▒● ░░    ░░░░▲ ▒▒░░  ░░  ░░  ● ▒▒● ● ░░░░  ░░  ▒▒░░●   ░░░░░░▓▓
▓▓  ░░░░░░░░  ░░▒▒  ░░  ░░░░● ▲ ▒▒░░░░░░  ▲ ░░░░▒▒●   ░░░░░░░░░░▒▒░░░░░░░░░░░░▓▓
▓▓● ░░      ░░░░▒▒░░░░░░░░● ░░  ▒▒░░  ●   ░░░░● ▒▒    ░░    ░░░░▒▒● ● ░░░░    ▓▓
▓▓▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒  ▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▓▓
▓▓░░● ░░▲ ░░● ░░▒▒░░● ░░░░  ▲ ● ▒▒  ░░░░  ░░░░● ▒▒  ░░░░░░▲   ● ▒▒░░●   ░░▲ ░░▓▓
▓▓● ░░  ░░● ░░░░▒▒  ░░░░    ● ░░▒▒● ░░░░  ░░░░● ▒▒░░░░●   ● ░░  ▒▒░░  ░░░░░░░░▓▓
▓▓                                                                            ▓▓
▓▓░░░░● ● ░░░░░░▒▒░░░░░░░░░░░░▲ ▒▒░░░░▲   ░░● ░░▒▒░░░░● ░░░░● ░░▒▒● ░░░░░░░░░░▓▓
▓▓● ░░    ░░● ░░▒▒● ░░● ░░● ░░░░▒▒  ░░░░  ░░░░░░▒▒░░░░░░░░░░░░░░▒▒░░░░░░  ░░░░▓▓
▓▓░░●         ░░▒▒░░░░  ░░  ● ░░▒▒░░R ░░  ● ● ░░▒▒●   ░░● ░░● ░░▒▒░░░░░░●   ░░▓▓
▓▓░░● ░░░░░░░░● ▒▒▲ ● ░░░░  ░░░░▒▒░░X ░░  ░░░░░░▒▒░░░░░░● ░░● ▲ ▒▒░░      ● ░░▓▓
▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓


*/

    20,       // milling
    20,0x32,  // diamond $
    6,          // rain

    3,02,1,0x57,0x58,       // randomiser[level]
    10,12,9,13,10,
    0x96,0x6E,0x46,0x46,0x46,

    CAVEDEF_PARALLAX,
    STEEL,DIRT,

    4,  CH_BLANK,       60,60,60,60,60,
        CH_BOULDER,     50,55,60,65,70,
        DIAMOND,     9,9,9,9,9,
        CH_FIREFLY_0,   2,3,4,5,6,

    0x40 + CH_BRICKWALL,1,6,2,0x26,
    0x40 + CH_BRICKWALL,1,13,2,0x26,
    0x40 + CH_BRICKWALL,8,1,4,20,
    0x40 + CH_BRICKWALL,16,1,4,20,
    0x40 + CH_BRICKWALL,24,1,4,20,
    0x40 + CH_BRICKWALL,0x20,1,4,20,
    0x40 + CH_BLANK,1,3,2,0x26,
    0x40 + CH_BLANK,1,9,2,0x26,
    0x40 + CH_BLANK,1,16,2,0x26,
    0x40 + CH_BLANK,20,1,4,20,

    CH_DOORCLOSED,18,20,     // exit
    CH_ROCKFORD_BIRTH,18,21-2,     // entry

    0xFF,

    // EXTRAS
            // LEVEL 0
    0xFF,   // LEVEL 1
    0xFF,   // LEVEL 2
    0xFF,   // LEVEL 3
    0xFF,   // LEVEL 4
    0xFF,

    'D','O','O','M',NEW_LINE,'R','O','O','M',END_STRING
};



const unsigned char caveC[]= {

/*

▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓
▓▓░░░░░░░░▒▒░░░░▒▒░░● ▒▒▲ ░░░░▒▒● ▒▒▒▒░░▒▒● ▒▒▒▒● ▲ ▒▒░░▒▒░░░░▒▒▒▒░░▒▒▒▒░░░░░░▓▓
▓▓▒▒░░R ▒▒● ░░░░● ▒▒● ● ░░░░▒▒░░● ▒▒░░░░▒▒░░░░▒▒● ░░▒▒░░● ▒▒▒▒● ░░░░● ░░░░▒▒▒▒▓▓
▓▓● ░░░░▒▒● ▲ ▒▒▒▒░░● ░░● ● ░░● ░░▒▒▒▒░░░░░░● ░░░░● ░░░░░░▒▒▒▒░░░░● ░░● ▒▒● ░░▓▓
▓▓░░● ░░▒▒● ● ░░● ▒▒▒▒░░░░▒▒░░▒▒░░▒▒▒▒▒▒▒▒░░● ▒▒▒▒▲ ░░▒▒● ▒▒▒▒░░░░▒▒░░▲ ● ● ▒▒▓▓
▓▓▒▒▒▒░░░░● ░░● ░░░░▲ ░░● ● ● ░░▒▒░░▒▒░░▒▒░░░░▒▒░░░░▒▒░░░░● ▲ ░░░░░░▲ ▲ ░░░░░░▓▓
▓▓░░▲ ▒▒▒▒░░● ▲ ░░░░░░░░░░▒▒▲ ░░░░▒▒░░░░░░● ░░● ░░░░░░● ▲ ░░░░● ░░░░▒▒░░░░  ░░▓▓
▓▓░░▲ ● ● ▒▒░░▒▒░░░░▒▒░░░░▒▒● ░░░░● ▒▒░░░░░░o ░░▒▒░░▒▒▲ ░░▲ ▒▒░░▒▒▒▒▒▒● ░░● ░░▓▓
▓▓● ░░░░░░░░░░░░░░● ● ▒▒░░▒▒░░░░● ▒▒● ░░▒▒● ░░░░▒▒░░░░░░▒▒░░● ░░▒▒░░▒▒░░▒▒●   ▓▓
▓▓░░● ▒▒▒▒░░▲ ● ░░● ░░░░● ● ● ▒▒░░░░░░░░░░░░░░░░● ▒▒● ● ▒▒● ▒▒▒▒░░░░░░░░● ░░░░▓▓
▓▓▒▒● ▒▒▒▒░░● ▒▒▲ ● ● ░░● ▒▒░░▒▒▒▒░░▲ ▒▒● ▒▒▒▒● ░░░░░░● ░░▒▒● ● ▒▒● ░░▒▒░░▒▒● ▓▓
▓▓░░● ░░● ░░▲ ░░▒▒● ░░▒▒░░░░░░▒▒░░▒▒░░░░●   ● ░░░░▒▒░░░░░░● ▒▒░░● ▒▒░░░░▲ ░░● ▓▓
▓▓● ● ░░░░▒▒░░▒▒░░▒▒░░▒▒▒▒░░▒▒▒▒▒▒▒▒▒▒░░● ● ▒▒▒▒░░░░░░● ▒▒● ░░▒▒░░░░▒▒▒▒░░● ░░▓▓
▓▓░░  ▒▒░░░░● ● ░░▒▒▒▒▒▒  ░░░░░░░░░░▒▒░░░░░░▒▒░░░░▒▒▒▒░░● ● ▒▒░░▒▒░░▒▒● ░░▒▒▒▒▓▓
▓▓░░░░░░● ● ● ▲ ▒▒▒▒░░● ░░░░● ░░░░▒▒● ● ● ░░░░░░░░▒▒▒▒▒▒● ● ░░▲ ░░▒▒▒▒░░░░░░▒▒▓▓
▓▓● ░░▲ ● ● ░░░░▒▒░░▒▒░░▒▒▒▒▒▒▒▒░░░░● ▒▒░░░░▲ ▲ ▒▒░░░░░░● ▒▒▒▒░░▒▒▒▒░░▲ ● ● ▲ ▓▓
▓▓░░░░░░░░▒▒● ░░░░░░▒▒▒▒░░░░░░▒▒▒▒● ░░░░░░● ▒▒░░░░▒▒● ▒▒░░░░▲ ▒▒▒▒░░▒▒░░▒▒░░░░▓▓
▓▓▒▒▲ ░░▒▒● ░░● ░░░░░░░░░░● ░░● ░░░░░░░░▒▒░░░░▒▒▒▒░░░░░░▒▒░░░░░░▒▒● ● ▒▒░░░░▒▒▓▓
▓▓░░░░▒▒● ● ● ▒▒░░▒▒● ░░● ▒▒▒▒● ░░● ▒▒▲ ░░░░░░▒▒● ░░▒▒░░░░▒▒● ▲ ● ░░░░░░░░░░░░X 
▓▓● ● ● ░░▲ ▒▒▒▒● ● ░░▒▒▒▒░░▒▒▒▒▒▒▒▒▒▒● ░░░░░░▒▒░░░░● ▒▒▒▒● ░░░░▒▒● ░░░░░░░░░░▓▓
▓▓░░░░░░░░● ░░▒▒░░░░░░░░░░░░● ░░░░░░░░▒▒░░▒▒░░● ▒▒▒▒▒▒░░░░▒▒░░░░▒▒▒▒▒▒● ░░● ░░▓▓
▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓

*/

    60,       // milling
    15,15,  // diamond $
    2,          // rain

    03,6,8,11,0x37,       // randomiser[level]
    24,20,16,12,8,
    75,75,75,75,75,

    CAVEDEF_PARALLAX,
    STEEL,DIRT,

    4,  CH_BRICKWALL,   50,55,60,65,70,
        CH_BOULDER,     10,20,30,40,50,
        DIAMOND,     9,9,9,9,9,
        CH_BLANK,       2,2,2,2,2,

    AMOEBA, 22,0x7,

    CH_DOORCLOSED,0x27,19,
    CH_ROCKFORD_BIRTH,3,2,

    0xFF,

    // EXTRAS
            // LEVEL 0
    0xFF,   // LEVEL 1
    0xFF,   // LEVEL 2
    0xFF,   // LEVEL 3
    0xFF,   // LEVEL 4
    0xFF,

    'S','T','O','N','E',NEW_LINE,
    'G','U','L','C','H',END_STRING
};



const unsigned char caveO[]= {

/*

▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓
▓▓R ░░░░░░░░░░░░░░░░░░░░● ░░░░░░░░░░░░░░░░● ░░░░● ░░░░░░░░░░░░░░░░░░░░░░░░░░░░▓▓
▓▓░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░● ░░░░░░░░░░░░░░░░░░░░░░░░░░░░▓▓
▓▓░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░▓▓
▓▓● ░░● ░░░░░░░░░░░░░░░░░░░░● ░░░░░░░░░░░░░░░░● ░░░░░░░░░░░░░░░░░░● ░░░░░░░░░░▓▓
▓▓░░░░● ░░░░░░░░░░░░░░░░░░░░● ● ● ░░░░░░░░░░░░░░░░░░░░░░● ░░● ░░░░░░● ░░░░● ░░▓▓
▓▓░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░▓▓
▓▓░░░░░░░░● ░░● ░░░░░░░░● ░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░● ░░● ░░▓▓
▓▓● ░░░░░░░░● ░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░▓▓
▓▓░░░░● ░░░░░░░░░░  B ░░░░░░░░░░░░  B ░░░░░░░░░░░░  B ░░░░░░░░░░░░  B ░░░░░░● ▓▓
▓▓░░░░░░░░░░░░░░░░    ░░░░░░● ░░░░    ░░░░░░░░░░░░    ░░░░░░░░░░░░    ░░░░░░░░▓▓
▓▓░░░░░░░░░░░░░░░░░░░░░░● ░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░● ░░░░░░░░░░░░░░░░▓▓
▓▓░░░░░░░░░░● ░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░● ░░░░░░░░░░░░░░░░▓▓
▓▓● ░░░░░░░░░░░░░░● ░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░▓▓
▓▓░░░░░░░░░░░░░░░░░░░░░░░░● ░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░▓▓
▓▓░░░░░░● ░░░░░░░░░░● ░░░░░░░░░░░░░░● ░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░▓▓
▓▓░░░░░░░░░░░░░░● ░░░░░░● ░░░░░░░░● ░░░░░░░░░░● ░░░░░░░░░░░░░░░░░░░░░░░░░░░░● ▓▓
▓▓░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░● ░░░░░░░░░░▓▓
▓▓░░░░░░░░░░░░░░░░░░░░░░░░░░● ░░░░░░░░░░░░░░░░● ░░░░░░░░░░░░░░░░● ░░░░░░░░░░░░▓▓
▓▓░░░░░░░░░░░░● ░░░░░░░░░░░░░░░░● ░░░░░░░░● ░░░░● ░░░░░░░░● ░░░░● ░░░░░░░░░░░░▓▓
▓▓░░░░░░● ░░░░░░░░● ● ░░░░● ● ░░░░░░░░░░░░░░░░● ░░░░● ░░░░░░░░░░░░░░░░░░░░░░X ▓▓
▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓

*/

    20,       // milling
    5,20,  // diamond $
        0,          // rain


    30,0x6E,0x70,0x73,6,       // randomiser[level]
    0x24,0x24,0x24,0x24,0x24,
    0x78,0x64,0x50,0x3C,0x32,

    CAVEDEF_PARALLAX, //|CAVEDEF_RAINBOW,
    STEEL,DIRT,

    2,  CH_BOULDER, 20,20,20,20,20,
        CH_FIREFLY_0, 0, 2, 3, 4, 5,

    0x80 + CH_DIRT,8,8,4,4,0,
    CH_BUTTERFLY_0,10,9,
    0x80 + CH_DIRT,16,8,4,4,0,
    CH_BUTTERFLY_0,18,9,
    0x80 + CH_DIRT,24,8,4,4,0,
    CH_BUTTERFLY_0,26,9,
    0x80 + CH_DIRT,0x20,8,4,4,0,
    CH_BUTTERFLY_0,0x22,9,

    
    CH_DOORCLOSED,0x26,20,
    CH_ROCKFORD_BIRTH,1,1,

    0xFF,

    // EXTRAS
            // LEVEL 0
    0xFF,   // LEVEL 1
    0xFF,   // LEVEL 2
    0xFF,   // LEVEL 3
    0xFF,   // LEVEL 4
    0xFF,

    'P','R','I','S','O','N',NEW_LINE,
    'B','R','E','A','K','S',END_STRING
};



const unsigned char caveP[]= {

/*

▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓
▓▓R ░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░▓▓
▓▓░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░▓▓
▓▓░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░▓▓
▓▓░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░▓▓
▓▓░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░▓▓
▓▓░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░▓▓
▓▓░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░▓▓
▓▓░░░░░░░░░░░░░░    F ░░░░░░░░░░    F ░░░░░░░░░░    F ░░░░░░░░░░    F ░░░░░░░░▓▓
▓▓░░░░░░░░░░░░░░      ░░░░░░░░░░      ░░░░░░░░░░      ░░░░░░░░░░      ░░░░░░░░▓▓
▓▓░░░░░░░░░░░░░░  ▲   ░░░░░░░░░░  ▲   ░░░░░░░░░░  ▲   ░░░░░░░░░░  ▲   ░░░░░░░░▓▓
▓▓░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░▓▓
▓▓░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░▓▓
▓▓░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░▓▓
▓▓░░░░░░░░░░░░░░    F ░░░░░░░░░░    F ░░░░░░░░░░    F ░░░░░░░░░░    F ░░░░░░░░▓▓
▓▓░░░░░░░░░░░░░░      ░░░░░░░░░░      ░░░░░░░░░░      ░░░░░░░░░░      ░░░░░░░░▓▓
▓▓░░░░░░░░░░░░░░  ▲   ░░░░░░░░░░  ▲   ░░░░░░░░░░  ▲   ░░░░░░░░░░  ▲   ░░░░░░░░▓▓
▓▓░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░▓▓
▓▓░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░▓▓
▓▓░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░▓▓
▓▓░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░X 
▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓

*/

    20,       // milling
    0x32,0x5A,  // diamond $
    3,          // rain


    03,4,16,6,17,       // randomiser[level]
    4,5,6,7,8,
    0x96,0x78,0x5A,0x3C,30,

    CAVEDEF_PARALLAX, //|CAVEDEF_RAINBOW,
    STEEL,DIRT,

    1,  CH_BOULDER, 0, 10, 20, 30, 40,


    0x80 + CH_BLANK,8,8,3,3,0,
    0x80 + CH_BLANK,16,8,3,3,0,
    0x80 + CH_BLANK,24,8,3,3,0,
    0x80 + CH_BLANK,0x20,8,3,3,0,

    CH_DOGE_00,9,10,
    CH_FIREFLY_0,10,8,
    CH_DOGE_00,17,10,
    CH_FIREFLY_0,18,8,
    CH_DOGE_00,25,10,
    CH_FIREFLY_0,26,8,
    CH_DOGE_00,0x21,10,
    CH_FIREFLY_0,0x22,8,

    0x80 + CH_BLANK,8,14,3,3,0,
    0x80 + CH_BLANK,16,14,3,3,0,
    0x80 + CH_BLANK,24,14,3,3,0,
    0x80 + CH_BLANK,0x20,14,3,3,0,

    CH_DOGE_00,9,16,
    CH_FIREFLY_0,10,14,
    CH_DOGE_00,17,16,
    CH_FIREFLY_0,18,14,
    CH_DOGE_00,25,16,
    CH_FIREFLY_0,26,14,
    CH_DOGE_00,0x21,16,
    CH_FIREFLY_0,0x22,14,

    CH_DOORCLOSED,0x27,20, //exit
    CH_ROCKFORD_BIRTH,1,1, //entry
    0xFF,

    // EXTRAS
            // LEVEL 0
    0xFF,   // LEVEL 1
    0xFF,   // LEVEL 2
    0xFF,   // LEVEL 3
    0xFF,   // LEVEL 4
    0xFF,

    'D','I','A','M','O','N','D',NEW_LINE,
    'H','E','I','S','T',END_STRING
};



const unsigned char caveQ[]= {

/*

▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓
▓▓▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒░░░░░░░░░░● ░░░░● ● ░░░░░░● ░░░░░░░░░░░░▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▓▓
▓▓▒▒                ░░● ● ░░░░● ░░░░░░░░░░░░░░░░░░░░░░░░● ░░                ▒▒▓▓
▓▓▒▒  ▲ F           ░░░░● ░░░░░░░░● ░░░░░░░░● ░░░░● ░░░░░░░░          F ▲   ▒▒▓▓
▓▓▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒░░░░░░░░░░░░░░░░░░░░░░░░░░░░● ░░░░● ░░░░▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▓▓
▓▓▒▒                ░░░░░░░░░░░░░░░░● ░░░░● ░░░░● ● ● ░░● ░░                ▒▒▓▓
▓▓▒▒  ▲ F           ░░░░░░░░░░░░░░░░● ░░░░░░░░░░░░● ● ░░░░░░          F ▲   ▒▒▓▓
▓▓▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒░░░░░░░░░░░░░░░░░░░░░░░░░░● ░░░░░░● ░░░░▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▓▓
▓▓▒▒                ░░░░░░░░░░░░░░░░░░● ░░░░● ░░░░● ░░░░░░░░                ▒▒▓▓
▓▓▒▒  ▲ F           ░░░░░░░░░░░░░░● ░░● ░░░░░░░░░░░░░░░░░░░░          F ▲   ▒▒▓▓
▓▓▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒░░● ● ░░░░░░░░░░░░░░░░░░░░░░░░░░░░● ░░░░▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▓▓
▓▓▒▒                ░░● ● ░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░                ▒▒▓▓
▓▓▒▒  ▲ F           ░░░░░░░░░░░░░░● ░░░░● ● ● ░░░░░░● ░░░░░░          F ▲   ▒▒▓▓
▓▓▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒░░● ● ░░░░● ░░░░░░░░░░░░░░● ░░░░░░░░░░░░▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▓▓
▓▓░░░░░░░░░░● ░░░░░░░░░░░░░░░░░░░░● ░░░░░░░░░░░░● ░░░░● ░░░░● ░░░░░░░░░░░░● ░░▓▓
▓▓░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░● ● ● ░░░░░░░░░░░░░░░░░░░░░░● ░░░░░░● ▓▓
▓▓░░░░░░░░░░░░░░░░● ● ░░░░░░░░░░░░░░░░░░░░░░● ● ● ░░░░░░░░░░░░░░░░░░░░░░░░░░░░▓▓
▓▓░░● ● ● ░░░░░░● ░░░░░░░░● ░░░░● ● ░░░░░░░░░░░░● ░░░░░░░░░░░░░░░░░░░░░░░░● ░░▓▓
▓▓░░░░R ░░░░░░░░░░● ░░░░░░░░░░░░░░░░● ● ░░░░● ░░● ● ░░░░● ░░░░░░░░░░● ● ░░░░X ▓▓
▓▓░░░░░░● ░░● ● ░░░░● ░░░░░░░░░░░░░░░░░░● ░░░░░░░░░░░░░░● ░░● ░░░░░░● ░░░░░░░░▓▓
▓▓░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░● ░░░░░░░░░░░░● ░░● ░░░░● ░░░░░░░░░░░░● ● ░░░░▓▓
▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓

*/

    20,       // mililng
    0x28,0x3C,  // diamond $
    7,          // rain

    30,20,21,22,32,       // randomiser[level]
    4,6,7,8,8,
    0x96,0x78,0x64,0x5A,0x50,

    CAVEDEF_PARALLAX,
    STEEL,DIRT,

    3,  
        CH_BLANK,   0, 60, 80, 100, 120,
        CH_BOULDER, 50,50,50,50,50,
        CH_FIREFLY_0, 0, 1, 2, 3, 4,

    0x80 + CH_BRICKWALL,1,1,10,4,0,
    0x80 + CH_BRICKWALL,1,4,10,4,0,
    0x80 + CH_BRICKWALL,1,7,10,4,0,
    0x80 + CH_BRICKWALL,1,10,10,4,0,

    0x40 + CH_DIRT,10,1,4,13,
    CH_DOGE_00,3,3,
    CH_FIREFLY_0,4,3,
    CH_DOGE_00,3,6,
    CH_FIREFLY_0,4,6,
    CH_DOGE_00,3,9,
    CH_FIREFLY_0,4,9,
    CH_DOGE_00,3,12,
    CH_FIREFLY_0,4,12,

    0x80 + CH_BRICKWALL,29,1,10,4,0,
    0x80 + CH_BRICKWALL,29,4,10,4,0,
    0x80 + CH_BRICKWALL,29,7,10,4,0,
    0x80 + CH_BRICKWALL,29,10,10,4,0,
    0x40 + CH_DIRT,29,1,4,13,

    CH_DOGE_00,0x24,3,
    CH_FIREFLY_0,0x23,3,
    CH_DOGE_00,0x24,6,
    CH_FIREFLY_0,0x23,6,
    CH_DOGE_00,0x24,9,
    CH_FIREFLY_0,0x23,9,
    CH_DOGE_00,0x24,12,
    CH_FIREFLY_0,0x23,12,

    CH_DOORCLOSED,0x26,18, // exit
    CH_ROCKFORD_BIRTH,3,18, // entry

    0xFF,

    // EXTRAS
            // LEVEL 0
    0xFF,   // LEVEL 1
    0xFF,   // LEVEL 2
    0xFF,   // LEVEL 3
    0xFF,   // LEVEL 4
    0xFF,

    'G','U','A','R','D',NEW_LINE,
    'R','O','O','M','S',END_STRING
};



const unsigned char caveD[]= {

/*

▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓
▓▓░░● ░░  ● ░░    ░░●     ●   ● ░░  ░░░░R ░░● F ░░░░░░░░  ░░░░  ░░░░● ●     ░░▓▓
▓▓    ░░  ░░    ● ░░░░●     ░░░░░░  ░░░░░░░░● ░░●   ░░░░● ●   ● ░░░░▲ ●     ░░▓▓
▓▓░░  ░░  ░░░░●   ░░  ░░●   ░░    ●   ░░░░░░  ░░░░░░░░  ▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▓▓
▓▓  ░░  ▲   ░░      ● ● ░░░░  ░░    ░░░░● ░░● ░░●     ░░● ● ● ░░    F ░░░░░░● ▓▓
▓▓▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒●   ●       ░░░░  F ░░░░  ░░░░F ●   ░░  ░░░░    ●   X 
▓▓░░  ●     ░░        ░░░░      ░░        ░░░░●     ░░░░░░░░░░░░● ░░░░  ░░░░░░▓▓
▓▓░░░░░░      F ░░░░● ░░F       ●   ● ░░  ░░░░●   ░░  ░░  ● ░░░░  ░░    ░░░░░░▓▓
▓▓░░░░░░●     ░░░░● ░░░░    ● ░░░░  ░░░░●   ░░  ░░░░  ● ░░●     ░░░░●   ░░░░░░▓▓
▓▓● ░░░░░░░░░░░░      ░░░░░░  ●   ● ░░  ░░  ░░░░░░  ░░● ● ░░  ● ● ● ● ░░░░░░  ▓▓
▓▓░░  ● ░░░░░░░░░░░░░░░░●   ░░░░  ●       ░░      ░░      ░░  ░░● ░░▲ ░░●   ● ▓▓
▓▓░░░░░░░░░░░░● ░░░░░░      ░░  ░░  ░░░░░░    ● ░░    ░░░░░░░░░░░░  ● ░░░░░░░░▓▓
▓▓░░░░░░▲ ░░░░░░      ● ● ░░░░●   ░░  ░░░░░░░░░░░░  ░░  ░░░░░░░░░░░░░░░░      ▓▓
▓▓  ░░● ░░    ░░    ░░░░● ░░░░░░░░  ░░    F ● ░░● ░░░░░░░░    ●   ░░  ░░░░●   ▓▓
▓▓      ●   ● F ░░░░░░░░      ░░░░░░● ░░░░░░●   ░░●   ░░●   ░░● ░░  ░░░░●     ▓▓
▓▓░░      ░░  ░░      ░░  ░░    ░░░░░░░░░░F ░░  ░░  ░░  ░░  ░░░░●   ░░  ●   ░░▓▓
▓▓    ░░░░░░░░      ● ● ●     ░░░░● ░░░░        ░░●   ░░░░● ░░  ● ░░  ░░    ● ▓▓
▓▓░░░░    ░░░░●   ░░░░░░░░  ░░░░░░░░  ░░░░●   ░░░░    ░░    ░░░░    ░░●   ● ░░▓▓
▓▓● ░░░░▲   ░░        ░░● ░░░░░░      ░░░░░░░░●   ░░●       ░░  ░░░░░░● ░░░░░░▓▓
▓▓░░  ░░░░  ● ░░░░░░░░  ░░  ░░  ●     o o     ░░  ░░  ●   ░░● ░░      ░░░░░░░░▓▓
▓▓░░░░░░░░░░● ░░      ░░░░░░░░░░  ● ░░░░    ░░░░  ░░      ░░░░░░    ▲       ░░▓▓
▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓

*/


    20,       // milling
    10,20,  // diamond $
    RAINHAILSHINE,          // rain


    2,7,8,10,9,       // randomiser[level]
    15,20,25,25,25,
    0x78,0x78,0x78,0x78,0x78,

    CAVEDEF_PARALLAX,          // water, ?, ?
    STEEL,DIRT,

    3,  CH_BLANK,       100,100,100,100,100,
        CH_BOULDER,     40,40,40,40,40,
        CH_FIREFLY_0,   2,2,2,2,2,


    0x40 + CH_BRICKWALL,1,5,2,12,
    0x40 + CH_BRICKWALL,28,3,2,11,
    0x40 + CH_AMOEBA_0,19,19,2,2,

    DIAMOND, 4, 4,
    DIAMOND, 4, 12,
    DIAMOND, 4, 18,
    DIAMOND, 34, 2,
    DIAMOND, 34, 10,
    DIAMOND, 34, 20,

    CH_DOORCLOSED, 39,5,          // exit
    CH_ROCKFORD_BIRTH, 20,1,      // entry

    0xFF,

    // EXTRAS
            // LEVEL 0
    0xFF,   // LEVEL 1
    0xFF,   // LEVEL 2
    0xFF,   // LEVEL 3
    0xFF,   // LEVEL 4
    0xFF,

    'D','A','R','W','I','N',NEW_LINE,
    'A','W','A','R','D','S',END_STRING
};



const unsigned char caveR[]= {

/*

▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓
▓▓  ░░░░░░░░● ░░  ░░░░  ░░  ░░    ░░      ░░  ● ░░░░░░● ░░  ░░        ░░● ░░  ▓▓
▓▓● ░░░░● ░░░░  ●     ░░●   ░░    ░░░░░░░░░░░░  ░░░░      ● ░░░░● ● ● ░░  ░░░░▓▓
▓▓  ░░░░░░░░░░░░● ░░  ░░  ░░░░●   ░░  ░░R ●   ●   F   ░░░░░░● ░░░░    ░░      ▓▓
▓▓░░● ░░░░░░░░░░F ░░░░  ░░░░░░░░  ░░  ░░  ░░░░●     ░░░░░░░░●   ● ░░▲ ░░░░● ░░▓▓
X ░░  ●     ░░░░  ● ░░    ░░░░● ● ● ░░░░░░░░● ░░●     ░░▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▓▓
▓▓  ░░● ▲ ░░░░░░░░░░        ░░  ░░  ░░░░  ● ░░    ░░░░░░  ░░● ░░      ░░●   ░░▓▓
▓▓▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒  ░░● ░░░░● ░░●     ░░░░● ░░  ░░  F   ░░  ░░░░░░░░░░▓▓
▓▓░░  ░░░░  ░░░░░░░░  ░░  ░░  ░░░░░░● ● ░░░░  ░░░░  ● ░░░░  ░░░░●     ░░● ● ░░▓▓
▓▓░░  ░░●       ░░░░░░░░░░●   ░░░░░░    ●   ●     ░░░░░░  ● ● ░░● ░░░░░░░░░░● ▓▓
▓▓░░  ░░░░░░░░  ● ░░░░░░  ● ░░  ░░░░░░● F     ●       ░░  ░░  ░░  ░░░░░░● ░░● ▓▓
▓▓░░    ● ░░      ░░░░  ░░░░  ░░● ░░●   ░░  ●   ●   ░░  ●   ● ●   ░░● ░░░░  ░░▓▓
▓▓    ░░░░░░  ░░● ░░░░● ░░░░  ░░░░● ░░░░  ░░● ░░  ● ●   ░░    ░░░░  ▲ ●   ░░░░▓▓
▓▓░░● ░░  ● ░░░░● ░░░░  ░░●   ░░░░░░● ░░░░░░░░  ░░  ░░░░▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▓▓
▓▓  ░░● ░░░░F ●   ░░░░  ● ░░░░● ░░● ░░● ● ░░  ░░  ░░● ░░░░    ░░░░F ░░░░  ● ░░▓▓
▓▓▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒░░░░░░░░░░░░░░░░░░  ░░  ░░░░●     ░░░░● ░░░░░░░░░░░░▓▓
▓▓  ░░░░● ░░  ░░░░● ░░● ▲ ● ░░░░  ░░░░░░●   ░░●     ● ░░░░░░  ░░░░░░░░● ░░●   ▓▓
▓▓    ● ░░  ░░  ░░░░░░● ● ● ▞▞▞▞▞▞▞▞▞▞▞▞▞▞▞▞  ░░░░░░● ░░░░● ░░● ░░●   ● ░░░░░░▓▓
▓▓    ●   ░░░░  ● ● ░░░░  ░░    ● ░░░░▲ ░░░░● ░░  ░░● ░░░░● ░░● ░░░░░░░░░░░░  ▓▓
▓▓░░░░  ●     ░░  ░░░░  ░░●   ● ░░░░● ░░░░    ░░░░  ░░░░░░░░  ● ● ●   ● ●     ▓▓
▓▓    ░░░░░░  ░░  ░░    ░░░░░░  ░░  ●   ░░░░░░░░░░░░●   ●   ░░● ░░  ░░░░░░░░  ▓▓
▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓

*/

    20,       // milling
    10,20,  // diamond $
        4,          // rain


    1,10,4,16,6,       // randomiser[level]
    5,5,5,4,5,       // diamonds[level]
    0x78,0x6E,0x64,0x5A,0x50,       // time[level]

    CAVEDEF_PARALLAX,
    STEEL,DIRT,

    3,  CH_BLANK,   90,95,100,105,110,
        CH_BOULDER, 50,55,50,65,70,
        CH_FIREFLY_0,   2,4,6,8,10,
        


    DIAMOND,4,6,
    DIAMOND,0x22,4,
    DIAMOND,0x22,12,



    0x40 + CH_BRICKWALL,1,7,2,12,
    0x40 + CH_BRICKWALL,1,15,2,12,
    0x40 + CH_BRICKWALL,28,5,2,11,
    0x40 + CH_BRICKWALL,28,13,2,11,
    0x40 + CH_MAGICWALL,14,17,2,8,

    DIAMOND,12,16,
    CH_BLANK,14,18,
    DIAMOND,19,18,

    0x40 + CH_DIRT,14,15,2,8,

    CH_DOORCLOSED,39,6,                 // outbox
    CH_ROCKFORD_BIRTH,20,3,                 // inbox
    0xFF,

     // EXTRAS
            // LEVEL 0
    0xFF,   // LEVEL 1
    0xFF,   // LEVEL 2
    0xFF,   // LEVEL 3
    0xFF,   // LEVEL 4
    0xFF,

   'M','A','G','I','C',END_STRING

};





const unsigned char caveB[]= {


/*

▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓
▓▓▲ ● ▲ ▲ ▲ ● ▲ ▲ ▲ ● ▲ ● ● ● ● ● ▲ ● ● ● ▲ ● ▲ ▲ ● ▲ ▲ ▲ ▲ ● ▲ ● ▲ ● ● ▲ ▲ ● ▓▓
▓▓▲ ▲ ● ▲ ● ● ▲ ● ▲ ● ● ▲ ● ▲ ● ● ● ▲ ● ● ▲ ▲ ▲ ▲ ● ● ▲ ▲ ● ▲ ● ● ▲ ● ▲ ▲ ● ▲ ▓▓
▓▓░░● ▲ ● ● ▲ ● ● ● ▲ ● ● ▲ ● ░░● ▲ ▲ ▲ ● ● ▲ ▲ ▲ ▲ ● ● ● ● ▲ ● ▲ ● ▲ ● ● ● ▲ ▓▓
▓▓▲ ▲ ░░● ● ▲ ● ▲ ● ▲ ● ▲ ▲ ● ● ● ● ● ● ● ● ● ● ▲ ▲ ● ▲ ● ● ● ● ▲ ▲ ● ● ● ● ▲ ▓▓
▓▓▲ ● ▲ ░░● ● ● ▲ ● ▲ ▲ ● ▲ ▲ ▲ ▲ ● ● ▲ ● ● ▲ ● ● ▲ ● ▲ ● ● ● ● ▲ ● ▲ ▲ ● ▲ ● ▓▓
▓▓▲ ▲ ● ● ▲ ● ▲ ▲ ● ▲ ▲ ● ● ▲ ▲ ▲ ● ▲ ▲ ▲ ▲ ▲ ▲ ● ● ● ▲ ● ● ● ● ▲ ● ● ● ▲ ● ▲ ▓▓
▓▓● ▲ ● ● ▲ ▲ ▲ ▲ ▲ ● ▲ ▲ ▲ ● ● ▲ ● ▲ ● ▲ ● ▲ ● ● ▲ ● ● ● ● ● ● ● ● ▲ ▲ ▲ ▲ ▲ ▓▓
▓▓● ▲ ▲ ● ▒▒▒▒▒▒▒▒▒▒▒▒▒▒░░▒▒▒▒▒▒▒▒▒▒● ● ▲ ● ● ● ● ▒▒▒▒▒▒▒▒▒▒▒▒░░▒▒▒▒▒▒▒▒▒▒▒▒▲ ▓▓
▓▓● ● ● ▲ ▒▒                      ▒▒░░● ● ● ● ▲ ● ▒▒                      ▒▒● ▓▓
▓▓░░● ● ● ▒▒  R X                 ▒▒▲ ● ● ▲ ● ● ● ▒▒                      ▒▒▲ ▓▓
▓▓● ▲ ▲ ● ▒▒                      ▒▒▲ ● ▲ ● ▲ ▲ ● ▒▒                      ▒▒▲ ▓▓
▓▓● ● ● ▲ ▒▒                      ▒▒▲ ▲ ▲ ● ▲ ● ▲ ▒▒                      ▒▒▲ ▓▓
▓▓▲ ▲ ▲ ▲ ▒▒                      ▒▒● ▲ ▲ ● ▲ ● ● ▒▒                      ▒▒● ▓▓
▓▓● ● ● ▲ ▒▒                      ▒▒▲ ● ▲ ▲ ● ● ▲ ▒▒                      ▒▒▲ ▓▓
▓▓▲ ▲ ▲ ▲ ▒▒                      ▒▒● ● ● ▲ ● ▲ ● ▒▒                      ▒▒● ▓▓
▓▓● ● ● ● ▒▒                      ▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒                      ▒▒● ▓▓
▓▓▲ ● ● ● ▒▒                                                              ▒▒▲ ▓▓
▓▓▲ ▲ ░░▲ ▒▒                      ▒▒● ▲ ▲ ● ● ● ● ▒▒                      ▒▒● ▓▓
▓▓░░● ▲ ● ▒▒                      ▒▒░░░░● ● ▲ ░░● ▒▒                      ▒▒▲ ▓▓
▓▓▲ ▲ ● ● ▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒● ● ▲ ░░● ● ● ▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▲ ▓▓
▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓

*/

    20,       // milling
    5,10,  // diamond $
    0,          // rain

    0x64,0x89,0x8C,0xFB,0x33,       // randomiser[level]
    0x4B,0x4B,0x50,0x55,0x5A,            // diamonds
    0x96,0x96,0x82,0x82,0x78,

    CAVEDEF_PARALLAX,  // NO PARALLAX
    STEEL,DIRT,

    2,  CH_BOULDER, 0xF0, 0xF0, 0xF0, 0xF0, 0xF0,
        DIAMOND, 0x78, 0x78, 0x78, 0x78, 0x78,

    0x80+CH_BRICKWALL,5,8,13,13,0,
    0x80+CH_BRICKWALL,25,8,13,13,0,
    0x40+CH_BRICKWALL,17,16,2,9,
    0x40+CH_BLANK,17,17,2,9,


    CH_DIRT,12,8,
    CH_DIRT,31,8,

    CH_DOORCLOSED,8,10,
    CH_ROCKFORD_BIRTH,7,10,

    0xFF,

    // EXTRAS
            // LEVEL 0
    0xFF,   // LEVEL 1
    0xFF,   // LEVEL 2
    0xFF,   // LEVEL 3
    0xFF,   // LEVEL 4
    0xFF,

    'S','I','L','V','E','R',NEW_LINE,
    'R','A','I','N',END_STRING
};



const unsigned char caveL[]= {


/*

▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓
▓▓░░░░░░░░░░░░░░░░░░░░░░░░R ░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░▓▓
▓▓▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒  ▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░▓▓
▓▓▒▒░░░░░░░░▲ ░░░░░░░░░░░░░░░░░░░░░░░░░░▲ ▒▒░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░▓▓
▓▓▒▒░░▒▒  ▒▒░░▒▒▒▒▒▒▒▒▒▒▒▒  ▒▒▒▒▒▒▒▒▒▒▒▒░░▒▒░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░▓▓
▓▓▒▒░░▒▒F ▒▒░░▒▒▲ ░░░░░░░░░░░░░░░░░░▲ ▒▒░░▒▒░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░▓▓
▓▓▒▒░░▒▒F ▒▒░░▒▒░░▒▒▒▒▒▒▒▒  ▒▒▒▒▒▒▒▒░░▒▒░░▒▒░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░▓▓
▓▓▒▒░░▒▒F ▒▒░░▒▒░░▒▒▲ ░░░░░░░░░░▲ ▒▒░░▒▒░░▒▒░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░▓▓
▓▓▒▒░░▒▒F ▒▒░░▒▒░░▒▒░░▒▒▒▒  ▒▒▒▒░░▒▒░░▒▒░░▒▒░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░▓▓
▓▓▒▒░░▒▒F ▒▒  ▒▒  ▒▒  ▒▒      ▒▒  ▒▒  ▒▒  ▒▒░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░▓▓
▓▓▒▒░░▒▒F ▒▒F ▒▒F ▒▒F ▒▒F F F ▒▒F ▒▒F ▒▒F ▒▒░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░▓▓
▓▓▒▒░░▒▒F ▒▒  ▒▒  ▒▒  ▒▒      ▒▒  ▒▒  ▒▒  ▒▒░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░▓▓
▓▓▒▒░░▒▒F ▒▒░░▒▒░░▒▒░░▒▒▒▒▒▒▒▒▒▒░░▒▒░░▒▒░░▒▒░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░▓▓
▓▓▒▒░░▒▒F ▒▒░░▒▒░░▒▒▲ ░░░░░░░░░░▲ ▒▒░░▒▒░░▒▒░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░▓▓
▓▓▒▒░░▒▒▲ ▒▒░░▒▒░░▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒░░▒▒░░▒▒░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░▓▓
▓▓▒▒░░▒▒▲ ▒▒░░▒▒▲ ░░░░░░░░░░░░░░░░░░▲ ▒▒░░▒▒░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░▓▓
▓▓▒▒░░▒▒▲ ▒▒░░▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒░░▒▒░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░▓▓
▓▓▒▒░░▒▒▲ ▒▒▲ ░░░░░░░░░░░░░░░░░░░░░░░░░░▲ ▒▒░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░▓▓
▓▓▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░▓▓
▓▓░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░▓▓
▓▓░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░XX
▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓


*/

    20,       // mililng
    25,0x3C,  // diamond $
    0,          // rain

    60,71,82,91,101,       // randomiser[level]
    12,12,12,12,12,
    0x96,0x82,0x78,0x6E,0x64,

    CAVEDEF_PARALLAX,
    STEEL,DIRT,

    1,  CH_BOULDER, 0, 10, 20, 30, 40,


//    FILLRECT+DIRT,1,1,22,18, CH_DIRT,
//    FILLRECT+CH_BRICKWALL,1,2,21,17,CH_DIRT,

#define INSTANT 0x80

    
    RECT + CH_BRICKWALL, XY(1,2), SIZE(21, 17),
    FILLRECT + CH_DIRT, 2,3,10,INSTANT+15,CH_DIRT,
    FILLRECT + CH_DIRT, 12,3,9,INSTANT+15,CH_DIRT,



    0x40 + DIAMOND,5,2,3,17,
    0x40 + DIAMOND,21,2,5,17,

    FILLRECT+0,5,9,16,3,CH_FIREFLY_0,

    0xC0 + CH_BRICKWALL,1,2,21,17,

    CH_BLANK,13,2,
    0xC0 + CH_BRICKWALL,7,4,13,13,

    CH_BLANK,13,4,
    0xC0 + CH_BRICKWALL,9,6,9,9,
    CH_BLANK,13,6,
    0xC0 + CH_BRICKWALL,11,8,5,5,
    CH_BLANK,13,8,
    FILLRECT+CH_BRICKWALL,3,4,3,15,FIREFLY,
    CH_BLANK,4,4,
    0x40 + DIAMOND,4,14,4,4,

    CH_DOORCLOSED,0x27,20,     // exit
    CH_ROCKFORD_BIRTH,13,1,     // entry
    0xFF,

    // EXTRAS
            // LEVEL 0
    0xFF,   // LEVEL 1
    0xFF,   // LEVEL 2
    0xFF,   // LEVEL 3
    0xFF,   // LEVEL 4
    0xFF,

    'A','M','A','Z','E',END_STRING
};



const unsigned char caveM[]= {

/*

▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓
▓▓░░░░● ▲   ░░░░●   ▒▒●   ● ▲ ░░    ░░● ▒▒  ● ● ▲ ● ●       ▒▒░░● ░░▲     ● ● ▓▓
▓▓    ● ░░░░  ░░░░░░▒▒░░░░F ░░● ░░░░    ▒▒        ░░  ● ░░░░▒▒● ● ░░░░  ░░  ░░▓▓
▓▓░░    ░░● ░░●   ░░▒▒● ● ● ░░░░░░    ░░▒▒● ░░●     ░░░░  ● ▒▒░░  ● ░░░░● ░░● ▓▓
▓▓  ░░░░░░  ● ● ░░░░▒▒●     ░░● ░░░░●   ▒▒● ░░░░░░░░  ░░░░● ▒▒● ░░●       ● ░░▓▓
▓▓░░  ● ● ● ░░  ● ░░▒▒░░●   ●     ● ░░  ▒▒● ░░░░░░░░  ● F ● ▒▒● ░░  ░░░░  ░░  ▓▓
▓▓░░● ░░    ░░● ░░░░▒▒● ░░●   ░░●     ░░▒▒● ░░░░░░  ░░░░░░● ▒▒● ● ● ● ●   ● ● ▓▓
▓▓      ░░  ● ░░░░░░▒▒    ● ●   ● ● ░░● ▒▒░░●   ░░● ░░● ● ● ▒▒● ░░●   ░░● ░░▒▒▓▓
▓▓F ░░░░  ░░░░●   ░░▒▒  ░░░░● ░░● ● ●   ▒▒░░●       ● ░░░░░░▒▒● ░░● ░░░░● ▒▒░░▓▓
▓▓● ● ░░░░▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒● ▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒░░▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒░░░░▒▒●   ▓▓
▓▓  ● ░░● ● ░░      ░░  ░░●     ● ░░░░░░░░● ░░░░░░  ░░░░● ░░░░●     ● ▒▒● ●   ▓▓
▓▓  ● ░░░░░░● ● ●     ░░  ░░░░  ● ░░░░  ● ░░░░  ░░●   ░░░░░░  ●   ░░▒▒● ░░░░░░▓▓
▓▓░░  ● ░░● ░░F ░░● ░░░░    ░░░░░░░░●   ░░░░  ░░░░░░● ● ● ░░● ● ● ▒▒●   ● ░░● ▓▓
▓▓░░░░░░░░  ░░  ● ●   ● ▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒░░● ● ▒▒  ░░●       ▓▓
▓▓  ░░░░●     ░░░░░░░░  ● ░░░░● ░░  ░░░░●   ● ░░░░░░░░░░  ░░● ▒▒░░●           ▓▓
▓▓░░  ● ░░░░░░  ░░  ● ░░    ░░    ●     ░░  ●   ●       ● ░░▒▒●   ● ░░  ░░  X ▓▓
▓▓●   ░░░░    ● ░░  ● ░░░░●   ░░  ●   ● ●   ░░░░░░●   ░░● ▒▒  ● ● ●   ░░  ● ░░▓▓
▓▓░░░░░░● ░░  ░░░░● ░░░░░░░░● ░░░░  ● ● ░░░░● ░░● ░░░░░░▒▒● ░░● ░░● ░░●   ● ░░▓▓
▓▓░░░░●   ░░● ░░● ░░F ░░░░  ● ░░  ░░●   R ● ● ● ░░░░░░  ● ● ░░░░● ░░░░    ░░  ▓▓
▓▓● ●   ● ░░        ░░● ░░● ● ░░░░░░● ░░░░░░● ░░    ░░● ░░░░●   ░░    ▲ ● ● ● ▓▓
▓▓░░  ░░▲ ● ● ░░●       ● ░░      ░░░░░░░░  ●   ░░░░● ● ● ●   F ░░● ░░● ░░  ● ▓▓
▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓

*/

    20,       // milling
    0x32,50,  // diamond $
    4,          // rain


    41,4,0x66,0x97,0x64,       // randomiser[level]
    6,6,6,6,6,
    0x78,0x78,0x96,0x96,0xF0,

    CAVEDEF_PARALLAX,
    STEEL,DIRT,

    4,  CH_BLANK,   80,100,120,140,160,
        CH_BOULDER, 20,30,40,50,60,
        CH_FIREFLY_0,   2,3,4,5,6,
        DIAMOND, 25,20,15,10,5,

    0x40 + CH_BRICKWALL,10,1,4,9,
    0x40 + CH_BRICKWALL,20,1,4,9,
    0x40 + CH_BRICKWALL,30,1,4,9,
    0x40 + CH_BRICKWALL,9,20,0,9,
    0x40 + CH_BRICKWALL,12,13,2,17,
    0x40 + CH_BRICKWALL,5,9,2,9,
    0x40 + CH_BRICKWALL,15,9,2,9,
    0x40 + CH_BRICKWALL,25,9,2,9,
    0x40 + CH_BRICKWALL,28,17,1,11,

    DIAMOND,4,1,
    DIAMOND,14,1,
    DIAMOND,24,1,
    DIAMOND,0x22,1,
    DIAMOND,4,20,
    DIAMOND,0x23,19,

    CH_DOORCLOSED,0x26,15,     // exit
    CH_ROCKFORD_BIRTH,20,18,     // entry

    0xFF,

    // EXTRAS
            // LEVEL 0
    0xFF,   // LEVEL 1
    0xFF,   // LEVEL 2
    0xFF,   // LEVEL 3
    0xFF,   // LEVEL 4
    0xFF,

    'C','A','P','P','E','D',NEW_LINE,
    'I','N',' ','Q','U','I','R','K',END_STRING
};



const unsigned char caveS[]= {

/*

▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓
▓▓░░░░░░░░░░▲ ░░░░░░░░●       ░░  ░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░  ● ░░░░░░░░▓▓
▓▓░░░░  ░░░░░░  ░░░░● ● ░░░░░░░░●       ● ░░░░░░░░● ░░  ░░░░░░░░░░░░● ● ● ░░░░▓▓
▓▓● ░░  ░░  ▲ ● ░░● ▒▒● ░░░░▒▒░░▲ ░░▒▒  ░░░░▒▒● ░░░░░░  ● ░░░░  F ░░  ░░● ░░  ▓▓
▓▓░░▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒  ▒▒░░░░● ▒▒▲ ░░░░▒▒░░░░░░░░● ░░░░░░    ░░░░░░░░  ░░▓▓
▓▓░░● ░░●   ● ░░  ● ▒▒  ░░░░▒▒● ● ░░▒▒░░● ░░▒▒● ░░░░░░●   ░░░░░░░░░░░░░░● ●   ▓▓
▓▓░░●   ● ░░░░░░░░● ▒▒  ░░  ▒▒░░░░░░▒▒░░░░● ▒▒░░● ●   ● ▲ ● ░░░░░░● ░░● ▲ ●   ▓▓
▓▓░░  ● ░░● ● ░░░░● ▒▒░░  ░░▒▒░░░░░░▒▒░░▲ ░░▒▒░░░░░░░░░░░░░░░░░░░░░░  ░░░░● ░░▓▓
▓▓  ▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒░░▒▒  ● ● ▒▒░░░░● ▒▒  ░░● ░░  ░░● ░░  F ░░░░    ● ░░▓▓
▓▓░░░░░░░░░░░░░░░░░░▒▒● ░░  ▒▒░░● ● ▒▒● ░░░░▒▒  ░░░░░░░░░░  ░░    ░░░░░░░░░░░░▓▓
▓▓░░● ░░░░▲ ░░░░░░● ▒▒░░▲ ░░▒▒░░▲ ░░▒▒░░░░░░▒▒  ░░●   ░░░░  ░░░░░░░░░░░░    ░░▓▓
▓▓░░● ░░░░  ░░▲     ▒▒░░░░  ▒▒● ● ░░▒▒  ● ░░▒▒░░● ░░● ● ░░  ░░  ░░░░▲ ░░  ░░░░▓▓
▓▓░░▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒● ▒▒░░░░░░▒▒● ● ░░▲ ● ░░░░░░░░░░░░░░░░●   ░░▓▓
▓▓●   ● ░░░░  ● ░░░░▒▒░░░░░░▒▒  ░░● ▒▒░░░░● ▒▒● ● ░░  ░░░░░░░░  F ░░░░● ░░░░▲ ▓▓
▓▓░░░░░░  ░░  ░░░░░░▒▒░░░░  ▒▒● ░░░░▒▒░░● ░░▒▒░░░░░░▲   ●   ░░    ░░●   ● ░░░░▓▓
▓▓░░░░░░    ░░    ● ▒▒● ░░░░▒▒● ▲ ░░▒▒░░░░░░▒▒●   ● ░░● ░░░░░░░░░░░░● ░░░░░░░░▓▓
▓▓  ▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒  ▒▒░░░░░░▒▒░░● ░░▒▒  ● ░░░░● ░░░░░░● ░░░░░░░░░░░░░░▓▓
▓▓  ▲ ░░  ● ▲ ░░░░░░▒▒░░● ░░▒▒░░░░● ▒▒░░● ░░▒▒● ░░●   ░░░░░░░░░░● ▲   ░░● ░░░░▓▓
▓▓░░░░R ● ░░░░░░    ▒▒░░░░░░▒▒● ░░░░▒▒░░░░░░▒▒░░░░░░░░░░░░● ░░░░░░  ░░  ●   ▲ ▓▓
▓▓● ░░░░  ░░  ●   ░░▒▒░░● ▲ ▒▒░░░░● ▒▒░░● ░░▒▒░░░░░░░░▲   ░░● ░░  ░░░░░░░░░░░░▓▓
▓▓●   ● ░░  ● ░░░░░░▒▒░░  ● ▒▒░░░░● ▒▒● ░░● ▒▒░░░░░░░░░░░░░░░░░░  ░░░░░░░░░░  X 
▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓

*/

    20,       // milling
    20,0,  // diamond $
    4,          // rain

    70,0x3C,2,0x3B,0x66,       // randomiser[level]
    19,19,14,16,21,
    0xB4,0xAA,0xA0,0xA0,0xA0,

    CAVEDEF_PARALLAX,
    STEEL,DIRT,

    3,  CH_BLANK,   60,60,60,60,60,
        CH_BOULDER, 50,50,50,50,50,
        DIAMOND, 9,9,9,9,9,
        

    0x40 + CH_BRICKWALL,10,3,4,18,
    0x40 + CH_BRICKWALL,14,3,4,18,
    0x40 + CH_BRICKWALL,18,3,4,18,
    0x40 + CH_BRICKWALL,22,3,4,18,
    0x40 + CH_BRICKWALL,2,4,2,11,
    0x40 + CH_BRICKWALL,2,8,2,11,
    0x40 + CH_BRICKWALL,2,12,2,15,
    0x40 + CH_BRICKWALL,2,16,2,11,

    0x80 + CH_DIRT,30,2,4,4,0,


    CH_FIREFLY_0,0x20,3,
    0x80 + CH_DIRT,30,7,4,4,0,
    CH_FIREFLY_0,0x20,8,
    0x80 + CH_DIRT,30,12,4,4,0,
    CH_FIREFLY_0,0x20,13,

    CH_DOORCLOSED,0x27,20,     // exit
    CH_ROCKFORD_BIRTH,3,18,     // entry

    0xFF,

    // EXTRAS
            // LEVEL 0
    0xFF,   // LEVEL 1
    0xFF,   // LEVEL 2
    0xFF,   // LEVEL 3
    0xFF,   // LEVEL 4
    0xFF,

    'U','N','L','O','V','E','D',END_STRING
};


const unsigned char caveK[]= {

/*

▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓
▓▓░░░░░░░░░░░░░░● ░░XX░░░░░░░░░░● ░░R ░░o ░░░░░░░░░░░░░░░░░░● ░░● ░░░░● ░░░░░░▓▓
▓▓░░░░░░● ░░░░░░░░░░░░░░░░░░● ░░░░░░░░░░░░● ░░░░░░░░● ░░░░░░░░░░░░● ░░░░░░░░░░▓▓
▓▓░░░░░░░░░░░░░░● ● ░░░░░░● ░░░░● ░░░░░░░░● ░░░░░░░░░░░░░░░░░░░░● ● ● ░░░░░░░░▓▓
▓▓░░░░░░░░░░░░░░░░░░░░● ● ░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░● ░░░░▓▓
▓▓░░░░● ░░░░● ● ░░░░░░░░░░░░░░░░● ░░░░░░░░░░░░░░░░░░░░░░░░░░░░● ░░░░░░░░░░░░░░▓▓
▓▓● ● ░░░░░░░░░░░░● ░░░░░░░░░░░░░░░░░░░░░░░░● ░░░░░░● ░░░░● ░░● ░░░░░░░░░░● ░░▓▓
▓▓● ░░░░░░░░░░░░░░● ░░░░░░░░░░░░● ░░░░░░░░░░░░░░░░░░░░░░░░● ░░● ░░░░░░░░░░░░░░▓▓
▓▓░░░░░░░░░░░░░░░░░░● ░░░░● ░░● ░░░░● ░░░░░░● ░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░▓▓
▓▓░░░░░░░░░░░░░░● ░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░● ░░░░● ░░░░░░░░░░░░● ▓▓
▓▓░░░░░░░░● ░░● ░░░░░░░░░░░░░░░░░░░░░░░░░░● ░░░░░░░░░░░░░░░░● ░░░░● ░░░░░░░░░░▓▓
▓▓● ░░░░● ░░░░░░● ● ░░░░░░░░░░░░● ░░░░● ░░░░░░● ░░● ░░░░░░░░░░░░░░░░░░● ● ░░░░▓▓
▓▓● ░░░░░░● ░░● ░░● ░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░● ░░░░░░░░▓▓
▓▓░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░● ● ● ░░░░░░░░░░● ░░░░░░░░░░░░░░▓▓
▓▓░░░░░░● ● ░░░░░░░░░░░░░░░░● ░░░░░░● ● ● ░░░░░░░░● ░░░░░░░░░░░░░░● ░░░░● ░░● ▓▓
▓▓░░░░● ░░░░░░░░░░░░░░░░● ● ● ● ░░● ░░● ░░░░░░░░░░░░░░░░● ░░░░░░░░░░░░░░░░● ░░▓▓
▓▓░░░░░░░░▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒░░░░░░░░▓▓
▓▓● ░░░░● B B B B B B B B B B B B B B B B B B B B B B B B B B B B B B ░░░░░░░░▓▓
▓▓░░░░░░● ● ● ● ● ● ● ● ● ● ● ● ● ● ● ● ● ● ● ● ● ● ● ● ● ● ● ● ● ● ● ░░░░░░░░▓▓
▓▓● ░░● ░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░▓▓
▓▓░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░▓▓
▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓


*/

    20,       // milling
    5,8,  // diamond $
    7,          // rain

    80,1,2,3,4,       // randomiser[level]
    0x32,0x37,0x3C,0x46,0x50,
    0xA0,0x9B,0x96,0x91,0x8C,

    CAVEDEF_PARALLAX,
    STEEL,DIRT,

    1,  CH_BOULDER, 40,40,40,40,40,



    CH_AMOEBA_0,20,1,

    0x80 + CH_BRICKWALL,5,16,30,2,CH_BLANK,
    0x40 + CH_BUTTERFLY_0,5,17,2,30,
    0x40 + CH_BOULDER,5,18,2,30,
    0xC0 + CH_DIRT,5,19,30,2,

    CH_DOORCLOSED,10,1,         // exit
    CH_ROCKFORD_BIRTH,18,1,         // entry
    0xFF,

    // EXTRAS
            // LEVEL 0
    0xFF,   // LEVEL 1
    0xFF,   // LEVEL 2
    0xFF,   // LEVEL 3
    0xFF,   // LEVEL 4
    0xFF,

    'S','T','U','T','T','E','R',END_STRING
};



const unsigned char caveT[]= {

/*

▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓
▓▓░░░░R ░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░▓▓
▓▓░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░▓▓
▓▓░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░▓▓
▓▓░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░▓▓
▓▓░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░F ░░F ░░F ░░F ░░F ░░F ░░░░░░░░░░░░▓▓
▓▓░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░● ░░● ░░● ░░● ░░● ░░● ░░░░░░░░░░░░▓▓
▓▓░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░▓▓
▓▓░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░▓▓
▓▓░░░░░░░░░░░░░░░░░░░░B ░░  ░░  ░░  ░░  ░░  ░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░▓▓
▓▓░░░░░░░░░░░░░░░░░░░░  ░░  ░░  ░░  ░░  ░░  ░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░▓▓
▓▓░░░░░░░░░░░░░░░░░░░░  ░░B ░░  ░░  ░░  ░░  ░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░▓▓
▓▓░░░░░░░░░░░░░░░░░░░░  ░░  ░░  ░░  ░░  ░░  ░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░▓▓
▓▓░░░░░░░░░░░░░░░░░░░░  ░░  ░░B ░░  ░░  ░░  ░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░▓▓
▓▓░░░░░░░░░░░░░░░░░░░░  ░░  ░░  ░░  ░░  ░░  ░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░▓▓
▓▓░░░░░░░░░░░░░░░░░░░░  ░░  ░░  ░░B ░░  ░░  ░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░▓▓
▓▓░░░░░░░░░░░░░░░░░░░░  ░░  ░░  ░░  ░░  ░░  ░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░▓▓
▓▓░░░░░░░░░░░░░░░░░░░░  ░░  ░░  ░░  ░░B ░░  ░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░▓▓
▓▓░░░░░░░░░░░░░░░░░░░░  ░░  ░░  ░░  ░░  ░░  ░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░XX
▓▓░░░░░░░░░░░░░░░░░░░░  ░░  ░░  ░░  ░░  ░░B ░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░▓▓
▓▓░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░▓▓
▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓


*/
    20,       // milling
    10,20,  // diamond $
    1,          // rain

    90,80,70,60,50,       // randomiser[level]
    30,0x23,0x28,0x2A,0x2D,
    0x96,0x91,0x8C,0x87,0x82,

    CAVEDEF_PARALLAX,
    STEEL,DIRT,

    1,  CH_BOULDER, 0,5,10,15,20,

    FILLRECT+DIRT,10,8,13,13,0,

    LINE+CH_BUTTERFLY_0,11,9,3, 11,
    0xC0 + CH_DIRT,12,8,3,13,
    0xC0 + CH_DIRT,16,8,3,13,
    0xC0 + CH_DIRT,20,8,3,13,
    LINE+BOULDER,22,6,2,12,
    LINE+CH_FIREFLY_0,22,5,2,12,
    0xC0 + CH_DIRT,23,4,3,4,
    0xC0 + CH_DIRT,27,4,3,4,
    0xC0 + CH_DIRT,31,4,3,4,

    CH_DOORCLOSED, 39,18,             // exit
    CH_ROCKFORD_BIRTH, 3,1,             // entry

    0xFF,

    // EXTRAS
            // LEVEL 0
    0xFF,   // LEVEL 1
    0xFF,   // LEVEL 2
    0xFF,   // LEVEL 3
    0xFF,   // LEVEL 4
    0xFF,

    'A','D','D','I','A','T','E',END_STRING
};




const unsigned char caveG[]= {

/*

▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓
▓▓░░░░      ░░░░░░● ░░● ● ● ░░● ● ● ● ● R ░░  ● ● ● ░░░░  ● ● ● ● ●     ░░░░  ▓▓
▓▓░░▒▒● ░░    ░░░░  ● ░░  ● ░░░░  ░░    ●   ░░● ▒▒░░    ●   ░░    ● ░░░░  ░░  ▓▓
▓▓● ● ▒▒░░░░●       ░░░░░░░░● ░░  ●   ░░● ●   ▒▒░░    ● ● ● ● ░░░░    ●   ░░░░▓▓
▓▓● ░░  ▒▒● ░░● ░░░░░░░░░░● ●   ● ░░░░░░  ● ▒▒    ░░  ░░● ░░  ░░●   ░░░░●   ● ▓▓
▓▓●   ░░● ▒▒        ░░░░░░░░  ● ░░  ░░░░● ▒▒  ●   ● ●   ░░░░░░░░░░  ● ░░  ░░● ▓▓
▓▓●   ░░●   ▒▒░░●   ●   ░░  ● ░░░░░░░░  ▒▒● ● ● ░░      ░░●   ░░  ░░  ● ● ● ░░▓▓
▓▓    ░░░░░░● ▒▒░░● ● ░░  ░░░░░░░░    ▒▒░░    ● ● ░░░░● ░░● ●   ░░  ░░░░░░░░░░▓▓
▓▓░░● ░░░░░░  ● ▒▒░░░░░░●   ●     ● ▒▒● ● ░░  ░░● ░░  ░░● ░░░░░░● ● ● ●   ░░░░▓▓
▓▓●   ░░░░● ░░░░░░▒▒░░░░● ░░░░    ▒▒  ●   ●     ░░░░  ● ░░░░  ● ░░  ● ░░● ░░░░▓▓
▓▓░░░░● ● ●     ● ● ▒▒░░    ░░░░▒▒●   ░░░░● ░░● ░░░░░░░░░░● ● ░░    ● ░░░░●   ▓▓
▓▓● ░░░░░░● ●   ░░  ░░▒▒●   ░░▒▒░░░░● ●   ● ● ░░░░● ░░░░░░      ░░    ●   ●   ▓▓
▓▓░░  ░░● ● ● ░░● ● ●   ░░░░░░░░  ●   ░░● ░░░░░░  ░░    ░░░░  ● ● ░░░░  F ░░░░▓▓
▓▓● ░░░░      ░░░░░░●   ▞▞▞▞▞▞● ░░● ░░░░●       ● ░░  ░░    ░░●   ● ░░░░░░● ● ▓▓
▓▓● ●           ● ░░● ░░  ░░░░● ░░░░░░● ● ● ● ●   ● ░░░░● ░░●       ● ● ░░    ▓▓
▓▓    ●   ● ● ░░    ░░    ●   ░░░░● ● ░░░░░░● ░░  ░░░░  ░░  ░░  ●   ░░● ░░  ░░▓▓
▓▓  ● ● ●     ░░░░░░● ● ● ░░● ● ● ● ░░  ░░  ░░░░●   ● ░░    ░░      ●   ● ●   ▓▓
▓▓    ● ░░  ░░░░░░░░░░● ● ░░  ● ● ● ░░░░● ● ● ●   ░░●   ● ●   ░░░░● ░░  ● ░░░░▓▓
▓▓  ● ░░●         ░░░░░░●   ● ░░● ● ░░░░░░░░        ● ● ░░      ●   ░░░░● ●   ▓▓
▓▓●   ● ● ●   ░░● ░░  ░░●   ● ░░● ░░░░F F ● ● ░░● ░░● ░░░░  ●   ● ░░░░  ░░░░● ▓▓
▓▓░░  ░░░░░░░░  ░░░░░░●   ● ● ● ● ● ░░░░X ░░● ░░░░░░░░░░    ░░  ░░● ░░  ░░● ● ▓▓
▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓


*/

    8,       // milling
    10,20,  // diamond $
    3,          // rain

    54,29,30,31,0x20,       // randomiser[level]
    15,20,20,25,30,
    0x78,0x78,0x78,0x78,0x8C,

    CAVEDEF_PARALLAX,
    STEEL,DIRT,

    3,  CH_BLANK,       100,100,100,100,100,
        CH_BOULDER,     60,65,70,75,80,
        CH_FIREFLY_0,   0,2,2,2,2,


    0x40 +CH_BRICKWALL,2,2,3,10,
    0x40 + CH_BRICKWALL,15,11,1,10,
    0x40 + CH_DIRT,12,12,2,3,
    0x40 + CH_MAGICWALL,12,13,2,3,

    CH_DOORCLOSED, 20,20,
    CH_ROCKFORD_BIRTH, 20,1,

    0xFF,

    // EXTRAS
            // LEVEL 0
    0xFF,   // LEVEL 1
    0xFF,   // LEVEL 2
    0xFF,   // LEVEL 3
    0xFF,   // LEVEL 4
    0xFF,

    'D','O','O','M',NEW_LINE,
    'F','U','N','N','E','L',END_STRING
};



const unsigned char caveU[]= {

/*

▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓
▓▓R ░░░░░░░░● ░░░░● ░░● ░░░░● ░░● ● ░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░▓▓
▓▓░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░● ░░░░░░░░░░░░░░● ░░░░░░░░░░● ░░● X 
▓▓░░● ● ░░● ░░░░░░● ░░░░● ░░░░● ░░░░░░● ░░░░░░░░● ░░● ░░● ● ░░● ● ░░● ● ░░● ░░▓▓
▓▓░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░● ░░░░░░░░● ░░░░░░░░● ● ░░░░● ░░░░░░░░▓▓
▓▓░░░░░░░░░░● ● ░░● ░░● ░░● ● ░░░░● ░░░░░░░░░░● ● ░░░░░░░░░░░░░░░░░░░░░░░░░░░░▓▓
▓▓░░░░● ░░● ░░● ● ● ░░░░● ░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░▓▓
▓▓░░░░░░░░● ░░░░░░░░░░● ● ░░░░░░░░░░● ░░● ░░░░░░░░░░░░░░░░░░░░░░░░● ░░░░░░░░● ▓▓
▓▓░░● ░░░░● ░░▞▞▞▞▞▞▞▞▞▞▞▞░░░░▞▞▞▞▞▞▞▞▞▞▞▞░░░░░░░░░░░░░░░░░░░░● ░░░░░░● ░░░░● ▓▓
▓▓░░● ░░░░░░░░▒▒░░░░░░░░E ░░░░▒▒░░░░░░● ▒▒● ░░░░░░░░░░● ░░● ░░░░░░░░░░░░░░░░░░▓▓
▓▓░░░░● ░░░░░░▒▒░░░░░░░░▒▒░░░░▒▒░░░░░░░░▒▒░░░░░░░░░░● ░░● ░░░░░░░░░░● ● ░░● ░░▓▓
▓▓░░░░░░░░░░● ▒▒░░░░● ░░▒▒░░● ▒▒░░● ░░░░▒▒● ░░░░░░░░░░░░░░░░● ░░░░░░░░● ░░░░░░▓▓
▓▓● ░░● ░░░░░░▒▒░░● ░░░░▒▒● ░░▒▒░░░░░░░░▒▒░░░░░░░░░░░░● ░░░░░░░░░░░░░░░░░░● ░░▓▓
▓▓░░░░░░░░░░░░▒▒░░░░░░░░▒▒░░░░▒▒░░░░░░░░▒▒░░░░● ░░░░░░░░░░● ░░░░░░░░░░░░░░● ░░▓▓
▓▓● ░░░░░░░░░░▒▒░░░░░░░░▒▒● ● ▒▒░░░░● ░░▒▒░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░● ░░▓▓
▓▓░░░░● ░░░░● ▒▒▒▒▒▒▒▒▒▒▒▒░░░░▒▒▒▒▒▒▒▒▒▒▒▒● ░░░░░░● ░░░░░░░░░░░░● ░░░░░░░░● ░░▓▓
▓▓░░░░░░● ░░░░░░░░░░░░░░░░░░░░░░░░░░░░● ░░░░░░░░░░░░░░● ░░░░░░░░● ░░░░░░░░░░░░▓▓
▓▓░░░░░░● ░░░░░░░░░░░░░░● ░░● ● ░░░░░░░░░░░░░░░░░░░░░░░░░░░░● ░░░░░░░░░░░░░░░░▓▓
▓▓░░░░░░░░░░░░░░░░  F ░░░░░░░░░░░░  F ░░░░░░● ░░░░  F ░░░░░░● ● ░░  F ░░░░░░● ▓▓
▓▓░░░░░░░░░░░░░░░░    ░░● ░░░░● ░░    ░░░░░░░░● ░░    ░░● ░░░░░░░░    ░░░░░░░░▓▓
▓▓░░● ░░● ░░░░░░░░░░░░░░░░░░● ░░░░░░░░░░░░● ░░● ░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░▓▓
▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓

*/

    20,       // milling
    10,20,  // diamond $
    1,          // rain

    1,0x78,0x81,0x7E,0x7B,       // randomiser[level]
    12,15,15,15,12,
    0x96,0x96,0x96,0x96,0x96,

    CAVEDEF_PARALLAX,
    STEEL,DIRT,

    1,  CH_BOULDER, 50,50,50,50,50,


    0x80 + CH_DIRT,8,17,4,4,0,

    CH_FIREFLY_0,10,18,
    0xC0 + CH_BRICKWALL,7,8,6,8,

    // 0x40 + CH_BRICKWALL, 7, 8, 4, 8,
    // 0x40 + CH_BRICKWALL, 12, 8, 4, 8,
    // 0x40 + CH_BRICKWALL, 7,15, 2, 6,

    0x40 + CH_MAGICWALL,7,8,2,6,
    0x80 + CH_DIRT,16,17,4,4,0,
    CH_FIREFLY_0,18,18,
    0xC0 + CH_BRICKWALL,15,8,6,8,

    // 0x40 + CH_BRICKWALL, 15, 8, 4, 8,
    // 0x40 + CH_BRICKWALL, 20, 8, 4, 8,
    // 0x40 + CH_BRICKWALL, 15,15, 2, 6,

    0x40 + CH_MAGICWALL,15,8,2,6,
    0x80 + CH_DIRT,24,17,4,4,0,
    CH_FIREFLY_0,26,18,
    0x80 + CH_DIRT,0x20,17,4,4,0,
    CH_FIREFLY_0,0x22,18,

    CH_EASTEREGG, 12, 9,

    CH_DOORCLOSED,0x27,2,     // exit
    CH_ROCKFORD_BIRTH,1,1,     // entry
    0xFF,

    // EXTRAS
            // LEVEL 0
    0xFF,   // LEVEL 1
    0xFF,   // LEVEL 2
    0xFF,   // LEVEL 3
    0xFF,   // LEVEL 4
    0xFF,

    'O','W','L','A','W','K',END_STRING

};



const unsigned char caveH[]= {

/*

▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓
▓▓▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▓▓
▓▓▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▓▓
▓▓▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▓▓
▓▓▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▓▓
▓▓▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▓▓
▓▓▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▓▓                                    ▓▓▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▓▓
▓▓▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▓▓                  ●                 ▓▓▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▓▓
▓▓▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▓▓    R             ░░                ▓▓▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▓▓
▓▓▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▓▓                                    ▓▓▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▓▓
▓▓▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▓▓                                    ▓▓▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▓▓
▓▓▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▓▓                                    ▓▓▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▓▓
▓▓▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▓▓                                    ▓▓▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▓▓
▓▓▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▓▓                                    ▓▓▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▓▓
▓▓▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▓▓                                    ▓▓▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▓▓
▓▓▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▓▓                  B               X ▓▓▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▓▓
▓▓▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▓▓
▓▓▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▓▓
▓▓▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▓▓
▓▓▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▓▓
▓▓▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▓▓
▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓

*/

    16,       // milling
    30,30,  // diamond $
    7,          // rain

    10,11,12,13,14,       // randomiser[level]
    6,6,6,6,6,       // diamonds[level]
    20,20,20,20,20,       // time[level]

    CAVEDEF_PARALLAX|CAVEDEF_OVERVIEW,
    CH_STEELWALL,CH_DIRT,                      // border, fill

    1,  AMOEBA, 5,5,5,5,5,

    0x80+ CH_STEELWALL,10,5,20,12,0,


    
    BUTTERFLY,20,15,
    BOULDER,20,7,
    DIRT,10+10,8,

    INBOX,13,8,                 // entry
    CH_DOORCLOSED,28,15,                 // exit


    0xFF,

    // EXTRAS
            // LEVEL 0
    0xFF,   // LEVEL 1
    0xFF,   // LEVEL 2
    0xFF,   // LEVEL 3
    0xFF,   // LEVEL 4
    0xFF,

    'B','O','N','U','S',END_STRING
};



const unsigned char caveI[]= {

/*

▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓
▓▓● ● ● ● ● ● ● ● ● ● ● ● ● ● ● ● ● ● ● ● ● ● ● ● ● ● ● ● ● ● ● ● ● ● ● ● ● ● ▓▓
▓▓● ● ● ● ● ● ● ● ● ● ● ● ● ● ● ● ● ● ● ● ● ● ● ● ● ● ● ● ● ● ● ● ● ● ● ● ● ● ▓▓
▓▓● ● ● ● ● ● ● ● ● ● ● ● ● ● ● ● ● ● ● ● ● ● ● ● ● ● ● ● ● ● ● ● ● ● ● ● ● ● ▓▓
▓▓● ● ● ● ● ● ● ● ● ● ● ● ● ● ● ● ● ● ● ● ● ● ● ● ● ● ● ● ● ● ● ● ● ● ● ● ● ● ▓▓
▓▓● ● ● ● ● ● ● ● ● ▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓● ● ● ● ● ● ● ● ● ▓▓
▓▓● ● ● ● ● ● ● ● ● ▓▓● F ░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░● ▓▓● ● ● ● ● ● ● ● ● ▓▓
▓▓● ● ● ● ● ● ● ● ● ▓▓R ● F ░░░░░░░░░░░░░░░░░░░░░░░░░░● X ▓▓● ● ● ● ● ● ● ● ● ▓▓
▓▓● ● ● ● ● ● ● ● ● ▓▓▲ ░░● F ░░░░░░░░░░░░░░░░░░░░░░● ░░▲ ▓▓● ● ● ● ● ● ● ● ● ▓▓
▓▓● ● ● ● ● ● ● ● ● ▓▓● ▲ ░░● F ░░░░░░░░░░░░░░░░░░● ░░▲ ● ▓▓● ● ● ● ● ● ● ● ● ▓▓
▓▓● ● ● ● ● ● ● ● ● ▓▓░░● ▲ ░░● F ░░░░░░░░░░░░░░● ░░▲ ● ░░▓▓● ● ● ● ● ● ● ● ● ▓▓
▓▓● ● ● ● ● ● ● ● ● ▓▓░░░░● ▲ ░░● F ░░░░░░░░░░● ░░▲ ● ░░░░▓▓● ● ● ● ● ● ● ● ● ▓▓
▓▓● ● ● ● ● ● ● ● ● ▓▓░░░░░░● ▲ ░░● F ░░░░░░● ░░▲ ● ░░░░░░▓▓● ● ● ● ● ● ● ● ● ▓▓
▓▓● ● ● ● ● ● ● ● ● ▓▓░░░░░░░░● ▲ ░░● F ░░● ░░▲ ● ░░░░░░░░▓▓● ● ● ● ● ● ● ● ● ▓▓
▓▓● ● ● ● ● ● ● ● ● ▓▓░░░░░░░░░░● ▲ ░░● ● ░░▲ ● ░░░░░░░░░░▓▓● ● ● ● ● ● ● ● ● ▓▓
▓▓● ● ● ● ● ● ● ● ● ▓▓░░░░░░░░░░░░● ▲ ░░░░▲ ● ░░░░░░░░░░░░▓▓● ● ● ● ● ● ● ● ● ▓▓
▓▓● ● ● ● ● ● ● ● ● ▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓● ● ● ● ● ● ● ● ● ▓▓
▓▓● ● ● ● ● ● ● ● ● ● ● ● ● ● ● ● ● ● ● ● ● ● ● ● ● ● ● ● ● ● ● ● ● ● ● ● ● ● ▓▓
▓▓● ● ● ● ● ● ● ● ● ● ● ● ● ● ● ● ● ● ● ● ● ● ● ● ● ● ● ● ● ● ● ● ● ● ● ● ● ● ▓▓
▓▓● ● ● ● ● ● ● ● ● ● ● ● ● ● ● ● ● ● ● ● ● ● ● ● ● ● ● ● ● ● ● ● ● ● ● ● ● ● ▓▓
▓▓● ● ● ● ● ● ● ● ● ● ● ● ● ● ● ● ● ● ● ● ● ● ● ● ● ● ● ● ● ● ● ● ● ● ● ● ● ● ▓▓
▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓

*/

    16,       // milling
    10,30,  // diamond $
    0,          // rain

    10,11,12,13,14,       // randomiser[level]
    16,16,16,16,16,       // diamonds[level]
    15,15,15,15,15,       // time[level]

    CAVEDEF_PARALLAX|CAVEDEF_RAINBOW|CAVEDEF_OVERVIEW,
    CH_STEELWALL,CH_BOULDER,

    0,

    0x80+ CH_STEELWALL,10,5,20,12,CH_DIRT,

    0x40 + CH_BOULDER,      1+10,6,3,9,
    0x40 + CH_FIREFLY_0,    2+10,6,3,8,
    0x40 + DIAMOND,      1+10,8,3,8,
    0x40 + CH_BOULDER,      1+10,9,3,7,
    0x40 + CH_BOULDER,      18+10,6,5,9,
    0x40 + DIAMOND,      18+10,8,5,8,
    0x40 + CH_BOULDER,      18+10,9,5,7,

    CH_DOORCLOSED,28,7,
    CH_ROCKFORD_BIRTH,11,7,

    0xFF,

    // EXTRAS
            // LEVEL 0
    0xFF,   // LEVEL 1
    0xFF,   // LEVEL 2
    0xFF,   // LEVEL 3
    0xFF,   // LEVEL 4
    0xFF,

    'D','I','A','G','O','N','A','L',END_STRING
};



// const unsigned char cave19[]= {
// 19,       // cave
// 0xA0,       // milling
// 10,0x00,  // diamond $

// 10,11,12,13,14,       // randomiser[level]
// 50,50,50,50,50,
// 0xE4,20,20,20,20,

// 0,0,CAVEDEF_PARALLAX|CAVEDEF_OVERVIEW,
// CH_BLANK_DUMMY,CH_BLANK_DUMMY,

// 0,0,CH_BOULDER,0x00,
// 0xA0,0xE0,0x20,0x00,
// 0xA0,0xE0,0x20,0x00,
// 0xA0,0xE0,0x20,0x00,
// 0xA0,0xE0,0x20,0x00,
// 0xA0,0xE0,0x20,0x00,



// FILLRECT+STEEL,20-2,10-1,5,5,CH_FIREFLY_0,
// CH_BOULDER,20,11,
// DIRT,20,12,

// //LINE+8,38,10+SHIFTY_19,6,0x0,




// CH_DOORCLOSED,39,3,     // exit
// CH_ROCKFORD_BIRTH,28,3,                 // entry

// CH_BUTTERFLY_1, 16,8,           // butterfly breeds on egg
// CH_BUTTERFLY_1, 17,8,           // butterfly breeds on egg
// CH_BUTTERFLY_1, 18,8,           // butterfly breeds on egg

// // CH_AMOEBA_0, 30, 18+SHIFTY_19,

// 0xFF,
// };




const unsigned char caveJ[]= {

/*

▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓
▓▓▲ ▲ ▲ ▲ ▲ ▲ ▲ ▲ ▲ ▲ ▲ ▲ ▲ ▲ ▲ ▲ ▲ ▲ ▲ ▲ ▲ ▲ ▲ ▲ ▲ ▲ ▲ ▲ ▲ ▲ ▲ ▲ ▲ ▲ ▲ ▲ ▲ ▲ ▓▓
▓▓▲ ▲ ▲ ▲ ▲ ▲ ▲ ▲ ▲ ▲ ▲ ▲ ▲ ▲ ▲ ▲ ▲ ▲ ▲ ▲ ▲ ▲ ▲ ▲ ▲ ▲ ▲ ▲ ▲ ▲ ▲ ▲ ▲ ▲ ▲ ▲ ▲ ▲ ▓▓
▓▓▲ ▲ ▲ ▲ ▲ ▲ ▲ ▲ ▲ ▲ ▲ ▲ ▲ ▲ ▲ ▲ ▲ ▲ ▲ ▲ ▲ ▲ ▲ ▲ ▲ ▲ ▲ ▲ ▲ ▲ ▲ ▲ ▲ ▲ ▲ ▲ ▲ ▲ ▓▓
▓▓▲ ▲ ▲ ▲ ▲ ▲ ▲ ▲ ▲ ▲ ▲ ▲ ▲ ▲ ▲ ▲ ▲ ▲ ▲ ▲ ▲ ▲ ▲ ▲ ▲ ▲ ▲ ▲ ▲ ▲ ▲ ▲ ▲ ▲ ▲ ▲ ▲ ▲ ▓▓
▓▓▲ ▲ ▲ ▲ ▲ ▲ ▲ ▲ ▲ ▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒E ▒▒▒▒▒▒▒▒▒▒▒▒▒▒▲ ▲ ▲ ▲ ▲ ▲ ▲ ▲ ▲ ▓▓
▓▓▲ ▲ ▲ ▲ ▲ ▲ ▲ ▲ ▲ ▒▒░░░░R ░░░░░░░░░░░░░░● ● ● ░░░░░░░░░░▒▒▲ ▲ ▲ ▲ ▲ ▲ ▲ ▲ ▲ ▓▓
▓▓▲ ▲ ▲ ▲ ▲ ▲ ▲ ▲ ▲ ▒▒░░░░░░░░░░░░░░░░░░░░● ● ● ░░░░░░░░░░▒▒▲ ▲ ▲ ▲ ▲ ▲ ▲ ▲ ▲ ▓▓
▓▓▲ ▲ ▲ ▲ ▲ ▲ ▲ ▲ ▲ ▒▒░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░▒▒▲ ▲ ▲ ▲ ▲ ▲ ▲ ▲ ▲ ▓▓
▓▓▲ ▲ ▲ ▲ ▲ ▲ ▲ ▲ ▲ ▒▒░░░░░░░░░░░░░░░░░░░░▞▞▞▞▞▞░░░░░░░░░░▒▒▲ ▲ ▲ ▲ ▲ ▲ ▲ ▲ ▲ ▓▓
▓▓▲ ▲ ▲ ▲ ▲ ▲ ▲ ▲ ▲ ▒▒░░░░░░░░░░░░░░● ░░░░      ░░░░░░░░░░▒▒▲ ▲ ▲ ▲ ▲ ▲ ▲ ▲ ▲ ▓▓
▓▓▲ ▲ ▲ ▲ ▲ ▲ ▲ ▲ ▲ ▒▒░░░░░░░░░░░░░░░░● ░░      ░░░░░░░░░░▒▒▲ ▲ ▲ ▲ ▲ ▲ ▲ ▲ ▲ ▓▓
▓▓▲ ▲ ▲ ▲ ▲ ▲ ▲ ▲ ▲ ▒▒░░░░░░░░░░░░░░░░░░●       ░░░░░░░░░░▒▒▲ ▲ ▲ ▲ ▲ ▲ ▲ ▲ ▲ ▓▓
▓▓▲ ▲ ▲ ▲ ▲ ▲ ▲ ▲ ▲ ▒▒░░░░░░░░░░░░░░░░X ░░▞▞▞▞▞▞░░░░░░░░░░▒▒▲ ▲ ▲ ▲ ▲ ▲ ▲ ▲ ▲ ▓▓
▓▓▲ ▲ ▲ ▲ ▲ ▲ ▲ ▲ ▲ ▒▒░░░░░░░░░░░░░░░░░░░░      ░░░░░░░░░░▒▒▲ ▲ ▲ ▲ ▲ ▲ ▲ ▲ ▲ ▓▓
▓▓▲ ▲ ▲ ▲ ▲ ▲ ▲ ▲ ▲ ▒▒░░░░░░░░░░░░░░░░░░░░      ░░░░░░░░░░▒▒▲ ▲ ▲ ▲ ▲ ▲ ▲ ▲ ▲ ▓▓
▓▓▲ ▲ ▲ ▲ ▲ ▲ ▲ ▲ ▲ ▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▲ ▲ ▲ ▲ ▲ ▲ ▲ ▲ ▲ ▓▓
▓▓▲ ▲ ▲ ▲ ▲ ▲ ▲ ▲ ▲ ▲ ▲ ▲ ▲ ▲ ▲ ▲ ▲ ▲ ▲ ▲ ▲ ▲ ▲ ▲ ▲ ▲ ▲ ▲ ▲ ▲ ▲ ▲ ▲ ▲ ▲ ▲ ▲ ▲ ▓▓
▓▓▲ ▲ ▲ ▲ ▲ ▲ ▲ ▲ ▲ ▲ ▲ ▲ ▲ ▲ ▲ ▲ ▲ ▲ ▲ ▲ ▲ ▲ ▲ ▲ ▲ ▲ ▲ ▲ ▲ ▲ ▲ ▲ ▲ ▲ ▲ ▲ ▲ ▲ ▓▓
▓▓▲ ▲ ▲ ▲ ▲ ▲ ▲ ▲ ▲ ▲ ▲ ▲ ▲ ▲ ▲ ▲ ▲ ▲ ▲ ▲ ▲ ▲ ▲ ▲ ▲ ▲ ▲ ▲ ▲ ▲ ▲ ▲ ▲ ▲ ▲ ▲ ▲ ▲ ▓▓
▓▓▲ ▲ ▲ ▲ ▲ ▲ ▲ ▲ ▲ ▲ ▲ ▲ ▲ ▲ ▲ ▲ ▲ ▲ ▲ ▲ ▲ ▲ ▲ ▲ ▲ ▲ ▲ ▲ ▲ ▲ ▲ ▲ ▲ ▲ ▲ ▲ ▲ ▲ ▓▓
▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓

*/

    CAVEHEADER(16, 30, 1, 0),

    31,32,33,34,35,       // randomiser[level]
    6,6,6,6,6,
    0x2C,0x2C,0x2C,0x2C,0x2C,

    CAVEDEF_PARALLAX|CAVEDEF_OVERVIEW,
    CH_STEELWALL,CH_DOGE_00,
    
    0,

    //---------------------------------------------------------------------------------------------

    0x80+ CH_STEELWALL,10,5,20,12,CH_DIRT,

        RECT + CH_BOULDER, XY(21,6), SIZE(3, 2),

        DRAW_SOLID_RECTANGLE( CH_BLANK, 21, 10, 3, 6, CH_BLANK),
        
        DRAW_LINE( CH_MAGICWALL, 21, 9, 3, LINE_E ),
        DRAW_LINE( CH_MAGICWALL, 21, 13, 3, LINE_E ),
        DRAW_LINE( CH_BOULDER, 18, 10, 3, LINE_SE ),
        CH_EASTEREGG, XY(22, 5),

        CH_DOORCLOSED, XY(19, 13),
        CH_ROCKFORD_BIRTH, XY(13, 6),


    //---------------------------------------------------------------------------------------------
    0xFF,

    // EXTRAS
            // LEVEL 0
    0xFF,   // LEVEL 1
    0xFF,   // LEVEL 2
    0xFF,   // LEVEL 3
    0xFF,   // LEVEL 4
    0xFF,

    'B','E','S','T',NEW_LINE,
    'F','R','I','E','N','D',END_STRING
};



const unsigned char *caveList[] = {

    #if __ENABLE_TRAINER

    caveZPH0,
    caveZPH1,
    caveZPH2  + CAVE_REQUIRES_AMOEBA_PALETTE,
    caveZPH3,
    caveZPH4,


    #else

    caveA,
    caveA3,
    caveA2,
    // caveV + CAVE_REQUIRES_AMOEBA_PALETTE       , // 24 Y *
    // newCaveA                                    , // 00 A *
    // newCaveB                                    , // 01 B *
    // newCaveC    + CAVE_REQUIRES_AMOEBA_PALETTE  , // 03 D *
    // caveB                                       , // 04 E *
    // caveC       + CAVE_REQUIRES_AMOEBA_PALETTE  , // 05 F *
    // caveD       + CAVE_REQUIRES_AMOEBA_PALETTE  , // 06 G *
    // caveE                                       , // 07 H *
    // caveF       + CAVE_REQUIRES_AMOEBA_PALETTE  , // 08 I *
    // caveG                                       , // 09 J *
    // caveH       + CAVE_REQUIRES_AMOEBA_PALETTE  , // 10 K * 
   // caveI                                       , // 11 L *
    // caveJ                                       , // 12 M *
    // caveK       + CAVE_REQUIRES_AMOEBA_PALETTE  , // 13 N *
    // caveL                                       , // 14 O *
    // caveM                                       , // 15 P *
    // caveN                                       , // 16 Q *
    // caveO                                       , // 17 R *
    // caveP                                       , // 18 S *
    // caveQ                                       , // 19 T *  << 580
    // caveR        , // 20 U *
    // caveS        , // 21 V *
    // caveT        , // 22 W *
    // caveU        , // 23 X *
    //newCaveAX + CAVE_REQUIRES_AMOEBA_PALETTE     // 00 A *
    #endif
    
};

const int caveCount = sizeof(caveList) / sizeof(unsigned char *);


//EOF
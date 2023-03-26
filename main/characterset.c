#include "main.h"
#include "animations.h"
#include "attribute.h"
#include "bitpatterns.h"
#include "characterset.h"
#include "colour.h"
#include "random.h"
#include "scroll.h"
#include "defines_cdfj.h"
#include "defines.h"
#include "player.h"



static unsigned char char_parallaxBlank[PIECE_DEPTH];
static unsigned char char_Dust_2[PIECE_DEPTH];
static unsigned char char_DustLeft_1[PIECE_DEPTH];
static unsigned char char_DustRight_1[PIECE_DEPTH];
static unsigned char char_uncover[PIECE_DEPTH];

const unsigned char __CHAR_DOGE_PEBBLE[] = {

    0b11111, // 00 <
    0b00000, // 01
    0b00000, // 02
    0b11111, // 03 <
    0b00000, // 04
    0b00000, // 05
    0b11011, // 06 <
    0b00000, // 07
    0b00100, // 08
    0b10001, // 09 <
    0b00110, // 10
    0b01110, // 11
    0b10001, // 12 <
    0b00110, // 13
    0b01110, // 14
    0b10001, // 15 <
    0b01110, // 16
    0b01110, // 17
    0b11011, // 18 <
    0b00100, // 19
    0b00100, // 20
    0b11111, // 21 <
    0b00000, // 22
    0b00000, // 23
    0b11111, // 24 <
    0b00000, // 25
    0b00000, // 26
    0b11111, // 27 <
    0b00000, // 28
    0b00000, // 29

};

const unsigned char __CHAR_PUSH_LEFT[] = {

        0b11000,    // 00
        0b11000,    // 01
        0b11000,    // 02
        0b11000,    // 03
        0b11000,    // 04
        0b11000,    // 05
        0b11111,    // 06
        0b11111,    // 07
        0b11111,    // 08
        0b11111,    // 09
        0b11111,    // 10
        0b11111,    // 11
        0b11111,    // 12
        0b11111,    // 13
        0b11111,    // 14
        0b11111,    // 15
        0b11111,    // 16
        0b00000,    // 17
        0b11111,    // 18
        0b11111,    // 19
        0b11000,    // 20
        0b11111,    // 21
        0b11111,    // 22
        0b11000,    // 23
        0b11000,    // 24
        0b11000,    // 25
        0b11000,    // 26
        0b11000,    // 27
        0b11000,    // 28
        0b11000,    // 29
};

const unsigned char __CHAR_PUSH_RIGHT[] = {

        0b00011,    // 00
        0b00011,    // 01
        0b00011,    // 02
        0b00011,    // 03
        0b00011,    // 04
        0b00011,    // 05
        0b11111,    // 06
        0b11111,    // 07
        0b11111,    // 08
        0b11111,    // 09
        0b11111,    // 10
        0b11111,    // 11
        0b11111,    // 12
        0b11111,    // 13
        0b11111,    // 14
        0b11111,    // 15
        0b11111,    // 16
        0b00000,    // 17
        0b11111,    // 18
        0b11111,    // 19
        0b00011,    // 20
        0b11111,    // 21
        0b11111,    // 22
        0b00011,    // 23
        0b00011,    // 24
        0b00011,    // 25
        0b00011,    // 26
        0b00011,    // 27
        0b00011,    // 28
        0b00011,    // 29
};

const unsigned char __CHAR_VERTICAL_BAR[] = {

        0b01110,    // 00
        0b01110,    // 01
        0b00110,    // 02
        0b01110,    // 03
        0b01110,    // 04
        0b00110,    // 05
        0b01110,    // 06
        0b01110,    // 07
        0b00110,    // 08
        0b01110,    // 09
        0b01110,    // 10
        0b00110,    // 11
        0b01110,    // 12
        0b01110,    // 13
        0b00110,    // 14
        0b01110,    // 15
        0b01110,    // 16
        0b00110,    // 17
        0b01110,    // 18
        0b01110,    // 19
        0b00110,    // 20
        0b01110,    // 21
        0b01110,    // 22
        0b00110,    // 23
        0b01110,    // 24
        0b01110,    // 25
        0b00110,    // 26
        0b01110,    // 27
        0b01110,    // 28
        0b00110,    // 29
};

const unsigned char __CHAR_PUSH_UP[] = {

        0b11111, // 0
        0b11111, // 1
        0b11111, // 2
        0b11111, // 3
        0b11111, // 4
        0b11111, // 5
        0b11111, // 6
        0b11111, // 7
        0b00111, // 8
        0b11111, // 9
        0b11111, // 10
        0b00110, // 11
        0b01110, // 12
        0b01110, // 13
        0b00110, // 14
        0b01110, // 15
        0b01110, // 16
        0b00110, // 17
        0b01110, // 18
        0b01110, // 19
        0b00110, // 20
        0b01110, // 21
        0b01110, // 22
        0b00110, // 23
        0b01110, // 24
        0b01110, // 25
        0b00110, // 26
        0b01110, // 27
        0b01110, // 28
        0b00110, // 29
};

const unsigned char __CHAR_PUSH_DOWN[] = {

        0b01110,    // 00
        0b01110,    // 01
        0b00110,    // 02
        0b01110,    // 03
        0b01110,    // 04
        0b00110,    // 05
        0b01110,    // 06
        0b01110,    // 07
        0b00110,    // 08
        0b01110,    // 09
        0b01110,    // 10
        0b00110,    // 11
        0b01110,    // 12
        0b01110,    // 13
        0b00110,    // 14
        0b01110,    // 15
        0b01110,    // 16
        0b00110,    // 17
        0b11111,    // 18
        0b11111,    // 19
        0b00111,    // 20
        0b11111,    // 21
        0b11111,    // 22
        0b11111,    // 23
        0b11111,    // 24
        0b11111,    // 25
        0b11111,    // 26
        0b11111,    // 27
        0b11111,    // 28
        0b11111,    // 29
};
const unsigned char __CHAR_HORIZONTAL_BAR[] = {

        0b00000,
        0b00000,
        0b00000,
        0b00000,
        0b00000,
        0b00000,
        0b11111,
        0b11111,
        0b11111,
        0b11111,
        0b11111,
        0b11111,
        0b11111,
        0b11111,
        0b11111,
        0b11111,
        0b11111,
        0b00000,
        0b11111,
        0b11111,
        0b00000,
        0b11111,
        0b11111,
        0b00000,
        0b00000,
        0b00000,
        0b00000,
        0b00000,
        0b00000,
        0b00000,
};


const unsigned char __CHAR_SWITCH_LEFT_OFF[] = {

        0b1000,
        0b1000,
        0b0000,
        0b1100,
        0b1100,
        0b0000,
        0b1100,
        0b1100,
        0b0000,
        0b1000,
        0b1000,
        0b0000,
        0b1000,
        0b1000,
        0b0000,
        0b1000,
        0b1000,
        0b0000,
        0b1000,
        0b1000,
        0b0000,
        0b1000,
        0b1000,
        0b0000,
};

const unsigned char __CHAR_SWITCH_LEFT_ON[] = {

        0b1000,
        0b1000,
        0b1000,
        0b1000,
        0b1000,
        0b1000,
        0b1000,
        0b1000,
        0b1000,
        0b1000,
        0b1000,
        0b1000,
        0b1100,
        0b1100,
        0b1000,
        0b1100,
        0b1100,
        0b1000,
        0b1000,
        0b1000,
        0b1000,
        0b1000,
        0b1000,
        0b1000,
};




const unsigned char __CHAR_WYRM_HEAD_U[] = {

    0b01110, // 00 <
    0b00000, // 01
    0b01110, // 02
    0b01110, // 03 <
    0b01010, // 04
    0b01110, // 05
    0b11111, // 06 <
    0b01010, // 07
    0b11111, // 08
    0b11111, // 09 <
    0b00000, // 10
    0b11111, // 11
    0b11111, // 12 <
    0b00000, // 13
    0b11111, // 14
    0b11111, // 15 <
    0b00000, // 16
    0b11111, // 17
    0b11111, // 18 <
    0b00000, // 19
    0b11111, // 20
    0b11111, // 21 <
    0b00000, // 22
    0b11111, // 23
    0b01110, // 24 <
    0b00000, // 25
    0b01110, // 26
    0b01110, // 27
    0b00000, // 28
    0b01110, // 29
};

const unsigned char __CHAR_WYRM_HEAD_D[] = {

    0b01110, // 27
    0b00000, // 28
    0b01110, // 29
    0b01110, // 24 <
    0b00000, // 25
    0b01110, // 26
    0b11111, // 21 <
    0b00000, // 22
    0b11111, // 23
    0b11111, // 18 <
    0b00000, // 19
    0b11111, // 20
    0b11111, // 15 <
    0b00000, // 16
    0b11111, // 17
    0b11111, // 12 <
    0b00000, // 13
    0b11111, // 14
    0b11111, // 09 <
    0b00000, // 10
    0b11111, // 11
    0b11111, // 06 <
    0b01010, // 07
    0b11111, // 08
    0b01110, // 03 <
    0b01010, // 04
    0b01110, // 05
    0b01110, // 00 <
    0b00000, // 01
    0b01110, // 02
};


const unsigned char __CHAR_WYRM_HEAD_L[] = {

    0b00000, // 00 <
    0b00000, // 01
    0b00000, // 02
    0b01110, // 03 <
    0b01000, // 04
    0b01110, // 05
    0b11110, // 06 <
    0b01000, // 07
    0b11110, // 08
    0b11111, // 09 <
    0b00000, // 10
    0b11111, // 11
    0b11111, // 12 <
    0b00000, // 13
    0b11111, // 14
    0b11111, // 15 <
    0b00000, // 16
    0b11111, // 17
    0b11111, // 18 <
    0b00000, // 19
    0b11111, // 20
    0b11110, // 21 <
    0b01000, // 22
    0b11110, // 23
    0b01110, // 24 <
    0b01000, // 25
    0b01110, // 26
    0b00000, // 27 <
    0b00000, // 28
    0b00000, // 29
};


const unsigned char __CHAR_WYRM_HEAD_R[] = {

    0b00000, // 00 <
    0b00000, // 01
    0b00000, // 02
    0b01110, // 03 <
    0b00010, // 04
    0b01110, // 05
    0b01111, // 06 <
    0b00010, // 07
    0b01111, // 08
    0b11111, // 09 <
    0b00000, // 10
    0b11111, // 11
    0b11111, // 12 <
    0b00000, // 13
    0b11111, // 14
    0b11111, // 15 <
    0b00000, // 16
    0b11111, // 17
    0b11111, // 18 <
    0b00000, // 19
    0b11111, // 20
    0b01111, // 21 <
    0b00010, // 22
    0b01111, // 23
    0b01110, // 24 <
    0b00010, // 25
    0b01110, // 26
    0b00000, // 27 <
    0b00000, // 28
    0b00000, // 29
};



const unsigned char __CHAR_WYRM_CORNER_RD[] = {

    0b00010, // 00 <
    0b00000, // 01
    0b00010, // 02
    0b00111, // 03 <
    0b00000, // 04
    0b00111, // 05
    0b01111, // 06 <
    0b00000, // 07
    0b01111, // 08
    0b01111, // 09 <
    0b00010, // 10
    0b01111, // 11
    0b01111, // 12 <
    0b00010, // 13
    0b01111, // 14
    0b01111, // 15 <
    0b00010, // 16
    0b01111, // 17
    0b01111, // 18 <
    0b00010, // 19
    0b01111, // 20
    0b01111, // 21 <
    0b00000, // 22
    0b01111, // 23
    0b01111, // 24 <
    0b00000, // 25
    0b01111, // 26
    0b01111, // 27 <
    0b00000, // 28
    0b01111, // 29
};


const unsigned char __CHAR_WYRM_CORNER_LD[] = {

    0b11000, // 00 <
    0b00000, // 01
    0b11000, // 02
    0b11100, // 03 <
    0b00000, // 04
    0b11100, // 05
    0b11110, // 06 <
    0b00000, // 07
    0b11110, // 08
    0b11110, // 09 <
    0b00000, // 10
    0b11110, // 11
    0b11110, // 12 <
    0b01000, // 13
    0b11110, // 14
    0b11110, // 15 <
    0b01000, // 16
    0b11110, // 17
    0b11110, // 18 <
    0b01000, // 19
    0b11110, // 20
    0b11110, // 21 <
    0b01000, // 22
    0b11110, // 23
    0b11110, // 24 <
    0b00000, // 25
    0b11110, // 26
    0b11110, // 27 <
    0b00000, // 28
    0b11110, // 29
};


const unsigned char __CHAR_WYRM_CORNER_RU[] = {

    0b01110, // 00 <
    0b00000, // 01
    0b01110, // 02
    0b01101, // 03 <
    0b00010, // 04
    0b01111, // 05
    0b01111, // 06 <
    0b00010, // 07
    0b01111, // 08
    0b01111, // 09 <
    0b00000, // 10
    0b01111, // 11
    0b00111, // 12 <
    0b00000, // 13
    0b00111, // 14
    0b00011, // 15 <
    0b00000, // 16
    0b00011, // 17
    0b00000, // 18 <
    0b00000, // 19
    0b00000, // 20
    0b00000, // 21 <
    0b00000, // 22
    0b00000, // 23
    0b00000, // 24 <
    0b00000, // 25
    0b00000, // 26
    0b00000, // 27 <
    0b00000, // 28
    0b00000, // 29
};


const unsigned char __CHAR_WYRM_CORNER_LU[] = {

    0b11110, // 00 <
    0b00000, // 01
    0b11110, // 02
    0b11110, // 03 <
    0b00000, // 04
    0b11110, // 05
    0b11110, // 06 <
    0b01000, // 07
    0b11110, // 08
    0b11110, // 09 <
    0b01000, // 10
    0b11110, // 11
    0b11110, // 12 <
    0b01000, // 13
    0b11110, // 14
    0b11110, // 15 <
    0b00000, // 16
    0b11110, // 17
    0b11100, // 18 <
    0b00000, // 19
    0b11100, // 20
    0b11000, // 21 <
    0b00000, // 22
    0b11000, // 23
    0b00000, // 24 <
    0b00000, // 25
    0b00000, // 26
    0b00000, // 27 <
    0b00000, // 28
    0b00000, // 29
};


const unsigned char __CHAR_INNER_CORNER_1[] = {

    //  0b1111, // 00 <
    //  0b0000, // 01
    //  0b0000, // 02
    //  0b1111, // 03 <
    //  0b0000, // 04
    //  0b0000, // 05
    //  0b1111, // 06 <
    //  0b0000, // 07
    //  0b0000, // 08
    //  0b1111, // 09 <
    //  0b0000, // 10
    //  0b0000, // 11
    //  0b0011, // 12 <
    //  0b1100, // 13
    //  0b1100, // 14
    //  0b0011, // 15 <
    //  0b1100, // 16
    //  0b1100, // 17
    //  0b0011, // 18 <
    //  0b1100, // 19
    //  0b1100, // 20
    //  0b0011, // 21 <
    //  0b1100, // 22
    //  0b1100, // 23
};

const unsigned char __CHAR_INNER_CORNER_0[] = {

    //  0b1111, // 00 <
    //  0b0000, // 01
    //  0b0000, // 02
    //  0b1111, // 03 <
    //  0b0000, // 04
    //  0b0000, // 05
    //  0b1111, // 06 <
    //  0b0000, // 07
    //  0b0000, // 08
    //  0b1111, // 09 <
    //  0b0000, // 10
    //  0b0000, // 11
    //  0b1111, // 12 <
    //  0b0000, // 13
    //  0b0000, // 14
    //  0b1111, // 15 <
    //  0b0000, // 10
    //  0b0000, // 17
    //  0b1111, // 18 <
    //  0b0000, // 19
    //  0b0000, // 20
    //  0b1111, // 21 <
    //  0b0000, // 22
    //  0b0000, // 23
};

const unsigned char __CHAR_INNER_CORNER_2[] = {

    //  0b1111, // 00 <
    //  0b0000, // 01
    //  0b0000, // 02
    //  0b1111, // 03 <
    //  0b0000, // 04
    //  0b0000, // 05
    //  0b1111, // 06 <
    //  0b0000, // 07
    //  0b0000, // 08
    //  0b1111, // 09 <
    //  0b0000, // 10
    //  0b0000, // 11
    //  0b1111, // 12 <
    //  0b0011, // 13
    //  0b0011, // 14
    //  0b1111, // 15 <
    //  0b0011, // 16
    //  0b0011, // 17
    //  0b1111, // 18 <
    //  0b0011, // 19
    //  0b0011, // 20
    //  0b1111, // 21 <
    //  0b0011, // 22
    //  0b0011, // 23
};

const unsigned char __CHAR_INNER_CORNER_3[] = {

// up + right soil

     0b00011, // 00 <
     0b00000, // 01
     0b00000, // 02
     0b00001, // 03 <
     0b00000, // 04
     0b00000, // 05
     0b00000, // 06 <
     0b00000, // 07
     0b00000, // 08
     0b00000, // 09 <
     0b00000, // 10
     0b00000, // 11
     0b00000, // 12 <
     0b00000, // 13
     0b00000, // 14
     0b00000, // 15 <
     0b00000, // 16
     0b00000, // 17
     0b00000, // 18 <
     0b00000, // 19
     0b00000, // 20
     0b00000, // 21 <
     0b00000, // 22
     0b00000, // 23
     0b00000, // 24 <
     0b00000, // 25
     0b00000, // 26
     0b00000, // 27 <
     0b00000, // 28
     0b00000, // 29
};

const unsigned char __CHAR_INNER_CORNER_4[] = {

    //  0b1111, // 00 <
    //  0b1100, // 01
    //  0b1100, // 02
    //  0b1111, // 03 <
    //  0b1100, // 04
    //  0b1100, // 05
    //  0b1111, // 06 <
    //  0b1100, // 07
    //  0b1100, // 08
    //  0b1111, // 09 <
    //  0b1100, // 10
    //  0b1100, // 11
    //  0b1111, // 12 <
    //  0b0000, // 13
    //  0b0000, // 14
    //  0b1111, // 15 <
    //  0b0000, // 16
    //  0b0000, // 17
    //  0b1111, // 18 <
    //  0b0000, // 19
    //  0b0000, // 20
    //  0b1111, // 21 <
    //  0b0000, // 22
    //  0b0000, // 23
};

const unsigned char __CHAR_INNER_CORNER_5[] = {

    //  0b1111, // 00 <
    //  0b1100, // 01
    //  0b1100, // 02
    //  0b1111, // 03 <
    //  0b1100, // 04
    //  0b1100, // 05
    //  0b1111, // 06 <
    //  0b1100, // 07
    //  0b1100, // 08
    //  0b1111, // 09 <
    //  0b1100, // 10
    //  0b1100, // 11
    //  0b1111, // 12 <
    //  0b1100, // 13
    //  0b1100, // 14
    //  0b1111, // 15 <
    //  0b1100, // 16
    //  0b1100, // 17
    //  0b1111, // 18 <
    //  0b1100, // 19
    //  0b1100, // 20
    //  0b1111, // 21 <
    //  0b1100, // 22
    //  0b1100, // 23
};


const unsigned char __CHAR_INNER_CORNER_6[] = {

// right+down soil

     0b00000, // 00 <
     0b00000, // 01
     0b00000, // 02
     0b00000, // 03 <
     0b00000, // 04
     0b00000, // 05
     0b00000, // 06 <
     0b00000, // 07
     0b00000, // 08
     0b00000, // 09 <
     0b00000, // 10
     0b00000, // 11
     0b00000, // 12 <
     0b00000, // 13
     0b00000, // 14
     0b00000, // 15 <
     0b00000, // 16
     0b00000, // 17
     0b00000, // 18 <
     0b00000, // 19
     0b00000, // 20
     0b00000, // 21 <
     0b00000, // 22
     0b00000, // 23
     0b00001, // 24 <
     0b00000, // 25
     0b00000, // 26
     0b00011, // 27 <
     0b00000, // 28
     0b00000, // 29
};

const unsigned char __CHAR_INNER_CORNER_7[] = {

// up+right+down soil

     0b00001, // 00 <
     0b00000, // 01
     0b00000, // 02
     0b00001, // 03 <
     0b00000, // 04
     0b00000, // 05
     0b00000, // 06 <
     0b00000, // 07
     0b00000, // 08
     0b00000, // 09 <
     0b00000, // 10
     0b00000, // 11
     0b00000, // 12 <
     0b00000, // 13
     0b00000, // 14
     0b00000, // 15 <
     0b00000, // 16
     0b00000, // 17
     0b00000, // 18 <
     0b00000, // 19
     0b00000, // 20
     0b00000, // 21 <
     0b00000, // 22
     0b00000, // 23
     0b00000, // 24 <
     0b00000, // 25
     0b00000, // 26
     0b00011, // 27 <
     0b00000, // 28
     0b00000, // 29
};


const unsigned char __CHAR_INNER_CORNER_8[] = {

    //  0b1100, // 00 <
    //  0b0011, // 01
    //  0b0011, // 02
    //  0b1100, // 03 <
    //  0b0011, // 04
    //  0b0011, // 05
    //  0b1100, // 06 <
    //  0b0011, // 07
    //  0b0011, // 08
    //  0b1100, // 09 <
    //  0b0011, // 10
    //  0b0011, // 11
    //  0b1111, // 12 <
    //  0b0000, // 13
    //  0b0000, // 14
    //  0b1111, // 15 <
    //  0b0000, // 16
    //  0b0000, // 17
    //  0b1111, // 18 <
    //  0b0000, // 19
    //  0b0000, // 20
    //  0b1111, // 21 <
    //  0b0000, // 22
    //  0b0000, // 23
};

const unsigned char __CHAR_INNER_CORNER_9[] = {
// ul

     0b11000, // 00 <
     0b00000, // 01
     0b00000, // 02
     0b10000, // 03 <
     0b00000, // 04
     0b00000, // 05
     0b10000, // 06 <
     0b00000, // 07
     0b00000, // 08
     0b00000, // 09 <
     0b00000, // 10
     0b00000, // 11
     0b00000, // 12 <
     0b00000, // 13
     0b00000, // 14
     0b00000, // 15 <
     0b00000, // 16
     0b00000, // 17
     0b00000, // 18 <
     0b00000, // 19
     0b00000, // 20
     0b00000, // 21 <
     0b00000, // 22
     0b00000, // 23
     0b00000, // 24 <
     0b00000, // 25
     0b00000, // 26
     0b00000, // 27 <
     0b00000, // 28
     0b00000, // 29
};

const unsigned char __CHAR_INNER_CORNER_10[] = {

    //  0b1100, // 00 <
    //  0b0011, // 01
    //  0b0011, // 02
    //  0b1100, // 03 <
    //  0b0011, // 04
    //  0b0011, // 05
    //  0b1100, // 06 <
    //  0b0011, // 07
    //  0b0011, // 08
    //  0b1100, // 09 <
    //  0b0011, // 10
    //  0b0011, // 11
    //  0b1111, // 12 <
    //  0b0011, // 13
    //  0b0011, // 14
    //  0b1111, // 15 <
    //  0b0011, // 16
    //  0b0011, // 17
    //  0b1111, // 18 <
    //  0b0011, // 19
    //  0b0011, // 20
    //  0b1111, // 21 <
    //  0b0011, // 22
    //  0b0011, // 23
};

const unsigned char __CHAR_INNER_CORNER_11[] = {

// up+left+right soil

     0b11001, // 00 <
     0b00000, // 01
     0b00000, // 02
     0b10001, // 03 <
     0b00000, // 04
     0b00000, // 05
     0b10000, // 06 <
     0b00000, // 07
     0b00000, // 08
     0b00000, // 09 <
     0b00000, // 10
     0b00000, // 11
     0b00000, // 12 <
     0b00000, // 13
     0b00000, // 14
     0b00000, // 15 <
     0b00000, // 16
     0b00000, // 17
     0b00000, // 18 <
     0b00000, // 19
     0b00000, // 20
     0b00000, // 21 <
     0b00000, // 22
     0b00000, // 23
     0b00000, // 24 <
     0b00000, // 25
     0b00000, // 26
     0b00000, // 27 <
     0b00000, // 28
     0b00000, // 29
};


const unsigned char __CHAR_INNER_CORNER_12[] = {

// ld

     0b00000, // 00 <
     0b00000, // 01
     0b00000, // 02
     0b00000, // 03 <
     0b00000, // 04
     0b00000, // 05
     0b00000, // 06 <
     0b00000, // 07
     0b00000, // 08
     0b00000, // 09 <
     0b00000, // 10
     0b00000, // 11
     0b00000, // 12 <
     0b00000, // 13
     0b00000, // 14
     0b00000, // 15 <
     0b00000, // 16
     0b00000, // 17
     0b00000, // 18 <
     0b00000, // 19
     0b00000, // 20
     0b00000, // 21 <
     0b00000, // 22
     0b00000, // 23
     0b00000, // 24 <
     0b00000, // 25
     0b00000, // 26
     0b10000, // 27 <
     0b00000, // 28
     0b00000, // 29
};


const unsigned char __CHAR_INNER_CORNER_13[] = {

// uld

     0b11000, // 00 <
     0b00000, // 01
     0b00000, // 02
     0b10000, // 03 <
     0b00000, // 04
     0b00000, // 05
     0b10000, // 06 <
     0b00000, // 07
     0b00000, // 08
     0b00000, // 09 <
     0b00000, // 10
     0b00000, // 11
     0b00000, // 12 <
     0b00000, // 13
     0b00000, // 14
     0b00000, // 15 <
     0b00000, // 16
     0b00000, // 17
     0b00000, // 18 <
     0b00000, // 19
     0b00000, // 20
     0b00000, // 21 <
     0b00000, // 22
     0b00000, // 23
     0b00000, // 24 <
     0b00000, // 25
     0b00000, // 26
     0b10000, // 27 <
     0b00000, // 28
     0b00000, // 29
};

const unsigned char __CHAR_INNER_CORNER_14[] = {

// lrd

     0b00000, // 00 <
     0b00000, // 01
     0b00000, // 02
     0b00000, // 03 <
     0b00000, // 04
     0b00000, // 05
     0b00000, // 06 <
     0b00000, // 07
     0b00000, // 08
     0b00000, // 09 <
     0b00000, // 10
     0b00000, // 11
     0b00000, // 12 <
     0b00000, // 13
     0b00000, // 14
     0b00000, // 15 <
     0b00000, // 16
     0b00000, // 17
     0b00000, // 18 <
     0b00000, // 19
     0b00000, // 20
     0b00000, // 21 <
     0b00000, // 22
     0b00000, // 23
     0b00000, // 24 <
     0b00000, // 25
     0b00000, // 26
     0b10001, // 27 <
     0b00000, // 28
     0b00000, // 29
};

const unsigned char __CHAR_INNER_CORNER_15[] = {

// udlr

     0b11011, // 00 <
     0b00000, // 01
     0b00000, // 02
     0b10001, // 03 <
     0b00000, // 04
     0b00000, // 05
     0b10001, // 06 <
     0b00000, // 07
     0b00000, // 08
     0b00000, // 09 <
     0b00000, // 10
     0b00000, // 11
     0b00000, // 12 <
     0b00000, // 13
     0b00000, // 14
     0b00000, // 15 <
     0b00000, // 16
     0b00000, // 17
     0b00000, // 18 <
     0b00000, // 19
     0b00000, // 20
     0b00000, // 21 <
     0b00000, // 22
     0b00000, // 23
     0b00001, // 24 <
     0b00000, // 25
     0b00000, // 26
     0b10001, // 27 <
     0b00000, // 28
     0b00000, // 29
};



#if __ENABLE_LAVA2

const unsigned char __CHAR_LAVA_0[] = {

    0b00000, // 00 <
    0b00000, // 01
    0b00000, // 02
    0b00000, // 03 <
    0b00000, // 04
    0b00000, // 05
    0b00000, // 06 <
    0b00100, // 08
    0b00000, // 09 <
    0b00000, // 10
    0b01110, // 11
    0b00000, // 12 <
    0b00000, // 13
    0b01110, // 14
    0b00000, // 15 <
    0b00000, // 16
    0b00100, // 17
    0b00000, // 18 <
    0b00000, // 19
    0b00000, // 20
    0b00000, // 21 <
    0b00000, // 07
    0b00000, // 22
    0b00000, // 23
    0b00000, // 24 <
    0b00000, // 25
    0b00000, // 26
    0b00000, // 27 <
    0b00000, // 28
    0b00000, // 29
};

const unsigned char __CHAR_LAVA_1[] = {

    0b00000, // 00 <
    0b00000, // 01
    0b00000, // 02
    0b00000, // 03 <
    0b00000, // 04
    0b00000, // 05
    0b00000, // 06 <
    0b00000, // 07
    0b00000, // 08
    0b00000, // 09 <
    0b00000, // 10
    0b00000, // 11
    0b00000, // 12 <
    0b00000, // 13
    0b00000, // 14
    0b00000, // 15 <
    0b00000, // 16
    0b00000, // 17
    0b01000, // 18 <
    0b00000, // 19
    0b00000, // 20
    0b11000, // 21 <
    0b00000, // 22
    0b00000, // 23
    0b01000, // 24 <
    0b00000, // 25
    0b00000, // 26
    0b00000, // 27 <
    0b00001, // 28
    0b00001, // 29
};


// const unsigned char __CHAR_LAVA_2[] = {

//     0b00000, // 00 <
//     0b00000, // 01
//     0b00000, // 02
//     0b00000, // 03 <
//     0b00000, // 04
//     0b00000, // 05
//     0b00000, // 06 <
//     0b00000, // 07
//     0b00000, // 08
//     0b00000, // 09 <
//     0b00000, // 10
//     0b00000, // 11
//     0b00000, // 12 <
//     0b00000, // 13
//     0b00000, // 14
//     0b00000, // 15 <
//     0b00000, // 16
//     0b00000, // 17
//     0b00000, // 18 <
//     0b00000, // 19
//     0b00000, // 20
//     0b00000, // 21 <
//     0b00000, // 22
//     0b00000, // 23
//     0b00000, // 24 <
//     0b00000, // 25
//     0b00000, // 26
//     0b00000, // 27 <
//     0b00000, // 28
//     0b00000, // 29
// };


const unsigned char __CHAR_LAVA_3[] = {

    0b00000,  // 00 < <--
    0b00000,  // 01 <--
    0b00000,  // 02 <-- raised small square
    0b00000,  // 03 < <--
    0b00000,  // 04 <--
    0b00000,  // 05
    0b00000,  // 06 <
    0b00100,  // 08
    0b00000,  // 09 <
    0b00000,  // 10
    0b00100,  // 11
    0b00000,  // 12 <
    0b00000,  // 13
    0b01110,  // 14
    0b00000,  // 15 <
    0b00000,  // 16
    0b00100,  // 17
    0b00000,  // 18 <
    0b00000,  // 19
    0b00100,  // 20
    0b00000,  // 07
    0b00000,  // 21 <
    0b00000,  // 22
    0b00000,  // 23
    0b00000,  // 24 <
    0b00000,  // 25
    0b00000,  // 26
    0b00000,  // 27 <
    0b00000,  // 28
    0b00000,  // 29
};

#endif // __ENABLE_LAVA2





extern const unsigned char shape_FRAME_BLANK[];

#define __CHAR_BLANK (shape_FRAME_BLANK + 3)

#define C(x) (const unsigned char *const) x



const unsigned char *const charSet[CH_MAX] = {

   // see ChName @ attribute.h


    C(char_parallaxBlank),          // CH_BLANK,                       // 000
    C(__CHAR_DIRT),                 // CH_DIRT,                        // 001
    C(__CHAR_BRICKWALL),            // CH_BRICKWALL,                   // 002
    C(__CHAR_STEELWALL),            // CH_DOORCLOSED,                  // 003
    C(__CHAR_STEELWALL),            // CH_DOOROPEN_0,                  // 004
    C(__CHAR_BLANK),                // CH_EXITBLANK,                   // 005
    C(__CHAR_STEELWALL),            // CH_STEELWALL,                   // 006
    C(__CHAR_PEBBLE1),              // CH_PEBBLE1,                     // 007
    C(__CHAR_PEBBLE2),              // CH_PEBBLE2,                     // 008
    C(__CHAR_BOULDER),              // CH_BOULDER,                     // 009
    C(__CHAR_BOULDER),              // CH_BOULDER_FALLING,             // 010
    C(__CHAR_DOGE_00),              // CH_DOGE_00,                     // 011
    C(__CHAR_DOGE_00),              // CH_DOGE_FALLING,                // 012
    C(__CHAR_BLANK),                // CH_ROCKFORD_BIRTH,              // 013
    C(__CHAR_LAVA_0),               // CH_LAVA_0,                      // 014
    C(__CHAR_LAVA_1),               // CH_LAVA_1,                      // 015
    C(__CHAR_BLANK),                // CH_LAVA_2,                      // 016
    C(__CHAR_LAVA_3),               // CH_LAVA_3,                      // 017
    C(__CHAR_BLANK),                // CH_ROCKFORD,                    // 018
    C(__CHAR_DOGE_01),              // CH_DOGE_01,                     // 019
    C(__CHAR_DOGE_02),              // CH_DOGE_02,                     // 020
    C(__CHAR_DOGE_03),              // CH_DOGE_03,                     // 021
    C(__CHAR_DOGE_04),              // CH_DOGE_04,                     // 022
    C(__CHAR_DOGE_05),              // CH_DOGE_05,                     // 023
    C(__CHAR_DOGE_00),              // CH_DOGE_STATIC,                 // 024
    C(__CHAR_DOGE_PEBBLE),          // CH_PEBBLE_BOULDER,              // 025
    C(__CHAR_EXPLODETO_0),          // CH_EXPLODETOBLANK_0,            // 026
    C(__CHAR_EXPLODETO_1),          // CH_EXPLODETOBLANK_1,            // 027
    C(__CHAR_EXPLODETO_2),          // CH_EXPLODETOBLANK_2,            // 028
    C(__CHAR_EXPLODETO_3),          // CH_EXPLODETOBLANK_3,            // 029
    C(__CHAR_EXPLODETO_4),          // CH_EXPLODETOBLANK_4,            // 030
    C(__CHAR_DOGE_02),              // CH_DOGE_GRAB,                   // 031
    C(__CHAR_DUST_0),               // CH_DUST_0,                      // 032
    C(__CHAR_DUST_1),               // CH_DUST_1,                      // 033
    C(char_Dust_2),                 // CH_DUST_2,                      // 034
    C(__CHAR_BOULDER_DOGE),         // CH_CONGLOMERATE,                // 035
    C(__CHAR_BOULDER_U),            // CH_CONGLOMERATE_1,              // 036
    C(__CHAR_BOULDER_R),            // CH_CONGLOMERATE_2,              // 037
    C(__CHAR_BOULDER_UR),           // CH_CONGLOMERATE_3,              // 038
    C(__CHAR_BOULDER_D),            // CH_CONGLOMERATE_4,              // 039
    C(__CHAR_BOULDER_UD),           // CH_CONGLOMERATE_5,              // 040
    C(__CHAR_BOULDER_RD),           // CH_CONGLOMERATE_6,              // 041
    C(__CHAR_BOULDER_URD),          // CH_CONGLOMERATE_7,              // 042
    C(__CHAR_BOULDER_L),            // CH_CONGLOMERATE_8,              // 043
    C(__CHAR_BOULDER_UL),           // CH_CONGLOMERATE_9,              // 044
    C(__CHAR_BOULDER_RL),           // CH_CONGLOMERATE_10,             // 045
    C(__CHAR_BOULDER_URL),          // CH_CONGLOMERATE_11,             // 046
    C(__CHAR_BOULDER_DL),           // CH_CONGLOMERATE_12,             // 047
    C(__CHAR_BOULDER_UDL),          // CH_CONGLOMERATE_13,             // 048
    C(__CHAR_BOULDER_RDL),          // CH_CONGLOMERATE_14,             // 049
    C(__CHAR_BOULDER_URDL),         // CH_CONGLOMERATE_15,             // 050
    C(__CHAR_DUST_ROCK_0),          // CH_DUST_ROCK_0,                 // 051
    C(__CHAR_DUST_ROCK_1),          // CH_DUST_ROCK_1,                 // 052
    C(__CHAR_DUST_ROCK_2),          // CH_DUST_ROCK_2,                 // 053
    C(__CHAR_DOGE_00),              // CH_DOGE_CONVERT,                // 054
    C(__CHAR_SWITCH_LEFT_OFF),      // CH_SWITCH_LEFT_OFF,             // 055
    C(__CHAR_SWITCH_LEFT_ON),       // CH_SWITCH_LEFT_ON,              // 056
    C(__CHAR_HORIZONTAL_BAR),       // CH_HORIZONTAL_BAR,              // 057
    C(__CHAR_PUSH_LEFT),            // CH_PUSH_LEFT,                   // 058
    C(__CHAR_PUSH_LEFT),            // CH_PUSH_LEFT_REVERSE,           // 059
    C(__CHAR_PUSH_RIGHT),           // CH_PUSH_RIGHT,                  // 060
    C(__CHAR_PUSH_RIGHT),           // CH_PUSH_RIGHT_REVERSE,          // 061
    C(__CHAR_VERTICAL_BAR),         // CH_VERTICAL_BAR,                // 062
    C(__CHAR_PUSH_UP),              // CH_PUSH_UP,                     // 063
    C(__CHAR_PUSH_UP),              // CH_PUSH_UP_REVERSE,             // 064
    C(__CHAR_PUSH_DOWN),            // CH_PUSH_DOWN,                   // 065
    C(__CHAR_PUSH_DOWN),            // CH_PUSH_DOWN_REVERSE,           // 066
    C(__CHAR_AMOEBA_0),             // CH_WYRM_BODY,                   // 067
    C(__CHAR_AMOEBA_2),             // CH_WYRM_VERT_BODY,              // 068
    C(__CHAR_WYRM_CORNER_LD),       // CH_WYRM_CORNER_LD,              // 069
    C(__CHAR_WYRM_CORNER_RD),       // CH_WYRM_CORNER_RD,              // 070
    C(__CHAR_WYRM_CORNER_LU),       // CH_WYRM_CORNER_LU,              // 071
    C(__CHAR_WYRM_CORNER_RU),       // CH_WYRM_CORNER_RU,              // 072
    C(__CHAR_WYRM_HEAD_U),          // CH_WYRM_HEAD_U,                 // 073
    C(__CHAR_WYRM_HEAD_R),          // CH_WYRM_HEAD_R,                 // 074
    C(__CHAR_WYRM_HEAD_D),          // CH_WYRM_HEAD_D,                 // 075
    C(__CHAR_WYRM_HEAD_L),          // CH_WYRM_HEAD_L,                 // 076
    C(__CHAR_INNER_CORNER_0),       // CH_CORNER_0,                    // 077
    C(__CHAR_INNER_CORNER_1),       // CH_CORNER_1,                    // 078
    C(__CHAR_INNER_CORNER_2),       // CH_CORNER_2,                    // 079
    C(__CHAR_INNER_CORNER_3),       // CH_CORNER_3,                    // 080
    C(__CHAR_INNER_CORNER_4),       // CH_CORNER_4,                    // 081
    C(__CHAR_INNER_CORNER_5),       // CH_CORNER_5,                    // 082
    C(__CHAR_INNER_CORNER_6),       // CH_CORNER_6,                    // 083
    C(__CHAR_INNER_CORNER_7),       // CH_CORNER_7,                    // 084
    C(__CHAR_INNER_CORNER_8),       // CH_CORNER_8,                    // 085
    C(__CHAR_INNER_CORNER_9),       // CH_CORNER_9,                    // 086
    C(__CHAR_INNER_CORNER_10),      // CH_CORNER_10,                   // 087
    C(__CHAR_INNER_CORNER_11),      // CH_CORNER_11,                   // 088
    C(__CHAR_INNER_CORNER_12),      // CH_CORNER_12,                   // 089
    C(__CHAR_INNER_CORNER_13),      // CH_CORNER_13,                   // 090
    C(__CHAR_INNER_CORNER_14),      // CH_CORNER_14,                   // 091
    C(__CHAR_INNER_CORNER_15),      // CH_CORNER_15,                   // 092
    C(__CHAR_BOULDER_URDL2),        // CH_CONGLOMERATE_MID,            // 093
    C(__CHAR_BOULDER_DOGE),         // CH_BOULDER_DOGE,                // 094
    C(__CHAR_BOULDER_DOGE),         // CH_BOULDER_DOGE_FALLING,        // 095
};


//EOF

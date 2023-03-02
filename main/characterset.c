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



void createParallaxCharset() {

//    return;

    static int lastX = -1;
    static int lastY = -1;

    #if ENABLE_SHAKE
        extern int shakeX, shakeY;
        int yOffset = ((scrollY + shakeY) >> 17) * 3;
        int offset = ((scrollX + shakeX) >> 15) & 3;
    #else
        int yOffset = ((scrollY) >> 17) * 3;
        int offset = ((scrollX) >> 15) & 3;
    #endif


    while (yOffset >= PIECE_DEPTH)
        yOffset -= PIECE_DEPTH;
    yOffset = PIECE_DEPTH - yOffset - 1;


    static bool lastParallax = false;

    if (displayMode == DISPLAY_NORMAL)
        if (((RIGHT_DIFFICULTY_A == enableParallax) != lastParallax)
            || (offset != lastX || yOffset != lastY)) {

            lastParallax = (enableParallax == RIGHT_DIFFICULTY_A);

            lastX = offset;
            lastY = yOffset;

            for (int i = 0; i < PIECE_DEPTH; i++) {

                int pb = char_parallaxBlank[i] = 0;
//                    lastParallax ? ((((const unsigned char *const)__CHAR_PARALLAX_TEMPLATE)[yOffset]
//                        >> offset) & 0xF) : 0;

                char_Dust_2[i]      = pb | ((unsigned char *)__CHAR_DUST_2)[i];
                char_DustLeft_1[i]  = pb | ((unsigned char *)__CHAR_DUST_LEFT_1)[i];
                char_DustRight_1[i] = pb | ((unsigned char *)__CHAR_DUST_RIGHT_1)[i];

                if (++yOffset >= PIECE_DEPTH)
                    yOffset = 0;
            }
        }


}



const unsigned char __CHAR_PUSH_LEFT[] = {

        0b1100,  
        0b1100,  
        0b1100,  
        0b1111,  
        0b1111,  
        0b1111,  
        0b1111,  
        0b1111,  
        0b1111,  
        0b1111,  
        0b1111,  
        0b0000,  
        0b1111,  
        0b1111,  
        0b1100,  
        0b1111,  
        0b1111,  
        0b1100,  
        0b1100,  
        0b1100,  
        0b0000,  
};

const unsigned char __CHAR_PUSH_RIGHT[] = {

        0b0011,  
        0b0011,  
        0b0011,  
        0b1111,  
        0b1111,  
        0b1111,  
        0b1111,  
        0b1111,  
        0b1111,  
        0b1111,  
        0b1111,  
        0b0000,  
        0b1111,  
        0b1111,  
        0b0011,  
        0b1111,  
        0b1111,  
        0b0011,  
        0b0011,  
        0b0011,  
        0b0000,  
};

const unsigned char __CHAR_VERTICAL_BAR[] = {

        0b0110,  
        0b0110,  
        0b0100,  
        0b0110,  
        0b0110,  
        0b0100,  
        0b0110,  
        0b0110,  
        0b0100,  
        0b0110,  
        0b0110,  
        0b0100,  
        0b0110,  
        0b0110,  
        0b0100,  
        0b0110,  
        0b0110,  
        0b0100,
        0b0110,  
        0b0110,  
        0b0100,  
};

const unsigned char __CHAR_PUSH_UP[] = {

        0b1111,  
        0b1111,  
        0b1111,  
        0b1111,  
        0b1111,  
        0b1111,  
        0b1111,  
        0b1111,  
        0b1100,  
        0b1111,  
        0b1111,  
        0b1100,  
        0b0110,  
        0b0110,  
        0b0100,  
        0b0110,  
        0b0110,  
        0b0100,
        0b0110,  
        0b0110,  
        0b0100,  
};

const unsigned char __CHAR_PUSH_DOWN[] = {

        0b0110,  
        0b0110,  
        0b0100,  
        0b0110,  
        0b0110,  
        0b0100,  
        0b0110,  
        0b0110,  
        0b0100,  
        0b1111,  
        0b1111,  
        0b1100,  
        0b1111,  
        0b1111,  
        0b1111,  
        0b1111,  
        0b1111,  
        0b1111,
        0b1111,  
        0b1111,  
        0b0000,  
};
const unsigned char __CHAR_HORIZONTAL_BAR[] = {
        0b0000,  
        0b0000,  
        0b0000,  
        0b1111,  
        0b1111,  
        0b1111,  
        0b1111,  
        0b1111,  
        0b1111,  
        0b1111,  
        0b1111,  
        0b0000,  
        0b1111,  
        0b1111,  
        0b0000,  
        0b1111,  
        0b1111,  
        0b0000,  
        0b0000,  
        0b0000,  
        0b0000,  
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

};




const unsigned char __CHAR_SNAKE_CORNER_RD[] = {

    0b0000, // 00 <
    0b0000, // 01
    0b0011, // 02
    0b0000, // 03 <
    0b0100, // 04
    0b0111, // 05
    0b0000, // 06 <
    0b0000, // 07
    0b1111, // 08
    0b0000, // 09 <
    0b0100, // 10
    0b1111, // 11
    0b0000, // 12 <
    0b1110, // 13
    0b1111, // 14
    0b0000, // 15 <
    0b0100, // 16
    0b1111, // 17
    0b0000, // 18 <
    0b0000, // 19
    0b1111, // 20
};


const unsigned char __CHAR_SNAKE_CORNER_LD[] = {

    0b0000, // 00 <
    0b0000, // 01
    0b1000, // 02
    0b0000, // 03 <
    0b0100, // 04
    0b1100, // 05
    0b0000, // 06 <
    0b0000, // 07
    0b1110, // 08
    0b0000, // 09 <
    0b0100, // 10
    0b1110, // 11
    0b0000, // 12 <
    0b1110, // 13
    0b1110, // 14
    0b0000, // 15 <
    0b0100, // 16
    0b1110, // 17
    0b0000, // 18 <
    0b0000, // 19
    0b1110, // 20
};


const unsigned char __CHAR_SNAKE_CORNER_RU[] = {

    0b0000, // 00 <
    0b0000, // 01
    0b1110, // 02
    0b0000, // 03 <
    0b0100, // 04
    0b1111, // 05
    0b0001, // 06 <
    0b0000, // 07
    0b1111, // 08
    0b0001, // 09 <
    0b0100, // 10
    0b1111, // 11
    0b0000, // 12 <
    0b0110, // 13
    0b0111, // 14
    0b0000, // 15 <
    0b0000, // 16
    0b0011, // 17
    0b0000, // 18 <
    0b0000, // 19
    0b0000, // 20
};


const unsigned char __CHAR_SNAKE_CORNER_LU[] = {

    0b0000, // 00 <
    0b0000, // 01
    0b1110, // 02
    0b0000, // 03 <
    0b0100, // 04
    0b1110, // 05
    0b0000, // 06 <
    0b0000, // 07
    0b1110, // 08
    0b0000, // 09 <
    0b0100, // 10
    0b1110, // 11
    0b0000, // 12 <
    0b1100, // 13
    0b1100, // 14
    0b0000, // 15 <
    0b0000, // 16
    0b1000, // 17
    0b0000, // 18 <
    0b0000, // 19
    0b0000, // 20
};






#define __CHAR_BLANK playerBigSprite

#define C(x) (const unsigned char *const) x



const unsigned char *const charSet[] = {

   // see ChName @ attribute.h


    C(char_parallaxBlank),                          // 00  CH_BLANK (RAM)
    C(__CHAR_DIRT),                                 // 01  CH_DIRT
    C(__CHAR_BRICKWALL),                            // 02  CH_BRICKWALL
    C(__CHAR_BRICKWALL),                            // 03  CH_MAGICWALL
    C(__CHAR_STEELWALL),                            // 04  CH_DOORCLOSED
    C(__CHAR_STEELWALL),                            // 05  CH_DOOROPEN_0       exit door (open)
    C(__CHAR_BLANK),                                // 06  CH_EXITBLANK        exit taken
    C(__CHAR_STEELWALL),                            // 07  CH_StEELWALL
    C(__CHAR_FIREFLY),                              // 08  CH_FIREFLY_0        (4 DIRECTIONS...)
    C(__CHAR_FIREFLY2),                             // 09  CH_FIREFLY_1
    C(__CHAR_FIREFLY3),                             // 10  CH_FIREFLY_2
    C(__CHAR_FIREFLY),                              // 11  CH_FIREFLY_3
    C(__CHAR_PEBBLE1),                              // 12  CH_PEBBLE1
    C(__CHAR_PEBBLE2),                              // 13  CH_PEBBLE2
    C(__CHAR_STEELWALL),                            // 14  CH_EASTEREGG
    C(__CHAR_BOULDER),                              // 15  CH_BOULDER
    C(__CHAR_BOULDER),                              // 16  CH_BOULDER_FALLING
    C(__CHAR_DOGE_00),                              // 17  CH_DIAMOND (RAM)
    C(__CHAR_DOGE_00),                              // 18  CH_DOGE_FALLING
    C(__CHAR_EXPLODETO_0),                          // 19  CH_EXPLODETODIAMOND_0
    C(__CHAR_EXPLODETO_1),                          // 20  CH_EXPLODETODIAMOND_1
    C(__CHAR_EXPLODETO_2),                          // 21  CH_EXPLODETODIAMOND_2 
    C(__CHAR_EXPLODETO_3),                          // 22  CH_EXPLODETODIAMOND_3
    C(__CHAR_EXPLODETO_4),                          // 23  CH_EXPLODETODIAMOND_4
    C(__CHAR_BLANK),                                // 24  CH_ROCKFORD_BIRTH
    C(__CHAR_MAGICWALL_1),                          // 25  CH_MAGICWALL_1
    C(__CHAR_MAGICWALL_2),                          // 26  CH_MAGICWALL_2
    C(__CHAR_MAGICWALL_3),                          // 27  CH_MAGICWALL_3
    C(__CHAR_BUTTERFLY_0),                          // 28  CH_BUTTERFLY_0  (4 DIRECTIONS...)
    C(__CHAR_BUTTERFLY_1),                          // 29  CH_BUTTERFLY_1
    C(__CHAR_BUTTERFLY_2),                          // 30  CH_BUTTERFLY_2
    C(__CHAR_BUTTERFLY_1),                          // 31  CH_BUTTERFLY_3  only 3 frames, so re-use 1
    C(__CHAR_AMOEBA_0),                             // 32
    C(__CHAR_AMOEBA_1),                             // 33
    C(__CHAR_AMOEBA_2),                             // 34
    C(__CHAR_AMOEBA_3),                             // 35
    C(__CHAR_BLANK),                                // 36  CH_ROCKFORD (RAM)
    C(__CHAR_DOGE_01),                              // 37  CH_DIAMOND_PULSE_0 (RAM)
    C(__CHAR_DOGE_02),                              // 38  CH_DIAMOND_PULSE_1 (RAM)
    C(__CHAR_DOGE_03),                              // 39  CH_DIAMOND_PULSE_2 (RAM)
    C(__CHAR_DOGE_04),                              // 40  CH_DIAMOND_PULSE_3 (RAM)
    C(__CHAR_DOGE_05),                              // 41  CH_DIAMOND_PULSE_4 (RAM)
    C(__CHAR_BLANK),                                // 42  CH_DIAMOND_PULSE_5  TYPE-HOLDER ONLY
    C(__CHAR_BLANK),                                // 43  CH_DIAMOND_PULSE_6  TYPE-HOLDER ONLY
    C(__CHAR_DOGE_00),                              // 44  CH_DIAMOND_STATIC (RAM) can switch animations

    C(__CHAR_LADDER_0),                             // 45  CH_LADDER_0
    C(__CHAR_LADDER_1),                             // 46  CH_LADDER_1
    C(__CHAR_LADDER_2),                             // 47  CH_LADDER_2

    // C(__CHAR_SPARKLE_0),                            // 45  CH_SPARKLE_0
    // C(__CHAR_SPARKLE_1),                            // 46  CH_SPARKLE_1
    // C(__CHAR_SPARKLE_2),                            // 47  CH_SPARKLE_2
    C(__CHAR_SPARKLE_3),                            // 48  CH_SPARKLE_3
    C(__CHAR_EXPLODETO_0),                          // 49  CH_EXPLODETOBLANK_0
    C(__CHAR_EXPLODETO_1),                          // 50  CH_EXPLODETOBLANK_1
    C(__CHAR_EXPLODETO_2),                          // 51  CH_EXPLODETOBLANK_2
    C(__CHAR_EXPLODETO_3),                          // 52  CH_EXPLODETOBLANK_3
    C(__CHAR_EXPLODETO_4),                          // 53  CH_EXPLODETOBLANK_4
    C(__CHAR_DOGE_02),                              // 54  CH_DIAMOND_GRAB
    C(__CHAR_DOGE_00),                              // 55  CH_DIAMOND_WITHOUT_DIRT
    C(__CHAR_DUST_0),                               // 56  CH_DUST_0
    C(__CHAR_DUST_1),                               // 57  CH_DUST_1
    C(char_Dust_2),                                 // 58  CH_DUST_2 (RAM)
    C(__CHAR_BOULDER_SHAKE),                        // 59  CH_BOULDER_SHAKE
    C(char_DustLeft_1),                             // 60  CH_DUST_LEFT_0
    C(char_DustLeft_1),                             // 61  CH_DUST_LEFT_1
    C(char_DustRight_1),                            // 62  CH_DUST_RIGHT_0
    C(char_DustRight_1),                            // 63  CH_DUST_RIGHT_1

    // merged boulders
    // 1 = up, 2 = right, 4 = down, 8 = left

    C(__CHAR_BOULDER),                              // 64  CH_BOULDER  0
    C(__CHAR_BOULDER_U),                            // 65  CH_BOULDER  1
    C(__CHAR_BOULDER_R),                            // 66  CH_BOULDER  2
    C(__CHAR_BOULDER_UR),                           // 67  CH_BOULDER  3
    C(__CHAR_BOULDER_D),                            // 68  CH_BOULDER  4
    C(__CHAR_BOULDER_UD),                           // 69  CH_BOULDER  5
    C(__CHAR_BOULDER_RD),                           // 70  CH_BOULDER  6
    C(__CHAR_BOULDER_URD),                          // 71  CH_BOULDER  7
    C(__CHAR_BOULDER_L),                            // 72  CH_BOULDER  8
    C(__CHAR_BOULDER_UL),                           // 73  CH_BOULDER  9
    C(__CHAR_BOULDER_RL),                           // 74  CH_BOULDER  10
    C(__CHAR_BOULDER_URL),                          // 75  CH_BOULDER  11
    C(__CHAR_BOULDER_DL),                           // 76  CH_BOULDER  12
    C(__CHAR_BOULDER_UDL),                          // 77  CH_BOULDER  13
    C(__CHAR_BOULDER_RDL),                          // 78  CH_BOULDER  14
    C(__CHAR_BOULDER_URDL),                         // 79  CH_BOULDER  15

    C(__CHAR_BOULDER_BROKEN),                       // 80  CH_BOULDER_BROKEN
    C(__CHAR_BOULDER_BROKEN),                       // 81  CH_BOULDER_BROKEN2

    C(__CHAR_DUST_ROCK_0),                          // 82  CH_DUST_ROCK_0
    C(__CHAR_DUST_ROCK_1),                          // 83  CH_DUST_ROCK_1
    C(__CHAR_DUST_ROCK_2),                          // 84  CH_DUST_ROCK_1

    C(__CHAR_DOGE_00),                              // 85  CH_DOGE_CONVERT

    C(__CHAR_SWITCH_LEFT_OFF),                      // 86  CH_SWITCH_LEFT_OFF
    C(__CHAR_SWITCH_LEFT_ON),                       // 87  CH_SWITCH_LEFT_ON
    C(__CHAR_PUSH_LEFT),                            // 88  CH_PUSH_LEFT
    C(__CHAR_HORIZONTAL_BAR),                       // 89  CH_HORIZONTAL_BAR
    C(__CHAR_PUSH_RIGHT),                           // 90  CH_PUSH_RIGHT    (TODO)
    C(__CHAR_PUSH_LEFT),                            // 91  CH_PUSH_LEFT_REVERSE
    C(__CHAR_PUSH_RIGHT),                           // 92  CH_PUSH_RIGHT_REVERSE

    C(__CHAR_PUSH_UP),                              // 93 CH_PUSH_UP,                     
    C(__CHAR_VERTICAL_BAR),                         // 94 CH_VERTICAL_BAR,                    
    C(__CHAR_PUSH_DOWN),                            // 95 CH_PUSH_DOWN,                    
    C(__CHAR_PUSH_UP),                              // 96 CH_PUSH_UP_REVERSE,                   // reverse
    C(__CHAR_PUSH_DOWN),                            // 97 CH_PUSH_DOWN_REVERSE,                 // reverse

    C(__CHAR_AMOEBA_0),
    C(__CHAR_AMOEBA_0),
    C(__CHAR_AMOEBA_2),

    C(__CHAR_SNAKE_CORNER_LD),
    C(__CHAR_SNAKE_CORNER_RD),
    C(__CHAR_SNAKE_CORNER_LU),
    C(__CHAR_SNAKE_CORNER_RU),



#if __ENABLE_LAVA
    C(__CHAR_LAVA_0),                               // 69  CH_LAVA_0
    C(__CHAR_LAVA_1),                               // 70  CH_LAVA_1
    C(__CHAR_LAVA_2),                               // 71  CH_LAVA_2
    C(__CHAR_LAVA_3),                               // 72  CH_LAVA_3
#endif
    
#if __ENABLE_WATER
    C(__CHAR_WATER_0),                              // 73  CH_WATER_0
    C(__CHAR_WATER_1),                              // 74  CH_WATER_1
    C(__CHAR_WATER_2),                              // 75  CH_WATER_2
    C(__CHAR_WATER_3),                              // 76  CH_WATER_3
#endif

};


//EOF

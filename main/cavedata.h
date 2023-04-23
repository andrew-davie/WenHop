#ifndef __CAVEDATA_H
#define __CAVEDATA_H

// #define CAVEFLAG_MIRROR_X       1
// #define CAVEFLAG_MIRROR_Y       2
// #define CAVEFLAG_MIRROR_XY      (CAVEFLAG_MIRROR_X + CAVEFLAG_MIRROR_Y)

extern const unsigned char *caveList[];
extern const int caveCount;
extern unsigned char caveFlags;

#define COLOURPOOL_SIZE 115

#define CAVEDEF_OVERVIEW 0x80
#define CAVEDEF_PARALLAX 0x40
#define CAVEDEF_RAINBOW 0x20
#define CAVEDEF_LEARN 0x10
#define CAVEDEF_ROCK_GENERATE 0x08

#define CAVE_REQUIRES_COMPATIBLE_PALETTE 0x80000000

#endif

#ifndef __ROCKFORD_H
#define __ROCKFORD_H

void moveRockford(unsigned char *this, unsigned char blanker);
void initRockford();

extern int frameAdjustX;
extern int frameAdjustY;

extern unsigned int pushCounter;
//extern int suppressDiamondSound;

extern enum FaceDirection rockfordFaceDirection;
extern int rockfordX, rockfordY;

extern bool rockfordDead;
//extern bool rockfordDeadRelease;

extern const signed char xInc[];
extern const signed char yInc[];

#endif
//EOF
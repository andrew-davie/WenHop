#ifndef __MELLON_H
#define __MELLON_H

void movePlayer(unsigned char *this);
void initPlayer();

extern int frameAdjustX;
extern int frameAdjustY;

extern unsigned int pushCounter;
// extern int suppressDiamondSound;

extern enum FaceDirectionX faceDirection;
extern int playerX, playerY;

extern bool playerDead;
// extern bool playerDeadRelease;

extern const signed char xInc[];
extern const signed char yInc[];

#endif
// EOF
#ifndef __MELLON_H
#define __MELLON_H

void movePlayer(unsigned char *thisss);
void initPlayer();

extern int frameAdjustX;
extern int frameAdjustY;

extern unsigned int pushCounter;

enum FaceDirectionX {
    FACE_LEFT = -1,
    FACE_RIGHT = 1,
    FACE_UP = -1,
    FACE_DOWN = 1,
};

extern enum FaceDirectionX faceDirection;
extern int playerX, playerY;

extern bool playerDead;
// extern bool playerDeadRelease;

extern const signed char xInc[];
extern const signed char yInc[];

#endif
// EOF
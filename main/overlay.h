#ifndef __OVERLAY_H
#define __OVERLAY_H

void Overlay(const unsigned char word[][5]);
void GameScheduleDrawOverlay();

extern int fSpeed;
extern int fIndex;
extern int rotateOffset;


extern const unsigned char overlayGameOver[][5];
extern const unsigned char overlayBoulderDash[][5];

extern const unsigned char (*overlayWord)[5];

#endif
//EOF
#ifndef __COLOUR_H
#define __COLOUR_H

void doFlash();
void setPalette();
void setBackgroundPalette(unsigned char *c);
void initColours();
void setFlash2(unsigned char col, int time);

void interleaveColour();
void loadPalette();
int convertColour(int colour);

#define FLASH(a, b)                                                                                \
    { setFlash2(a, b); }

extern unsigned char bgPalette[];
extern unsigned char fgPalette[];
extern int roller;
extern int interleavedColour;

#endif
// EOF

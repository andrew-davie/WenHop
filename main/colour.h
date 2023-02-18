#ifndef __COLOUR_H
#define __COLOUR_H


//void setFlash(unsigned char colourNTSC, unsigned char colourPAL, unsigned char colourSECAM, int time);
void doFlash();
void setPalette();
void setBackgroundPalette(unsigned char *c);
void initColours();
void setFlash2(unsigned char col, int time);
#if ENABLE_RAINBOW
void doRainbowBackground();
void rollRainbow();
#endif
void interleaveColour();
void loadPalette();
int convertColour(int colour);

#define FLASH(a,b) \
    { \
        setFlash2(a, b); \
    }

extern unsigned char bgPalette[22];
extern unsigned char fgPalette[2];
extern int roller;
extern bool interleavedColour;

#endif
//EOF
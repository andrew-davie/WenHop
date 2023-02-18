#ifndef __DECODECAVES_H
#define __DECODECAVES_H

struct CAVE_DEFINITION {

    unsigned char millingTime;
    unsigned char diamondValue;
    unsigned char extraDiamondValue;
    unsigned char weather;
    
    unsigned char randomInit[5];
    unsigned char diamondsRequired[5];
    unsigned char timeToComplete[5];
    
    unsigned char flags;            // CAVEDEF_...

    unsigned char borderCharacter;
    unsigned char interiorCharacter;

    unsigned char objectCount;
    unsigned char objectData;

//    unsigned char extraObjectType[4];
//    unsigned char extraObjectProbability[5][4];
};

extern struct CAVE_DEFINITION *theCave;

void decodeCave(int cave);
int decodeExplicitData(bool sfx);

enum DECODE_STATE {
    DECODE_NONE,
    DECODE_START,
    DECODE_STOP,
    DECODE_FLASH,
};

extern enum DECODE_STATE decodeState;
extern int decodingRow;
extern const unsigned char *theCaveData;
extern int totalDiamondsPossible;



#endif
//EOF
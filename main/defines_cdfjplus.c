/*****************************************************************************
File: declares_cdfjplus.c
Description: CDFJ Plus C Bankswitching Utilities
Chris Walton, Fred Quimby, Darrell Spice Jr, John Champeau
(C) Copyright 2022
******************************************************************************/

#include "defines_cdfjplus.h"

// Raw queue pointers
// Set fetcher pointer (offset from start of display data)
void setPointer(const int fetcher, const unsigned int offset) { _QPTR[fetcher] = offset << 16; }

// Set fetcher pointer and fraction
void setPointerFrac(const int fetcher, const unsigned int offset, const unsigned int frac) {
    _QPTR[fetcher] = (offset << 16) | (frac << 8);
}

// Set fetcher increment
void setIncrement(const int fetcher, const unsigned char whole, const unsigned char frac) {
    _QINC[fetcher] = ((whole << 8) | frac);
}

#ifndef CDFJ_NO_MUSIC

// Set waveform (32-byte offset in ROM)
void setWaveform(int wave, unsigned char offset) { _WAVEFORM[wave] = 0x40000800 + (offset << 5); }

// Set DA sample address
void setSamplePtr(unsigned int address) { _WAVEFORM[0] = address; }

// Set note frequency
void setNote(int note, unsigned int freq) {
    unsigned int setNoteFn = 0x00000751;
    asm volatile("mov r2, %0\n\t"
                 "mov r3, %1\n\t"
                 "mov r4, %2\n\t"
                 "mov lr, pc\n\t"
                 "bx  r4\n\r"
                 :
                 : "r"(note), "r"(freq), "r"(setNoteFn)
                 : "r2", "r3", "r4", "lr", "cc");
}

// Reset waveform
void resetWave(int wave) {
    unsigned int resetWaveFn = 0x00000755;
    asm volatile("mov r2, %0\n\t"
                 "mov r4, %1\n\t"
                 "mov lr, pc\n\t"
                 "bx r4\n\r"
                 :
                 : "r"(wave), "r"(resetWaveFn)
                 : "r2", "r4", "lr", "cc");
}

// Get waveform pointer
unsigned int getWavePtr(int wave) {
    unsigned int getWavePtrFn = 0x00000759;
    unsigned int ptr;
    asm volatile("mov r2, %1\n\t"
                 "mov r4, %2\n\t"
                 "mov lr, pc\n\t"
                 "bx r4\n\t"
                 "mov %0, r2\n\r"
                 : "=r"(ptr)
                 : "r"(wave), "r"(getWavePtrFn)
                 : "r2", "r4", "lr", "cc");
    return ptr;
}

// Set waveform size:
// 20 = 4096 bytes
// 21 = 2048 bytes
// 22 = 1024 bytes
// 23 = 512 bytes
// 24 = 256 bytes
// 25 = 128 bytes
// 26 = 64 bytes
// 27 = 32 bytes (DEFAULT)
// 28 = 16 bytes
// 29 = 8 bytes
// 30 = 4 bytes
// 31 = 2 bytes
void setWaveSize(int wave, unsigned int size) {
    unsigned int setWaveSizeFn = 0x0000075d;
    if (size < 20 || size > 31)
        return;
    asm volatile("mov r2, %0\n\t"
                 "mov r3, %1\n\t"
                 "mov r4, %2\n\t"
                 "mov lr, pc\n\t"
                 "bx r4\n\r"
                 :
                 : "r"(wave), "r"(size), "r"(setWaveSizeFn)
                 : "r2", "r3", "r4", "r5", "lr", "cc");
}

#endif

#ifndef CDFJ_NO_PITCH_TABLE

// Pitch table
const unsigned int _pitchTable[12] = {
    476196134, // C6s   77
    504512230, // D6    78
    534512088, // D6s   79
    566295831, // E6    80
    599969533, // F6    81
    635645578, // F6s   82
    673443031, // G6    83
    713488038, // G6s   84
    755914244, // A7    85
    800863244, // A7s   86
    848485051, // B7    87
    898938597  // C7    88
};

// Calculate frequency for note
unsigned int getPitch(unsigned int note) {
    // on the fly frequency calculations.  Saves from having to store
    // 88 values in both ROM and RAM. Note will be 1-88: 1=A0, 88=C7
    int scale = 0;
    while (note < 77) {
        scale++;
        note += 12;
    }
    return (_pitchTable[note - 77]) >> scale;
}

#endif

#ifndef CDFJ_NO_RANDOM32

// Generate random number
unsigned int getRandom32() {
    // using a 32-bit Galois LFSR as a psuedo random number generator.
    // http://en.wikipedia.org/wiki/Linear_feedback_shift_register#Galois_LFSRs
    static unsigned int random = 0x02468ace;
    return random = (random >> 1) ^ (unsigned int)(-(random & 1u) & 0xd0000001u);
}

#endif

#ifndef CDFJ_NO_MEMSET
// Set memory area to fill value
void myMemset(unsigned char *destination, unsigned int fill, unsigned int count) {
    unsigned int i;
    for (i = 0; i < count; ++i) {
        destination[i] = fill;
    }
}
#endif

#ifndef CDFJ_NO_MEMCOPY
// Copy memory from source to destination
void myMemcpy(unsigned char *destination, unsigned char *source, unsigned int count) {
    unsigned int i;
    for (i = 0; i < count; ++i) {
        destination[i] = source[i];
    }
}
#endif

#ifndef CDFJ_NO_MEMSET_INT
// Set memory area to fill value
// in theory 4x faster than myMemset(), but data must be WORD (4 byte) aligned
void myMemsetInt(unsigned int *destination, unsigned int fill, unsigned int count) {
    unsigned int i;
    for (i = 0; i < count; ++i) {
        destination[i] = fill;
    }
}
#endif

#ifndef CDFJ_NO_MEMCOPY_INT
// Copy memory from source to destination
// in theory 4x faster than myMemset(), but data must be WORD (4 byte) aligned
void myMemcpyInt(unsigned int *destination, unsigned int *source, unsigned int count) {
    unsigned int i;
    for (i = 0; i < count; ++i) {
        destination[i] = source[i];
    }
}
#endif

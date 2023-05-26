/*****************************************************************************
File: defines_cdfjplus.h
Description: CDFJ Plus C Bankswitching Utilities
Chris Walton, Fred Quimby, Darrell Spice Jr, John Champeau
(C) Copyright 2022
******************************************************************************/

#ifndef __CDFJPLUSDEFINES_H
#define __CDFJPLUSDEFINES_H

#define CDFJ_NO_RANDOM32

// Raw queue pointers
#define _QUE ((void *const)0x40000800)
#define _QUEUE ((unsigned char *)0x40000800)
#define _QUEUE_INT ((unsigned int *)0x40000800)
#define _QUEUE_SINT ((unsigned short int *)0x40000800)

#define DDR ((void *)0x40000800ULL)
#define RAM ((unsigned char *)DDR)
#define RAM_INT ((unsigned int *)DDR)
#define RAM_SINT ((unsigned short int *)DDR)

#define ROM ((unsigned char *)0)
#define ROM_INT ((unsigned int *)0)
#define ROM_SINT ((unsigned short int *)0)

#define RAM_START 0x40000800ULL

#if _PC_TABLE_SIZE == 2
#define TABLE unsigned short int
#else
#define TABLE unsigned int
#endif

// Queue variables
#define _QPTR ((unsigned int *const)0x40000098)
#define _QINC ((unsigned int *const)0x40000124)
#define _WAVEFORM ((unsigned int *const)0x400001B0)
#define _FF_OFFSET ((unsigned char *)0x400003E0ULL)

// Set fetcher pointer (offset from start of display data)
extern void setPointer(const int fetcher, const unsigned int offset);

// Set fetcher pointer and fraction
extern void setPointerFrac(const int fetcher, const unsigned int offset, const unsigned int frac);

// Set fetcher increment
extern void setIncrement(const int fetcher, const unsigned char whole, const unsigned char frac);

#ifndef CDFJ_NO_MUSIC

// Set waveform (32-byte offset in ROM)
extern void setWaveform(int wave, unsigned char offset);

// Set DA sample address
extern void setSamplePtr(unsigned int address);

// Set note frequency
extern void setNote(int note, unsigned int freq);

// Reset waveform
extern void resetWave(int wave);

// Get waveform pointer
extern unsigned int getWavePtr(int wave);

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

extern void setWaveSize(int wave, unsigned int size);

#endif

#ifndef CDFJ_NO_PITCH_TABLE

// Pitch table
extern const unsigned int _pitchTable[12];

// Calculate frequency for note
extern unsigned int getPitch(unsigned int note);

#endif

#ifndef CDFJ_NO_RANDOM32

// Generate random number
extern unsigned int getRandom32();

#endif

#ifndef CDFJ_NO_MEMSET
// Set memory area to fill value
extern void myMemset(unsigned char *destination, unsigned int fill, unsigned int count);

#endif

#ifndef CDFJ_NO_MEMCOPY
// Copy memory from source to destination
extern void myMemcpy(unsigned char *destination, unsigned char *source, unsigned int count);

#endif

#ifndef CDFJ_NO_MEMSET_INT
// Set memory area to fill value
// in theory 4x faster than myMemset(), but data must be WORD (4 byte) aligned
extern void myMemsetInt(unsigned int *destination, unsigned int fill, unsigned int count);

#endif

#ifndef CDFJ_NO_MEMCOPY_INT
// Copy memory from source to destination
// in theory 4x faster than myMemset(), but data must be WORD (4 byte) aligned
extern void myMemcpyInt(unsigned int *destination, unsigned int *source, unsigned int count);

#endif
#endif

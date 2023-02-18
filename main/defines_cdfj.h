/*****************************************************************************
File: defines_cdf.h
Description: CDF bankswitching utilities
(C) Copyright 2017 - Chris Walton, Fred Quimby, Darrell Spice Jr
used, modified and distributed with permission (April 2022)
******************************************************************************/

#ifndef __CDFDEFINES_H
#define __CDFDEFINES_H

// Start of C code in FLASH (uncomment to use)
// unsigned char * const _CBASE=(unsigned char*)0x800;

// Start of Atari banks in FLASH(uncomment to use)
// unsigned char * const _BANK0=(unsigned char*)0x1000;

// Raw queue pointers
#define DDR ((void*)0x40000800)

#define RAM ((unsigned char*)DDR)
#define RAM_INT ((unsigned int*)DDR)
#define RAM_SINT ((unsigned short int*)DDR)

#define ROM ((unsigned char*)0)
#define ROM_INT ((unsigned int*)0)
#define ROM_SINT ((unsigned short int*)0)

#define QPTR ((unsigned int *) 0x40000098)
#define QINC ((unsigned int *) 0x40000124)

#endif


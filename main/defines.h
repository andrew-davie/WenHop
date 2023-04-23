#ifndef __DEFINES_H
#define __DEFINES_H

#define RUN_FUNC RAM[_RUN_FUNC]
#define P0_X RAM[_P0_X]
#define P1_X RAM[_P1_X]
#define P0_Xb RAM[_P0_Xb]
#define P1_Xb RAM[_P1_Xb]

#define TV_TYPE RAM[_TV_TYPE]
#define KERNEL RAM[_KERNEL]

#define ARENA_COLOUR RAM[_ARENA_COLOUR]

#define SWCHA RAM[_SWCHA]
#define SWCHB RAM[_SWCHB]
#define INPT4 RAM[_INPT4]
#define INPT5 RAM[_INPT5]

#define JOY0_LEFT !(SWCHA & 0x40)
#define JOY0_RIGHT !(SWCHA & 0x80)
#define JOY0_UP !(SWCHA & 0x10)
#define JOY0_DOWN !(SWCHA & 0x20)
#define JOY0_FIRE !(INPT4 & 0x80)
#define JOY0_NOTHING ((SWCHA & 0xF0) == 0xF0)

#define JOY1_LEFT !(SWCHA & 0x04)
#define JOY1_RIGHT !(SWCHA & 0x08)
#define JOY1_UP !(SWCHA & 0x01)
#define JOY1_DOWN !(SWCHA & 0x02)
#define JOY1_FIRE !(INPT5 & 0x80)

// console switch states
#define GAME_RESET_PRESSED (!(SWCHB & 0x01))
#define GAME_SELECT_PRESSED (!(SWCHB & 0x02))
#define TV_TYPE_COLOR ((SWCHB & 0x08))
#define TV_TYPE_BW (!(SWCHB & 0x08))
#define LEFT_DIFFICULTY_A ((SWCHB & 0x40))
#define LEFT_DIFFICULTY_B (!(SWCHB & 0x40))
#define RIGHT_DIFFICULTY_A ((SWCHB & 0x80))
#define RIGHT_DIFFICULTY_B (!(SWCHB & 0x80))

// console detection
#define NTSC 0
#define PAL 1
#define PAL_60 2
#define SECAM 3
#define T1TCR *(unsigned int *)0xE0008004         // Timer Control Register
#define T1TC *(volatile unsigned int *)0xE0008008 // Timer Counter

#endif
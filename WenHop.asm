; Wen Hop CDFJ
; (c) 2023 Andrew Davie

; REMEMBER cannot use lda # as this is overloaded for datastream access!!
; use ldx # or ldy # instead

        PROCESSOR 6502
        include "vcs.h"
        include "macro.h"
        include "cdfjplus.h"

;===============================================================================
; Project Configuration
;----------------------------------------
;   _PC_ROM_SIZE        Size of ROM, in kilobytes
;        32              32 KB of ROM and  8 KB of RAM
;        64              64 KB of ROM and 16 KB of RAM
;       128             128 KB of ROM and 16 KB of RAM
;       256             256 KB of ROM and 32 KB of RAM
;       512             512 KB of ROM and 32 KB of RAM
;
;   _PC_DD_SIZE         Size of Display Data, in bytes
;       4096
;
;   _PC_CDFJ_FF         Select CDFJ+ driver based on Fast Fetcher usage:
;       FF_LDA          LDA # only
;       FF_LDA_LDX      LDA # and LDX #
;       FF_LDA_LDY      LDA # and LDY #
;       FF_LDA_LDX_LDY  LDA #, LDX #, and LDY #
;
;   _PC_FF_OFFSET       offset for Fast Fetchers
;       0 - 220         adjusts which LDA # values are overridden for fast
;                       fetcher use (and optionally LDX # and/or LDY #)
;===============================================================================

_PC_ROM_SIZE    = 64
_PC_DD_SIZE     = 4096 - 512
_PC_CDFJ_FF     = FF_LDA
_PC_FF_OFFSET   = $80

;===============================================================================
; Define constants
;----------------------------------------
;   Define constants used by 6507 code, as well as those used by both
;   6507 code and the C code.
;
;   To make it easier to synchronize values between the 6507 and C code the
;   make process will auto-export anything with a _ prefix to file:
;       main/defines_from_dasm_for_c.h
;
;   and anything with a _PC_ prefix to file:
;       main/symbols_from_dasm_for_lds.h
;
;   it does this by using awk to parse the symbol file created by dasm
;===============================================================================


__ENABLE_TRAINER = 0
__ENABLE_ATARIVOX = 0       ; 415 bytes
__ENABLE_WATER = 0

__ENABLE_LAVA2 = 1
__ENABLE_WATER2 = 1

 IF __ENABLE_TRAINER == 1
__ENABLE_DEMO = 0       ; 260 bytes + joystick data (DO NOT ADJUST)
 ELSE
__ENABLE_DEMO = 0;1       ; 260 bytes + joystick data (adjust this on/off as required)

 ENDIF

    IF __ENABLE_ATARIVOX
        include "atarivox/speakjet.h"
    ENDIF


; Symbols prefixed with _ are exported to 'main/defines_from_dasm_for_c.h'
; This is done via 'awk' in the makefile.


; which ARM function to run
; also must update runFunc table in main.c with same order

_FN_SYSTEM_RESET        = 0         ; SystemReset()
_FN_MENU_OS             = 1         ; MenuOverScan()
_FN_MENU_VB             = 2         ; MenuVerticalBlank()
_FN_MENU_IDLE           = 3         ; SchedulerMenu()
_FN_INIT_GAME_KERNEL    = 4         ; InitializeGameKernel()
_FN_GAME_OS             = 5         ; GameOverscan()
_FN_GAME_VB             = 6         ; GameVerticalBlank()
_FN_GAME_IDLE           = 7         ; Scheduler()


_DS_COLUP0      = DS0DATA
_DS_COLUP1      = DS1DATA

_DS_SPEECH      = DS2DATA

; datastream usage for Game Kernel
_DS_PF0_LEFT    = DS4DATA
_DS_PF1_LEFT    = DS5DATA
_DS_PF2_LEFT    = DS6DATA
_DS_PF0_RIGHT   = DS7DATA
_DS_PF1_RIGHT   = DS8DATA
_DS_PF2_RIGHT   = DS9DATA

_DS_CTRLPF      = DS10DATA

_DS_GRP0a       = DS11DATA
_DS_GRP1a       = DS12DATA

_DS_COLUBK      = DS13DATA

_DS_AUDV0       = DS14DATA
_DS_AUDC0       = DS15DATA
_DS_AUDF0       = DS16DATA

_DS_GRP0b       = DS17DATA
_DS_GRP1b       = DS18DATA
_DS_GRP0c       = DS19DATA
_DS_GRP1c       = DS20DATA

_DS_COLUPF      = DS21DATA


; timer values
VB_TIM64T = 43
OS_TIM64T = 29

; controls spacing in main menu

_ARENA_SCANLINES    = 198   ; number of scanlines for the arena
ARENA_BUFFER_SIZE   = _ARENA_SCANLINES    ; PF buffer size for largest arena

;===============================================================================
; Define custom Macros
;----------------------------------------
;   These functions appear at the same position in both banks of 6507 code
;===============================================================================


; (none)


;===============================================================================
; Define other macros (use anywhere)
;===============================================================================

        MAC CHECK_ARENA_BUFFER_SIZE
        ; trigger a compile time error if the arena buffer need to be increased
            IF {1} > ARENA_BUFFER_SIZE
                echo "Increase ARENA_BUFFER_SIZE to",[{1}]d
                err
            ENDIF
        ENDM


;===============================================================================
; Define Zero Page RAM Usage
;----------------------------------------
;   ZP RAM variables can only be seen by the 6507 CPU
;   Likewise C variables can only be seen by the ARM CPU
;===============================================================================

        SEG.U VARS
        ORG $80

Mode:           ds 1    ; $00 = splash, $01 = menu, $80 = game
                        ; these values allow for easy testing of Mode:
                        ;   LDA Mode
                        ;   BMI GAME_ROUTINE
                        ;   BNE MENU_ROUTINE
                        ;   BEQ SPLASH_routine
TimeLeftOS:     ds 1
TimeLeftVB:     ds 1

tv_type         ds 1                    ; 0 NTSC, 1 PAL, 2 = PAL-60 3 SECAM  TODO: init
kernel          ds 1       ; 0 copyright, 1 menu, 2 game, 3 stats
currentKernel   ds 1

    IF __ENABLE_ATARIVOX
;spoken          ds 1
what            ds 1
∫    ENDIF

    IF __ENABLE_ATARIVOX
highScoreSK         ds 3
startCave           ds 1        ; cave * 5
startLevel          ds 1
offsetSK            ds 1        ; for calculating the SK slot address

    ENDIF


        echo "----",($00FE - *) , "bytes of RAM left (space reserved for 2 byte stack)"



;===============================================================================
; Define Start of Cartridge
;----------------------------------------
;   CDFJ cartridges must start with the Harmony/Melody driver.  The driver is
;   the ARM code that emulates the CDFJ coprocessor.
;===============================================================================

                    SEG CODE
                    ORG 0

    include "configure_cdfjplus.h"

SIZEOF_CDFJ_DRIVER = *
        echo "CDFJ driver = $0 - ", *, "(",[*]d, "bytes)"

;===============================================================================

                    ORG $0800
                    RORG $F000

START6502

; PLACE THESE EARLY IF POSSIBLE, SO THAT THE $EA-WAIT LOOP HAS PLENTY OF LEEWAY/TIME

; idleProcess first calls the OS/VB (passed in Y) and then the idle routine. It continues
; to call idle until the timer is approaching the auto-sync time. The less 6507 cycles
; used here, the more ARM code  can be executed, so high efficiency is crucial.
; ASSUMED we don't overflow time - otherwise INTIM will fail and we get scanline > 262


idleProcess         ; y = ARM function ID to call

                    ldx #0
                    stx DSPTR
                    stx DSPTR
                    sty DSWRITE                     ; --> _RUN_FUNC (OS or VB)

                    ldy #$FF                        ; Run ARM code w/out digital audio interrupts
                    sty CALLFN                      ; runs main() in the C code (6507 is $EA-locked)

    ; EA-wait resumes here

                    stx DSPTR
                    stx DSPTR

                    ldx #_FN_GAME_IDLE
                    stx DSWRITE                     ; --> _RUN_FUNC (IDLE)

                    sty CALLFN

    ; EA-wait resumes here

safeTimerWait       lda INTIM
                    bpl safeTimerWait
                    rts


CallArmCode

    ; Y = function to run

                    ldx #<_DS_TO_ARM
                    stx DSPTR
                    stx DSPTR

                    sty DSWRITE                      ; --> _RUN_FUNC
                    ldx SWCHA
                    stx DSWRITE                      ; joysticks -> _SWCHA
                    ldx SWCHB
                    stx DSWRITE                      ; switches ->_SWCHB
                    ldx INPT4
                    stx DSWRITE                      ; left fire ->_INPT4
;                    ldx INPT5
;                    stx DSWRITE                      ; right fire ->_INPT5

runARM              ldx #$FF                         ; FF = Run ARM code w/out digital audio interrupts
                    stx CALLFN                       ; runs main() in the C code (6507 is $EA-locked)

    ; EA-wait resumes here

                    rts



;    echo "early 6502 code (ARM calls) end at ", *


SPEECH_TABLE

     MAC WORDIS
     .word SPEAK_{1}
     ENDM

__WORD_COUNT SET 0

    IF __ENABLE_ATARIVOX

__WORD_COUNT SET 9

__WORD_NULL         = 0

__WORD_BOO          = 1
__WORD_WATCHOUT     = 2
__WORD_GETREADY     = 3
__WORD_AARGH        = 4
__WORD_WET          = 5
__WORD_TOO_LATE     = 6
__WORD_LETSGOBABY   = 7
__WORD_TRAP         = 8
__WORD_DOSOMETHING  = 9
__WORD_RAGEQUIT     = 10
__WORD_GOODBYE      = 11
__WORD_SOSAD        = 12
__WORD_WENHOP  = 13
__WORD_CAVE_ONE     = 14


__SPEECH_ADDRESS

    WORDIS NULL
    WORDIS BOO
    WORDIS WATCHOUT
    WORDIS GETREADY
    WORDIS AARGH
    WORDIS WET
    WORDIS TOO_LATE
    WORDIS LETSGOBABY
    WORDIS TRAP
    WORDIS DOSOMETHING
    WORDIS RAGEQUIT
    WORDIS GOODBYE
    WORDIS SOSAD
    WORDIS WENHOP
    WORDIS CAVE_ONE

;    echo "   - SPEECH TABLE from", SPEECH_TABLE, "to", *, "(", (* - SPEECH_TABLE) , "bytes)"

    ENDIF


; __COPYRIGHT_START

;     include "copyright.asm"

;    echo "   - COPYRIGHT DATA from", __COPYRIGHT_START, "to", *, "(", (* - __COPYRIGHT_START) , "bytes)"


#if __ENABLE_DEMO

R = 0
L = 1
U = 2
D = 3
NONE = 4




__DEMO_JOYSTICK

    MAC M ; a,b
        dc {1} * 16 + {2}
    ENDM

    MAC DOUBLECLICK
        M BUT+NONE,1
        M NONE,1
        M BUT+NONE,1
        M NONE, {1}-3
    ENDM

BUT = 0x80



 M NONE, 10


 M NONE, 15
 M R,1
 M NONE, 3
 M BUT+R,5
 M D,1
 M R,2
 M D,1
 M NONE, 3
 M BUT+L,5

 M R,2
 M D,2
 M R,2

 M NONE,6
 M U,2
 M R,5

 M U,1
 M R,2
 M D,3
 M R,3

 M U,3
 M R,6

 M U,1
 M R,5
 M D,2
 M NONE,5
 M BUT+L,3

 M R,4
 M NONE,4
 M U,2
 M NONE,3
 M BUT+R,3
 M U,1
 M R,4
 M D,3
 M L,2
 M D,4
 M L,4

 M NONE,4
 M U,1
 M NONE,6

  M D,5
 M R,3
 M U,1
 M L,7
 M D,2
 M L,4
 M U,1
 M R,1
 M L,2
 M U,1
 M L,4
 M D,2
;  M BUT+R,5
;  M L,1
;  M NONE,4
;  M BUT+U,1


 M NONE, 15

 M R,1
 M L,2
 M NONE,5
 M U,4



 M L,3
 M D,2
 M L,8
 M U,1
 M NONE,4
 M D,3
 M R,1

 M U,2
 M L,5
 M U,3

 M D,6

 M R,2
 M D,1
 M R,1
 M D,1

 M R,1
 M D,3

 M R,5
 M D,1
 M R,5

 M U,3
 M R,1
 M U,2

 M NONE,5

 M R,3
 M D,3
 M R,1

 M D,2
 M R,2
 M L,1
 M U,1

 M L,1
 M U,1
 M L,1

 M U,1
 M R,4
 M D,2
 M R,5

 M D,1
 M R,2
 M U,5

 M R,5
 M NONE,5
 M D,1

 M NONE, 15

 ;DOUBLECLICK 10
;  M NONE,10
;  M U,1
;  M D,1
;  M L,2
;  M D,2
;  M BUT+NONE,10
;  M R,6
;  M U,3
;  M R,7
;  M D,1


 M    0,   0


    echo "   - DEMO JOYSTICK Cfrom", __DEMO_JOYSTICK, "to", *, "(", [* - __DEMO_JOYSTICK) , "bytes)"
#ENDIF



__COLOUR_POOL
;const unsigned char colourPool[][4] = {

    ; NTSC, PAL, SECAM

;ffbf8bbc
;b4460202

; __COMPATIBLE_COMPATIBLE_PALETTE = 1
__PALETTE_COUNT = 16

 ;   dc $14, 0x94, 4, 4

    ;0

    dc $14, 0x94, 4, 4
;    dc 0x28, 0x96, 4, 4
;    dc 12, 10, 14, 14

    ;1
    dc  0xA6, 0x24, 0x32, 0x52
;    dc 0x96, 0x26, 0x34, 0x34
;    dc 10, 12, 8, 8

    ; 2
    dc 0x88, 0xD6, 20, 20
;    dc 0xE8, 0x66, 0xA2, 0xA2 ;0xD6, 0x46, 18, 18
;    dc 6, 10, 12, 12

    ; 3
    dc 0xA6, 0xC4, 0x46, 0x22
;    dc 0x2A, 0x68, 0x44, 0x44 ;0x94, 0x54, 0x44, 0x44
;    dc 10, 12, 4, 4

    ; 4
    dc 0x98, 0x24, 4, 4
;    dc 0xB4, 0x46, 2, 2
;    dc 10, 12, 8, 8

    ; 5
    dc 0x26, 0xD4, 0x84, 0xE4     ; NTSC  BOO's preferred
;        dc 0x44, 0x94, 0xA2, 0xA2
;    dc 0x44, 0x34, 0x84, 0xE4
;    dc 10, 12, 8, 8

    ; 6
    dc 0x98, 0x24, 0x86, 0x46
;    dc 0xB6, 0x28, 0x82, 0x82
;    dc 10, 12, 8, 8

    ; 7
    dc 0x44, 0xA6, 0xC6, 0xE6
;    dc 0x4A, 0xB4, 0x64, 0x64 ;0x66, 0xB4, 0xC2, 0xC2
;    dc 10, 12, 8, 8

    ; 8
    dc 0x96, 0x24, 0xF6, 0xC6
;    dc 0x68, 0x76, 0x54, 0x54 ;0xB4, 0x24, 0x32, 0x32
;    dc 10, 12, 8, 8

    ; 9=J
    dc 0x26, 0x46, 0x98, 0x66
;    dc 0x96, 0x84, 0x82, 0x82
;    dc 10, 12, 8, 8

    ; 10=K
    dc 0x36, 0x94, 0xC6, 0xb4
 ;   dc 0x46, 0x32, 0xA2, 0xA2
 ;   dc 10, 12, 8, 8

    ; 11=L
    dc 0x06, 0x34, 0x96, 0xB4
 ;   dc 0xEA, 0x46, 0x94, 0x94
 ;   dc 10, 12, 8, 8

    ; 12
    dc 0xD6, 0x34, 0xA6, 0x74
 ;   dc 0x96, 0x46, 0xA2, 0xA2
 ;   dc 8, 4, 10, 10

    ; 13
    dc 0x38, 0xD4, 0x44, 0xC4
 ;   dc 0x66, 0x72, 0x92, 0x92
 ;   dc 10, 8, 12, 12

    ; 14 tan rock purple soil aqua doge good glint
    dc 0x38, 0xA4, 0x64, 0x44
 ;   dc 0x96, 0x68, 0x92, 0x92 ;0x66, 0x72, 0x92, 0x92
 ;   dc 4, 8, 10, 10

    ; 15 purple rock light blue doge green mortar good glint
    dc 0x78, 0xC4, 0x26, 0xB4
 ;   dc 0x4A, 0x94, 0xA4, 0xA4 ;0x66, 0x72, 0x92, 0x92
 ;   dc 0xA0, 0x08, 0x04, 0x04






;     ;0

; ;    dc $14, 0xA4, 4, 4
;     dc 0x2A, 0xA8, 4, 4
; ;    dc 12, 10, 14, 14

;     ;1
; ;    dc 0x56, 0x24, 0xD2, 0xC2
;     dc 0xA6, 0x26, 0xD4, 0xD4
; ;    dc 10, 12, 8, 8

;     ; 2
; ;    dc 0x58, 0yD8, 0x28, 0xC4
;     dc  0x08, 0x46, 0x52, 0x52 ;0yD6, 0x36, 18, 18
; ;    dc 6, 10, 12, 12

;     ; 3*
; ;    dc 0x56, 0yC4, 0x36, 0x22
;     dc 0x2A, 0x48, 0x34, 0x34 ;0xA4, 0xC4, 0x34, 0x34
; ;    dc 10, 12, 4, 4

;     ; 4
; ;    dc 0xA8, 0x24, 4, 4
;     dc 0x94, 0x36, 2, 2
; ;    dc 10, 12, 8, 8

;     ; 5*
;     dc 0x26, 0xD4, 0x54, 0x04     ; NTSC  BOO's preferred
; ;        dc 0x34, 0xA4, 0x52, 0x52
; ;    dc 0x34, 0xD4, 0x54, 0x04

; ;x    dc 0xA8, 0x36, 0x92, 0x92
; ;    dc 10, 12, 8, 8

;     ; 6
; ;    dc 0xA8, 0x24, 0x56, 0x36
;     dc 0x96, 0x28, 0x52, 0x52
; ;    dc 10, 12, 8, 8

;     ; 7
; ;    dc 0x34, 0x56, 0yC6, 0x06
;     dc 0x3A, 0x94, 0x44, 0x44 ;0x46, 0x94, 0yC2, 0yC2
; ;    dc 10, 12, 8, 8

;     ; 8
; ;    dc 0xA6, 0x24, 0yF6, 0yC6
;     dc 0x48, 0xA6, 0xC4, 0xC4 ;0x94, 0x24, 0xD2, 0xD2
; ;    dc 10, 12, 8, 8

;     ; 9=J
; ;    dc 0x26, 0x36, 0xA8, 0x46
;     dc 0xA6, 0x54, 0x52, 0x52
; ;    dc 10, 12, 8, 8

;     ; 10=K
; ;    dc 0xD6, 0xA4, 0yC6, 0x94
; ;    dc 0x36, 0xD2, 0x52, 0x52
;     dc 0x28, 0x06, 0x52, 0x52
; ;    dc 10, 12, 8, 8

;     ; 11=L
; ;    dc 0y06, 0xD4, 0xA6, 0x94
;     dc 0x0A, 0x36, 0xA4, 0xA4
; ;    dc 10, 12, 8, 8

;     ; 12
; ;    dc 0yD6, 0xD4, 0x56, 0xA4
;     dc 0xA6, 0x36, 0x52, 0x52
; ;    dc 8, 4, 10, 10

;     ; 13
;     dc 0xD8, 0xD4, 0x34, 0xC4
; ;x    dc 0x46, 0xA2, 0xA2, 0xA2
; ;    dc 10, 8, 12, 12

;     ; 14 tan rock purple soil aqua doge good glint
; ;    dc 0xD8, 0x54, 0x44, 0x34
;     dc __COMPATIBLE_COMPATIBLE_PALETTE + 0xA6, 0x48, 0xA2, 0xA2 ;0x46, 0xA2, 0xA2, 0xA2
; ;    dc 4, 8, 10, 10

;     ; 15 purple rock light blue doge green mortar good glint *
;     dc __COMPATIBLE_COMPATIBLE_PALETTE + 0xA8, 0xC4, 0x26, 0x94
; ;x    dc 0x3A, 0xA4, 0x54, 0x54 ;0x46, 0xA2, 0xA2, 0xA2
; ;    dc 0x50, 0y08, 0y04, 0y04


    #include "characterset.asm"



;    echo "   - CHARACTER SET DATA from", CHAR_BLOCK_START, "to", *, "(", [(* - CHAR_BLOCK2_START)]d , " bytes, ", [(* - CHAR_BLOCK2_START) / CHAR_SIZE]d, "characters)"

B________ = 0
B_______X = 1
B______X_ = 2
B______XX = 3
B_____X__ = 4
B_____X_X = 5
B_____XX_ = 6
B_____XXX = 7
B____X___ = 8
B____X__X = 9
B____X_X_ = 10
B____X_XX = 11
B____XX__ = 12
B____XX_X = 13
B____XXX_ = 14
B____XXXX = 15
B___X____ = 16
B___X___X = 17
B___X__X_ = 18
B___X__XX = 19
B___X_X__ = 20
B___X_X_X = 21
B___X_XX_ = 22
B___X_XXX = 23
B___XX___ = 24
B___XX__X = 25
B___XX_X_ = 26
B___XX_XX = 27
B___XXX__ = 28
B___XXX_X = 29
B___XXXX_ = 30
B___XXXXX = 31
B__X_____ = 32
B__X____X = 33
B__X___X_ = 34
B__X___XX = 35
B__X__X__ = 36
B__X__X_X = 37
B__X__XX_ = 38
B__X__XXX = 39
B__X_X___ = 40
B__X_X__X = 41
B__X_X_X_ = 42
B__X_X_XX = 43
B__X_XX__ = 44
B__X_XX_X = 45
B__X_XXX_ = 46
B__X_XXXX = 47
B__XX____ = 48
B__XX___X = 49
B__XX__X_ = 50
B__XX__XX = 51
B__XX_X__ = 52
B__XX_X_X = 53
B__XX_XX_ = 54
B__XX_XXX = 55
B__XXX___ = 56
B__XXX__X = 57
B__XXX_X_ = 58
B__XXX_XX = 59
B__XXXX__ = 60
B__XXXX_X = 61
B__XXXXX_ = 62
B__XXXXXX = 63
B_X______ = 64
B_X_____X = 65
B_X____X_ = 66
B_X____XX = 67
B_X___X__ = 68
B_X___X_X = 69
B_X___XX_ = 70
B_X___XXX = 71
B_X__X___ = 72
B_X__X__X = 73
B_X__X_X_ = 74
B_X__X_XX = 75
B_X__XX__ = 76
B_X__XX_X = 77
B_X__XXX_ = 78
B_X__XXXX = 79
B_X_X____ = 80
B_X_X___X = 81
B_X_X__X_ = 82
B_X_X__XX = 83
B_X_X_X__ = 84
B_X_X_X_X = 85
B_X_X_XX_ = 86
B_X_X_XXX = 87
B_X_XX___ = 88
B_X_XX__X = 89
B_X_XX_X_ = 90
B_X_XX_XX = 91
B_X_XXX__ = 92
B_X_XXX_X = 93
B_X_XXXX_ = 94
B_X_XXXXX = 95
B_XX_____ = 96
B_XX____X = 97
B_XX___X_ = 98
B_XX___XX = 99
B_XX__X__ = 100
B_XX__X_X = 101
B_XX__XX_ = 102
B_XX__XXX = 103
B_XX_X___ = 104
B_XX_X__X = 105
B_XX_X_X_ = 106
B_XX_X_XX = 107
B_XX_XX__ = 108
B_XX_XX_X = 109
B_XX_XXX_ = 110
B_XX_XXXX = 111
B_XXX____ = 112
B_XXX___X = 113
B_XXX__X_ = 114
B_XXX__XX = 115
B_XXX_X__ = 116
B_XXX_X_X = 117
B_XXX_XX_ = 118
B_XXX_XXX = 119
B_XXXX___ = 120
B_XXXX__X = 121
B_XXXX_X_ = 122
B_XXXX_XX = 123
B_XXXXX__ = 124
B_XXXXX_X = 125
B_XXXXXX_ = 126
B_XXXXXXX = 127
BX_______ = 128
BX______X = 129
BX_____X_ = 130
BX_____XX = 131
BX____X__ = 132
BX____X_X = 133
BX____XX_ = 134
BX____XXX = 135
BX___X___ = 136
BX___X__X = 137
BX___X_X_ = 138
BX___X_XX = 139
BX___XX__ = 140
BX___XX_X = 141
BX___XXX_ = 142
BX___XXXX = 143
BX__X____ = 144
BX__X___X = 145
BX__X__X_ = 146
BX__X__XX = 147
BX__X_X__ = 148
BX__X_X_X = 149
BX__X_XX_ = 150
BX__X_XXX = 151
BX__XX___ = 152
BX__XX__X = 153
BX__XX_X_ = 154
BX__XX_XX = 155
BX__XXX__ = 156
BX__XXX_X = 157
BX__XXXX_ = 158
BX__XXXXX = 159
BX_X_____ = 160
BX_X____X = 161
BX_X___X_ = 162
BX_X___XX = 163
BX_X__X__ = 164
BX_X__X_X = 165
BX_X__XX_ = 166
BX_X__XXX = 167
BX_X_X___ = 168
BX_X_X__X = 169
BX_X_X_X_ = 170
BX_X_X_XX = 171
BX_X_XX__ = 172
BX_X_XX_X = 173
BX_X_XXX_ = 174
BX_X_XXXX = 175
BX_XX____ = 176
BX_XX___X = 177
BX_XX__X_ = 178
BX_XX__XX = 179
BX_XX_X__ = 180
BX_XX_X_X = 181
BX_XX_XX_ = 182
BX_XX_XXX = 183
BX_XXX___ = 184
BX_XXX__X = 185
BX_XXX_X_ = 186
BX_XXX_XX = 187
BX_XXXX__ = 188
BX_XXXX_X = 189
BX_XXXXX_ = 190
BX_XXXXXX = 191
BXX______ = 192
BXX_____X = 193
BXX____X_ = 194
BXX____XX = 195
BXX___X__ = 196
BXX___X_X = 197
BXX___XX_ = 198
BXX___XXX = 199
BXX__X___ = 200
BXX__X__X = 201
BXX__X_X_ = 202
BXX__X_XX = 203
BXX__XX__ = 204
BXX__XX_X = 205
BXX__XXX_ = 206
BXX__XXXX = 207
BXX_X____ = 208
BXX_X___X = 209
BXX_X__X_ = 210
BXX_X__XX = 211
BXX_X_X__ = 212
BXX_X_X_X = 213
BXX_X_XX_ = 214
BXX_X_XXX = 215
BXX_XX___ = 216
BXX_XX__X = 217
BXX_XX_X_ = 218
BXX_XX_XX = 219
BXX_XXX__ = 220
BXX_XXX_X = 221
BXX_XXXX_ = 222
BXX_XXXXX = 223
BXXX_____ = 224
BXXX____X = 225
BXXX___X_ = 226
BXXX___XX = 227
BXXX__X__ = 228
BXXX__X_X = 229
BXXX__XX_ = 230
BXXX__XXX = 231
BXXX_X___ = 232
BXXX_X__X = 233
BXXX_X_X_ = 234
BXXX_X_XX = 235
BXXX_XX__ = 236
BXXX_XX_X = 237
BXXX_XXX_ = 238
BXXX_XXXX = 239
BXXXX____ = 240
BXXXX___X = 241
BXXXX__X_ = 242
BXXXX__XX = 243
BXXXX_X__ = 244
BXXXX_X_X = 245
BXXXX_XX_ = 246
BXXXX_XXX = 247
BXXXXX___ = 248
BXXXXX__X = 249
BXXXXX_X_ = 250
BXXXXX_XX = 251
BXXXXXX__ = 252
BXXXXXX_X = 253
BXXXXXXX_ = 254
BXXXXXXXX = 255



__DIGIT_SHAPE

       dc B__X__X__
       dc B__X_XXX_
       dc B_XX_XXX_
       dc B_XX_XXX_
       dc B_XX_X_X_
       dc B_XX_X_X_
       dc B__X_X_X_
       dc B__X_X_X_
       dc B__X_X_X_
       dc B__X_X_X_
       dc B__X_X_X_
       dc B__X_X_X_
       dc B__X_X_X_
       dc B__X_X_X_
       dc B__X_XXX_
       dc B__X_XXX_
       dc B__X_XXX_
       dc B__X_XXX_
       dc B__X__X__
       dc B________


       dc B_X___X__
       dc BXXX_XXX_
       dc BXXX_XXX_
       dc BXXX_XXX_
       dc BX_X_X_X_
       dc B__X___X_
       dc B__X___X_
       dc B_XX___X_
       dc B_X___XX_
       dc B_XX_XXX_
       dc B_XX_XX__
       dc B__X_X___
       dc B__X_X___
       dc BX_X_X_X_
       dc BXXX_XXX_
       dc BXXX_XXX_
       dc BXXX_XXX_
       dc BXXX_XXX_
       dc B_X__XXX_
       dc B________


       dc BXXX_X___
       dc BXXX_X___
       dc BXXX_X___
       dc BX_X_X_X_
       dc BX___X_X_
       dc BX___X_X_
       dc BXX__X_X_
       dc BXXX_X_X_
       dc BXXX_X_X_
       dc BXXX_XXX_
       dc B__X_XXX_
       dc B__X_XXX_
       dc BX_X_XXX_
       dc BX_X___X_
       dc BXXX___X_
       dc BXXX___X_
       dc BXXX___X_
       dc BXXX___X_
       dc B_X____X_
       dc B________


       dc BXXX__X__
       dc BXXX_XXX_
       dc BXXX_XXX_
       dc BXXX_XXX_
       dc BX_X_X_X_
       dc B__X_X___
       dc B__X_XX__
       dc B__X_XXX_
       dc B__X_XXX_
       dc B_XX_XXX_
       dc B_X__X_X_
       dc B_X__X_X_
       dc B_X__X_X_
       dc B_X__X_X_
       dc B_X__XXX_
       dc B_X__XXX_
       dc B_X__XXX_
       dc B_X__XXX_
       dc B_X___X__
       dc B________


       dc B_X___X__
       dc BXXX_XXX_
       dc BXXX_XXX_
       dc BXXX_XXX_
       dc BX_X_X_X_
       dc BX_X_X_X_
       dc BX_X_X_X_
       dc BX_X_XXX_
       dc BXXX__X__
       dc BXXX__X__
       dc B_XX_XXX_
       dc B__X_X_X_
       dc B__X_X_X_
       dc BX_X_X_X_
       dc BXXX_XXX_
       dc BXXX_XXX_
       dc BXXX_XXX_
       dc BXXX_XXX_
       dc B_X___X__
       dc B________


    ;    dc B________
    ;    dc B________
    ;    dc B________
    ;    dc B________
    ;    dc B________
    ;    dc B________
    ;    dc B________
    ;    dc B________
    ;    dc B________
    ;    dc B________
    ;    dc B________
    ;    dc B________
    ;    dc B________
    ;    dc B________
    ;    dc B________
    ;    dc B________
    ;    dc B________
    ;    dc B________


    ;    dc B_X___X__
    ;    dc B_X___X__
    ;    dc B_X___X__
    ;    dc B_X______
    ;    dc B_X__XXX_
    ;    dc B_X__XXX_
    ;    dc B_X__XXX_
    ;    dc B_X__XXX_
    ;    dc B_X___X__
    ;    dc B_X___X__
    ;    dc B_X___X__
    ;    dc B_____X__
    ;    dc B____X_X_
    ;    dc B____X_X_
    ;    dc B_X__X_X_
    ;    dc B_X__X_X_
    ;    dc B_X__X_X_
    ;    dc B________
    ;    dc B________
    ;    dc B________


       dc B___XXX__
       dc B___XXX__
       dc B___XXX__
       dc B___X_XX_
       dc B___X__X_
       dc B___X__X_
       dc B__XXX_X_
       dc B__XXX_X_
       dc B__XXX_X_
       dc B__XXX_X_
       dc B__XXX_X_
       dc B__XXX_X_
       dc B___X__X_
       dc B___X__X_
       dc B___X_XX_
       dc B___XXX__
       dc B___XXX__
       dc B___XXX__
       dc B________
       dc B________


       dc BXX___X__
       dc BXXX__X__
       dc BXXX__X__
       dc BXXX_XXX_
       dc BX_X_XXX_
       dc BX_X_X_X_
       dc BX_X_X_X_
       dc BXXX_X_X_
       dc BXX__X_X_
       dc BXXX_XXX_
       dc BX_X_XXX_
       dc BX_X_XXX_
       dc BX_X_XXX_
       dc BX_X_XXX_
       dc BX_X_XXX_
       dc BXXX_X_X_
       dc BXXX_X_X_
       dc BXXX_X_X_
       dc BXX__X_X_
       dc B________


       dc BX____XX_
       dc BXX___XX_
       dc BXX__XXX_
       dc BXXX_XXX_
       dc BXXX_XX__
       dc BX_X_X___
       dc BX_X_X___
       dc BX_X_X___
       dc BX_X_X___
       dc BX_X_X___
       dc BX_X_X___
       dc BX_X_X___
       dc BX_X_X_X_
       dc BX_X_XXX_
       dc BXXX_XXX_
       dc BXXX_XXX_
       dc BXXX_XXX_
       dc BXXX_XXX_
       dc BXX___XX_
       dc B________


       dc BXXX_XXX_
       dc BXXX_XXX_
       dc BXXX_XXX_
       dc BXXX_XXX_
       dc BX___X___
       dc BX___X___
       dc BX___XX__
       dc BX___XX__
       dc BXX__XX__
       dc BXX__XX__
       dc BXX__X___
       dc BXX__X___
       dc BX___X___
       dc BX___XXX_
       dc BX___XXX_
       dc BX___XXX_
       dc BX___XXX_
       dc BX___XXX_
       dc BX___XXX_
       dc B________


       dc BX_X__X__
       dc BX_X_XXX_
       dc BX_X_XXX_
       dc BX_X_XXX_
       dc BX_X_X_X_
       dc BX_X_X___
       dc BX_X_X___
       dc BX_X_X___
       dc BXXX_X_X_
       dc BXXX_X_X_
       dc BXXX_X_X_
       dc BXXX_X_X_
       dc BX_X_X_X_
       dc BX_X_X_X_
       dc BX_X_XXX_
       dc BX_X_XXX_
       dc BX_X_XXX_
       dc BX_X_XXX_
       dc BX_X__XX_
       dc B________

       dc B__X_XXX_
       dc B__X_XXX_
       dc B__X_XXX_
       dc B__X_XXX_
       dc B__X__X__
       dc B__X__X__
       dc B__X__X__
       dc B__X__X__
       dc B__X__X__
       dc B__X__X__
       dc B__X__X__
       dc B__X__X__
       dc BX_X__X__
       dc BX_X_XXX_
       dc BXXX_XXX_
       dc BXXX_XXX_
       dc BXXX_XXX_
       dc BXXX_XXX_
       dc B_X__XXX_
       dc B________

       dc BX___X_X_
       dc BX___X_X_
       dc BX___X_X_
       dc BX___X_X_
       dc BX___X_X_
       dc BX___X_X_
       dc BX___XXX_
       dc BX___XX__
       dc BX___XX__
       dc BX___XX__
       dc BX___XX__
       dc BX___XXX_
       dc BX_X_XXX_
       dc BXXX_X_X_
       dc BXXX_X_X_
       dc BXXX_X_X_
       dc BXXX_X_X_
       dc BXXX_X_X_
       dc BXXX_X_X_
       dc B________

    ;    dc BXX__X_X_
    ;    dc BXX__X_X_
    ;    dc BXX__X_X_
    ;    dc BXXX_XXX_
    ;    dc BXXX_XXX_
    ;    dc BXXX_XXX_
    ;    dc BXXX_XXX_
    ;    dc BX_X_XXX_
    ;    dc BX_X_XXX_
    ;    dc BX_X_X_X_
    ;    dc BX_X_X_X_
    ;    dc BX_X_X_X_
    ;    dc BX_X_X_X_
    ;    dc BX_X_X_X_
    ;    dc BX_X_X_X_
    ;    dc BX_X_X_X_
    ;    dc BX_X_X_X_
    ;    dc BX_X_X_X_

       dc B__X_X_X_
       dc B__X_X_X_
       dc BX_X_X_X_
       dc BX_X_XXX_
       dc BX_X_XXX_
       dc BXXX_XXX_
       dc BXXX_XXX_
       dc BXXX_XXX_
       dc BXXX_XXX_
       dc BXXX_X_X_
       dc BXXX_X_X_
       dc BXXX_X_X_
       dc BXXX_X_X_
       dc BX_X_X_X_
       dc BX_X_X_X_
       dc BX_X_X_X_
       dc BX___X_X_
       dc BX___X_X_
       dc BX___X_X_
       dc B________


       dc BXX___X__
       dc BXXX_XXX_
       dc BXXX_XXX_
       dc BXXX_XXX_
       dc BX_X_X_X_
       dc BX_X_X_X_
       dc BX_X_X_X_
       dc BX_X_X_X_
       dc BXXX_X_X_
       dc BXXX_X_X_
       dc BXXX_X_X_
       dc BXXX_X_X_
       dc BXXX_X_X_
       dc BXX__X_X_
       dc BX___XXX_
       dc BX___XXX_
       dc BX___XXX_
       dc BX___XXX_
       dc BX____X__
       dc B________

       dc BXX___X__
       dc BXXX_XXX_
       dc BXXX_XXX_
       dc BXXX_XXX_
       dc BXXX_X_X_
       dc BX_X_X_X_
       dc BX_X_X_X_
       dc BXXX_X_X_
       dc BXXX_X_X_
       dc BXX__X_X_
       dc BXX__X_X_
       dc BXXX_X_X_
       dc BXXX_X___
       dc BX_X_X_X_
       dc BX_X_X_XX
       dc BX_X_XXXX
       dc BX_X_XXXX
       dc BX_X_XX_X
       dc BX_X__X_X
       dc B________

       dc BXXX__XX_
       dc BXXX_XXX_
       dc BXXX_XXX_
       dc BXXX_XXX_
       dc BXXX_X_X_
       dc BXX__X___
       dc B_X__XX__
       dc B_X__XXX_
       dc B_X__XXX_
       dc B_X___XX_
       dc B_X____X_
       dc B_X____X_
       dc B_X____X_
       dc B_X__XXX_
       dc B_X__XXX_
       dc B_X__XXX_
       dc B_X__XXX_
       dc B_X__XXX_
       dc B_X__XX__
       dc B________

       dc BX_X_X_X_
       dc BX_X_X_X_
       dc BX_X_X_X_
       dc BX_X_X_X_
       dc BX_X_X_X_
       dc BX_X_X_X_
       dc BX_X_X_X_
       dc BX_X_X_X_
       dc BX_X_X_X_
       dc BX_X_X_X_
       dc BX_X_X_X_
       dc BXXX_X_X_
       dc BXXX_X_X_
       dc BXXX_XXX_
       dc B_X__XXX_
       dc B_X__XXX_
       dc B_X__XXX_
       dc B_X__XXX_
       dc B_X___X__
       dc B________

       dc BX_X_X_X_
       dc BX_X_X_X_
       dc BX_X_X_X_
       dc BX_X_X_X_
       dc BX_X_X_X_
       dc BX_X_X_X_
       dc BXXX_X_X_
       dc BXXX_X_X_
       dc B_X__X_X_
       dc B_X__X_X_
       dc B_X__X_X_
       dc BXXX_XXX_
       dc BXXX_XXX_
       dc BX_X_XXX_
       dc BX_X_XXX_
       dc BX_X_XXX_
       dc BX_X_X_X_
       dc BX_X_X_X_
       dc BX_X_X_X_
       dc B________

       dc BXXX_X_X_
       dc BXXX_X_X_
       dc BXXX_X_X_
       dc BXXX_X_X_
       dc B__X_X_X_
       dc B__X_X_X_
       dc B__X_XXX_
       dc B__X_XXX_
       dc B_XX_XXX_
       dc BXXX_XXX_
       dc BXXX__X__
       dc BXX___X__
       dc BX____X__
       dc BX____X__
       dc BX____X__
       dc BX____X__
       dc BXXX__X__
       dc BXXX__X__
       dc BXXX__X__
       dc B________

    ;    dc ________
    ;    dc ________
    ;    dc ________
    ;    dc ________
    ;    dc ________
    ;    dc XX__XX__
    ;    dc XXX_XXX_
    ;    dc XXX_XXX_
    ;    dc X_X_XXX_
    ;    dc X_X_X_X_
    ;    dc X_X_X_X_
    ;    dc X_X_X_X_
    ;    dc X_X_X_X_
    ;    dc XXX_X_X_
    ;    dc XX__X_X_
    ;    dc X_______
    ;    dc X_______
    ;    dc X_______


;    echo "   - 3PIX DIGIT SHAPES from", __DIGIT_SHAPE, "to", *, "(", [(* - __DIGIT_SHAPE)]d , " bytes"


;███████████████████████████████████████████████████████████████████████████████

__TITLE_SCREEN

    include "titleData.asm"

;    echo "   - TITLE SCREEN  from", __TITLE_SCREEN, "to", *, "(", (* - __TITLE_SCREEN) , "bytes)"





    IF __ENABLE_ATARIVOX

speakJet

; AtariVox Speech Synth Driver
;; By Alex Herbert, 2004
; Updated for CDFJ usage by Andrew Davie 2022


SERIAL_OUTMASK      equ     $01
SERIAL_RDYMASK      equ     $02

;                    ldy #0
;                    sty spoken


                    lda SWCHA
                    and #SERIAL_RDYMASK     ; buffer full?
                    beq .speechDone

                    lda #_DS_SPEECH         ; data stream phoneme
                    eor #$FF
                    beq .speechDone

;kk jmp kk
    ; output byte as serial data
    ; send 1 start bit, 8 data bits, 1 stop bit

                    ldy #10

                    sec                     ; start bit
.serialiseBit       tax                     ; 2 @2

                    lda SWACNT              ; 4 @6
                    and #$fe                ; 2 @8
                    adc #0                  ; 2 @10     C -> D0
                    sta SWACNT              ; 4 @14     (and C now clear)

                    dey                     ; 2 @16
                    beq .speechDone         ; 2 @18

                    lda #-6                 ; 2 @20
.wasteCycles        adc #1                  ; 2         C is clear!
                    bcc .wasteCycles        ; 3(2) =5*6 - 1 = 29 loop

                    SLEEP 6                 ; @55

                    txa                     ; 2 @57
                    lsr                     ; 2 @59     next bit --> C
                    bpl .serialiseBit       ; 3 @62     unconditional


.speechDone


    IF >.serialiseBit != >.
        ECHO "ERROR: page crossing in speech serialise loop"
        ERR
    ENDIF
                    rts

    ENDIF



    IF 0

;------------------------------------------------------------------------------

;
; i2c_v2.3.inc
;
;
; AtariVox EEPROM Driver
;
; By Alex Herbert, 2004
;
; Optimisations by Thomas Jentzsch, 2006/2008
;
; Fix for Speakjet noise during I2C_TXBIT, 2016


; I/O Constants

I2C_SDA_MASK    equ     $04
I2C_SCL_MASK    equ     $08


; Signalling Macros

;  MAC     I2C_SCL_0
;    ldx     #$00
;    stx     SWCHA
;  ENDM

;  MAC     I2C_SCL_1
;    ldx     #I2C_SCL_MASK
;    stx     SWCHA
;  ENDM

;  MAC     I2C_SDA_IN
;    ldx     #I2C_SCL_MASK
;    stx     SWACNT
;  ENDM

;  MAC     I2C_SDA_OUT
;    ldx     #I2C_SCL_MASK|I2C_SDA_MASK
;    stx     SWACNT
;  ENDM


  MAC     I2C_START
; I2C_SCL_1
    ldx     #(I2C_SCL_MASK|I2C_SDA_MASK)*2  ; 2         I2C_SCL_MASK
    stx     SWCHA                           ; 4
; I2C_SDA_OUT
    txa
    lsr                                     ; 2         I2C_SCL_MASK|I2C_SDA_MASK
    sta     SWACNT                          ; 4
; total: 12 cycles
  ENDM


  MAC     I2C_TXBIT
; I2C_SCL_0
    ldx     #$0                             ; 2
    stx     SWCHA                           ; 4
    txa
; set bit
    adc     #I2C_SCL_MASK >> 2              ; 2         %10 / %11
    asl                                     ; 2
    asl                                     ; 2
    sta     SWACNT                          ; 4         SDA = !C (a = %1000 / %1100)
; I2C_SCL_1
    ldx     #I2C_SCL_MASK                   ; 2
    stx     SWCHA                           ; 4
; total: 22 cycles
  ENDM


  MAC     I2C_TXNACK
; I2C_SCL_0
    ldx     #I2C_SCL_MASK*2                 ; 2         $00
    stx     SWCHA                           ; 4
    txa
; I2C_SDA_IN
    lsr                                     ; 2         I2C_SCL_MASK
    sta     SWACNT                          ; 4
; I2C_SCL_1
    nop                                     ; 2         required for timing!
    sta     SWCHA                           ; 4         I2C_SCL_MASK
; total: 18 cycles
  ENDM


; Subroutine Macros

  MAC     I2C_SUBS

i2c_startread
; use V to flag if previous byte needs ACK
    ldy     #%10100001                      ; 2         eeprom read command
    .byte   $2c                             ; 2
i2c_startwrite
    ldy     #%10100000                      ; 2         eeprom write command
    I2C_START                               ;12         start signal (clears V flag)
    tya                                     ; 2 = 16
i2c_txbyte
    eor     #$ff                            ; 2         invert data byte
    sec                                     ; 2
    rol                                     ; 2 =  6    shift loop bit into a
i2c_txbyteloop
    tay                                     ; 2
    I2C_TXBIT                               ;22         transmit
    tya                                     ; 2
    asl                                     ; 2         shift next bit into C
    bne     i2c_txbyteloop                  ; 2�= 30/31

; receive acknowledge bit

    beq     i2c_rxbit                       ;43 = 43
; i2c_txbyte: 296 cycles
;-------------------------------------------------------------------------------

i2c_rxbyte
    bvc     i2c_rxskipack                   ; 2�        previous byte needs acknowledge?
    jsr     i2c_txack                       ;24         transmit acknowledge bit

i2c_rxskipack
    bit     i2c_rxbyte                      ; 4         set V - next byte(s) require acknowledge

    ldy     #1                              ; 2
    tya
i2c_rxbyteloop
    tay                                     ; 2 =  2
i2c_rxbit:                                  ;           receive bit in C
    I2C_TXNACK                              ;18 = 18

    lda     SWCHA                           ; 4
    lsr                                     ; 2
    lsr                                     ; 2
    lsr                                     ; 2 = 10    C = SDA

    tya                                     ; 2
    rol                                     ; 2         rotate into Y
    bcc     i2c_rxbyteloop                  ; 2�=  6/7

; received byte in A
    rts                                     ; 6 =  6
; i2c_rxbit:  40 cycles
; i2c_rxbyte: 310/333 cycles
;-------------------------------------------------------------------------------

i2c_stopread
    bvc     i2c_stopwrite                   ; 2�
    ldy     #$80                            ; 2
    jsr     i2c_rxbit                       ;46         transmit no-acknowledge

i2c_stopwrite
    jsr     i2c_txack                       ;30

; return port to input mode
    ldx     #0                              ; 2         0
    stx     SWACNT                          ; 4
    rts                                     ; 6 = 12
; i2c_stopread:  45/92
; i2c_stopwrite: 42
;-------------------------------------------------------------------------------

i2c_txack
; I2C_SCL_0
    ldx     #0                              ; 2         $00
    stx     SWCHA                           ; 4
; I2C_SDA_OUT
    ldx     #(I2C_SCL_MASK|I2C_SDA_MASK)    ; 2         I2C_SCL_MASK|I2C_SDA_MASK
    stx     SWACNT                          ; 4
; I2C_SCL_1
    asl                                     ; 2         I2C_SCL_MASK
    sta     SWCHA                           ; 4

    rts                                     ; 6
; total: 24 cycles
;-------------------------------------------------------------------------------

  ENDM




    i2c_subs

HandleSaveKey

SAVEKEY_ADR     = $0600         ;           TODO : fix - reserved address for Wen Hop Dash (64 bytes)

; SK Memory Map:
;               cave    level
; $0600-$0602   A       1
; $0603-$0605   A       2
; $0606-$0608   A       3
; $0609-$060b   A       4
; $060c-$060e   A       5
; $060f-$0611   E       1
; $0612-$0614   E       2
; $0615-$0617   E       3
; $0618-$061a   unused          HIJACKED!
; $061b-$061d   unused          HIJACKED!
; $061e-$0620   I       1
; $0621-$0623   I       2
; $0624-$0626   I       3
; $0627-$0629   unused          HIJACKED!
; $062a-$062c   unused          HIJACKED!
; $062d-$062f   M       1
; $0630-$0632   M       2
; $0633-$0635   M       3
; $0636-$063f   unused          HIJACKED!


;------------------------------------------------------------------------------

ReadSaveKey ; = 2371

; assume no SaveKey found:
    lda     #$ff                ; 2         return $ff if no SaveKey found
    sta     highScoreSK+2       ; 3

; setup SaveKey:
;    lda     #0; //startCave           ; 3         load start cave*5 and level
;    ldx     #0; //level               ; 3
    jsr     SetupSaveKey        ;6+853
    bcc     NoSKfound           ; 2/3

    ;    lda     #$34
    ;    sta     COLUBK

; start read
    jsr     i2c_stopwrite       ;6+42       end of "fake" write
    jsr     i2c_startread       ;6+284      Start signal and $a1 command byte

; read high score:
    ldx     #3-1                ; 2 = 1187
.loopRead
    jsr     i2c_rxbyte          ;6+333      read byte from EEPROM
    cmp     #$ff                ; 2         EEPROM slot empty?
    bne     .skipEmpty          ; 2/3        no, skip clear
    lda     #0                  ; 2         clear EEPROM slot
.skipEmpty
    sta     highScoreSK,x       ; 4
    dex                         ; 2
    bpl     .loopRead           ; 2/3= 354

; stop read:
    jmp     i2c_stopread        ;3+92=95    terminate read

;------------------------------------------------------------------------------

WriteSaveKey ; = 1751

; check if new high score:
    ldx     highScoreSK         ; 3
    inx                         ; 2
    ;beq     NoSKfound           ; 2/3       no new high score, abort

; setup SaveKey:
    lda     startCave           ; 3         load start cave*5 and level
    ldx     startLevel          ; 3
    jsr     SetupSaveKey        ; 6+853
    bcc     NoSKfound           ; 2/3

    ;    lda     #$64
    ;    sta     COLUBK

; write high score:
    ldx     #3-1                ; 2 = 841
.loopWrite
    lda     highScoreSK,x       ; 4
    jsr     i2c_txbyte          ;6+264      transmit to EEPROM
    dex                         ; 2
    bpl     .loopWrite          ; 2/3= 837

; stop write:
    jmp     i2c_stopwrite       ; 3+42= 45  terminate write and commit to memory


;------------------------------------------------------------------------------

SetupSaveKey ; = 853

    ldx #<(SAVEKEY_ADR+24)                        ; 2 = 22
; detect SaveKey:
    jsr     i2c_startwrite      ;6+280
    bne     .exitSK             ; 2/3

; setup address:
    clv                         ; 2
    ldx     #>SAVEKEY_ADR       ; 2         upper byte of address
    txa
    jsr     i2c_txbyte          ;6+264
    txa                         ; 2         x = lower byte offset
    jmp     i2c_txbyte          ;3+264      returns C==1

.exitSK
    clc
    rts
NoSKfound
; jmp NoSKfound
     rts
  ENDIF


    ENDIF


;███████████████████████████████████████████████████████████████████████████████
;===============================================================================
; Bank 6 - 6507 code
;----------------------------------------
;   CDFJ will always start in bank 6 because banks 0-5 could contain ARM code
;===============================================================================

;    echo "regular 6502 code begins at", *


;  .-.-.   .-.-.   .-.-.   .-.-.   .-.-.   .-.-.   .-.-.   .-.-.   .-.-.   .-.-.   .-.-.   .-.-.
; / / \ \ / / \ \ / / \ \ / / \ \ / / \ \ / / \ \ / / \ \ / / \ \ / / \ \ / / \ \ / / \ \ / / \ \
;`-'   `-`-'   `-`-'   `-`-'   `-`-'   `-`-'   `-`-'   `-`-'   `-`-'   `-`-'   `-`-'   `-`-'   `-`




KernelCopyright
KernelMenu
KernelStatus


doMenuSystem

    include "menuKernel.asm"




;  .-.-.   .-.-.   .-.-.   .-.-.   .-.-.   .-.-.   .-.-.   .-.-.   .-.-.   .-.-.   .-.-.   .-.-.
; / / \ \ / / \ \ / / \ \ / / \ \ / / \ \ / / \ \ / / \ \ / / \ \ / / \ \ / / \ \ / / \ \ / / \ \
;`-'   `-`-'   `-`-'   `-`-'   `-`-'   `-`-'   `-`-'   `-`-'   `-`-'   `-`-'   `-`-'   `-`-'   `-`



                ;  NTSC       PAL           PAL-60        SECAM
TimerOS         dc OS_TIM64T, OS_TIM64T+29, OS_TIM64T, OS_TIM64T+29
TimerVB         dc VB_TIM64T, VB_TIM64T+30, VB_TIM64T, VB_TIM64T+30

;overscanInit    dc _FN_GAME_OS, _FN_GAME_OS2


KernelGame

;                    ldx #<_DS_TO_ARM            ; assumed 0

                    ldx #0
                    stx NUSIZ0
                    stx NUSIZ1
    IF __ENABLE_ATARIVOX
;                    stx spoken
    ENDIF

                    stx DSPTR
                    stx DSPTR
                    ldx #_FN_INIT_GAME_KERNEL
                    stx DSWRITE
                    jsr runARM              ; one-off game initialisation



OverScan

                    sta WSYNC
                    ldx #2
                    stx VBLANK              ; video output off
                    ldx tv_type
                    lda TimerOS,x
                    sta TIM64T              ; set timer for OS


    IF __ENABLE_ATARIVOX
         jsr speakJet
    ENDIF

                    ldy #_FN_GAME_OS
                    jsr idleProcess


VerticalSync:
                    ldy #2
                    ldx tv_type
                    lda TimerVB,x
                    sty WSYNC


; --- start scanline 1 of Vertical Sync ---
                    sty VSYNC           ; 3  3  turn on Vertical Sync signal
                    sta TIM64T          ; 4  7



                    ldx #0
                    stx GRP0
                    stx GRP1

                    stx PF0
                    stx PF1
                    stx PF2
                    stx CTRLPF
                    stx COLUBK

                    ldy #<_DS_TO_ARM
                    sty DSPTR
                    sty DSPTR
                    sty DSWRITE                     ; DUMMY
                    ldy SWCHA                       ; read state of both joysticks
                    sty DSWRITE                     ; save in _SWCHA
                    ldy SWCHB                       ; read state of console switches
                    sty DSWRITE                     ; save in _SWCHB
                    ldy INPT4                       ; read state of left joystick firebutton
                    sty DSWRITE                     ; save in _INPT4
;                    ldy INPT5                       ; read state of right joystick firebutton
;                    sty DSWRITE                     ; save in _INPT5

;                    stx WSYNC

    ; ldx highScoreSK
    ; stx DSWRITE
    ; ldx highScoreSK+1
    ; stx DSWRITE
    ; ldx highScoreSK+2
    ; stx DSWRITE




;                    stx WSYNC           ; end of VerticalSync scanline 3
;                    stx VSYNC           ; turn off Vertical Sync signal


                    ldx #1
                    lda #DSCOMM     ; = _P1_X





                    sty WSYNC           ; 3 10/0

; --- start scanline 2 of Vertical Sync ---
        ; A BIT OF SPARE TIME HERE IF REQUIRED



                    sec
                    sta WSYNC
DivideLoop2         sbc #15
                    bcs DivideLoop2

                    eor #7
                    asl
                    asl
                    asl
                    asl

                    sta.wx HMP0,X
                    sta RESP0,X

                    dex
                    stx VSYNC

                    lda #_DS_AUDV0
                    sta AUDV0
                    lda #_DS_AUDC0
                    sta AUDC0
                    lda #_DS_AUDF0
                    sta AUDF0


                    lda #DSCOMM     ; = _P0_X


                    sec
                    sta WSYNC
DivideLoop3         sbc #15
                    bcs DivideLoop3

                    eor #7
                    asl
                    asl
                    asl
                    asl
                    sta.wx HMP0,X
                    sta RESP0,X


                    lda #DSCOMM             ; tv_type
                    ;sta tv_type            ; superfluous/unused here


                    lda #_DS_AUDV0
                    sta AUDV1
                    lda #_DS_AUDC0
                    sta AUDC1
                    lda #_DS_AUDF0
                    sta AUDF1

                    lda #_DS_COLUP0                 ; score colours
                    sta COLUP0
                    lda #_DS_COLUP1
                    sta COLUP1

                    lda #DSCOMM
                    cmp currentKernel
                    sta kernel

                    sta WSYNC
                    sta HMOVE

                    bne startAnyKernel

GameVB

    ; IF __ENABLE_ATARIVOX
    ;     jsr speakJet
    ; ENDIF


                    ldy #_FN_GAME_VB
                    jsr idleProcess

                    ldx #0
                    stx VBLANK                      ; video output on
                    sta WSYNC
                    jmp FASTJMP1                    ; kernel starts @3




InitSystem
                    cld


        ; Remarkable system clear by Omegamatrix
        ; SP=$FF, X=A=0

.clear_machine      ldx #$A                 ; ASL opcode = $0A
                    inx
                    txs
                    pha
                    bne .clear_machine+1    ; jump between operator and operand to do ASL

                    stx SETMODE             ; <-- x=0   "Fast Fetch" enable
                    ;stx kernel              ; "copyright" ==0 by sys clear

    ; #if __ENABLE_ATARIVOX
    ;     ldx #$FF
    ;     stx _BUF_SPEECH ;tmp
    ; #endif
                    ldy #_FN_SYSTEM_RESET
                    jsr CallArmCode

;                    jsr ReadSaveKey

    ; fall through

startAnyKernel      ldx kernel
                    stx currentKernel
                    lda KernelVectorHi,x
                    pha
                    lda KernelVectorLo,x
                    pha
                    rts

KernelVectorLo      .byte <(KernelCopyright-1)
                    .byte <(KernelMenu-1)
                    .byte <(KernelGame-1)
                    .byte <(KernelStatus-1)

KernelVectorHi      .byte >(KernelCopyright-1)
                    .byte >(KernelMenu-1)
                    .byte >(KernelGame-1)
                    .byte >(KernelStatus-1)

    include "normalKernel.asm"


    echo "Kernels end @", * - 1


FREE_SPACE = ARM_DIRECT_DATA_END - $8000 - *
    echo "FREE END-SPACE =", (FREE_SPACE)d, "bytes"


        echo "---- @", *, " with ",($FFF0 - *) , "bytes left in bank 0"


; NOTE: if Reset or BRK are triggered in this bank the game will crash...

    ORG     $17F0
    RORG    $FFF0
    DC.B    0, 0, 0, 0          ; CDFJ Hotspots
    DC.L    C_STACK             ; $F4   C Stack
    DC.L    _PC_ARM_CODE+1      ; $F8   C Code (+1 for THUMB Mode)
    DC.W    InitSystem          ; $FC   Reset
    DC.W    InitSystem          ; $FE   BRK

;===============================================================================
; Bank 1 - 6507 code
;----------------------------------------
; Game Kernels
;===============================================================================

    ;     ORG $1800
    ;     RORG $F000

    ; ORG     $17F0
    ; RORG    $FFF0
    ; DC.B    0, 0, 0, 0          ; CDFJ Hotspots
    ; DC.L    C_STACK             ; $F4   C Stack
    ; DC.L    _PC_ARM_CODE+1      ; $F8   C Code (+1 for THUMB Mode)
    ; DC.W    InitSystem          ; $FC   Reset
    ; DC.W    InitSystem          ; $FE   BRK

;===============================================================================
; ARM user code
;----------------------------------------
;   Starting location for the ARM code depends upon which bank you decided
;   to start it in.
;       Bank1   $1800
;       Bank2   $2800
;       Bank3   $3800
;       Bank4   $4800
;       Bank5   $5800
;       Bank6   $6800
;       C Code  $7800
;===============================================================================

        ORG $1800
        RORG $1800

ARM_DIRECT_DATA:
;        include arm_direct_data.asm  ; ?? none
    echo "----",[* - ARM_DIRECT_DATA] , "bytes of ARM Direct Data"

ARM_DIRECT_DATA_END

;===============================================================================
; ARM code
;----------------------------------------
;
;===============================================================================
    align 4         ; need to check if align 2 is OK for this
_PC_ARM_CODE:
    ; include the custom ARM code.
        INCBIN "main/bin/armcode.bin"

_PC_ARM_CODE_SIZE = . - _PC_ARM_CODE;
    echo "---- C CODE", (_PC_ARM_CODE_SIZE)d, "bytes"

;===============================================================================
; ARM Indirect Data
;----------------------------------------
;   Data that the C code indirectly accesses can be stored immediately after the
;   custom ARM code.
;===============================================================================


SPEECH_DATA

    IF __ENABLE_ATARIVOX

        include "atarivox/speechData.asm"
SIZEOF_SPEECH_DATA = * - SPEECH_DATA
        echo "Speech data =", SPEECH_DATA, "-", *, "(",[SIZEOF_SPEECH_DATA]d, "bytes)"

    ENDIF


END_OF_INDIRECT_DATA
;    echo "ARM INDIRECT DIRECT DATA ends @", *
;    echo "<----"



    echo "---- ROM", (_PC_ROM_SIZE * 1024 - .)d, "bytes free"

    ds _PC_ROM_SIZE * 1024 - ., $FF


;===============================================================================
; ARM Direct Data
;----------------------------------------
;   I find it easier, and more space efficient, to store some of the data the
;   C code needs to access in the 6507 code instead of the C code.  Because the
;   build process is:
;
;       1) assemble 6507 code to create defines_from_dasm_for_c.h
;       2) compile C code to create ARM routines
;       3) assemble 6507 to create final ROM
;
;   the ARM code could change size between steps 1 and 3, which would shift data
;   that immediately comes after it. So the data that C directly accesses needs
;   to be after an ORG to prevent it from moving.
;
;   The _IMAGE_GRAPHICS, _IMAGE_COLORS, etc data tables are directly access by
;   the C code so must be in the Direct Data area. The data they point to is
;   indirectly accessed by the C code, so they can go in the Indirect Data area.
;   Note the labels for the tables are prefixed by _ so they'll end up in the
;   defines_from_dasm_for_c.h file, while the labels for the data the tables
;   point to are not prefixed by _

;CHAR_SIZE = 21
;TITLESCREEN_DATA = (4 * 198)
;CHAR_COUNT = 55


; .DIRECT_DATA_SIZE .SET TITLESCREEN_DATA

; .DIRECT_DATA_SIZE .SET .DIRECT_DATA_SIZE + (__WORD_COUNT * 2)
; .DIRECT_DATA_SIZE .SET .DIRECT_DATA_SIZE + __COPYRIGHT_ROWS * 6
; .DIRECT_DATA_SIZE .SET .DIRECT_DATA_SIZE + (CHAR_COUNT * CHAR_SIZE)

;     echo .DIRECT_DATA_SIZE, "bytes of ARM_DIRECT_DATA expected, consisting of..."


; 6507 code lives at the end of the ROM, so we ORG it to ~$7FFF - its length
; It "grows" down - the bigger it is, the lower the address. We can exact-fit it
; so that the "kernel bytes available" is 0.  The C code grows UP to the ORG
; address here. The delta between end of the C code and this ORG is free space

    echo "FREE C-SPACE = ", [ARM_DIRECT_DATA - *]d, "bytes"



;===============================================================================
; Display Data
;----------------------------------------
;   4K of RAM shared between the 6507 and ARM.
;
;   NOTE: anything prefixed with _ ends up in main/defines_from_dasm_for_c.h
;         so that the C code will have the same values as the 6507 code
;===============================================================================

    SEG.U DISPLAYDATA
    ORG $0000

_DS_TO_ARM

_RUN_FUNC           ds 1        ; function to run
_SWCHA              ds 1        ; joystick directions to ARM code
_SWCHB              ds 1        ; console switches to ARM code
_INPT4              ds 1        ; left firebutton state to ARM code
;_INPT5              ds 1        ; right firebutton state to ARM code

;_HIGHSCORE          ds 3


_DS_FROM_ARM

_P1_X               ds 1        ; position of player 1
_P0_X               ds 1        ; position of player 0
_TV_TYPE            ds 1        ; 0 NTSC, 1 PAL, 2 PAL-60 3 SECAM
_KERNEL             ds 1        ; 0 = copyright, 1 = menu, 2 = game, 3 = stats

_ARENA_COLOUR       ds 1


_BUF_AUDV           ds 2
_BUF_AUDC           ds 2
_BUF_AUDF           ds 2


    align 4

_BUF_JUMP1          ds _ARENA_SCANLINES * 2         ; long-word align!!
_BUF_JUMP1_EXIT     ds 2


_BOARD_COLS = 40
_BOARD_ROWS = 22

_BOARD              ds _BOARD_COLS * _BOARD_ROWS + 4    ; extra for grab+1 in drawscreen "bug"



    IF __ENABLE_ATARIVOX
_BUF_SPEECH         ds 1
    ENDIF
;------------------------------------------------------------------------------

_BUFFERS = *

    SEG.U BUFFER1
    ORG _BUFFERS

BUFN SET 0
    MAC DEFBUF ;name
_BUF_{1}             ds ARENA_BUFFER_SIZE
BUFN SET BUFN + 1
    ENDM

;    DEFBUF HMP0
;    DEFBUF HMP1

    DEFBUF COLUP0
    DEFBUF COLUP1
    DEFBUF COLUPF
    DEFBUF COLUBK

    ; Axiom: PF buffers contiguous (optimisation)
    DEFBUF PF0_LEFT
    DEFBUF PF1_LEFT
    DEFBUF PF2_LEFT
    DEFBUF PF0_RIGHT
    DEFBUF PF1_RIGHT
    DEFBUF PF2_RIGHT

    DEFBUF GRP0A
    DEFBUF GRP1A


_BUFFER_BLOCK_SIZE = * - _BUFFERS





;------------------------------------------------------------------------------

    SEG.U BUFFER2
    ORG _BUFFERS

    DEFBUF MENU_COLUPF
    DEFBUF MENU_COLUP0

    ; Order of these 4 important...
    DEFBUF MENU_PF1_LEFT
    DEFBUF MENU_PF2_LEFT
    DEFBUF MENU_PF1_RIGHT
    DEFBUF MENU_PF2_RIGHT

    DEFBUF MENU_GRP0A
    DEFBUF MENU_GRP1A
    DEFBUF MENU_GRP0B
    DEFBUF MENU_GRP1B
    DEFBUF MENU_GRP0C
    DEFBUF MENU_GRP1C

;    SEG.U OVERLAP
;    ORG _BUFFERS + _BUFFER_BLOCK_SIZE


;    ds 10 * 21



; OverlapDisplayDataRam:  ; mark the beginning of overlapped RAM
; ; Splash screen datastream buffers
; ;_BUF_SPLASH0:   ds 192
; ;_BUF_SPLASH1:   ds 192
; ;_BUF_SPLASH2:   ds 192
; ;_BUF_SPLASH3:   ds 192

;     echo "----",($1000 - *) , "Splash bytes of Display Data RAM left"
; ;----------------------------------------
; ; this ORG overlaps the Menu datastreams on top of the Splash datastreams
; ;----------------------------------------

;     ; Generic overlap variable usage
;     ORG OverlapDisplayDataRam
;     echo "----",($1000 - *) , "Menu bytes of Example Overlap RAM left"

; ;----------------------------------------
; ; this ORG overlaps the Game datastreams on top of the Splash and Menu datastreams
; ;----------------------------------------
;     ORG OverlapDisplayDataRam
; ; Game datastream buffers
; _EVERY_FRAME_ZERO_START:

;     align 4 ; need to be 4 byte aligned to use myMemsetInt
; _EVERY_FRAME_ZERO_COUNT=*-_EVERY_FRAME_ZERO_START   ; end of zeroed out data



    ; modify custom.boot.lds to adjust display data RAM

    echo "----",($E5F - *)d , "bytes of Display Data RAM avaialble"
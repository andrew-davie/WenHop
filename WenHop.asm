; Wen Hop CDFJ
; (c) 2023 Andrew Davie

; REMEMBER cannot use lda # as this is overloaded for datastream access!!
; use ldx # or ldy # instead

        PROCESSOR 6502
        include "vcs.h"
        include "macro.h"
        include "cdfj.h"

_ENABLE_TRAINER = 0
_ENABLE_ATARIVOX = 0       ; 415 bytes
_ENABLE_WATER = 0

_ENABLE_LAVA2 = 1
_ENABLE_WATER2 = 1

 IF _ENABLE_TRAINER == 1
_ENABLE_DEMO = 0       ; 260 bytes + joystick data (DO NOT ADJUST)
 ELSE
_ENABLE_DEMO = 0;1       ; 260 bytes + joystick data (adjust this on/off as required)

 ENDIF

    IF _ENABLE_ATARIVOX
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

    IF _ENABLE_ATARIVOX
;spoken          ds 1
what            ds 1
∫    ENDIF

    IF _ENABLE_ATARIVOX
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

                    incbin "cdfdriver20190317.bin"

SIZEOF_CDFJ_DRIVER = *
        echo "CDFJ driver = $0 - ", *, "(",[*]d, "bytes)"

;===============================================================================
; ARM user code
; Banks 0 thru n
;----------------------------------------
;   The ARM code starts at $0800 and grows into bank 0+
;===============================================================================

;                    ORG $0800
ARM_CODE

                    incbin "main/bin/armcode.bin"

SIZEOF_ARM_CODE = * - ARM_CODE
        echo "C (ARM code) =", ARM_CODE, "-", *, "(",[SIZEOF_ARM_CODE]d, "bytes)"


;===============================================================================
; ARM Indirect Data
;----------------------------------------
;   Data that the C code indirectly accesses can be stored immediately after the
;   custom ARM code.
;===============================================================================

;    echo "---->"
;    echo "ARM INDIRECT DATA starts at", *

SPEECH_DATA

    IF _ENABLE_ATARIVOX

        include "atarivox/speechData.asm"
SIZEOF_SPEECH_DATA = * - SPEECH_DATA
        echo "Speech data =", SPEECH_DATA, "-", *, "(",[SIZEOF_SPEECH_DATA]d, "bytes)"

    ENDIF


END_OF_INDIRECT_DATA
;    echo "ARM INDIRECT DIRECT DATA ends @", *
;    echo "<----"


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

; .DIRECT_DATA_SIZE .SET .DIRECT_DATA_SIZE + (ooWORD_COUNT * 2)
; .DIRECT_DATA_SIZE .SET .DIRECT_DATA_SIZE + ooCOPYRIGHT_ROWS * 6
; .DIRECT_DATA_SIZE .SET .DIRECT_DATA_SIZE + (CHAR_COUNT * CHAR_SIZE)

;     echo .DIRECT_DATA_SIZE, "bytes of ARM_DIRECT_DATA expected, consisting of..."


; 6507 code lives at the end of the ROM, so we ORG it to ~$7FFF - its length
; It "grows" down - the bigger it is, the lower the address. We can exact-fit it
; so that the "kernel bytes available" is 0.  The C code grows UP to the ORG
; address here. The delta between end of the C code and this ORG is free space

    echo "FREE C-SPACE = ", [ARM_DIRECT_DATA - *]d, "bytes"

BASE_6507_START SET $74EF
#if _ENABLE_ATARIVOX
BASE_6507_START SET BASE_6507_START
#endif

    ORG BASE_6507_START

ARM_DIRECT_DATA

;    echo "CHAFF SPACE = ", [* - END_OF_INDIRECT_DATA]d, "bytes"

;    echo "ARM DIRECT DATA starts at", *



;███████████████████████████████████████████████████████████████████████████████

WASTE SET 0

    IF * < $7000
        echo "shifted 6502 as it was too early @", *
WASTE SET $7000 - *
        ORG $7000
    ELSE
    ENDIF

    echo "6502 origin is ", *
    IF WASTE
        echo "  --> wastage", WASTE
    ENDIF

;    IF * > $7000
;OVERUSE = * - $7000
;        echo "  --> 'EA' potential, overuse", (OVERUSE)d, "bytes"
;    ENDIF




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

                    ldx #<_DS_TooARM
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

ooWORD_COUNT SET 0

    IF _ENABLE_ATARIVOX

ooWORD_COUNT SET 9

ooWORD_NULL         = 0

ooWORD_BOO          = 1
ooWORD_WATCHOUT     = 2
ooWORD_GETREADY     = 3
ooWORD_AARGH        = 4
ooWORD_WET          = 5
ooWORD_TOooLATE     = 6
ooWORD_LETSGOBABY   = 7
ooWORD_TRAP         = 8
ooWORD_DOSOMETHING  = 9
ooWORD_RAGEQUIT     = 10
ooWORD_GOODBYE      = 11
ooWORD_SOSAD        = 12
ooWORD_WENHOP  = 13
ooWORD_CAVE_ONE     = 14


ooSPEECH_ADDRESS

    WORDIS NULL
    WORDIS BOO
    WORDIS WATCHOUT
    WORDIS GETREADY
    WORDIS AARGH
    WORDIS WET
    WORDIS TOooLATE
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


; ooCOPYRIGHT_START

;     include "copyright.asm"

;    echo "   - COPYRIGHT DATA from", ooCOPYRIGHT_START, "to", *, "(", (* - ooCOPYRIGHT_START) , "bytes)"


#if _ENABLE_DEMO

R = 0
L = 1
U = 2
D = 3
NONE = 4




ooDEMooJOYSTICK

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


    echo "   - DEMO JOYSTICK Cfrom", ooDEMooJOYSTICK, "to", *, "(", [* - ooDEMooJOYSTICK) , "bytes)"
#ENDIF



_COLOUR_POOL
;const unsigned char colourPool[][4] = {

    ; NTSC, PAL, SECAM

;ffbf8bbc
;b4460202

; ooCOMPATIBLE_COMPATIBLE_PALETTE = 1
_PALETTE_COUNT = 16

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
;     dc ooCOMPATIBLE_COMPATIBLE_PALETTE + 0xA6, 0x48, 0xA2, 0xA2 ;0x46, 0xA2, 0xA2, 0xA2
; ;    dc 4, 8, 10, 10

;     ; 15 purple rock light blue doge green mortar good glint *
;     dc ooCOMPATIBLE_COMPATIBLE_PALETTE + 0xA8, 0xC4, 0x26, 0x94
; ;x    dc 0x3A, 0xA4, 0x54, 0x54 ;0x46, 0xA2, 0xA2, 0xA2
; ;    dc 0x50, 0y08, 0y04, 0y04


    #include "characterset.asm"



;    echo "   - CHARACTER SET DATA from", CHAR_BLOCK_START, "to", *, "(", [(* - CHAR_BLOCK2_START)]d , " bytes, ", [(* - CHAR_BLOCK2_START) / CHAR_SIZE]d, "characters)"

oooooooo = 0
oooooooX = 1
ooooooXo = 2
ooooooXX = 3
oooooXoo = 4
oooooXoX = 5
oooooXXo = 6
oooooXXX = 7
ooooXooo = 8
ooooXooX = 9
ooooXoXo = 10
ooooXoXX = 11
ooooXXoo = 12
ooooXXoX = 13
ooooXXXo = 14
ooooXXXX = 15
oooXoooo = 16
oooXoooX = 17
oooXooXo = 18
oooXooXX = 19
oooXoXoo = 20
oooXoXoX = 21
oooXoXXo = 22
oooXoXXX = 23
oooXXooo = 24
oooXXooX = 25
oooXXoXo = 26
oooXXoXX = 27
oooXXXoo = 28
oooXXXoX = 29
oooXXXXo = 30
oooXXXXX = 31
ooXooooo = 32
ooXooooX = 33
ooXoooXo = 34
ooXoooXX = 35
ooXooXoo = 36
ooXooXoX = 37
ooXooXXo = 38
ooXooXXX = 39
ooXoXooo = 40
ooXoXooX = 41
ooXoXoXo = 42
ooXoXoXX = 43
ooXoXXoo = 44
ooXoXXoX = 45
ooXoXXXo = 46
ooXoXXXX = 47
ooXXoooo = 48
ooXXoooX = 49
ooXXooXo = 50
ooXXooXX = 51
ooXXoXoo = 52
ooXXoXoX = 53
ooXXoXXo = 54
ooXXoXXX = 55
ooXXXooo = 56
ooXXXooX = 57
ooXXXoXo = 58
ooXXXoXX = 59
ooXXXXoo = 60
ooXXXXoX = 61
ooXXXXXo = 62
ooXXXXXX = 63
oXoooooo = 64
oXoooooX = 65
oXooooXo = 66
oXooooXX = 67
oXoooXoo = 68
oXoooXoX = 69
oXoooXXo = 70
oXoooXXX = 71
oXooXooo = 72
oXooXooX = 73
oXooXoXo = 74
oXooXoXX = 75
oXooXXoo = 76
oXooXXoX = 77
oXooXXXo = 78
oXooXXXX = 79
oXoXoooo = 80
oXoXoooX = 81
oXoXooXo = 82
oXoXooXX = 83
oXoXoXoo = 84
oXoXoXoX = 85
oXoXoXXo = 86
oXoXoXXX = 87
oXoXXooo = 88
oXoXXooX = 89
oXoXXoXo = 90
oXoXXoXX = 91
oXoXXXoo = 92
oXoXXXoX = 93
oXoXXXXo = 94
oXoXXXXX = 95
oXXooooo = 96
oXXooooX = 97
oXXoooXo = 98
oXXoooXX = 99
oXXooXoo = 100
oXXooXoX = 101
oXXooXXo = 102
oXXooXXX = 103
oXXoXooo = 104
oXXoXooX = 105
oXXoXoXo = 106
oXXoXoXX = 107
oXXoXXoo = 108
oXXoXXoX = 109
oXXoXXXo = 110
oXXoXXXX = 111
oXXXoooo = 112
oXXXoooX = 113
oXXXooXo = 114
oXXXooXX = 115
oXXXoXoo = 116
oXXXoXoX = 117
oXXXoXXo = 118
oXXXoXXX = 119
oXXXXooo = 120
oXXXXooX = 121
oXXXXoXo = 122
oXXXXoXX = 123
oXXXXXoo = 124
oXXXXXoX = 125
oXXXXXXo = 126
oXXXXXXX = 127
Xooooooo = 128
XooooooX = 129
XoooooXo = 130
XoooooXX = 131
XooooXoo = 132
XooooXoX = 133
XooooXXo = 134
XooooXXX = 135
XoooXooo = 136
XoooXooX = 137
XoooXoXo = 138
XoooXoXX = 139
XoooXXoo = 140
XoooXXoX = 141
XoooXXXo = 142
XoooXXXX = 143
XooXoooo = 144
XooXoooX = 145
XooXooXo = 146
XooXooXX = 147
XooXoXoo = 148
XooXoXoX = 149
XooXoXXo = 150
XooXoXXX = 151
XooXXooo = 152
XooXXooX = 153
XooXXoXo = 154
XooXXoXX = 155
XooXXXoo = 156
XooXXXoX = 157
XooXXXXo = 158
XooXXXXX = 159
XoXooooo = 160
XoXooooX = 161
XoXoooXo = 162
XoXoooXX = 163
XoXooXoo = 164
XoXooXoX = 165
XoXooXXo = 166
XoXooXXX = 167
XoXoXooo = 168
XoXoXooX = 169
XoXoXoXo = 170
XoXoXoXX = 171
XoXoXXoo = 172
XoXoXXoX = 173
XoXoXXXo = 174
XoXoXXXX = 175
XoXXoooo = 176
XoXXoooX = 177
XoXXooXo = 178
XoXXooXX = 179
XoXXoXoo = 180
XoXXoXoX = 181
XoXXoXXo = 182
XoXXoXXX = 183
XoXXXooo = 184
XoXXXooX = 185
XoXXXoXo = 186
XoXXXoXX = 187
XoXXXXoo = 188
XoXXXXoX = 189
XoXXXXXo = 190
XoXXXXXX = 191
XXoooooo = 192
XXoooooX = 193
XXooooXo = 194
XXooooXX = 195
XXoooXoo = 196
XXoooXoX = 197
XXoooXXo = 198
XXoooXXX = 199
XXooXooo = 200
XXooXooX = 201
XXooXoXo = 202
XXooXoXX = 203
XXooXXoo = 204
XXooXXoX = 205
XXooXXXo = 206
XXooXXXX = 207
XXoXoooo = 208
XXoXoooX = 209
XXoXooXo = 210
XXoXooXX = 211
XXoXoXoo = 212
XXoXoXoX = 213
XXoXoXXo = 214
XXoXoXXX = 215
XXoXXooo = 216
XXoXXooX = 217
XXoXXoXo = 218
XXoXXoXX = 219
XXoXXXoo = 220
XXoXXXoX = 221
XXoXXXXo = 222
XXoXXXXX = 223
XXXooooo = 224
XXXooooX = 225
XXXoooXo = 226
XXXoooXX = 227
XXXooXoo = 228
XXXooXoX = 229
XXXooXXo = 230
XXXooXXX = 231
XXXoXooo = 232
XXXoXooX = 233
XXXoXoXo = 234
XXXoXoXX = 235
XXXoXXoo = 236
XXXoXXoX = 237
XXXoXXXo = 238
XXXoXXXX = 239
XXXXoooo = 240
XXXXoooX = 241
XXXXooXo = 242
XXXXooXX = 243
XXXXoXoo = 244
XXXXoXoX = 245
XXXXoXXo = 246
XXXXoXXX = 247
XXXXXooo = 248
XXXXXooX = 249
XXXXXoXo = 250
XXXXXoXX = 251
XXXXXXoo = 252
XXXXXXoX = 253
XXXXXXXo = 254
XXXXXXXX = 255

_DIGIT_SHAPE

       dc ooXooXoo
       dc ooXoXXXo
       dc oXXoXXXo
       dc oXXoXXXo
       dc oXXoXoXo
       dc oXXoXoXo
       dc ooXoXoXo
       dc ooXoXoXo
       dc ooXoXoXo
       dc ooXoXoXo
       dc ooXoXoXo
       dc ooXoXoXo
       dc ooXoXoXo
       dc ooXoXoXo
       dc ooXoXXXo
       dc ooXoXXXo
       dc ooXoXXXo
       dc ooXoXXXo
       dc ooXooXoo
       dc oooooooo


       dc oXoooXoo
       dc XXXoXXXo
       dc XXXoXXXo
       dc XXXoXXXo
       dc XoXoXoXo
       dc ooXoooXo
       dc ooXoooXo
       dc oXXoooXo
       dc oXoooXXo
       dc oXXoXXXo
       dc oXXoXXoo
       dc ooXoXooo
       dc ooXoXooo
       dc XoXoXoXo
       dc XXXoXXXo
       dc XXXoXXXo
       dc XXXoXXXo
       dc XXXoXXXo
       dc oXooXXXo
       dc oooooooo


       dc XXXoXooo
       dc XXXoXooo
       dc XXXoXooo
       dc XoXoXoXo
       dc XoooXoXo
       dc XoooXoXo
       dc XXooXoXo
       dc XXXoXoXo
       dc XXXoXoXo
       dc XXXoXXXo
       dc ooXoXXXo
       dc ooXoXXXo
       dc XoXoXXXo
       dc XoXoooXo
       dc XXXoooXo
       dc XXXoooXo
       dc XXXoooXo
       dc XXXoooXo
       dc oXooooXo
       dc oooooooo


       dc XXXooXoo
       dc XXXoXXXo
       dc XXXoXXXo
       dc XXXoXXXo
       dc XoXoXoXo
       dc ooXoXooo
       dc ooXoXXoo
       dc ooXoXXXo
       dc ooXoXXXo
       dc oXXoXXXo
       dc oXooXoXo
       dc oXooXoXo
       dc oXooXoXo
       dc oXooXoXo
       dc oXooXXXo
       dc oXooXXXo
       dc oXooXXXo
       dc oXooXXXo
       dc oXoooXoo
       dc oooooooo


       dc oXoooXoo
       dc XXXoXXXo
       dc XXXoXXXo
       dc XXXoXXXo
       dc XoXoXoXo
       dc XoXoXoXo
       dc XoXoXoXo
       dc XoXoXXXo
       dc XXXooXoo
       dc XXXooXoo
       dc oXXoXXXo
       dc ooXoXoXo
       dc ooXoXoXo
       dc XoXoXoXo
       dc XXXoXXXo
       dc XXXoXXXo
       dc XXXoXXXo
       dc XXXoXXXo
       dc oXoooXoo
       dc oooooooo


    ;    dc oooooooo
    ;    dc oooooooo
    ;    dc oooooooo
    ;    dc oooooooo
    ;    dc oooooooo
    ;    dc oooooooo
    ;    dc oooooooo
    ;    dc oooooooo
    ;    dc oooooooo
    ;    dc oooooooo
    ;    dc oooooooo
    ;    dc oooooooo
    ;    dc oooooooo
    ;    dc oooooooo
    ;    dc oooooooo
    ;    dc oooooooo
    ;    dc oooooooo
    ;    dc oooooooo


    ;    dc oXoooXoo
    ;    dc oXoooXoo
    ;    dc oXoooXoo
    ;    dc oXoooooo
    ;    dc oXooXXXo
    ;    dc oXooXXXo
    ;    dc oXooXXXo
    ;    dc oXooXXXo
    ;    dc oXoooXoo
    ;    dc oXoooXoo
    ;    dc oXoooXoo
    ;    dc oooooXoo
    ;    dc ooooXoXo
    ;    dc ooooXoXo
    ;    dc oXooXoXo
    ;    dc oXooXoXo
    ;    dc oXooXoXo
    ;    dc oooooooo
    ;    dc oooooooo
    ;    dc oooooooo


       dc oooXXXoo
       dc oooXXXoo
       dc oooXXXoo
       dc oooXoXXo
       dc oooXooXo
       dc oooXooXo
       dc ooXXXoXo
       dc ooXXXoXo
       dc ooXXXoXo
       dc ooXXXoXo
       dc ooXXXoXo
       dc ooXXXoXo
       dc oooXooXo
       dc oooXooXo
       dc oooXoXXo
       dc oooXXXoo
       dc oooXXXoo
       dc oooXXXoo
       dc oooooooo
       dc oooooooo


       dc XXoooXoo
       dc XXXooXoo
       dc XXXooXoo
       dc XXXoXXXo
       dc XoXoXXXo
       dc XoXoXoXo
       dc XoXoXoXo
       dc XXXoXoXo
       dc XXooXoXo
       dc XXXoXXXo
       dc XoXoXXXo
       dc XoXoXXXo
       dc XoXoXXXo
       dc XoXoXXXo
       dc XoXoXXXo
       dc XXXoXoXo
       dc XXXoXoXo
       dc XXXoXoXo
       dc XXooXoXo
       dc oooooooo


       dc XooooXXo
       dc XXoooXXo
       dc XXooXXXo
       dc XXXoXXXo
       dc XXXoXXoo
       dc XoXoXooo
       dc XoXoXooo
       dc XoXoXooo
       dc XoXoXooo
       dc XoXoXooo
       dc XoXoXooo
       dc XoXoXooo
       dc XoXoXoXo
       dc XoXoXXXo
       dc XXXoXXXo
       dc XXXoXXXo
       dc XXXoXXXo
       dc XXXoXXXo
       dc XXoooXXo
       dc oooooooo


       dc XXXoXXXo
       dc XXXoXXXo
       dc XXXoXXXo
       dc XXXoXXXo
       dc XoooXooo
       dc XoooXooo
       dc XoooXXoo
       dc XoooXXoo
       dc XXooXXoo
       dc XXooXXoo
       dc XXooXooo
       dc XXooXooo
       dc XoooXooo
       dc XoooXXXo
       dc XoooXXXo
       dc XoooXXXo
       dc XoooXXXo
       dc XoooXXXo
       dc XoooXXXo
       dc oooooooo


       dc XoXooXoo
       dc XoXoXXXo
       dc XoXoXXXo
       dc XoXoXXXo
       dc XoXoXoXo
       dc XoXoXooo
       dc XoXoXooo
       dc XoXoXooo
       dc XXXoXoXo
       dc XXXoXoXo
       dc XXXoXoXo
       dc XXXoXoXo
       dc XoXoXoXo
       dc XoXoXoXo
       dc XoXoXXXo
       dc XoXoXXXo
       dc XoXoXXXo
       dc XoXoXXXo
       dc XoXooXXo
       dc oooooooo

       dc ooXoXXXo
       dc ooXoXXXo
       dc ooXoXXXo
       dc ooXoXXXo
       dc ooXooXoo
       dc ooXooXoo
       dc ooXooXoo
       dc ooXooXoo
       dc ooXooXoo
       dc ooXooXoo
       dc ooXooXoo
       dc ooXooXoo
       dc XoXooXoo
       dc XoXoXXXo
       dc XXXoXXXo
       dc XXXoXXXo
       dc XXXoXXXo
       dc XXXoXXXo
       dc oXooXXXo
       dc oooooooo

       dc XoooXoXo
       dc XoooXoXo
       dc XoooXoXo
       dc XoooXoXo
       dc XoooXoXo
       dc XoooXoXo
       dc XoooXXXo
       dc XoooXXoo
       dc XoooXXoo
       dc XoooXXoo
       dc XoooXXoo
       dc XoooXXXo
       dc XoXoXXXo
       dc XXXoXoXo
       dc XXXoXoXo
       dc XXXoXoXo
       dc XXXoXoXo
       dc XXXoXoXo
       dc XXXoXoXo
       dc oooooooo

    ;    dc XXooXoXo
    ;    dc XXooXoXo
    ;    dc XXooXoXo
    ;    dc XXXoXXXo
    ;    dc XXXoXXXo
    ;    dc XXXoXXXo
    ;    dc XXXoXXXo
    ;    dc XoXoXXXo
    ;    dc XoXoXXXo
    ;    dc XoXoXoXo
    ;    dc XoXoXoXo
    ;    dc XoXoXoXo
    ;    dc XoXoXoXo
    ;    dc XoXoXoXo
    ;    dc XoXoXoXo
    ;    dc XoXoXoXo
    ;    dc XoXoXoXo
    ;    dc XoXoXoXo

       dc ooXoXoXo
       dc ooXoXoXo
       dc XoXoXoXo
       dc XoXoXXXo
       dc XoXoXXXo
       dc XXXoXXXo
       dc XXXoXXXo
       dc XXXoXXXo
       dc XXXoXXXo
       dc XXXoXoXo
       dc XXXoXoXo
       dc XXXoXoXo
       dc XXXoXoXo
       dc XoXoXoXo
       dc XoXoXoXo
       dc XoXoXoXo
       dc XoooXoXo
       dc XoooXoXo
       dc XoooXoXo
       dc oooooooo


       dc XXoooXoo
       dc XXXoXXXo
       dc XXXoXXXo
       dc XXXoXXXo
       dc XoXoXoXo
       dc XoXoXoXo
       dc XoXoXoXo
       dc XoXoXoXo
       dc XXXoXoXo
       dc XXXoXoXo
       dc XXXoXoXo
       dc XXXoXoXo
       dc XXXoXoXo
       dc XXooXoXo
       dc XoooXXXo
       dc XoooXXXo
       dc XoooXXXo
       dc XoooXXXo
       dc XooooXoo
       dc oooooooo

       dc XXoooXoo
       dc XXXoXXXo
       dc XXXoXXXo
       dc XXXoXXXo
       dc XXXoXoXo
       dc XoXoXoXo
       dc XoXoXoXo
       dc XXXoXoXo
       dc XXXoXoXo
       dc XXooXoXo
       dc XXooXoXo
       dc XXXoXoXo
       dc XXXoXooo
       dc XoXoXoXo
       dc XoXoXoXX
       dc XoXoXXXX
       dc XoXoXXXX
       dc XoXoXXoX
       dc XoXooXoX
       dc oooooooo

       dc XXXooXXo
       dc XXXoXXXo
       dc XXXoXXXo
       dc XXXoXXXo
       dc XXXoXoXo
       dc XXooXooo
       dc oXooXXoo
       dc oXooXXXo
       dc oXooXXXo
       dc oXoooXXo
       dc oXooooXo
       dc oXooooXo
       dc oXooooXo
       dc oXooXXXo
       dc oXooXXXo
       dc oXooXXXo
       dc oXooXXXo
       dc oXooXXXo
       dc oXooXXoo
       dc oooooooo

       dc XoXoXoXo
       dc XoXoXoXo
       dc XoXoXoXo
       dc XoXoXoXo
       dc XoXoXoXo
       dc XoXoXoXo
       dc XoXoXoXo
       dc XoXoXoXo
       dc XoXoXoXo
       dc XoXoXoXo
       dc XoXoXoXo
       dc XXXoXoXo
       dc XXXoXoXo
       dc XXXoXXXo
       dc oXooXXXo
       dc oXooXXXo
       dc oXooXXXo
       dc oXooXXXo
       dc oXoooXoo
       dc oooooooo

       dc XoXoXoXo
       dc XoXoXoXo
       dc XoXoXoXo
       dc XoXoXoXo
       dc XoXoXoXo
       dc XoXoXoXo
       dc XXXoXoXo
       dc XXXoXoXo
       dc oXooXoXo
       dc oXooXoXo
       dc oXooXoXo
       dc XXXoXXXo
       dc XXXoXXXo
       dc XoXoXXXo
       dc XoXoXXXo
       dc XoXoXXXo
       dc XoXoXoXo
       dc XoXoXoXo
       dc XoXoXoXo
       dc oooooooo

       dc XXXoXoXo
       dc XXXoXoXo
       dc XXXoXoXo
       dc XXXoXoXo
       dc ooXoXoXo
       dc ooXoXoXo
       dc ooXoXXXo
       dc ooXoXXXo
       dc oXXoXXXo
       dc XXXoXXXo
       dc XXXooXoo
       dc XXoooXoo
       dc XooooXoo
       dc XooooXoo
       dc XooooXoo
       dc XooooXoo
       dc XXXooXoo
       dc XXXooXoo
       dc XXXooXoo
       dc oooooooo

    ;    dc oooooooo
    ;    dc oooooooo
    ;    dc oooooooo
    ;    dc oooooooo
    ;    dc oooooooo
    ;    dc XXooXXoo
    ;    dc XXXoXXXo
    ;    dc XXXoXXXo
    ;    dc XoXoXXXo
    ;    dc XoXoXoXo
    ;    dc XoXoXoXo
    ;    dc XoXoXoXo
    ;    dc XoXoXoXo
    ;    dc XXXoXoXo
    ;    dc XXooXoXo
    ;    dc Xooooooo
    ;    dc Xooooooo
    ;    dc Xooooooo


;    echo "   - 3PIX DIGIT SHAPES from", _DIGIT_SHAPE, "to", *, "(", [(* - _DIGIT_SHAPE)]d , " bytes"


;███████████████████████████████████████████████████████████████████████████████

_TITLE_SCREEN

    include "titleData.asm"

;    echo "   - TITLE SCREEN  from", _TITLE_SCREEN, "to", *, "(", (* - _TITLE_SCREEN) , "bytes)"





    IF _ENABLE_ATARIVOX

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

;                    ldx #<_DS_TooARM            ; assumed 0

                    ldx #0
                    stx NUSIZ0
                    stx NUSIZ1
    IF _ENABLE_ATARIVOX
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


    IF _ENABLE_ATARIVOX
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

                    ldy #<_DS_TooARM
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
                    lda #DSCOMM     ; = _P1oX





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


                    lda #DSCOMM     ; = _P0oX


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

    ; IF _ENABLE_ATARIVOX
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

    ; #if _ENABLE_ATARIVOX
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


;    echo "Kernels end @", * - 1




FREE_INDIRECT = ARM_DIRECT_DATA - END_OF_INDIRECT_DATA

 ;   echo "----", *, " (end of kernels)"

 ;   echo "----", [$7FED-*]d, " kernel bytes available"
 ;   echo "----", [FREE_INDIRECT]d, " indirect bytes available"

;    echo "TOTAL free ROM space =", [FREE_INDIRECT + ($7FEd - *)]d, "bytes"


FREE_SPACE = ARM_DIRECT_DATA_END - $8000 - *
    echo "FREE END-SPACE =", (FREE_SPACE)d, "bytes"

;===============================================================================

    ORG $7FED
    RORG $FFED

ARM_DIRECT_DATA_END

                    jmp InitSystem

                    ds 12, 0                         ; reserve space for CDFJ registers

                    .WORD InitSystem
                    .WORD InitSystem

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

_DS_TooARM

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

_1ROW = _BOARD_COLS


_BOARD              ds _BOARD_COLS * _BOARD_ROWS + 4    ; extra for grab+1 in drawscreen "bug"



    IF _ENABLE_ATARIVOX
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
; _EVERY_FRAME_ZERooSTART:

;     align 4 ; need to be 4 byte aligned to use myMemsetInt
; _EVERY_FRAME_ZERooCOUNT=*-_EVERY_FRAME_ZERooSTART   ; end of zeroed out data



    ; modify custom.boot.lds to adjust display data RAM

    echo "----",($E5F - *)d , "bytes of Display Data RAM avaialble"
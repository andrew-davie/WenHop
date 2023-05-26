;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
; CDFJ Plus - Atari 2600 Bankswitching Include
; Chris Walton, Fred Quimby, Darrell Spice Jr, John Champeau
; (C) Copyright 2022
;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;

; Fetcher Constants
DS0DATA     = $00
DS1DATA     = $01
DS2DATA     = $02
DS3DATA     = $03
DS4DATA     = $04
DS5DATA     = $05
DS6DATA     = $06
DS7DATA     = $07
DS8DATA     = $08
DS9DATA     = $09
DS10DATA    = $0A
DS11DATA    = $0B
DS12DATA    = $0C
DS13DATA    = $0D
DS14DATA    = $0E
DS15DATA    = $0F
DS16DATA    = $10
DS17DATA    = $11
DS18DATA    = $12
DS19DATA    = $13
DS20DATA    = $14
DS21DATA    = $15
DS22DATA    = $16
DS23DATA    = $17
DS24DATA    = $18
DS25DATA    = $19
DS26DATA    = $1A
DS27DATA    = $1B
DS28DATA    = $1C
DS29DATA    = $1D
DS30DATA    = $1E
DS31DATA    = $1F
DSCOMM      = $20           ; datastream used for DSPTR and DSWRITE
DSJMP1      = $21           ; datastream used for JMP FASTJMP1
DSJMP2      = $22           ; datastream used for JMP FASTJMP2
AMPLITUDE   = $23

; Mode Constants
FASTON      = $00
FASTOFF     = $0F
AUDIOSAMPLE = $00
AUDIOMUSIC  = $F0

; FastJmp Address
FASTJMP1    = $0000
FASTJMP2    = $0001

DSJMP       = DSJMP1        ; for backwards compaitibility
FASTJMP     = FASTJMP1      ; for backwards compatibility

  ; Fast Fetcher options
FF_LDA          = 0         ; LDA # is used for Fast Fetchers
FF_LDA_LDX      = 1         ; LDA # and LDX # are used for Fast Fetchers
FF_LDA_LDY      = 2         ; LDA # and LDY # are used for Fast Fetchers
FF_LDA_LDX_LDY  = 3         ; LDA #, LDX #, and LDY # are used for Fast Fetchers

  ; CDF Base Address
  IFNCONST CDF_BASE_ADDRESS
CDF_BASE_ADDRESS = $1FF0
  ENDIF

  ; CDF Registers
  SEG.U CDF_REGISTERS
  ORG CDF_BASE_ADDRESS

  ; Write Registers
DSWRITE     DS 1    ; $1FF0
DSPTR       DS 1    ; $1FF1
SETMODE     DS 1    ; $1FF2
CALLFN      DS 1    ; $1FF3

  ; Bankswitching Hotspots
SELECTBANK0 DS 1    ; $1FF4
SELECTBANK1 DS 1    ; $1FF5
SELECTBANK2 DS 1    ; $1FF6
SELECTBANK3 DS 1    ; $1FF7
SELECTBANK4 DS 1    ; $1FF8
SELECTBANK5 DS 1    ; $1FF9
SELECTBANK6 DS 1    ; $1FFA

    MAC FFA
.DS SET {1}    
    lda #(.DS + _PC_FF_OFFSET)
    ENDM

    MAC FFX
.DS SET {1}    
    ldx #(.DS + _PC_FF_OFFSET)
    ENDM
    
    MAC FFY
.DS SET {1}    
    ldy #(.DS + _PC_FF_OFFSET)
    ENDM    

    MAC FFSTA
.DS     SET {1}
.DEST   SET {2}
    lda #(.DS + _PC_FF_OFFSET)
    sta .DEST
    ENDM

    MAC FFSTX
.DS     SET {1}
.DEST   SET {2}
    ldx #(.DS + _PC_FF_OFFSET)
    stx .DEST
    ENDM

    MAC FFSTY
.DS     SET {1}
.DEST   SET {2}
    ldy #(.DS + _PC_FF_OFFSET)
    sty .DEST
    ENDM
    
    MAC SLDA
.VAL    SET {1}
    IF (_PC_FF_OFFSET <= .VAL && .VAL <= (_PC_FF_OFFSET + AMPLITUDE) )
        ECHO ""
        ECHO "LDA #",.VAL, "is within Fast Fetcher range of",(_PC_FF_OFFSET)d,"and",(_PC_FF_OFFSET + AMPLITUDE)
        ERR
    ELSE
        lda #.VAL
    ENDIF
    ENDM
    
    MAC SLDX
.VAL    SET {1}
    IF (_PC_FF_OFFSET <= .VAL && .VAL <= (_PC_FF_OFFSET + AMPLITUDE) )
        ECHO ""
        ECHO "LDX #",.VAL, "is within Fast Fetcher range of",(_PC_FF_OFFSET)d,"and",(_PC_FF_OFFSET + AMPLITUDE)
        ERR
    ELSE
        ldx #.VAL
    ENDIF
    ENDM

    MAC SLDY
.VAL    SET {1}
    IF (_PC_FF_OFFSET <= .VAL && .VAL <= (_PC_FF_OFFSET + AMPLITUDE) )
        ECHO ""
        ECHO "LDY #",.VAL, "is within Fast Fetcher range of",(_PC_FF_OFFSET)d,"and",(_PC_FF_OFFSET + AMPLITUDE)
        ERR
    ELSE
        ldy #.VAL
    ENDIF
    ENDM
    
  SEG


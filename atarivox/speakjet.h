; AtariVox Speech Synth Driver
;; By Alex Herbert, 2004
; Updated for CDFJ usage by Andrew Davie 2022


SERIAL_OUTMASK  equ     $01
SERIAL_RDYMASK  equ     $02


    MAC SPKOUT2

    IF __ENABLE_ATARIVOX

                lda SWCHA
                and #SERIAL_RDYMASK     ; buffer full?
                beq .speechDone

                lda #_DS_SPEECH         ; data stream phoneme
                eor #$FF
                beq .speechDone


    ; output byte as serial data
    ; send 1 start bit, 8 data bits, 1 stop bit

                ldy #10

                sec                     ; start bit
.serialiseBit   tax                     ; 2 @2

                lda SWACNT              ; 4 @6
                and #$fe                ; 2 @8
                adc #0                  ; 2 @10     C -> D0
                sta SWACNT              ; 4 @14     (and C now clear)

                dey                     ; 2 @16
                beq .speechDone         ; 2 @18

                lda #-6                 ; 2 @20
.wasteCycles    adc #1                  ; 2         C is clear!
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


    ENDIF   // __ATARIVOX
    ENDM


    IF 0

;
; AtariVox EEPROM Driver
; By Alex Herbert, 2004
; Optimisations by Thomas Jentzsch, 2006/2008
; Fix for Speakjet noise during I2C_TXBIT, 2016
; adapted for CDFJ by Andrew Davie 2022

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




    ENDIF



; EOF

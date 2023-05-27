
                    ldx #%00110011
                    stx NUSIZ0                      ; three copies close, missile x8
                    stx NUSIZ1                      ; three copies close, missile x8
                    stx VDELP0                      ; vertical delay on
                    stx VDELP1                      ; vertical delay on

OverScanMenu

    ; axiom: D2 of X == 1

                    sta WSYNC
                    stx VBLANK              ; video output off (D2 of X is 1 always!)


                    ldx kernel
                    cpx currentKernel
                    beq thisKernel

                    jmp startAnyKernel
thisKernel


                    ldx tv_type
                    lda TimerOS,x
                    clc
                    adc #1
                    sta TIM64T              ; set timer for OS

                    lda #_DS_AUDV0
                    sta AUDV0
                    lda #_DS_AUDC0
                    sta AUDC0
                    lda #_DS_AUDF0
                    sta AUDF0

                    lda #_DS_AUDV0
                    sta AUDV1
                    lda #_DS_AUDC0
                    sta AUDC1
                    lda #_DS_AUDF0
                    sta AUDF1


    IF _ENABLE_ATARIVOX
        jsr speakJet
    ENDIF

                    ldy #_FN_MENU_OS
processArmOSMenu    jsr CallArmCode
                    ldy #_FN_MENU_IDLE
                    jsr CallArmCode
                    ;jsr safeTimerCheck
                    ;tmp bcs processArmOSMenu

safeTimerWait2      lda INTIM
                    bpl safeTimerWait2
                    ;jsr safeTimerWait


VerticalSyncMenu

                    ldy #2

                    ldx tv_type
                    lda TimerVB,x

                    sty WSYNC

; --- start scanline 1 of Vertical Sync ---

                    sty VSYNC           ; turn on Vertical Sync signal
                    sta TIM64T
                    sty WSYNC

; --- start scanline 2 of Vertical Sync ---

                    ; use otherwise wasted time to zero out some TIA registers

                    ldx #0              ; 2  2
                    stx PF0             ; 3 17
;                    stx CTRLPF          ; 3 26
                    stx WSYNC           ; 3 29/0

; --- start scanline 3 of Vertical Sync ---



    ; IF _ENABLE_ATARIVOX
    ;     jsr speakJet
    ; ENDIF


                    ldy #_FN_MENU_VB
                    stx WSYNC           ; end of VerticalSync scanline 3
                    stx VSYNC           ; turn off Vertical Sync signal
                    jsr CallArmCode

                    ldx #1
vbSetInitialMenu    lda #DSCOMM                 ; P1_X, P0_X

PosObject

    ; A = X position value
    ; X = 0=P0, 1=P1, 2=M0, 3=M1, 4=Ball

                    sec
                    sta WSYNC
DivideLoop          sbc #15
                    bcs DivideLoop

                    eor #7
                    asl
                    asl
                    asl
                    asl
                    sta.wx HMP0,X
                    sta RESP0,X

                    dex
                    bpl vbSetInitialMenu

                    lda #DSCOMM
                    sta tv_type                 ; _TV_TYPE = NTSC, PAL, PAL-60, SECAM
                    lda #DSCOMM
                    sta kernel
                    lda #DSCOMM
                    sta COLUBK

                    sta WSYNC
                    sta HMOVE




processArmVBMenu    ldy #_FN_MENU_IDLE
                    jsr CallArmCode
                    ;jsr safeTimerCheck
                    ;tmp bcs processArmVBMenu
                    ;jsr safeTimerWait
safeTimerWait3      lda INTIM
                    bpl safeTimerWait3


                    ldx #0
                    stx VBLANK              ; video output on
                    stx PF0

                    ldx #%00000001
                    stx CTRLPF              ; reflect PF

                    lda #_DS_COLUPF
                    sta COLUPF

                    sta WSYNC
    ;                sta WSYNC
                    jmp FASTJMP1


_MENU_KERNEL

;@3

                    lda #_DS_PF1_LEFT
                    sta PF1                         ; 5
                    lda #_DS_GRP0a
                    sta GRP0                        ; 5
                    lda #_DS_GRP1a
                    sta GRP1                        ; 5
                    lda #_DS_GRP0b
                    sta GRP0                        ; 5

                    lda #_DS_GRP1c                  ; 2
                    tay                             ; 2

                    lda #_DS_PF2_LEFT
                    sta PF2                         ; 5

                    lda #_DS_GRP0c                  ; 2
                    tax                             ; 2
                    lda #_DS_PF1_RIGHT
                    sta PF1                         ; 5
;@41
                    lda #_DS_PF2_RIGHT              ; 2
                    nop                             ; 2
                    sta PF2                         ; 3

                    lda #_DS_GRP1b                  ; 2
                    sta GRP1                        ; 3
                    stx GRP0                        ; 3
                    sty GRP1                        ; 3
                    sta GRP0                        ; 3

;@62

                    lda #_DS_COLUP0                 ; 2
                    sta COLUP0                      ; 3
                    sta.w COLUP1                    ; 4

                    lda #_DS_COLUPF                 ; 2
                    sta COLUPF                      ; 3
;@76=0

                    jmp FASTJMP1                    ; 3

;@3--> start of line again :)


_EXIT_MENU_KERNEL

                    ldx #2
                    stx VBLANK
                    ldy #0
                    sty PF1
                    sty PF2

                    jmp OverScanMenu

; EOF
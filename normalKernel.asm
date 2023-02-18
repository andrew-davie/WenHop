_NORMAL_KERNEL

    ; This is the entire display
    ;@3

                    SLEEP 5                         ; @8

                    lda #_DS_COLUBK
                    sta WSYNC                       ; 5 @13

                    sta COLUBK                      ; 3

                    lda #_DS_COLUPF
                    sta COLUPF                      ; 5 @21

                    lda #_DS_PF0_LEFT
                    sta PF0                         ; 5

                    lda #_DS_GRP0a
                    sta GRP0                        ; 5

                    lda #_DS_PF1_LEFT
                    sta PF1                         ; 5

                    lda #_DS_GRP1a
                    sta GRP1                        ; 5 @41

                    lda #_DS_PF2_LEFT
                    sta PF2                         ; 5

                    lda #_DS_PF0_RIGHT
                    sta PF0                         ; 5
                    lda #_DS_PF1_RIGHT
                    sta PF1                         ; 5
                    lda #_DS_PF2_RIGHT
                    sta PF2                         ; 5 @61 

                    SLEEP 5                         ; @66

                    lda #_DS_COLUP0
                    sta COLUP0                      ; 5
                    lda #_DS_COLUP1
                    sta COLUP1                      ; 5 @76

                    jmp FASTJMP1                    ; 3 @3   --> NORMAL_KERNEL until last line

    ;@3--> start of line again :)


_EXIT_KERNEL        SLEEP 5

                    ldx #2
                    stx VBLANK
            
                    jmp OverScan

; EOF
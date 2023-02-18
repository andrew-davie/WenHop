; MACRO.H
; Version 1.07, 2/SEPTEMBER/2013

VERSION_MACRO         = 107  ; unoffical version

;
; THIS FILE IS EXPLICITLY SUPPORTED AS A DASM-PREFERRED COMPANION FILE
; PLEASE DO *NOT* REDISTRIBUTE MODIFIED VERSIONS OF THIS FILE!
;
; This file defines DASM macros useful for development for the Atari 2600.
; It is distributed as a companion machine-specific support package
; for the DASM compiler. Updates to this file, DASM, and associated tools are
; available at at http://www.atari2600.org/dasm
;
; Many thanks to the people who have contributed.  If you take issue with the
; contents, or would like to add something, please write to me
; (atari2600@taswegian.com) with your contribution.
;
; Latest Revisions...
;
; 1.06  03/SEP/2004     - nice revision of VERTICAL_BLANK (Edwin Blink)
; 1.05  14/NOV/2003     - Added VERSION_MACRO equate (which will reflect 100x version #)
;                         This will allow conditional code to verify MACRO.H being
;                         used for code assembly.
; 1.04  13/NOV/2003     - SET_POINTER macro added (16-bit address load)
;
; 1.03  23/JUN/2003     - CLEAN_START macro added - clears TIA, RAM, registers
;
; 1.02  14/JUN/2003     - VERTICAL_SYNC macro added
;                         (standardised macro for vertical synch code)
; 1.01  22/MAR/2003     - SLEEP macro added.
;                       - NO_ILLEGAL_OPCODES switch implemented
; 1.0   22/MAR/2003     Initial release

; Note: These macros use illegal opcodes.  To disable illegal opcode usage,
;   define the symbol NO_ILLEGAL_OPCODES (-DNO_ILLEGAL_OPCODES=1 on command-line).
;   If you do not allow illegal opcode usage, you must include this file
;   *after* including VCS.H (as the non-illegal opcodes access hardware
;   registers and require them to be defined first).

; Available macros...
;   SLEEP n             - sleep for n cycles
;   VERTICAL_SYNC       - correct 3 scanline vertical synch code
;   CLEAN_START         - set machine to known state on startup
;   SET_POINTER         - load a 16-bit absolute to a 16-bit variable

;-------------------------------------------------------------------------------
; SLEEP duration
; Original author: Thomas Jentzsch
; Inserts code which takes the specified number of cycles to execute.  This is
; useful for code where precise timing is required.
; ILLEGAL-OPCODE VERSION DOES NOT AFFECT FLAGS OR REGISTERS.
; LEGAL OPCODE VERSION MAY AFFECT FLAGS
; Uses illegal opcode (DASM 2.20.01 onwards).

            MAC SLEEP            ;usage: SLEEP n (n>1)
.CYCLES     SET {1}

                IF .CYCLES < 2
                    ECHO "MACRO ERROR: 'SLEEP': Duration must be > 1"
                    ERR
                ENDIF

                IF .CYCLES & 1
                    IFNCONST NO_ILLEGAL_OPCODES
                        nop 0
                    ELSE
                        bit VSYNC
                    ENDIF
.CYCLES             SET .CYCLES - 3
                ENDIF

                REPEAT .CYCLES / 2
                    nop
                REPEND
            ENDM

;-------------------------------------------------------------------------------
; VERTICAL_SYNC
; revised version by Edwin Blink -- saves bytes!
; Inserts the code required for a proper 3 scanline vertical sync sequence
; Note: Alters the accumulator

; OUT: A = 0

             MAC VERTICAL_SYNC
                lda #%1110          ; each '1' bits generate a VSYNC ON line (bits 1..3)
.VSLP1          sta WSYNC           ; 1st '0' bit resets Vsync, 2nd '0' bit exit loop
                sta VSYNC
                lsr
                bne .VSLP1          ; branch until VYSNC has been reset
             ENDM

;-------------------------------------------------------------------------------
; CLEAN_START
; Original author: Omegamatrix
; - Minimal bytes used to set stack pointer, Clear RIOT ram and TIA registers
; - Uses no illegal opcodes.
; - Finishes with SP=$FF, X=0, A=0, Y=0
; - Jumps between operator and operand to perform ASL until A=0, TIA registers
;   finally get cleared at their mirrored locations ($40 and up).
; - SEI is unnecessary and can be cut because the 2600 has no interrupt line.
; - TAY at the end is not really necessary, and can also be cut.

  MAC CLEAN_START
    sei      
    cld
.CLEAR_STACK
    ldx    #$0A            ; ASL opcode = $0A
    inx
    txs
    pha
    bne    .CLEAR_STACK+1  ; jump between operator and operand to do ASL
    tay							; SP=$FF, X = A = Y = 0
  ENDM

;-------------------------------------------------------
; SET_POINTER
; Original author: Manuel Rotschkar
;
; Sets a 2 byte RAM pointer to an absolute address.
;
; Usage: SET_POINTER pointer, address
; Example: SET_POINTER SpritePTR, SpriteData
;
; Note: Alters the accumulator, NZ flags
; IN 1: 2 byte RAM location reserved for pointer
; IN 2: absolute address

            MAC SET_POINTER
.POINTER    SET {1}
.ADDRESS    SET {2}

                LDA #<.ADDRESS  ; Get Lowbyte of Address
                STA .POINTER    ; Store in pointer
                LDA #>.ADDRESS  ; Get Hibyte of Address
                STA .POINTER+1  ; Store in pointer+1

            ENDM

;-------------------------------------------------------
; BOUNDARY byte#
; Original author: Denis Debro (borrowed from Bob Smith / Thomas)
;
; Push data to a certain position inside a page and keep count of how
; many free bytes the programmer will have.
;
; eg: BOUNDARY 5    ; position at byte #5 in page

.FREE_BYTES SET 0
   MAC BOUNDARY
      REPEAT 256
         IF <. % {1} = 0
            MEXIT
         ELSE
.FREE_BYTES SET .FREE_BYTES + 1
            .byte $00
         ENDIF
      REPEND
   ENDM

;-------------------------------------------------------
; SAME PAGE BRANCH CHECK
; Original auther: John Payson
;
; Usage: sbeq, sbne, etc just like a normal beq, bne, etc.
;        A message will be output if the target of the branch
;        is not on the same page.
;
            mac sbcc
                bcc     {1}
                if (* ^ {1}) & $FF00
                echo "PAGE CROSSING","WARNING ",{1}," at ",*
                err
                endif
            endm

            mac sbcs
                bcs     {1}
                if (* ^ {1}) & $FF00
                echo "PAGE CROSSING","WARNING ",{1}," at ",*
                err
                endif
            endm

            mac sbeq
                beq     {1}
                if (* ^ {1}) & $FF00
                echo "PAGE CROSSING","WARNING ",{1}," at ",*
                err
                endif
            endm

            mac sbmi
                bmi     {1}
                if (* ^ {1}) & $FF00
                echo "PAGE CROSSING","WARNING ",{1}," at ",*
                err
                endif
            endm

            mac sbne
                bne     {1}
                if (* ^ {1}) & $FF00
                echo "PAGE CROSSING","WARNING ",{1}," at ",*
                err
                endif
            endm

            mac sbpl
                bpl     {1}
                if (* ^ {1}) & $FF00
                echo "PAGE CROSSING","WARNING ",{1}," at ",*
                err
                endif
            endm

            mac sbvc
                bvc     {1}
                if (* ^ {1}) & $FF00
                echo "PAGE CROSSING","WARNING ",{1}," at ",*
                err
                endif
            endm

            mac sbvs
                bvs     {1}
                if (* ^ {1}) & $FF00
                echo "PAGE CROSSING","WARNING ",{1}," at ",*
                err
                endif
            endm

;-------------------------------------------------------
; DIFFERENT PAGE BRANCH CHECK
; Original auther: Darrell Spice, Jr.
;
; Usage: dbeq, dbne, etc just like a normal beq, bne, etc.
;        A message will be output if the target of the branch
;        is not on a different page.
;
            mac dbcc
                bcc     {1}
                if ((* ^ {1}) & $FF00) = 0
                echo "SAME PAGE","WARNING ",{1}," at ",*
                err
                endif
            endm

            mac dbcs
                bcs     {1}
                if ((* ^ {1}) & $FF00) = 0
                echo "SAME PAGE","WARNING ",{1}," at ",*
                err
                endif
            endm

            mac dbeq
                beq     {1}
                if ((* ^ {1}) & $FF00) = 0
                echo "SAME PAGE","WARNING ",{1}," at ",*
                err
                endif
            endm

            mac dbmi
                bmi     {1}
                if ((* ^ {1}) & $FF00) = 0
                echo "SAME PAGE","WARNING ",{1}," at ",*
                err
                endif
            endm

            mac dbne
                bne     {1}
                if ((* ^ {1}) & $FF00) = 0
                echo "SAME PAGE","WARNING ",{1}," at ",*
                err
                endif
            endm

            mac dbpl
                bpl     {1}
                if ((* ^ {1}) & $FF00) = 0
                echo "SAME PAGE","WARNING ",{1}," at ",*
                err
                endif
            endm

            mac dbvc
                bvc     {1}
                if ((* ^ {1}) & $FF00) = 0
                echo "SAME PAGE","WARNING ",{1}," at ",*
                err
                endif
            endm

            mac dbvs
                bvs     {1}
                if ((* ^ {1}) & $FF00) = 0
                echo "SAME PAGE","WARNING ",{1}," at ",*
                err
                endif
            endm


; EOF

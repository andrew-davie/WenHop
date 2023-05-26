;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
; CDFJ Plus - Atari 2600 Configure CDFJ+ Project
; Chris Walton, Fred Quimby, Darrell Spice Jr, John Champeau
; (C) Copyright 2022
;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;


;===============================================================================
; Validiate _PC_ROM_SIZE
;----------------------------------------
;   Valid ROM sizes are 32, 64, 128, 256, and 512
;===============================================================================

    IF (_PC_ROM_SIZE != 32 && _PC_ROM_SIZE != 64 && _PC_ROM_SIZE != 128 && _PC_ROM_SIZE != 256 && _PC_ROM_SIZE != 512)

        ECHO ""
        ECHO "==============================================="
        ECHO (_PC_ROM_SIZE)d, "is an unsupported size for _PC_ROM_SIZE."
        ECHO "Supported values are 32, 64, 128, 256, and 512."
        ECHO "==============================================="
        ERR

    ENDIF



;===============================================================================
; Configure RAM
;----------------------------------------
;   Set _PC_RAM_SIZE and the C Stack Pointer based on the ROM size
;   Note: If using IAP then decrease C Stack Pointer to $4000xFDC
;===============================================================================

    IF (_PC_ROM_SIZE == 32)

_PC_RAM_SIZE = 8
C_STACK = $40001FFC

    ENDIF

    IF (_PC_ROM_SIZE == 64 || _PC_ROM_SIZE == 128)

_PC_RAM_SIZE = 16
C_STACK = $40003FFC

    ENDIF

    IF (_PC_ROM_SIZE == 256 || _PC_ROM_SIZE == 512)

_PC_RAM_SIZE = 32
C_STACK = $40007FFC

    ENDIF



;===============================================================================
; Validiate _PC_DD_SIZE
;----------------------------------------
;   Make sure there's enough RAM left for C usage after factoring in the amount
;   of Display Data RAM that was allocated and the size of the CDFJ+ driver.
;===============================================================================


    IF (_PC_RAM_SIZE * 1024 - _PC_DD_SIZE - 2048 < 0)
        ECHO ""
        ECHO "==========================================================="
        ECHO "_PC_DD_SIZE of", (_PC_DD_SIZE)d, "leaves no RAM for C Variables and Stack"
        ECHO "==========================================================="
        ERR
    ENDIF

    IF (_PC_RAM_SIZE * 1024 - _PC_DD_SIZE - 2048 < 512)
        ECHO ""
        ECHO "==========================================================="
        ECHO "WARNING: _PC_DD_SIZE of", (_PC_DD_SIZE)d, "bytes"
        ECHO "         only leaves", (_PC_RAM_SIZE * 1024 - _PC_DD_SIZE - 2048)d, "bytes for C Variables and Stack"
        ECHO "==========================================================="
        ECHO ""
    ELSE
        ECHO "---- C Variable and Stack has", (_PC_RAM_SIZE * 1024 - _PC_DD_SIZE - 2048)d, "bytes of RAM"
    ENDIF

    IF ((_PC_DD_SIZE & 3) != 0)
        ECHO ""
        ECHO "==========================================================="
        ECHO "WARNING: _PC_DD_SIZE is", (_PC_DD_SIZE)d, "bytes"
        ECHO "         but should be evenly divisible by 4"
        ECHO "==========================================================="
    ENDIF



;===============================================================================
; Validiate _PC_FF_OFFSET
;----------------------------------------
;   Make sure all datastreams are accessible using the specified offset.
;===============================================================================

    IF (_PC_FF_OFFSET < 0 || _PC_FF_OFFSET  > 220 )
        ECHO ""
        ECHO "==========================================================="
        ECHO "_PC_FF_OFFSET is", (_PC_FF_OFFSET)d, "it should be from 0 to 220"
        ECHO "==========================================================="
        ERR
    ENDIF


;===============================================================================
; Configure table sizes
;----------------------------------------
;   For 32 and 64K projects use 2 byte entries
;   For 128K+ projects use 4 byte table entries
;
; NOTE: still need to test this
;===============================================================================

    IF (_PC_ROM_SIZE == 32 || _PC_ROM_SIZE == 64)

_PC_TABLE_SIZE = 2

        MAC CTABLE
            .word {1}
            ENDM

    ELSE

_PC_TABLE_SIZE = 4

        MAC CTABLE
            .long {1}
            ENDM
    ENDIF



;===============================================================================
; CDFJ+ Driver
;----------------------------------------
;   Include the appropriate driver based on ROM SIZE and the
;   Fast Fetcher configuration
;
;   Can the driver be patched with LDX, LDY, and OFFSET during make?
;   That would simplify this if possible.
;===============================================================================

   IF (_PC_ROM_SIZE = 32 && _PC_CDFJ_FF = 0)
         INCBIN "cdfjplus_driver/cdfjplus48A_20220131.bin"
  ENDIF
  IF (_PC_ROM_SIZE = 32 && _PC_CDFJ_FF = 1)
         INCBIN "cdfjplus_driver/cdfjplus48AX_20220131.bin"
  ENDIF
  IF (_PC_ROM_SIZE = 32 && _PC_CDFJ_FF = 2)
         INCBIN "cdfjplus_driver/cdfjplus48AY_20220131.bin"
  ENDIF
  IF (_PC_ROM_SIZE = 32 && _PC_CDFJ_FF = 3)
         INCBIN "cdfjplus_driver/cdfjplus48AXY_20220131.bin"
  ENDIF

  IF (_PC_ROM_SIZE >= 64 && _PC_CDFJ_FF = 0)
         INCBIN "cdfjplus_driver/cdfjplus64A_20220131.bin"
  ENDIF
  IF (_PC_ROM_SIZE >= 64 && _PC_CDFJ_FF = 1)
         INCBIN "cdfjplus_driver/cdfjplus64AX_20220131.bin"
  ENDIF
  IF (_PC_ROM_SIZE >= 64 && _PC_CDFJ_FF = 2)
         INCBIN "cdfjplus_driver/cdfjplus64AY_20220131.bin"
  ENDIF
  IF (_PC_ROM_SIZE >= 64 && _PC_CDFJ_FF = 3)
         INCBIN "cdfjplus_driver/cdfjplus64AXY_20220131.bin"
  ENDIF
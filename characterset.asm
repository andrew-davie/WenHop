; Character set definitions

CHAR_BLOCK_START

;CHARSET_START

____ = %00000000
___X = %00000001
__X_ = %00000010
__XX = %00000011
_X__ = %00000100
_X_X = %00000101
_XX_ = %00000110
_XXX = %00000111
X___ = %00001000
X__X = %00001001
X_X_ = %00001010
X_XX = %00001011
XX__ = %00001100
XX_X = %00001101
XXX_ = %00001110
XXXX = %00001111

_____ = %00000000
____X = %00000001
___X_ = %00000010
___XX = %00000011
__X__ = %00000100
__X_X = %00000101
__XX_ = %00000110
__XXX = %00000111
_X___ = %00001000
_X__X = %00001001
_X_X_ = %00001010
_X_XX = %00001011
_XX__ = %00001100
_XX_X = %00001101
_XXX_ = %00001110
_XXXX = %00001111

X____ = %00010000
X___X = %00010001
X__X_ = %00010010
X__XX = %00010011
X_X__ = %00010100
X_X_X = %00010101
X_XX_ = %00010110
X_XXX = %00010111
XX___ = %00011000
XX__X = %00011001
XX_X_ = %00011010
XX_XX = %00011011
XXX__ = %00011100
XXX_X = %00011101
XXXX_ = %00011110
XXXXX = %00011111


__ = %00000000
_X = %00010000
X_ = %00100000
XX = %00110000

__ = %00000000
_Y = %01000000
Y_ = %10000000
YY = %11000000



__CHAR_LADDER_0

    dc XX | __ | XXXX ; 00 <
    dc XX | YY | XXXX ; 01
    dc __ | YY | XXXX ; 02
    dc __ | __ | X__X ; 03 <
    dc XX | YY | X__X ; 04
    dc __ | _Y | X__X ; 05
    dc __ | __ | X__X ; 06 <
    dc XX | YY | X__X ; 07
    dc __ | __ | X__X ; 08
    dc      __ | X__X ; 09 <
    dc      YY | X__X ; 10
    dc      __ | X__X ; 11
    dc      __ | X__X ; 12 <
    dc      YY | X__X ; 13
    dc      __ | X__X ; 14
    dc           X__X ; 15 <
    dc           X__X ; 16
    dc           X__X ; 17
    dc           X__X ; 18 <
    dc           X__X ; 19
    dc           X__X ; 20


__CHAR_LADDER_1

    dc XX | __ | X__X ; 00 <
    dc XX | YY | X__X ; 01
    dc __ | YY | X__X ; 02
    dc __ | __ | X__X ; 03 <
    dc XX | YY | X__X ; 04
    dc __ | _Y | X__X ; 05
    dc __ | __ | X__X ; 06 <
    dc XX | YY | XXXX ; 07
    dc __ | __ | XXXX ; 08
    dc      __ | XXXX ; 09 <
    dc      YY | X__X ; 10
    dc      __ | X__X ; 11
    dc      __ | X__X ; 12 <
    dc      YY | X__X ; 13
    dc      __ | X__X ; 14
    dc           X__X ; 15 <
    dc           X__X ; 16
    dc           X__X ; 17
    dc           X__X ; 18 <
    dc           X__X ; 19
    dc           X__X ; 20

__CHAR_LADDER_2

    dc XX | __ | X__X ; 00 <
    dc XX | YY | X__X ; 01
    dc __ | YY | X__X ; 02
    dc __ | __ | X__X ; 03 <
    dc XX | YY | X__X ; 04
    dc __ | _Y | X__X ; 05
    dc __ | __ | X__X ; 06 <
    dc XX | YY | X__X ; 07
    dc __ | __ | X__X ; 08
    dc      __ | X__X ; 09 <
    dc      YY | X__X ; 10
    dc      __ | X__X ; 11
    dc      __ | X__X ; 12 <
    dc      YY | X__X ; 13
    dc      __ | XXXX ; 14
    dc           XXXX ; 15 <
    dc           XXXX ; 16
    dc           X__X ; 17
    dc           X__X ; 18 <
    dc           X__X ; 19
    dc           X__X ; 20


__CHAR_BOULDER_BROKEN

    dc XX | __ | __X_ ; 00 <
    dc XX | YY | _XX_ ; 01
    dc __ | YY | ____ ; 02
    dc __ | __ | __X_ ; 03 <
    dc XX | YY | _XX_ ; 04
    dc __ | _Y | ____ ; 05
    dc __ | __ | __X_ ; 06 <
    dc XX | YY | _XX_ ; 07
    dc __ | __ | ____ ; 08
    dc      __ | ____ ; 09 <
    dc      YY | ____ ; 10
    dc      __ | ____ ; 11
    dc      __ | _X_X ; 12 <
    dc      YY | XXXX ; 13
    dc      __ | ____ ; 14
    dc           _X_X ; 15 <
    dc           XXXX ; 16
    dc           ____ ; 17
    dc           _X_X ; 18 <
    dc           XXXX ; 19
    dc           ____ ; 20



__CHAR_BOULDER
__CHAR_BOULDER_SHAKE

    dc __XX_ ; 00 <
    dc _____ ; 01
    dc __XX_ ; 02
    dc _____ ; 03 <
    dc _____ ; 04
    dc _XXX_ ; 05
    dc _____ ; 06 <
    dc ____X ; 07
    dc _XXXX ; 08
    dc ____X ; 09 <
    dc _____ ; 10
    dc XXXXX ; 11
    dc ____X ; 12 <
    dc _____ ; 13
    dc XXXXX ; 14
    dc ____X ; 15 <
    dc _____ ; 16
    dc XXXXX ; 17
    dc ____X ; 18 <
    dc _____ ; 19
    dc XXXXX ; 20
    dc ____X ; 21 <
    dc _____ ; 22
    dc XXXXX ; 23
    dc ____X ; 24 <
    dc _____ ; 25
    dc XXXXX ; 26
    dc ___X_ ; 27 <
    dc _____ ; 28
    dc _XXX_ ; 29


__CHAR_BOULDER_DOGE

    dc __XX_ ; 00 <
    dc __XX_ ; 01
    dc _____ ; 02
    dc _____ ; 03 <
    dc _XXX_ ; 04
    dc _____ ; 05
    dc _____ ; 06 <
    dc _XXXX ; 07
    dc ____X ; 08
    dc ____X ; 09 <
    dc XXXXX ; 10
    dc __X_X ; 11
    dc ____X ; 12 <
    dc XXXXX ; 13
    dc _XXX_ ; 14
    dc ____X ; 15 <
    dc XXXXX ; 16
    dc _XXX_ ; 17
    dc ____X ; 18 <
    dc XXXXX ; 19
    dc _XXX_ ; 20
    dc ____X ; 21 <
    dc XXXXX ; 22
    dc __X__ ; 23
    dc ____X ; 24 <
    dc XXXXX ; 25
    dc _____ ; 26
    dc ___X_ ; 27 <
    dc _XXX_ ; 28
    dc _____ ; 29




__CHAR_BOULDER_U

    dc _____ ; 00 <
    dc XX_XX ; 01
    dc __X__ ; 02
    dc _____ ; 03 <
    dc XX_XX ; 04
    dc __X__ ; 05
    dc ____X ; 06 <
    dc XX_XX ; 07
    dc __X__ ; 08
    dc ____X ; 09 <
    dc XXXXX ; 10
    dc __X__ ; 11
    dc _____ ; 12 <
    dc XXXXX ; 13
    dc _XXX_ ; 14
    dc _____ ; 15 <
    dc XXXXX ; 16
    dc _XXX_ ; 17
    dc _____ ; 18 <
    dc XXXXX ; 19
    dc _XXX_ ; 20
    dc ____X ; 21 <
    dc XXXXX ; 22
    dc __X__ ; 23
    dc ____X ; 24 <
    dc XXXXX ; 25
    dc _____ ; 26
    dc ___X_ ; 27 <
    dc _XXX_ ; 28
    dc _____ ; 29



__CHAR_BOULDER_R

    dc __XXX ; 00 <
    dc __XXX ; 01
    dc _____ ; 02
    dc _____ ; 03 <
    dc _XXXX ; 04
    dc _____ ; 05
    dc _____ ; 06 <
    dc _XXXX ; 07
    dc _____ ; 08
    dc _____ ; 09 <
    dc XXXXX ; 10
    dc __X__ ; 11
    dc _____ ; 12 <
    dc XXXX_ ; 13
    dc _XXXX ; 14
    dc _____ ; 15 <
    dc XXXX_ ; 16
    dc _XXXX ; 17
    dc _____ ; 18 <
    dc XXXX_ ; 19
    dc _XXXX ; 20
    dc _____ ; 21 <
    dc XXXXX ; 22
    dc __X__ ; 23
    dc _____ ; 24 <
    dc XXXXX ; 25
    dc _____ ; 26
    dc _____ ; 27 <
    dc _XXXX ; 28
    dc _____ ; 29


__CHAR_BOULDER_D

    dc __XX_ ; 00 <
    dc __XX_ ; 01
    dc _____ ; 02
    dc _____ ; 03 <
    dc _XXX_ ; 04
    dc _____ ; 05
    dc _____ ; 06 <
    dc _XXXX ; 07
    dc ____X ; 08
    dc ____X ; 09 <
    dc XXXXX ; 10
    dc __X__ ; 11
    dc _____ ; 12 <
    dc XXXXX ; 13
    dc _XXX_ ; 14
    dc _____ ; 15 <
    dc XXXXX ; 16
    dc _XXX_ ; 17
    dc _____ ; 18 <
    dc XXXXX ; 19
    dc _XXX_ ; 20
    dc _____ ; 21 <
    dc XXXXX ; 22
    dc __X__ ; 23
    dc _____ ; 24 <
    dc XX_XX ; 25
    dc __X__ ; 26
    dc _____ ; 27 <
    dc XX_XX ; 28
    dc __X__ ; 29



__CHAR_BOULDER_L

    dc XXXX_ ; 00 <
    dc XXXX_ ; 01
    dc _____ ; 02
    dc _____ ; 03 <
    dc XXXX_ ; 04
    dc _____ ; 05
    dc _____ ; 06 <
    dc XXXXX ; 07
    dc ____X ; 08
    dc ____X ; 09 <
    dc XXXXX ; 10
    dc __X__ ; 11
    dc _____ ; 12 <
    dc _XXXX ; 13
    dc XXXX_ ; 14
    dc _____ ; 15 <
    dc _XXXX ; 16
    dc XXXX_ ; 17
    dc _____ ; 18 <
    dc _XXXX ; 19
    dc XXXX_ ; 20
    dc ____X ; 21 <
    dc XXXXX ; 22
    dc __X__ ; 23
    dc ____X ; 24 <
    dc XXXXX ; 25
    dc _____ ; 26
    dc ___X_ ; 27 <
    dc XXXX_ ; 28
    dc _____ ; 29



__CHAR_BOULDER_UR

    dc _____ ; 00 <
    dc XX_XX ; 01
    dc __X__ ; 02
    dc _____ ; 03 <
    dc XX_XX ; 04
    dc __X__ ; 05
    dc _____ ; 06 <
    dc XX_XX ; 07
    dc __X__ ; 08
    dc _____ ; 09 <
    dc XXXXX ; 10
    dc __X__ ; 11
    dc _____ ; 12 <
    dc XXXX_ ; 13
    dc _XXXX ; 14
    dc _____ ; 15 <
    dc XXXX_ ; 16
    dc _XXXX ; 17
    dc _____ ; 18 <
    dc XXXX_ ; 19
    dc _XXXX ; 20
    dc _____ ; 21 <
    dc XXXXX ; 22
    dc __X__ ; 23
    dc _____ ; 24 <
    dc XXXXX ; 25
    dc _____ ; 26
    dc _____ ; 27 <
    dc _XXXX ; 28
    dc _____ ; 29



__CHAR_BOULDER_UD

    dc ____X ; 00 <
    dc XX_XX ; 01
    dc __X__ ; 02
    dc ____X ; 03 <
    dc XX_XX ; 04
    dc __X__ ; 05
    dc _____ ; 06 <
    dc XX_XX ; 07
    dc __X__ ; 08
    dc _____ ; 09 <
    dc XXXXX ; 10
    dc __X__ ; 11
    dc _____ ; 12 <
    dc XXXXX ; 13
    dc _XXX_ ; 14
    dc _____ ; 15 <
    dc XXXXX ; 16
    dc _XXX_ ; 17
    dc _____ ; 18 <
    dc XXXXX ; 19
    dc _XXX_ ; 20
    dc _____ ; 21 <
    dc XXXXX ; 22
    dc __X__ ; 23
    dc _____ ; 24 <
    dc XX_XX ; 25
    dc __X__ ; 26
    dc _____ ; 27 <
    dc XX_XX ; 28
    dc __X__ ; 29


__CHAR_BOULDER_UL

    dc _____ ; 00 <
    dc XX_XX ; 01
    dc __X__ ; 02
    dc _____ ; 03 <
    dc XX_XX ; 04
    dc __X__ ; 05
    dc _____ ; 06 <
    dc XX_XX ; 07
    dc __X__ ; 08
    dc _____ ; 09 <
    dc XXXXX ; 10
    dc __X__ ; 11
    dc _____ ; 12 <
    dc _XXXX ; 13
    dc XXXX_ ; 14
    dc _____ ; 15 <
    dc _XXXX ; 16
    dc XXXX_ ; 17
    dc _____ ; 18 <
    dc _XXXX ; 19
    dc XXXX_ ; 20
    dc _____ ; 21 <
    dc XXXXX ; 22
    dc __X__ ; 23
    dc ____X ; 24 <
    dc XXXXX ; 25
    dc _____ ; 26
    dc ___X_ ; 27 <
    dc XXXX_ ; 28
    dc _____ ; 29


__CHAR_BOULDER_RD

    dc __XXX ; 00 <
    dc __XXX ; 01
    dc _____ ; 02
    dc _____ ; 03 <
    dc _XXXX ; 04
    dc _____ ; 05
    dc _____ ; 06 <
    dc _XXXX ; 07
    dc _____ ; 08
    dc _____ ; 09 <
    dc XXXXX ; 10
    dc __X__ ; 11
    dc _____ ; 12 <
    dc XXXX_ ; 13
    dc _XXXX ; 14
    dc _____ ; 15 <
    dc XXXX_ ; 16
    dc _XXXX ; 17
    dc _____ ; 18 <
    dc XXXX_ ; 19
    dc _XXXX ; 20
    dc _____ ; 21 <
    dc XXXXX ; 22
    dc __X__ ; 23
    dc _____ ; 24 <
    dc XX_XX ; 25
    dc __X__ ; 26
    dc _____ ; 27 <
    dc XX_XX ; 28
    dc __X__ ; 29


__CHAR_BOULDER_RL

    dc XXXXX ; 00 <
    dc XXXXX ; 01
    dc _____ ; 02
    dc _____ ; 03 <
    dc XXXXX ; 04
    dc _____ ; 05
    dc _____ ; 06 <
    dc XXXXX ; 07
    dc _____ ; 08
    dc _____ ; 09 <
    dc XXXXX ; 10
    dc __X__ ; 11
    dc _____ ; 12 <
    dc _XXX_ ; 13
    dc XXXXX ; 14
    dc _____ ; 15 <
    dc _XXX_ ; 16
    dc XXXXX ; 17
    dc _____ ; 18 <
    dc _XXX_ ; 19
    dc XXXXX ; 20
    dc _____ ; 21 <
    dc XXXXX ; 22
    dc __X__ ; 23
    dc _____ ; 24 <
    dc XXXXX ; 25
    dc _____ ; 26
    dc _____ ; 27 <
    dc XXXXX ; 28
    dc _____ ; 29

__CHAR_BOULDER_DL

    dc XXXX_ ; 00 <
    dc XXXX_ ; 01
    dc _____ ; 02
    dc _____ ; 03 <
    dc XXXX_ ; 04
    dc _____ ; 05
    dc _____ ; 06 <
    dc XXXXX ; 07
    dc ____X ; 08
    dc ____X ; 09 <
    dc XXXXX ; 10
    dc __X__ ; 11
    dc _____ ; 12 <
    dc _XXXX ; 13
    dc XXXX_ ; 14
    dc _____ ; 15 <
    dc _XXXX ; 16
    dc XXXX_ ; 17
    dc _____ ; 18 <
    dc _XXXX ; 19
    dc XXXX_ ; 20
    dc _____ ; 21 <
    dc XXXXX ; 22
    dc __X__ ; 23
    dc _____ ; 24 <
    dc XX_XX ; 25
    dc __X__ ; 26
    dc _____ ; 27 <
    dc XX_XX ; 28
    dc __X__ ; 29


__CHAR_BOULDER_URD

    dc X____ ; 00 <
    dc XX_XX ; 01
    dc X_X__ ; 02
    dc X____ ; 03 <
    dc XX_XX ; 04
    dc X_X__ ; 05
    dc X____ ; 06 <
    dc XX_XX ; 07
    dc X_X__ ; 08
    dc X____ ; 09 <
    dc XXXXX ; 10
    dc __X__ ; 11
    dc _____ ; 12 <
    dc XXXX_ ; 13
    dc _XXXX ; 14
    dc _____ ; 15 <
    dc XXXX_ ; 16
    dc _XXXX ; 17
    dc _____ ; 18 <
    dc XXXX_ ; 19
    dc _XXXX ; 20
    dc _____ ; 21 <
    dc XXXXX ; 22
    dc __X__ ; 23
    dc _____ ; 24 <
    dc XX_XX ; 25
    dc __X__ ; 26
    dc _____ ; 27 <
    dc XX_XX ; 28
    dc __X__ ; 29


__CHAR_BOULDER_URL

    dc _____ ; 00 <
    dc XX_XX ; 01
    dc __X__ ; 02
    dc _____ ; 03 <
    dc XX_XX ; 04
    dc __X__ ; 05
    dc _____ ; 06 <
    dc XX_XX ; 07
    dc __X__ ; 08
    dc _____ ; 09 <
    dc XXXXX ; 10
    dc __X__ ; 11
    dc _____ ; 12 <
    dc _XXX_ ; 13
    dc XXXXX ; 14
    dc _____ ; 15 <
    dc _XXX_ ; 16
    dc XXXXX ; 17
    dc _____ ; 18 <
    dc _XXX_ ; 19
    dc XXXXX ; 20
    dc _____ ; 21 <
    dc XXXXX ; 22
    dc __X__ ; 23
    dc _____ ; 24 <
    dc XXXXX ; 25
    dc _____ ; 26
    dc _____ ; 27 <
    dc XXXXX ; 28
    dc _____ ; 29

__CHAR_BOULDER_UDL

    dc _____ ; 00 <
    dc XX_XX ; 01
    dc __X__ ; 02
    dc _____ ; 03 <
    dc XX_XX ; 04
    dc __X_X ; 05
    dc ____X ; 06 <
    dc XX_XX ; 07
    dc __X_X ; 08
    dc ____X ; 09 <
    dc XXXXX ; 10
    dc __X__ ; 11
    dc _____ ; 12 <
    dc _XXXX ; 13
    dc XXXX_ ; 14
    dc _____ ; 15 <
    dc _XXXX ; 16
    dc XXXX_ ; 17
    dc _____ ; 18 <
    dc _XXXX ; 19
    dc XXXX_ ; 20
    dc _____ ; 21 <
    dc XXXXX ; 22
    dc __X__ ; 23
    dc _____ ; 24 <
    dc XX_XX ; 25
    dc __X__ ; 26
    dc _____ ; 27 <
    dc XX_XX ; 28
    dc __X__ ; 29

__CHAR_BOULDER_RDL

    dc XXXXX ; 00 <
    dc XXXXX ; 01
    dc _____ ; 02
    dc _____ ; 03 <
    dc XXXXX ; 04
    dc _____ ; 05
    dc _____ ; 06 <
    dc XXXXX ; 07
    dc _____ ; 08
    dc _____ ; 09 <
    dc XXXXX ; 10
    dc __X__ ; 11
    dc _____ ; 12 <
    dc _XXX_ ; 13
    dc XXXXX ; 14
    dc _____ ; 15 <
    dc _XXX_ ; 16
    dc XXXXX ; 17
    dc _____ ; 18 <
    dc _XXX_ ; 19
    dc XXXXX ; 20
    dc _____ ; 21 <
    dc XXXXX ; 22
    dc __X__ ; 23
    dc _____ ; 24 <
    dc XX_XX ; 25
    dc __X__ ; 26
    dc _____ ; 27 <
    dc XX_XX ; 28
    dc __X__ ; 29

__CHAR_BOULDER_URDL

    dc _____ ; 00 <
    dc XX_XX ; 01
    dc __X__ ; 02
    dc _____ ; 03 <
    dc XX_XX ; 04
    dc __X__ ; 05
    dc _____ ; 06 <
    dc XX_XX ; 07
    dc __X__ ; 08
    dc _____ ; 09 <
    dc XXXXX ; 10
    dc __X__ ; 11
    dc _____ ; 12 <
    dc _XXX_ ; 13
    dc XX_XX ; 14
    dc _____ ; 15 <
    dc _XXX_ ; 16
    dc XX_XX ; 17
    dc _____ ; 18 <
    dc _XXX_ ; 19
    dc XX_XX ; 20
    dc _____ ; 21 <
    dc XXXXX ; 22
    dc __X__ ; 23
    dc _____ ; 24 <
    dc XX_XX ; 25
    dc __X__ ; 26
    dc _____ ; 27 <
    dc XX_XX ; 28
    dc __X__ ; 29

__CHAR_BOULDER_URDL2

    dc _____ ; 00 <
    dc XX_XX ; 01
    dc __X__ ; 02
    dc _____ ; 03 <
    dc XX_XX ; 04
    dc __X__ ; 05
    dc _____ ; 06 <
    dc XX_XX ; 07
    dc __X__ ; 08
    dc _____ ; 09 <
    dc XX_XX ; 10
    dc __X__ ; 11
    dc _____ ; 12 <
    dc _____ ; 13
    dc XXXXX ; 14
    dc _____ ; 15 <
    dc _____ ; 16
    dc XXXXX ; 17
    dc _____ ; 18 <
    dc _____ ; 19
    dc XXXXX ; 20
    dc _____ ; 21 <
    dc XX_XX ; 22
    dc __X__ ; 23
    dc _____ ; 24 <
    dc XX_XX ; 25
    dc __X__ ; 26
    dc _____ ; 27 <
    dc XX_XX ; 28
    dc __X__ ; 29

;        __XXX___,__XXX___,________,     
;        _XXXXX__,_XX_XX__,___X____,     
;        _XXXXX__,_X___X__,__XXX___,     
;        _XXXXX__,_X___X__,__XXX___,     
;        _XXXXX__,_X___X__,__XXX___,     
;        _XXXXX__,_X___X__,__XXX___,     
;        _XXXXX__,_X___X__,__XXX___,     
;        _XXXXX__,_XX_XX__,___X____,     
;        __XXX___,__XXX___,________,     
;    },

;    {  27,
;        ________,________,________,     
;        ________,________,________,     
;        ___X____,___X____,________,     
;        __XXX___,__XXX___,________,     
;        __X_X___,__XXX___,________,     
;        __X_X___,__XXX___,________,     
;        __XXX___,__XXX___,________,     
;        ___X____,___X____,________,     
;        ________,________,________,     
;    },




__CHAR_FIREFLY

;     dc XX | YY | _XX_ ; 00 <
;     dc XX | YY | _XX_ ; 01
;     dc XX | YY | ____ ; 02
;     dc XX | __ | XXXX ; 03 <
;     dc XX | __ | XXXX ; 04
;     dc XX | YY | _XX_ ; 05
;     dc __ | __ | X__X ; 06 <
;     dc __ | __ | X__X ; 07
;     dc __ | YY | _XX_ ; 08
;     dc      __ | X__X ; 09 <
;     dc      YY | X__X ; 10
;     dc      YY | _XX_ ; 11
;     dc      __ | X__X ; 12 <
;     dc      __ | X__X ; 13
;     dc      __ | _XX_ ; 14
;     dc           XXXX ; 15 <
;     dc           XXXX ; 16
;     dc           _XX_ ; 17
;     dc           _XX_ ; 18 <
;     dc           _XX_ ; 19
 ;   dc           ____ ; 20


__CHAR_FIREFLY2

;     dc __ | YY | ____ ; 00 <
;     dc XX | YY | ____ ; 01
;     dc __ | YY | ____ ; 02
;     dc __ | __ | _XX_ ; 03 <
;     dc XX | __ | _XX_ ; 04
;     dc __ | YY | _XX_ ; 05
;     dc __ | __ | X__X ; 06 <
;     dc __ | __ | X__X ; 07
;     dc __ | YY | XXXX ; 08
;     dc      __ | X__X ; 09 <
;     dc      YY | X__X ; 10
;     dc      YY | XXXX ; 11
;     dc      __ | X__X ; 12 <
;     dc      __ | X__X ; 13
;     dc      __ | XXXX ; 14
;     dc           _XX_ ; 15 <
;     dc           _XX_ ; 16
;     dc           _XX_ ; 17
;    dc           ____ ; 18 <
;    dc           ____ ; 19
;    dc           ____ ; 20


__CHAR_FIREFLY3

;     dc __ | YY | ____ ; 00 <
;     dc __ | YY | ____ ; 01
;     dc __ | YY | ____ ; 02
;     dc __ | YY | ____ ; 03 <
;     dc __ | YY | ____ ; 04
;     dc __ | YY | ____ ; 05
;     dc __ | YY | _XX_ ; 06 <
;     dc __ | YY | _XX_ ; 07
;     dc __ | YY | _XX_ ; 08
;     dc      YY | _XX_ ; 09 <
;     dc      YY | _XX_ ; 10
;     dc      YY | _XX_ ; 11
;     dc      __ | _XX_ ; 12 <
;     dc      __ | _XX_ ; 13
;     dc      __ | _XX_ ; 14
;     dc           ____ ; 15 <
;     dc           ____ ; 16
;    dc           ____ ; 17
;    dc           ____ ; 18 <
;    dc           ____ ; 19
;    dc           ____ ; 20


;CHARSET_END

;CHARSET_START
CHAR_BLOCK2_START



__CHAR_SPARKLE_0

;     dc X_ | __ | ____ ; 00 <
;     dc X_ | __ | ____ ; 01
;     dc __ | __ | ____ ; 02
;     dc _X | Y_ | ____ ; 03 <
;     dc _X | Y_ | X___ ; 04
;     dc __ | __ | X___ ; 05
;     dc __ | __ | X___ ; 06 <
;     dc __ | __ | X___ ; 07
;     dc __ | __ | ____ ; 08
;     dc      __ | ____ ; 09 <
;     dc      __ | ____ ; 10
;     dc      __ | ____ ; 11
;     dc      __ | ____ ; 12 <
;     dc      __ | ____ ; 13
;    dc      __ | ____ ; 14
;    dc           ____ ; 15 <
;    dc           ____ ; 16
;    dc           ____ ; 17
;    dc           ____ ; 18 <
;    dc           ____ ; 19
;    dc           ____ ; 20


__CHAR_SPARKLE_1

;     dc __ | __ | ____ ; 00 <
;     dc __ | __ | ____ ; 01
;     dc __ | __ | ____ ; 02
;     dc X_ | __ | ____ ; 03 <
;     dc X_ | __ | ____ ; 04
;     dc __ | __ | ____ ; 05
;     dc _X | __ | ____ ; 06 <
;     dc _X | __ | ___X ; 07
;     dc __ | __ | ___X ; 08
;     dc      _Y | ___X ; 09 <
;     dc      _Y | ___X ; 10
;    dc      __ | ____ ; 11
;    dc      __ | ____ ; 12 <
;    dc      __ | ____ ; 13
;    dc      __ | ____ ; 14
;    dc           ____ ; 15 <
;    dc           ____ ; 16
;    dc           ____ ; 17
;    dc           ____ ; 18 <
;    dc           ____ ; 19
;    dc           ____ ; 20


__CHAR_SPARKLE_2

    dc _X | __ | ____ ; 00 <
    dc _X | __ | ____ ; 01
    dc __ | __ | ____ ; 02
    dc __ | __ | ____ ; 03 <
    dc __ | __ | ____ ; 04
    dc __ | __ | ____ ; 05
    dc X_ | __ | ____ ; 06 <
    dc X_ | __ | ____ ; 07
    dc __ | __ | ____ ; 08
    dc      __ | ____ ; 09 <
    dc      __ | ____ ; 10
    dc      __ | ____ ; 11
    dc      Y_ | ____ ; 12 <
    dc      Y_ | _X__ ; 13
    dc      __ | _X__ ; 14
    dc           _X__ ; 15 <
    dc           _X__ ; 16
;    dc           ____ ; 17
;    dc           ____ ; 18 <
;    dc           ____ ; 19
;    dc           ____ ; 20


__CHAR_SPARKLE_3

    dc __ | _Y | ____ ; 00 <
    dc __ | _Y | ____ ; 01
    dc __ | __ | ____ ; 02
    dc __ | __ | ____ ; 03 <
    dc __ | __ | ____ ; 04
    dc __ | __ | ____ ; 05
    dc __ | __ | ____ ; 06 <
    dc __ | __ | ____ ; 07
    dc __ | __ | ____ ; 08
    dc      __ | ____ ; 09 <
    dc      __ | ____ ; 10
    dc      __ | ____ ; 11
    dc      __ | ____ ; 12 <
    dc      __ | ____ ; 13
    dc      __ | ____ ; 14
    dc           ____ ; 15 <
    dc           __X_ ; 16
    dc           __X_ ; 17
    dc           __X_ ; 18 <
    dc           __X_ ; 19
;    dc           ____ ; 20




__CHAR_PEBBLE2

     dc XXXXX ; 00 <
     dc _____ ; 01
     dc _____ ; 02
     dc XXXXX ; 03 <
     dc _____ ; 04
     dc _____ ; 05
     dc XXXXX ; 06 <
     dc _____ ; 07
     dc _____ ; 08
     dc XXXXX ; 09 <
     dc _____ ; 10
     dc _____ ; 11
     dc XXXXX ; 12 <
     dc _____ ; 13
     dc _____ ; 14
     dc XXXXX ; 15 <
     dc _____ ; 16
     dc _X___ ; 17
     dc XXXXX ; 18 <
     dc _X___ ; 19
     dc _____ ; 20
     dc XXXXX ; 21 <
     dc _____ ; 22
     dc _____ ; 23
     dc XXXXX ; 24 <
     dc _____ ; 25
     dc _____ ; 26
     dc XXXXX ; 27 <
     dc _____ ; 28
     dc _____ ; 29


__CHAR_BUTTERFLY_0

;     dc __ | __ | XX__ ; 00 <
;     dc _X | _Y | XX_X ; 01
;     dc _X | Y_ | ___X ; 02
;     dc X_ | Y_ | XX__ ; 03 <
;     dc XX | _Y | XX_X ; 04
;     dc XX | Y_ | ___X ; 05
;     dc _X | __ | XXX_ ; 06 <
;     dc __ | __ | XXXX ; 07
;     dc _X | YY | __XX ; 08
;     dc      Y_ | __X_ ; 09 <
;     dc      _Y | _XX_ ; 10
;     dc      Y_ | _XX_ ; 11
;     dc      Y_ | _XXX ; 12 <
;     dc      _Y | XX__ ; 13
;     dc      __ | XXXX ; 14
;     dc           __XX ; 15 <
;     dc           X___ ; 16
;     dc           X_XX ; 17
;     dc           __XX ; 18 <
;     dc           ____ ; 19
;     dc           ____ ; 20




__CHAR_BUTTERFLY_2

;     dc __ | __ | __X_ ; 00 <
;     dc X_ | __ | __X_ ; 01
;     dc X_ | __ | ____ ; 02
;     dc _X | __ | __X_ ; 03 <
;     dc XX | __ | __X_ ; 04
;     dc XX | __ | ____ ; 05
;     dc X_ | __ | __X_ ; 06 <
;     dc __ | Y_ | __X_ ; 07
;     dc X_ | _Y | __X_ ; 08
;     dc      __ | __X_ ; 09 <
;     dc      __ | _XX_ ; 10
;     dc      __ | _XX_ ; 11
;     dc      __ | _X__ ; 12 <
;     dc      __ | _X__ ; 13
;     dc      __ | _X__ ; 14
;     dc           _X__ ; 15 <
;     dc           ____ ; 16
;     dc           _X__ ; 17
;     dc           _X__ ; 18 <
;    dc           ____ ; 19
;    dc           ____ ; 20



    ;  dc __ | __ | ____ ; 00 <
    ;  dc __ | __ | ____ ; 01
    ;  dc __ | __ | ____ ; 02
    ;  dc _X | __ | _XX_ ; 03 <
    ;  dc XX | YY | _XX_ ; 04
    ;  dc X_ | YY | __X_ ; 05
    ;  dc __ | __ | __X_ ; 06 <
    ;  dc XX | YY | XX_X ; 07
    ;  dc __ | _Y | ___X ; 08
    ;  dc      __ | ___X ; 09 <
    ;  dc      YY | XXXX ; 10
    ;  dc      __ | ___X ; 11
    ;  dc      __ | ___X ; 12 <
    ;  dc      YY | XXXX ; 13
    ;  dc      __ | ____ ; 14
    ;  dc           ___X ; 15 <
    ;  dc           XXXX ; 16
    ;  dc           ____ ; 17
    ;  dc           __XX ; 18 <
    ;  dc           _XX_ ; 19
;     dc           ____ ; 20


__CHAR_STEELWALL

     dc XXXXX ; 00 <
     dc _____ ; 01
     dc XXXXX ; 02
     dc XXXXX ; 03 <
     dc X_X_X ; 04
     dc XXXXX ; 05
     dc XXXXX ; 06 <
     dc _____ ; 07
     dc _X_X_ ; 08
     dc XXXXX ; 09 <
     dc _____ ; 10
     dc XXXXX ; 11
     dc XXXXX ; 12 <
     dc XX_X_ ; 13
     dc XXXXX ; 14
     dc XXXXX ; 15 <
     dc _____ ; 16
     dc __X_X ; 17
     dc XXXXX ; 18 <
     dc _____ ; 19
     dc XXXXX ; 20
     dc XXXXX ; 21 <
     dc X_X_X ; 22
     dc XXXXX ; 23
     dc XXXXX ; 24 <
     dc _____ ; 25
     dc _X_X_ ; 26
     dc XXXXX ; 27 <
     dc _____ ; 28
     dc XXXXX ; 29



__CHAR_DIRT

    dc XXXXX ; 00 <
    dc _____ ; 01
    dc _____ ; 02
    dc XXXXX ; 03 <
    dc _____ ; 04
    dc _____ ; 05
    dc XXXXX ; 06 <
    dc _____ ; 07
    dc _____ ; 08
    dc XXXXX ; 09 <
    dc _____ ; 10
    dc _____ ; 11
    dc XXXXX ; 12 <
    dc _____ ; 13
    dc _____ ; 14
    dc XXXXX ; 15 <
    dc _____ ; 16
    dc _____ ; 17
    dc XXXXX ; 18 <
    dc _____ ; 19
    dc _____ ; 20
    dc XXXXX ; 21 <
    dc _____ ; 22
    dc _____ ; 23
    dc XXXXX ; 24 <
    dc _____ ; 25
    dc _____ ; 26
    dc XXXXX ; 27 <
    dc _____ ; 28
    dc _____ ; 29


__CHAR_BUTTERFLY_1

;     dc __ | __ | _XX_ ; 00 < 
;     dc XX | __ | _XX_ ; 01 
;     dc _X | __ | ____ ; 02 
;     dc XX | Y_ | _XX_ ; 03 < 
;     dc XX | _Y | _XX_ ; 04 
;     dc _X | Y_ | ____ ; 05 
;     dc XX | Y_ | _XX_ ; 06 < 
;     dc __ | _Y | _XX_ ; 07 
;     dc XX | Y_ | __X_ ; 08 
;     dc      __ | __X_ ; 09 < 
;     dc      _Y | _XX_ ; 10 
;     dc      __ | _XX_ ; 11 
;     dc      __ | _XX_ ; 12 < 
;     dc      __ | _X__ ; 13 
;     dc      __ | _XX_ ; 14 
;     dc           _XX_ ; 15 < 
;     dc           ____ ; 16 
;     dc           _XX_ ; 17 
;     dc           _XX_ ; 18 < 
;     dc           ____ ; 19 
;    dc           ____ ; 20 



__CHAR_BRICKWALL

    ;  dc X_ | _Y | ____ ; 00 <
    ;  dc X_ | _Y | XXX_ ; 01
    ;  dc XX | YY | XXXX ; 02
    ;  dc _X | Y_ | XXX_ ; 03 <
    ;  dc _X | Y_ | XXX_ ; 04
    ;  dc XX | YY | XXXX ; 05
    ;  dc X_ | __ | XXX_ ; 06 <
    ;  dc X_ | _Y | XXX_ ; 07
    ;  dc XX | YY | XXXX ; 08
    ;  dc      _Y | XXX_ ; 09 <
    ;  dc      _Y | ____ ; 10
    ;  dc      YY | XXXX ; 11
    ;  dc      Y_ | X_XX ; 12 <
    ;  dc      Y_ | X_XX ; 13
    ;  dc      YY | XXXX ; 14
    ;  dc           X_XX ; 15 <
    ;  dc           X_XX ; 16
    ;  dc           XXXX ; 17
    ;  dc           X_XX ; 18 <
    ;  dc           X_XX ; 19
    ;  dc           XXXX ; 20

    ;  dc           X_XX ; 18 <
    ;  dc           X_XX ; 19
    ;  dc           XXXX ; 20










__CHAR_EXPLODETO_0

     dc __ | _Y | __X_ ; 00 <
     dc XX | _Y | X_X_ ; 01
     dc __ | _Y | X_X_ ; 02
     dc XX | __ | X___ ; 03 <
     dc XX | Y_ | ____ ; 04
     dc __ | Y_ | ____ ; 05
     dc XX | YY | __X_ ; 06 <
     dc __ | _Y | __X_ ; 07
     dc __ | YY | __X_ ; 08
     dc      Y_ | ____ ; 09 <
     dc      Y_ | __X_ ; 10
     dc      __ | X_X_ ; 11
     dc      __ | X_X_ ; 12 <
     dc      __ | X___ ; 13
     dc      __ | ___X ; 14
     dc           ___X ; 15 <
     dc           _X_X ; 16
     dc           _X__ ; 17
     dc           _X_X ; 18 <
     dc           ___X ; 19
     dc           ___X ; 20





__CHAR_EXPLODETO_1

     dc XX | __ | ____ ; 00 <
     dc __ | Y_ | _X__ ; 01
     dc __ | Y_ | _X__ ; 02
     dc __ | Y_ | _X_X ; 03 <
     dc XX | _Y | ___X ; 04
     dc XX | _Y | ___X ; 05
     dc __ | _Y | __X_ ; 06 <
     dc XX | __ | X_X_ ; 07
     dc __ | __ | X_X_ ; 08
     dc      _Y | X___ ; 09 <
     dc      _Y | ____ ; 10
     dc      _Y | ____ ; 11
     dc      __ | __X_ ; 12 <
     dc      __ | __X_ ; 13
     dc      __ | __X_ ; 14
     dc           ____ ; 15 <
     dc           __X_ ; 16
     dc           X_X_ ; 17
     dc           X_X_ ; 18 <
     dc           X___ ; 19
;     dc           ____ ; 20




__CHAR_EXPLODETO_3

     dc XX | _Y | ____ ; 00 <
     dc XX | _Y | X___ ; 01
     dc XX | _Y | X___ ; 02
     dc __ | __ | X___ ; 03 <
     dc XX | __ | ____ ; 04
     dc __ | __ | ____ ; 05
     dc XX | _Y | __X_ ; 06 <
     dc XX | _Y | __X_ ; 07
     dc __ | _Y | __X_ ; 08
     dc      __ | ____ ; 09 <
     dc      __ | __X_ ; 10
     dc      __ | __X_ ; 11
     dc      __ | __X_ ; 12 <
     dc      __ | ____ ; 13
     dc      __ | ___X ; 14
     dc           ___X ; 15 <
     dc           _X_X ; 16
     dc           _X__ ; 17
     dc           _X__ ; 18 <
;     dc           ____ ; 19
;     dc           ____ ; 20




__CHAR_EXPLODETO_4

     dc __ | __ | ____ ; 00 <
     dc __ | __ | ____ ; 01
     dc __ | __ | ____ ; 02
     dc XX | __ | ____ ; 03 <
     dc XX | __ | __X_ ; 04
     dc __ | _Y | __X_ ; 05
     dc __ | _Y | __X_ ; 06 <
     dc XX | _Y | ____ ; 07
     dc __ | __ | ____ ; 08
     dc      __ | ____ ; 09 <
     dc      __ | __X_ ; 10
     dc      __ | X_X_ ; 11
     dc      __ | X_X_ ; 12 <
     dc      __ | X___ ; 13
     dc      __ | ____ ; 14
     dc           ____ ; 15 <
     dc           ____ ; 16
     dc           ____ ; 17
     dc           ___X ; 18 <
     dc           ___X ; 19
     dc           ___X ; 20




__CHAR_EXPLODETO_2

     dc XX | __ | __X_ ; 00 <
     dc XX | __ | __X_ ; 01
     dc __ | _Y | __X_ ; 02
     dc XX | _Y | ____ ; 03 <
     dc __ | _Y | __X_ ; 04
     dc XX | Y_ | X_X_ ; 05
     dc XX | Y_ | X_X_ ; 06 <
     dc XX | Y_ | X___ ; 07
     dc __ | __ | ____ ; 08
     dc      Y_ | ____ ; 09 <
     dc      Y_ | __X_ ; 10
     dc      Y_ | X_X_ ; 11
     dc      __ | X_X_ ; 12 <
     dc      __ | X___ ; 13
     dc      __ | ___X ; 14
     dc           ___X ; 15 <
     dc           _X_X ; 16
     dc           _X__ ; 17
     dc           _X_X ; 18 <
     dc           ___X ; 19
     dc           ___X ; 20





; __CHAR_DIRT_GRABBED

;      dc XX | __ | ____ ; 00 <
;      dc __ | __ | ____ ; 01
;      dc __ | __ | ____ ; 02
;      dc XX | _Y | _XX_ ; 03 <
;      dc __ | __ | ____ ; 04
;      dc __ | __ | ____ ; 05
;      dc XX | __ | __X_ ; 06 <
;      dc __ | __ | ____ ; 07
;      dc __ | __ | ____ ; 08
;      dc      Y_ | _XX_ ; 09 <
;      dc      __ | ____ ; 10
;      dc      __ | ____ ; 11
;      dc      __ | _XX_ ; 12 <
;      dc      __ | ____ ; 13
;      dc      __ | ____ ; 14
;      dc           _X__ ; 15 <
;      dc           ____ ; 16
;      dc           ____ ; 17
;      dc           ____ ; 18 <
;      dc           ____ ; 19
;      dc           ____ ; 20



__CHAR_DUST_ROCK_0
 dc 0
__CHAR_DUST_0

     dc _____ ; 24 <
     dc _____ ; 25
     dc _____ ; 26
     dc _____ ; 27 <
     dc _____ ; 28
     dc _____ ; 29
     dc _X___ ; 00 <
     dc _____ ; 01
     dc _____ ; 02
     dc XXX__ ; 03 <
     dc _____ ; 04
     dc _____ ; 05
     dc _X___ ; 06 <
     dc _____ ; 07
     dc _____ ; 08
     dc _____ ; 09 <
     dc _____ ; 10
     dc _____ ; 11
     dc __X__ ; 12 <
     dc _____ ; 13
     dc _____ ; 14
     dc _XXX_ ; 15 <
     dc _____ ; 16
     dc _____ ; 17
     dc __X__ ; 18 <
     dc _____ ; 19
     dc _____ ; 20
     dc _____ ; 21 <
     dc _____ ; 22
     dc _____ ; 23

__CHAR_DUST_ROCK_1
 dc 0
__CHAR_DUST_1


     dc _____ ; 27
     dc _____ ; 28
     dc _____ ; 29
     dc _____ ; 27
     dc _____ ; 28
     dc _____ ; 29
     dc _____ ; 00 <
     dc _____ ; 01
     dc _____ ; 02
     dc _X___ ; 03 <
     dc _____ ; 04
     dc _____ ; 05
     dc __X__ ; 06 <
     dc _____ ; 07
     dc _____ ; 08
     dc _XXX_ ; 09 <
     dc _____ ; 10
     dc _____ ; 11
     dc __X__ ; 12 <
     dc _____ ; 13
     dc _____ ; 14
     dc _____ ; 15 <
     dc _____ ; 16
     dc _____ ; 17
     dc __X__ ; 18 <
     dc _____ ; 19
     dc _____ ; 20
     dc _____ ; 21
     dc _____ ; 22
     dc _____ ; 23



__CHAR_DUST_ROCK_2
 dc 0

__CHAR_DUST_2



     dc _____ ; 24
     dc _____ ; 25 <
     dc _____ ; 26
     dc _____ ; 27
     dc _____ ; 28 <
     dc _____ ; 29
     dc _____ ; 00 <
     dc _____ ; 01
     dc _____ ; 02
     dc _____ ; 03 <
     dc _____ ; 04
     dc _____ ; 05
     dc _____ ; 06 <
     dc _____ ; 07
     dc _____ ; 08
     dc __X__ ; 09 <
     dc _____ ; 10
     dc _____ ; 11
     dc _____ ; 12 <
     dc _____ ; 13
     dc _____ ; 14
     dc _____ ; 15 <
     dc _____ ; 16
     dc _____ ; 17
     dc _____ ; 18 <
     dc _____ ; 19
     dc _____ ; 20
     dc _____ ; 21
     dc _____ ; 22 <
     dc _____ ; 23

 
;     dc           ____ ; 20

__CHAR_PARALLAX_TEMPLATE        ; squished in here - careful about count above/below chars

    ;  dc   %00000000 ;,  // 00
    ;  dc   %00010001 ;, // 01
    ;  dc   %00000000 ;, // 02
    ;  dc   %00000000 ;, // 03
    ;  dc   %00100010 ;, // 04
    ;  dc   %00000000 ;, // 05
    ;  dc   %00000000 ;, // 06
    ;  dc   %00000000 ;, // 07
    ;  dc   %00000000 ;, // 08
    ;  dc   %00000000 ;, // 09
    ;  dc   %10001000 ;, // 10
    ;  dc   %00000000 ;, // 11
    ;  dc   %00000000 ;, // 12
    ;  dc   %00000000 ;, // 13
    ;  dc   %00000000 ;, // 14
    ;  dc   %00000000 ;, // 15
    ;  dc   %01000100 ;, // 16
;        ________, // 17
;        ________, // 18
;        ________, // 19
;        ________, // 20


__CHAR_DUST_RIGHT_1
     dc _____ ; 00 <
     dc _____ ; 01
     dc _____ ; 02
     dc _____ ; 03 <
     dc _____ ; 04
     dc _____ ; 05
     dc _____ ; 06 <
     dc _____ ; 07
     dc _____ ; 08
     dc _____ ; 09 <
     dc _____ ; 10
     dc _____ ; 11
     dc _____ ; 12 <
     dc __X__ ; 13
     dc _____ ; 14
     dc _____ ; 15 <
     dc _X___ ; 16
     dc _____ ; 17
     dc _____ ; 18 <
     dc __X__ ; 19
     dc _____ ; 20
     dc _____ ; 21
     dc _____ ; 22 <
     dc _____ ; 23
     dc _____ ; 24
     dc _____ ; 25 <
     dc _____ ; 26
     dc _____ ; 27
     dc _____ ; 28 <
     dc _____ ; 29



__CHAR_DUST_LEFT_1

     dc ____ ; 00 <
     dc ____ ; 01
     dc ____ ; 02
     dc ____ ; 03 <
     dc ____ ; 04
     dc ____ ; 05
     dc ____ ; 06 <
     dc ____ ; 07
     dc ____ ; 08
     dc ____ ; 09 <
     dc ____ ; 10
     dc ____ ; 11
     dc ____ ; 12 <
     dc __X_ ; 13
     dc ____ ; 14
     dc ____ ; 15 <
     dc ___X ; 16
     dc ____ ; 17
     dc ____ ; 18 <
     dc __X_ ; 19
     dc ____ ; 20 <
     dc ____ ; 21
     dc ____ ; 22
     dc ____ ; 23 <
     dc ____ ; 24
     dc ____ ; 25
     dc ____ ; 26 <
     dc ____ ; 27
     dc ____ ; 28
     dc ____ ; 29 <




__CHAR_MAGICWALL_2

     ; dc __ | _Y | ____ ; 00 <
     ; dc X_ | _Y | X_XX ; 01
     ; dc XX | YY | XXXX ; 02
     ; dc XX | __ | X_XX ; 03 <
     ; dc X_ | Y_ | X_XX ; 04
     ; dc XX | YY | XXXX ; 05
     ; dc XX | Y_ | X_XX ; 06 <
     ; dc X_ | Y_ | X_XX ; 07
     ; dc __ | YY | XXXX ; 08
     ; dc      _Y | X_XX ; 09 <
     ; dc      _Y | ____ ; 10
     ; dc      YY | XXXX ; 11
     ; dc      Y_ | XXX_ ; 12 <
     ; dc      Y_ | XXX_ ; 13
     ; dc      YY | XXXX ; 14
     ; dc           XXX_ ; 15 <
     ; dc           XXX_ ; 16
     ; dc           XXXX ; 17
     ; dc           XXX_ ; 18 <
     ; dc           XXX_ ; 19
     ; dc           XXXX ; 20


__CHAR_DOGE_00 ; doged

     dc _____ ; 00 <
     dc _____ ; 01
     dc _____ ; 02
     dc _____ ; 03 <
     dc _____ ; 04
     dc _____ ; 05
     dc _____ ; 06 <
     dc _____ ; 07
     dc __X__ ; 08
     dc _____ ; 09 <
     dc __XX_ ; 10
     dc _XXX_ ; 11
     dc _____ ; 12 <
     dc __XX_ ; 13
     dc _XXX_ ; 14
     dc _____ ; 15 <
     dc _XXX_ ; 16
     dc _XXX_ ; 17
     dc _____ ; 18 <
     dc __X__ ; 19
     dc __X__ ; 20
     ; dc _____ ; 21 <
     ; dc _____ ; 22
     ; dc _____ ; 23
     ; dc _____ ; 24 <
     ; dc _____ ; 25
     ; dc _____ ; 26
     ; dc _____ ; 27 <
     ; dc _____ ; 28
     ; dc _____ ; 29

__CHAR_DOGE_01 ; doged

     dc _____ ; 00 <
     dc _____ ; 01
     dc _____ ; 02
     dc _____ ; 03 <
     dc _____ ; 04
     dc _____ ; 05
     dc _____ ; 06 <
     dc _____ ; 07
     dc _____ ; 08
     dc _____ ; 09 <
     dc __X__ ; 10
     dc __X__ ; 11
     dc _____ ; 12 <
     dc _XXX_ ; 13
     dc _XXX_ ; 14
     dc _____ ; 15 <
     dc __X__ ; 16
     dc __X__ ; 17
     ; dc _____ ; 18 <
     ; dc _____ ; 19
     ; dc _____ ; 20
     ; dc _____ ; 21 <
     ; dc _____ ; 22
     ; dc _____ ; 23
     ; dc _____ ; 24 <
     ; dc _____ ; 25
     ; dc _____ ; 26
     ; dc _____ ; 27 <
     ; dc _____ ; 28
     ; dc _____ ; 29

__CHAR_DOGE_02 ;doged

     dc _____ ; 00 <
     dc _____ ; 01
     dc _____ ; 02
     dc _____ ; 03 <
     dc _____ ; 04
     dc _____ ; 05
     dc _____ ; 06 <
     dc _____ ; 07
     dc _____ ; 08
     dc _____ ; 09 <
     dc _____ ; 10
     dc _____ ; 11
     dc _____ ; 12 <
     dc _XXX_ ; 13
     dc _XXX_ ; 14
     dc _____ ; 15 <
     dc _____ ; 16
     dc _____ ; 17
     ; dc _____ ; 18 <
     ; dc _____ ; 19
     ; dc _____ ; 20
     ; dc _____ ; 21 <
     ; dc _____ ; 22
     ; dc _____ ; 23
     ; dc _____ ; 24 <
     ; dc _____ ; 25
     ; dc _____ ; 26
     ; dc _____ ; 27 <
     ; dc _____ ; 28
     ; dc _____ ; 29

__CHAR_DOGE_03 ; doged

     dc _____ ; 00 <
     dc _____ ; 01
     dc _____ ; 02
     dc _____ ; 03 <
     dc _____ ; 04
     dc _____ ; 05
     dc _____ ; 06 <
     dc _____ ; 07
     dc _____ ; 08
     dc _____ ; 09 <
     dc _____ ; 10
     dc _____ ; 11
     dc _XXX_ ; 12 <
     dc _XXX_ ; 13
     dc _XXX_ ; 14
     dc _XXX_ ; 15 <
     dc _____ ; 16
     dc _____ ; 17
     dc _____ ; 18 <
     dc _____ ; 19
     dc _____ ; 20
     ; dc _____ ; 21 <
     ; dc _____ ; 22
     ; dc _____ ; 23
     ; dc _____ ; 24 <
     ; dc _____ ; 25
     ; dc _____ ; 26
     ; dc _____ ; 27 <
     ; dc _____ ; 28
     ; dc _____ ; 29

__CHAR_DOGE_04 ; doged

     dc _____ ; 00 <
     dc _____ ; 01
     dc _____ ; 02
     dc _____ ; 03 <
     dc _____ ; 04
     dc _____ ; 05
     dc _____ ; 06 <
     dc _____ ; 07
     dc _____ ; 08
     dc __X__ ; 09 <
     dc __X__ ; 10
     dc __X__ ; 11
     dc _XXX_ ; 12 <
     dc _XXX_ ; 13
     dc _XXX_ ; 14
     dc _XXX_ ; 15 <
     dc __X__ ; 16
     dc __X__ ; 17
     dc __X__ ; 18 <
     dc _____ ; 19
     dc _____ ; 20
     dc _____ ; 21 <
     dc _____ ; 22
     dc _____ ; 23
     ; dc _____ ; 24 <
     ; dc _____ ; 25
     ; dc _____ ; 26
     ; dc _____ ; 27 <
     ; dc _____ ; 28
     ; dc _____ ; 29

__CHAR_DOGE_05

     dc _____ ; 00 <
     dc _____ ; 01
     dc _____ ; 02
     dc _____ ; 03 <
     dc _____ ; 04
     dc _____ ; 05
     dc __X__ ; 06 <
     dc __X__ ; 07
     dc __X__ ; 08
     dc _XXX_ ; 09 <
     dc _XXX_ ; 10
     dc _XXX_ ; 11
     dc _XXX_ ; 12 <
     dc _XXX_ ; 13
     dc _XXX_ ; 14
     dc _XXX_ ; 15 <
     dc _XXX_ ; 16
     dc _XXX_ ; 17
     dc _XXX_ ; 18 <
     dc __X__ ; 19
     dc __X__ ; 20
     dc __X__ ; 21 <
     dc _____ ; 22
     dc _____ ; 23
     dc _____ ; 24 <
     dc _____ ; 25
     dc _____ ; 26
     dc _____ ; 27 <
     dc _____ ; 28
     dc _____ ; 29


__CHAR_DOGE_FALLING ;

     dc ____X ; 00 <
     dc ____X ; 01
     dc ____X ; 02
     dc _____ ; 03 <
     dc _____ ; 04
     dc _____ ; 05
     dc ___X_ ; 06 <
     dc ___XX ; 07
     dc ___XX ; 08
     dc __X__ ; 09 <
     dc __XXX ; 10
     dc __XXX ; 11
     dc _____ ; 12 <
     dc __XXX ; 13
     dc __XXX ; 14
     dc _____ ; 15 <
     dc ___XX ; 16
     dc ___XX ; 17
     dc _____ ; 18 <
     dc ____X ; 19
     dc ____X ; 20
     dc _____ ; 21 <
     dc _____ ; 22
     dc _____ ; 23
     dc _____ ; 24 <
     dc _____ ; 25
     dc _____ ; 26
     dc _____ ; 27 <
     dc _____ ; 28
     dc _____ ; 29


__CHAR_AMOEBA_1

     ; dc __ | __ | ____ ; 00 <
     ; dc __ | __ | ____ ; 01
     ; dc XX | YY | ____ ; 02
     ; dc _X | __ | ____ ; 03 <
     ; dc __ | __ | XXX_ ; 04
     ; dc XX | YY | XXXX ; 05
     ; dc __ | __ | ____ ; 06 <
     ; dc X_ | __ | _X__ ; 07
     ; dc XX | YY | XXXX ; 08
     ; dc      _Y | ____ ; 09 <
     ; dc      __ | ____ ; 10
     ; dc      YY | XXXX ; 11
     ; dc      _Y | ____ ; 12 <
     ; dc      __ | ____ ; 13
     ; dc      YY | XXXX ; 14
     ; dc           ___X ; 15 <
     ; dc           ____ ; 16
     ; dc           XXXX ; 17
     ; dc           ____ ; 18 <
     ; dc           ____ ; 19
     ; dc           ____ ; 20


__CHAR_PEBBLE1

     dc XXXXX ; 00 <
     dc _____ ; 01
     dc _____ ; 02
     dc XXXXX ; 03 <
     dc _____ ; 04
     dc ___X_ ; 05
     dc XXXXX ; 06 <
     dc ___X_ ; 07
     dc _____ ; 08
     dc XXXXX ; 09 <
     dc _____ ; 10
     dc _____ ; 11
     dc XXXXX ; 12 <
     dc _____ ; 13
     dc _____ ; 14
     dc XXXXX ; 15 <
     dc _____ ; 16
     dc _____ ; 17
     dc XXXXX ; 18 <
     dc _____ ; 19
     dc _____ ; 20
     dc XXXXX ; 21 <
     dc _____ ; 22
     dc _____ ; 23
     dc XXXXX ; 24 <
     dc _____ ; 25
     dc _____ ; 26
     dc XXXXX ; 27 <
     dc _____ ; 28
     dc _____ ; 29

; actually worm horiz body
__CHAR_AMOEBA_0

     dc ___XX ; 00 <
     dc _____ ; 01
     dc ___XX ; 02
     dc XXXXX ; 03 <
     dc _____ ; 04
     dc XXXXX ; 05
     dc XXXXX ; 06 <
     dc _____ ; 07
     dc XXXXX ; 08
     dc XX_XX ; 09 <
     dc __X__ ; 10
     dc XXXXX ; 11
     dc XX_XX ; 12 <
     dc _XXX_ ; 13
     dc XXXXX ; 14
     dc XX_XX ; 15 <
     dc _XXX_ ; 16
     dc XXXXX ; 17
     dc XX_XX ; 18 <
     dc __X__ ; 19
     dc XXXXX ; 20
     dc XXXXX ; 21 <
     dc _____ ; 22
     dc XXXXX ; 23
     dc XXX__ ; 24 <
     dc _____ ; 25
     dc XXX__ ; 26
     dc _____ ; 27 <
     dc _____ ; 28
     dc _____ ; 29


__CHAR_AMOEBA_2

     dc _XXX_ ; 00 <
     dc _____ ; 01
     dc _XXX_ ; 02
     dc _XXX_ ; 03 <
     dc _____ ; 04
     dc _XXX_ ; 05
     dc _XXX_ ; 06 <
     dc _____ ; 07
     dc _XXX_ ; 08
     dc _XXX_ ; 09 <
     dc __X__ ; 10
     dc _XXX_ ; 11
     dc _XXX_ ; 12 <
     dc __X__ ; 13
     dc _XXX_ ; 14
     dc _XXX_ ; 15 <
     dc __X__ ; 16
     dc _XXX_ ; 17
     dc _XXX_ ; 18 <
     dc __X__ ; 19
     dc _XXX_ ; 20
     dc _XXX_ ; 21 <
     dc _____ ; 22
     dc _XXX_ ; 23
     dc _XXX_ ; 24 <
     dc _____ ; 25
     dc _XXX_ ; 26
     dc _XXX_ ; 27 <
     dc _____ ; 28
     dc _XXX_ ; 29


__CHAR_AMOEBA_3

     ; dc __ | __ | _X__ ; 00 < <--
     ; dc __ | __ | _X__ ; 01 <--
     ; dc XX | YY | X_XX ; 02 <-- raised small square
     ; dc __ | Y_ | _X__ ; 03 < <--
     ; dc __ | Y_ | _X__ ; 04 <--
     ; dc XX | YY | X_XX ; 05
     ; dc _X | __ | ____ ; 06 <
     ; dc __ | _Y | ____ ; 07
     ; dc XX | YY | XXXX ; 08
     ; dc      __ | ____ ; 09 <
     ; dc      __ | __X_ ; 10
     ; dc      YY | XXXX ; 11
     ; dc      __ | ____ ; 12 <
     ; dc      __ | _XXX ; 13
     ; dc      YY | XXXX ; 14
     ; dc           ____ ; 15 <
     ; dc           _XXX ; 16
     ; dc           XXXX ; 17
     ; dc           ____ ; 18 <
     ; dc           __X_ ; 19
     ; dc           XXXX ; 20


    #IF __ENABLE_LAVA

__CHAR_LAVA_0

     dc __ | __ | ____ ; 00 <
     dc XX | __ | ____ ; 01
     dc __ | __ | ____ ; 02
     dc __ | __ | ____ ; 03 <
     dc __ | __ | _X__ ; 04
     dc __ | __ | ____ ; 05
     dc __ | __ | ____ ; 06 <
     dc __ | __ | ____ ; 07
     dc __ | __ | ____ ; 08
     dc      __ | ___X ; 09 <
     dc      __ | _X__ ; 10
     dc      __ | ____ ; 11
     dc      __ | ____ ; 12 <
     dc      __ | XXX_ ; 13
     dc      __ | ____ ; 14
     dc           ____ ; 15 <
     dc           _X__ ; 16
     dc           ____ ; 17
     dc           ____ ; 18 <
     dc           ____ ; 19
     dc           ____ ; 20


__CHAR_LAVA_1

     dc __ | __ | ____ ; 00 <
     dc __ | __ | _X__ ; 01
     dc __ | __ | ____ ; 02
     dc __ | __ | ____ ; 03 <
     dc __ | __ | XXX_ ; 04
     dc __ | __ | ____ ; 05
     dc XX | __ | ____ ; 06 <
     dc __ | __ | _X__ ; 07
     dc __ | __ | ____ ; 08
     dc      __ | ____ ; 09 <
     dc      __ | ____ ; 10
     dc      __ | ____ ; 11
     dc      __ | ____ ; 12 <
     dc      __ | ____ ; 13
     dc      __ | ____ ; 14
     dc           ____ ; 15 <
     dc           ____ ; 16
     dc           ____ ; 17
     dc           ___X ; 18 <
     dc           ____ ; 19
     dc           ____ ; 20


__CHAR_LAVA_2

     dc __ | __ | __X_ ; 00 <
     dc __ | __ | _XXX ; 01
     dc __ | __ | ____ ; 02
     dc __ | __ | __X_ ; 03 <
     dc XX | __ | _XXX ; 04
     dc __ | __ | ____ ; 05
     dc __ | __ | __X_ ; 06 <
     dc __ | __ | __X_ ; 07
     dc __ | __ | ____ ; 08
     dc      __ | ____ ; 09 <
     dc      __ | ____ ; 10
     dc      __ | ____ ; 11
     dc      __ | ____ ; 12 <
     dc      __ | ___X ; 13
     dc      __ | ____ ; 14
     dc           ____ ; 15 <
     dc           ____ ; 16
     dc           ____ ; 17
     dc           ____ ; 18 <
     dc           ____ ; 19
     dc           ____ ; 20


__CHAR_LAVA_3

     dc __ | __ | _X__ ; 00 < <--
     dc __ | __ | _X__ ; 01 <--
     dc __ | __ | ____ ; 02 <-- raised small square
     dc __ | __ | _X__ ; 03 < <--
     dc __ | __ | _X__ ; 04 <--
     dc __ | __ | ____ ; 05
     dc __ | __ | ____ ; 06 <
     dc __ | __ | ____ ; 07
     dc __ | __ | ____ ; 08
     dc      __ | ____ ; 09 <
     dc      __ | __X_ ; 10
     dc      __ | ____ ; 11
     dc      __ | ____ ; 12 <
     dc      __ | _XXX ; 13
     dc      __ | ____ ; 14
     dc           ____ ; 15 <
     dc           _XXX ; 16
     dc           ____ ; 17
     dc           ____ ; 18 <
     dc           __X_ ; 19
     dc           ____ ; 20

    ENDIF ; ENABLE_LAVA
    

    IF __ENABLE_WATER

__CHAR_WATER_0

     dc XX | __ | ____ ; 00 <
     dc __ | __ | ____ ; 01
     dc __ | __ | _XXX ; 02
     dc __ | __ | XXXX ; 03 <
     dc __ | __ | X___ ; 04
     dc __ | __ | ____ ; 05
     dc __ | __ | ____ ; 06 <
     dc __ | __ | ____ ; 07
     dc __ | __ | ____ ; 08
     dc      __ | ____ ; 09 <
     dc      __ | ____ ; 10
     dc      __ | ____ ; 11
     dc      __ | XX__ ; 12 <
     dc      __ | XXXX ; 13
     dc      __ | _XXX ; 14
     dc           ___X ; 15 <
     dc           ____ ; 16
     dc           ____ ; 17
     dc           ____ ; 18 <
     dc           ____ ; 19
     dc           ____ ; 20


__CHAR_WATER_1

     dc __ | __ | ____ ; 00 <
     dc XX | __ | __XX ; 01
     dc __ | __ | XXXX ; 02
     dc __ | __ | XX__ ; 03 <
     dc __ | __ | ____ ; 04
     dc __ | __ | ____ ; 05
     dc __ | __ | ____ ; 06 <
     dc __ | __ | ____ ; 07
     dc __ | __ | ____ ; 08
     dc      __ | ____ ; 09 <
     dc      __ | ____ ; 10
     dc      __ | ____ ; 11
     dc      __ | XX__ ; 12 <
     dc      __ | XXXX ; 13
     dc      __ | __XX ; 14
     dc           ____ ; 15 <
     dc           ____ ; 16
     dc           ____ ; 17
     dc           ____ ; 18 <
     dc           ____ ; 19
     dc           ____ ; 20


__CHAR_WATER_2

     dc __ | __ | ____ ; 00 <
     dc XX | __ | ____ ; 01
     dc __ | __ | X___ ; 02
     dc __ | __ | XXX_ ; 03 <
     dc __ | __ | _XXX ; 04
     dc __ | __ | ___X ; 05
     dc __ | __ | ____ ; 06 <
     dc __ | __ | ____ ; 07
     dc __ | __ | ____ ; 08
     dc      __ | ____ ; 09 <
     dc      __ | ____ ; 10
     dc      __ | ____ ; 11
     dc      __ | ___X ; 12 <
     dc      __ | _XXX ; 13
     dc      __ | XXX_ ; 14
     dc           X___ ; 15 <
     dc           ____ ; 16
     dc           ____ ; 17
     dc           ____ ; 18 <
     dc           ____ ; 19
     dc           ____ ; 20


__CHAR_WATER_3

     dc __ | __ | ____ ; 00 <
     dc XX | __ | ____ ; 01
     dc __ | __ | ____ ; 02
     dc __ | __ | XX__ ; 03 <
     dc __ | __ | XXXX ; 04
     dc __ | __ | __XX ; 05
     dc __ | __ | ____ ; 06 <
     dc __ | __ | ____ ; 07
     dc __ | __ | ____ ; 08
     dc      __ | ____ ; 09 <
     dc      __ | ____ ; 10
     dc      __ | ____ ; 11
     dc      __ | ___X ; 12 <
     dc      __ | XXXX ; 13
     dc      __ | XXX_ ; 14
     dc           ____ ; 15 <
     dc           ____ ; 16
     dc           ____ ; 17
     dc           ____ ; 18 <
     dc           ____ ; 19
     dc           ____ ; 20

    ENDIF ; ENABLE_WATER






CHAR_BLOCK_SIZE = * - CHAR_BLOCK_START
    echo "Char block = ", CHAR_BLOCK_START, "-", *, "(", [CHAR_BLOCK_SIZE]d, "bytes)" 
;CHARSET_END

; EOF
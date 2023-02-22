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

    dc XX | __ | _XX_ ; 00 <
    dc XX | YY | _XX_ ; 01
    dc __ | YY | __X_ ; 02
    dc __ | __ | __X_ ; 03 <
    dc XX | YY | XX_X ; 04
    dc __ | _Y | ___X ; 05
    dc __ | __ | ___X ; 06 <
    dc XX | YY | XXXX ; 07
    dc __ | __ | ___X ; 08
    dc      __ | ___X ; 09 <
    dc      YY | XXXX ; 10
    dc      __ | ____ ; 11
    dc      __ | ___X ; 12 <
    dc      YY | XXXX ; 13
    dc      __ | ____ ; 14
    dc           ___X ; 15 <
    dc           XXXX ; 16
    dc           ____ ; 17
    dc           __X_ ; 18 <
    dc           _XX_ ; 19
    dc           ____ ; 20


__CHAR_BOULDER_U

    dc __ | __ | ____ ; 00 <
    dc XX | YY | XXXX ; 01
    dc __ | __ | ____ ; 02
    dc __ | __ | ____ ; 03 <
    dc XX | YY | XXXX ; 04
    dc __ | __ | ____ ; 05
    dc __ | __ | ____ ; 06 <
    dc XX | YY | XXXX ; 07
    dc __ | __ | ___X ; 08
    dc      __ | ___X ; 09 <
    dc      YY | XXXX ; 10
    dc      __ | ____ ; 11
    dc      __ | ___X ; 12 <
    dc      YY | XXXX ; 13
    dc      __ | ____ ; 14
    dc           ___X ; 15 <
    dc           XXXX ; 16
    dc           ____ ; 17
    dc           __X_ ; 18 <
    dc           _XX_ ; 19
    dc           ____ ; 20



__CHAR_BOULDER_R

    dc XX | __ | _XXX ; 00 <
    dc XX | YY | _XXX ; 01
    dc __ | YY | ____ ; 02
    dc __ | __ | ____ ; 03 <
    dc XX | YY | XXXX ; 04
    dc __ | __ | ____ ; 05
    dc __ | __ | ____ ; 06 <
    dc XX | YY | XXXX ; 07
    dc __ | __ | ____ ; 08
    dc      __ | ____ ; 09 <
    dc      YY | XXXX ; 10
    dc      __ | ____ ; 11
    dc      __ | ____ ; 12 <
    dc      YY | XXXX ; 13
    dc      __ | ____ ; 14
    dc           ____ ; 15 <
    dc           XXXX ; 16
    dc           ____ ; 17
    dc           ____ ; 18 <
    dc           _XXX ; 19
    dc           ____ ; 20


__CHAR_BOULDER_D

    dc XX | __ | _XX_ ; 00 <
    dc XX | YY | _XX_ ; 01
    dc __ | YY | __X_ ; 02
    dc __ | __ | __X_ ; 03 <
    dc XX | YY | XX_X ; 04
    dc __ | _Y | ___X ; 05
    dc __ | __ | ___X ; 06 <
    dc XX | YY | XXXX ; 07
    dc __ | __ | ___X ; 08
    dc      __ | ___X ; 09 <
    dc      YY | XXXX ; 10
    dc      __ | ____ ; 11
    dc      __ | ___X ; 12 <
    dc      YY | XXXX ; 13
    dc      __ | ____ ; 14
    dc           ____ ; 15 <
    dc           XXXX ; 16
    dc           ____ ; 17
    dc           ____ ; 18 <
    dc           XXXX ; 19
    dc           ____ ; 20



__CHAR_BOULDER_L

    dc XX | __ | XXX_ ; 00 <
    dc XX | YY | XXX_ ; 01
    dc __ | YY | __X_ ; 02
    dc __ | __ | __X_ ; 03 <
    dc XX | YY | XX_X ; 04
    dc __ | _Y | ___X ; 05
    dc __ | __ | ___X ; 06 <
    dc XX | YY | XXXX ; 07
    dc __ | __ | ___X ; 08
    dc      __ | ___X ; 09 <
    dc      YY | XXXX ; 10
    dc      __ | ____ ; 11
    dc      __ | ___X ; 12 <
    dc      YY | XXXX ; 13
    dc      __ | ____ ; 14
    dc           ____ ; 15 <
    dc           XXXX ; 16
    dc           ____ ; 17
    dc           ____ ; 18 <
    dc           XXX_ ; 19
    dc           ____ ; 20



__CHAR_BOULDER_UR

    dc __ | __ | ____ ; 00 <
    dc XX | YY | XXXX ; 01
    dc __ | __ | ____ ; 02
    dc __ | __ | ____ ; 03 <
    dc XX | YY | XXXX ; 04
    dc __ | __ | ____ ; 05
    dc __ | __ | ____ ; 06 <
    dc XX | YY | XXXX ; 07
    dc __ | __ | ____ ; 08
    dc      __ | ____ ; 09 <
    dc      YY | XXXX ; 10
    dc      __ | ____ ; 11
    dc      __ | ____ ; 12 <
    dc      YY | XXXX ; 13
    dc      __ | ____ ; 14
    dc           ____ ; 15 <
    dc           XXXX ; 16
    dc           ____ ; 17
    dc           ____ ; 18 <
    dc           _XXX ; 19
    dc           ____ ; 20



__CHAR_BOULDER_UD

    dc __ | __ | ____ ; 00 <
    dc XX | YY | XXXX ; 01
    dc __ | __ | ____ ; 02
    dc __ | __ | ____ ; 03 <
    dc XX | YY | XXXX ; 04
    dc __ | __ | ____ ; 05
    dc __ | __ | ____ ; 06 <
    dc XX | YY | XXXX ; 07
    dc __ | __ | ____ ; 08
    dc      __ | ____ ; 09 <
    dc      YY | XXXX ; 10
    dc      __ | ____ ; 11
    dc      __ | ____ ; 12 <
    dc      YY | XXXX ; 13
    dc      __ | ____ ; 14
    dc           ____ ; 15 <
    dc           XXXX ; 16
    dc           ____ ; 17
    dc           ____ ; 18 <
    dc           XXXX ; 19
    dc           ____ ; 20



__CHAR_BOULDER_UL

    dc __ | __ | ____ ; 00 <
    dc XX | YY | XXXX ; 01
    dc __ | __ | ____ ; 02
    dc __ | __ | ____ ; 03 <
    dc XX | YY | XXXX ; 04
    dc __ | __ | ____ ; 05
    dc __ | __ | ____ ; 06 <
    dc XX | YY | XXXX ; 07
    dc __ | __ | ___X ; 08
    dc      __ | ___X ; 09 <
    dc      YY | XXXX ; 10
    dc      __ | ____ ; 11
    dc      __ | ___X ; 12 <
    dc      YY | XXXX ; 13
    dc      __ | ____ ; 14
    dc           ___X ; 15 <
    dc           XXXX ; 16
    dc           ____ ; 17
    dc           __X_ ; 18 <
    dc           XXX_ ; 19
    dc           ____ ; 20


__CHAR_BOULDER_RD

    dc XX | __ | _XXX ; 00 <
    dc XX | YY | _XXX ; 01
    dc __ | YY | ____ ; 02
    dc __ | __ | ____ ; 03 <
    dc XX | YY | XXXX ; 04
    dc __ | Y_ | ____ ; 05
    dc __ | __ | ____ ; 06 <
    dc XX | YY | XXXX ; 07
    dc __ | __ | ____ ; 08
    dc      __ | ____ ; 09 <
    dc      YY | XXXX ; 10
    dc      __ | ____ ; 11
    dc      __ | ____ ; 12 <
    dc      YY | XXXX ; 13
    dc      __ | ____ ; 14
    dc           ____ ; 15 <
    dc           XXXX ; 16
    dc           ____ ; 17
    dc           ____ ; 18 <
    dc           XXXX ; 19
    dc           ____ ; 20



__CHAR_BOULDER_RL

    dc XX | __ | XXXX ; 00 <
    dc XX | YY | XXXX ; 01
    dc __ | YY | ____ ; 02
    dc __ | __ | ____ ; 03 <
    dc XX | YY | XXXX ; 04
    dc __ | __ | ____ ; 05
    dc __ | __ | ____ ; 06 <
    dc XX | YY | XXXX ; 07
    dc __ | __ | ____ ; 08
    dc      __ | ____ ; 09 <
    dc      YY | XXXX ; 10
    dc      __ | ____ ; 11
    dc      __ | ____ ; 12 <
    dc      YY | XXXX ; 13
    dc      __ | ____ ; 14
    dc           ____ ; 15 <
    dc           XXXX ; 16
    dc           ____ ; 17
    dc           ____ ; 18 <
    dc           XXXX ; 19
    dc           ____ ; 20


__CHAR_BOULDER_DL

    dc XX | __ | XXX_ ; 00 <
    dc XX | YY | XXX_ ; 01
    dc __ | YY | __X_ ; 02
    dc __ | __ | __X_ ; 03 <
    dc XX | YY | XXXX ; 04
    dc __ | _Y | ___X ; 05
    dc __ | __ | ___X ; 06 <
    dc XX | YY | XXXX ; 07
    dc __ | __ | ___X ; 08
    dc      __ | ___X ; 09 <
    dc      YY | XXXX ; 10
    dc      __ | ____ ; 11
    dc      __ | ___X ; 12 <
    dc      YY | XXXX ; 13
    dc      __ | ____ ; 14
    dc           ____ ; 15 <
    dc           XXXX ; 16
    dc           ____ ; 17
    dc           ____ ; 18 <
    dc           XXXX ; 19
    dc           ____ ; 20


__CHAR_BOULDER_URD

    dc __ | __ | X___ ; 00 <
    dc XX | YY | XXXX ; 01
    dc __ | __ | X___ ; 02
    dc __ | __ | X___ ; 03 <
    dc XX | YY | XXXX ; 04
    dc __ | __ | X___ ; 05
    dc __ | __ | X___ ; 06 <
    dc XX | YY | XXXX ; 07
    dc __ | __ | X___ ; 08
    dc      __ | X___ ; 09 <
    dc      YY | XXXX ; 10
    dc      __ | X___ ; 11
    dc      __ | X___ ; 12 <
    dc      YY | XXXX ; 13
    dc      __ | ____ ; 14
    dc           ____ ; 15 <
    dc           XXXX ; 16
    dc           ____ ; 17
    dc           ____ ; 18 <
    dc           XXXX ; 19
    dc           ____ ; 20


__CHAR_BOULDER_URL

    dc __ | __ | ____ ; 00 <
    dc XX | YY | XXXX ; 01
    dc __ | __ | ____ ; 02
    dc __ | __ | ____ ; 03 <
    dc XX | YY | XXXX ; 04
    dc __ | __ | ____ ; 05
    dc __ | __ | ____ ; 06 <
    dc XX | YY | XXXX ; 07
    dc __ | __ | ____ ; 08
    dc      __ | ____ ; 09 <
    dc      YY | XXXX ; 10
    dc      __ | ____ ; 11
    dc      __ | ____ ; 12 <
    dc      YY | XXXX ; 13
    dc      __ | ____ ; 14
    dc           ____ ; 15 <
    dc           XXXX ; 16
    dc           ____ ; 17
    dc           ____ ; 18 <
    dc           XXXX ; 19
    dc           ____ ; 20

__CHAR_BOULDER_UDL

    dc __ | __ | ____ ; 00 <
    dc XX | YY | XXXX ; 01
    dc __ | __ | ____ ; 02
    dc __ | __ | ____ ; 03 <
    dc XX | YY | XXXX ; 04
    dc __ | __ | ___X ; 05
    dc __ | __ | ___X ; 06 <
    dc XX | YY | XXXX ; 07
    dc __ | __ | ___X ; 08
    dc      __ | ___X ; 09 <
    dc      YY | XXXX ; 10
    dc      __ | ____ ; 11
    dc      __ | ___X ; 12 <
    dc      YY | XXXX ; 13
    dc      __ | ____ ; 14
    dc           ____ ; 15 <
    dc           XXXX ; 16
    dc           ____ ; 17
    dc           ____ ; 18 <
    dc           XXXX ; 19
    dc           ____ ; 20

__CHAR_BOULDER_RDL

    dc XX | __ | XXXX ; 00 <
    dc XX | YY | XXXX ; 01
    dc __ | YY | ____ ; 02
    dc __ | __ | ____ ; 03 <
    dc XX | YY | XXXX ; 04
    dc __ | _Y | ____ ; 05
    dc __ | __ | ____ ; 06 <
    dc XX | YY | XXXX ; 07
    dc __ | __ | ____ ; 08
    dc      __ | ____ ; 09 <
    dc      YY | XXXX ; 10
    dc      __ | ____ ; 11
    dc      __ | ____ ; 12 <
    dc      YY | XXXX ; 13
    dc      __ | ____ ; 14
    dc           ____ ; 15 <
    dc           XXXX ; 16
    dc           ____ ; 17
    dc           ____ ; 18 <
    dc           XXXX ; 19
    dc           ____ ; 20

__CHAR_BOULDER_URDL

    dc __ | __ | ____ ; 00 <
    dc XX | YY | XXXX ; 01
    dc __ | __ | ____ ; 02
    dc __ | __ | ____ ; 03 <
    dc XX | YY | XXXX ; 04
    dc __ | __ | ____ ; 05
    dc __ | __ | ____ ; 06 <
    dc XX | YY | XXXX ; 07
    dc __ | __ | ____ ; 08
    dc      __ | ____ ; 09 <
    dc      YY | XXXX ; 10
    dc      __ | ____ ; 11
    dc      __ | ____ ; 12 <
    dc      YY | XXXX ; 13
    dc      __ | ____ ; 14
    dc           ____ ; 15 <
    dc           XXXX ; 16
    dc           ____ ; 17
    dc           ____ ; 18 <
    dc           XXXX ; 19
    dc           ____ ; 20


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


#if 0








const unsigned char CHAR_DOGE6[] = {
__    ____  
XX    ____  
XX    ____  
XX    _X__  
XX    _X__  
XX    _X__  
XX    XXX_  
__    XXX_  
__    XXX_  
      XXX_  
      XXX_  
      XXX_  
      XXX_  
      XXX_  
      XXX_  
      XXX_  
      _X__  
      _X__  
      _X__  
      ____  
      ____  

};



#endif


__CHAR_FIREFLY

    dc XX | YY | _XX_ ; 00 <
    dc XX | YY | _XX_ ; 01
    dc XX | YY | ____ ; 02
    dc XX | __ | XXXX ; 03 <
    dc XX | __ | XXXX ; 04
    dc XX | YY | _XX_ ; 05
    dc __ | __ | X__X ; 06 <
    dc __ | __ | X__X ; 07
    dc __ | YY | _XX_ ; 08
    dc      __ | X__X ; 09 <
    dc      YY | X__X ; 10
    dc      YY | _XX_ ; 11
    dc      __ | X__X ; 12 <
    dc      __ | X__X ; 13
    dc      __ | _XX_ ; 14
    dc           XXXX ; 15 <
    dc           XXXX ; 16
    dc           _XX_ ; 17
    dc           _XX_ ; 18 <
    dc           _XX_ ; 19
 ;   dc           ____ ; 20


__CHAR_FIREFLY2

    dc __ | YY | ____ ; 00 <
    dc XX | YY | ____ ; 01
    dc __ | YY | ____ ; 02
    dc __ | __ | _XX_ ; 03 <
    dc XX | __ | _XX_ ; 04
    dc __ | YY | _XX_ ; 05
    dc __ | __ | X__X ; 06 <
    dc __ | __ | X__X ; 07
    dc __ | YY | XXXX ; 08
    dc      __ | X__X ; 09 <
    dc      YY | X__X ; 10
    dc      YY | XXXX ; 11
    dc      __ | X__X ; 12 <
    dc      __ | X__X ; 13
    dc      __ | XXXX ; 14
    dc           _XX_ ; 15 <
    dc           _XX_ ; 16
    dc           _XX_ ; 17
;    dc           ____ ; 18 <
;    dc           ____ ; 19
;    dc           ____ ; 20


__CHAR_FIREFLY3

    dc __ | YY | ____ ; 00 <
    dc __ | YY | ____ ; 01
    dc __ | YY | ____ ; 02
    dc __ | YY | ____ ; 03 <
    dc __ | YY | ____ ; 04
    dc __ | YY | ____ ; 05
    dc __ | YY | _XX_ ; 06 <
    dc __ | YY | _XX_ ; 07
    dc __ | YY | _XX_ ; 08
    dc      YY | _XX_ ; 09 <
    dc      YY | _XX_ ; 10
    dc      YY | _XX_ ; 11
    dc      __ | _XX_ ; 12 <
    dc      __ | _XX_ ; 13
    dc      __ | _XX_ ; 14
    dc           ____ ; 15 <
    dc           ____ ; 16
;    dc           ____ ; 17
;    dc           ____ ; 18 <
;    dc           ____ ; 19
;    dc           ____ ; 20


;CHARSET_END

;CHARSET_START
CHAR_BLOCK2_START



__CHAR_SPARKLE_0

    dc X_ | __ | ____ ; 00 <
    dc X_ | __ | ____ ; 01
    dc __ | __ | ____ ; 02
    dc _X | Y_ | ____ ; 03 <
    dc _X | Y_ | X___ ; 04
    dc __ | __ | X___ ; 05
    dc __ | __ | X___ ; 06 <
    dc __ | __ | X___ ; 07
    dc __ | __ | ____ ; 08
    dc      __ | ____ ; 09 <
    dc      __ | ____ ; 10
    dc      __ | ____ ; 11
    dc      __ | ____ ; 12 <
    dc      __ | ____ ; 13
;    dc      __ | ____ ; 14
;    dc           ____ ; 15 <
;    dc           ____ ; 16
;    dc           ____ ; 17
;    dc           ____ ; 18 <
;    dc           ____ ; 19
;    dc           ____ ; 20


__CHAR_SPARKLE_1

    dc __ | __ | ____ ; 00 <
    dc __ | __ | ____ ; 01
    dc __ | __ | ____ ; 02
    dc X_ | __ | ____ ; 03 <
    dc X_ | __ | ____ ; 04
    dc __ | __ | ____ ; 05
    dc _X | __ | ____ ; 06 <
    dc _X | __ | ___X ; 07
    dc __ | __ | ___X ; 08
    dc      _Y | ___X ; 09 <
    dc      _Y | ___X ; 10
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


__CHAR_MAGICWALL_1

     dc __ | Y_ | ____ ; 00 <
     dc __ | Y_ | _XXX ; 01
     dc XX | YY | XXXX ; 02
     dc XX | __ | _XXX ; 03 <
     dc __ | _Y | _XXX ; 04
     dc XX | YY | XXXX ; 05
     dc XX | _Y | _XXX ; 06 <
     dc __ | _Y | _XXX ; 07
     dc __ | YY | XXXX ; 08
     dc      Y_ | _XXX ; 09 <
     dc      Y_ | ____ ; 10
     dc      YY | XXXX ; 11
     dc      _Y | XX_X ; 12 <
     dc      _Y | XX_X ; 13
     dc      YY | XXXX ; 14
     dc           XX_X ; 15 <
     dc           XX_X ; 16
     dc           XXXX ; 17
     dc           XX_X ; 18 <
     dc           XX_X ; 19
;     dc           XXXX ; 20



__CHAR_PEBBLE2

     dc XX | YY | XXXX ; 00 <
     dc __ | __ | ____ ; 01
     dc __ | __ | ____ ; 02
     dc XX | YY | X_XX ; 03 <
     dc __ | __ | ____ ; 04
     dc __ | __ | ____ ; 05
     dc XX | YY | _XXX ; 06 <
     dc __ | __ | ____ ; 07
     dc __ | __ | ____ ; 08
     dc      YY | XX_X ; 09 <
     dc      __ | ____ ; 10
     dc      __ | ____ ; 11
     dc      YY | XXXX ; 12 <
     dc      _Y | ____ ; 13
     dc      __ | ____ ; 14
     dc           X_XX ; 15 <
     dc           ____ ; 16
     dc           X___ ; 17
     dc           XXX_ ; 18 <
     dc           X___ ; 19
     dc           ____ ; 20



__CHAR_BUTTERFLY_0

    dc __ | __ | XX__ ; 00 <
    dc _X | _Y | XX_X ; 01
    dc _X | Y_ | ___X ; 02
    dc X_ | Y_ | XX__ ; 03 <
    dc XX | _Y | XX_X ; 04
    dc XX | Y_ | ___X ; 05
    dc _X | __ | XXX_ ; 06 <
    dc __ | __ | XXXX ; 07
    dc _X | YY | __XX ; 08
    dc      Y_ | __X_ ; 09 <
    dc      _Y | _XX_ ; 10
    dc      Y_ | _XX_ ; 11
    dc      Y_ | _XXX ; 12 <
    dc      _Y | XX__ ; 13
    dc      __ | XXXX ; 14
    dc           __XX ; 15 <
    dc           X___ ; 16
    dc           X_XX ; 17
    dc           __XX ; 18 <
    dc           ____ ; 19
    dc           ____ ; 20




__CHAR_BUTTERFLY_2

    dc __ | __ | __X_ ; 00 <
    dc X_ | __ | __X_ ; 01
    dc X_ | __ | ____ ; 02
    dc _X | __ | __X_ ; 03 <
    dc XX | __ | __X_ ; 04
    dc XX | __ | ____ ; 05
    dc X_ | __ | __X_ ; 06 <
    dc __ | Y_ | __X_ ; 07
    dc X_ | _Y | __X_ ; 08
    dc      __ | __X_ ; 09 <
    dc      __ | _XX_ ; 10
    dc      __ | _XX_ ; 11
    dc      __ | _X__ ; 12 <
    dc      __ | _X__ ; 13
    dc      __ | _X__ ; 14
    dc           _X__ ; 15 <
    dc           ____ ; 16
    dc           _X__ ; 17
    dc           _X__ ; 18 <
;    dc           ____ ; 19
;    dc           ____ ; 20


__CHAR_BOULDER_SHAKE

     dc __ | __ | ____ ; 00 <
     dc __ | __ | ____ ; 01
     dc __ | __ | ____ ; 02
     dc _X | __ | _XX_ ; 03 <
     dc XX | YY | _XX_ ; 04
     dc X_ | YY | __X_ ; 05
     dc __ | __ | __X_ ; 06 <
     dc XX | YY | XX_X ; 07
     dc __ | _Y | ___X ; 08
     dc      __ | ___X ; 09 <
     dc      YY | XXXX ; 10
     dc      __ | ___X ; 11
     dc      __ | ___X ; 12 <
     dc      YY | XXXX ; 13
     dc      __ | ____ ; 14
     dc           ___X ; 15 <
     dc           XXXX ; 16
     dc           ____ ; 17
     dc           __XX ; 18 <
     dc           _XX_ ; 19
;     dc           ____ ; 20


__CHAR_MAGICWALL_3

     dc __ | _Y | ____ ; 00 <
     dc _X | _Y | XX_X ; 01
     dc X_ | YY | XXXX ; 02
     dc XX | Y_ | XX_X ; 03 <
     dc XX | Y_ | XX_X ; 04
     dc XX | YY | XXXX ; 05
     dc XX | Y_ | XX_X ; 06 <
     dc X_ | Y_ | XX_X ; 07
     dc __ | YY | XXXX ; 08
     dc      _Y | XX_X ; 09 <
     dc      _Y | ____ ; 10
     dc      YY | XXXX ; 11
     dc      __ | _XXX ; 12 <
     dc      Y_ | _XXX ; 13
     dc      YY | XXXX ; 14
     dc           _XXX ; 15 <
     dc           _XXX ; 16
     dc           XXXX ; 17
     dc           _XXX ; 18 <
     dc           _XXX ; 19
;     dc           XXXX ; 20



__CHAR_STEELWALL
     dc XX | YY | XXXX ; 00 <
     dc __ | __ | ____ ; 01
     dc XX | YY | XXXX ; 02
     dc XX | YY | XXXX ; 03 <
     dc __ | Y_ | X___ ; 04
     dc XX | _Y | XXXX ; 05
     dc XX | YY | XXXX ; 06 <
     dc __ | __ | ____ ; 07
     dc XX | YY | _XXX ; 08
     dc XX | YY | XXXX ; 09 <
     dc __ | _Y | ____ ; 10
     dc XX | Y_ | XXXX ; 11
     dc XX | YY | XXXX ; 12 <
     dc __ | __ | __X_ ; 13
     dc XX | YY | XXXX ; 14
     dc XX |      XXXX ; 15 <
     dc __ |      ____ ; 16
     dc XX |      XX_X ; 17
     dc XX |      XXXX ; 18 <
     dc __ |      ____ ; 19
;     dc XX |      XXXX ; 20




__CHAR_DIRT

    dc XX | YY | XXXX ; 00 <
    dc __ | __ | ____ ; 01
    dc __ | __ | ____ ; 02
    dc XX | YY | X_XX ; 03 <
    dc __ | __ | ____ ; 04
    dc __ | __ | ____ ; 05
    dc XX | YY | _XXX ; 06 <
    dc __ | __ | ____ ; 07
    dc __ | __ | ____ ; 08
    dc      YY | XX_X ; 09 <
    dc      __ | ____ ; 10
    dc      __ | ____ ; 11
    dc      YY | XXXX ; 12 <
    dc      __ | ____ ; 13
    dc      __ | ____ ; 14
    dc           X_XX ; 15 <
    dc           ____ ; 16
    dc           ____ ; 17
    dc           XXX_ ; 18 <
    dc           ____ ; 19
    dc           ____ ; 20



__CHAR_BUTTERFLY_1

    dc __ | __ | _XX_ ; 00 < 
    dc XX | __ | _XX_ ; 01 
    dc _X | __ | ____ ; 02 
    dc XX | Y_ | _XX_ ; 03 < 
    dc XX | _Y | _XX_ ; 04 
    dc _X | Y_ | ____ ; 05 
    dc XX | Y_ | _XX_ ; 06 < 
    dc __ | _Y | _XX_ ; 07 
    dc XX | Y_ | __X_ ; 08 
    dc      __ | __X_ ; 09 < 
    dc      _Y | _XX_ ; 10 
    dc      __ | _XX_ ; 11 
    dc      __ | _XX_ ; 12 < 
    dc      __ | _X__ ; 13 
    dc      __ | _XX_ ; 14 
    dc           _XX_ ; 15 < 
    dc           ____ ; 16 
    dc           _XX_ ; 17 
    dc           _XX_ ; 18 < 
    dc           ____ ; 19 
;    dc           ____ ; 20 



__CHAR_BRICKWALL

     dc X_ | _Y | ____ ; 00 <
     dc X_ | _Y | XXX_ ; 01
     dc XX | YY | XXXX ; 02
     dc _X | Y_ | XXX_ ; 03 <
     dc _X | Y_ | XXX_ ; 04
     dc XX | YY | XXXX ; 05
     dc X_ | __ | XXX_ ; 06 <
     dc X_ | _Y | XXX_ ; 07
     dc XX | YY | XXXX ; 08
     dc      _Y | XXX_ ; 09 <
     dc      _Y | ____ ; 10
     dc      YY | XXXX ; 11
     dc      Y_ | X_XX ; 12 <
     dc      Y_ | X_XX ; 13
     dc      YY | XXXX ; 14
     dc           X_XX ; 15 <
     dc           X_XX ; 16
     dc           XXXX ; 17
     dc           X_XX ; 18 <
     dc           X_XX ; 19
     dc           XXXX ; 20











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

     dc __ | __ | _X__ ; 00 <
     dc __ | __ | ____ ; 01
     dc __ | __ | ____ ; 02
     dc __ | __ | XXX_ ; 03 <
     dc __ | __ | ____ ; 04
     dc __ | __ | ____ ; 05
     dc __ | __ | _X__ ; 06 <
     dc __ | __ | ____ ; 07
     dc __ | __ | ____ ; 08
     dc      __ | ____ ; 09 <
     dc      __ | ____ ; 10
     dc      __ | ____ ; 11
     dc      __ | __X_ ; 12 <
     dc      __ | ____ ; 13
     dc      __ | ____ ; 14
     dc           _XXX ; 15 <
     dc           ____ ; 16
     dc           ____ ; 17
     dc           __X_ ; 18 <
;     dc           ____ ; 19
;     dc           ____ ; 20


__CHAR_DUST_ROCK_1
 dc 0
__CHAR_DUST_1


     dc __ | __ | ____ ; 00 <
     dc __ | __ | ____ ; 01
     dc __ | __ | ____ ; 02
     dc __ | __ | _X__ ; 03 <
     dc __ | __ | ____ ; 04
     dc __ | __ | ____ ; 05
     dc __ | __ | __X_ ; 06 <
     dc __ | __ | ____ ; 07
     dc __ | __ | ____ ; 08
     dc      __ | _XXX ; 09 <
     dc      __ | ____ ; 10
     dc      __ | ____ ; 11
     dc      __ | __X_ ; 12 <
     dc      __ | ____ ; 13
     dc      __ | ____ ; 14
     dc           ____ ; 15 <
     dc           ____ ; 16
     dc           ____ ; 17
     dc           __X_ ; 18 <
;     dc           ____ ; 19
;     dc           ____ ; 20



__CHAR_DUST_ROCK_2
 dc 0

__CHAR_DUST_2



     dc __ | __ | ____ ; 00 <
     dc __ | __ | ____ ; 01
     dc __ | __ | ____ ; 02
     dc __ | __ | ____ ; 03 <
     dc __ | __ | ____ ; 04
     dc __ | __ | ____ ; 05
     dc __ | __ | ____ ; 06 <
     dc __ | __ | ____ ; 07
     dc __ | __ | ____ ; 08
     dc      __ | __X_ ; 09 <
     dc      __ | ____ ; 10
     dc      __ | ____ ; 11
     dc      __ | ____ ; 12 <
     dc      __ | ____ ; 13
     dc      __ | ____ ; 14
     dc           ____ ; 15 <
     dc           ____ ; 16
     dc           ____ ; 17
     dc           ____ ; 18 <
     dc           ____ ; 19

 
;     dc           ____ ; 20

__CHAR_PARALLAX_TEMPLATE        ; squished in here - careful about count above/below chars

     dc   %00000000 ;,  // 00
     dc   %00010001 ;, // 01
     dc   %00000000 ;, // 02
     dc   %00000000 ;, // 03
     dc   %00100010 ;, // 04
     dc   %00000000 ;, // 05
     dc   %00000000 ;, // 06
     dc   %00000000 ;, // 07
     dc   %00000000 ;, // 08
     dc   %00000000 ;, // 09
     dc   %10001000 ;, // 10
     dc   %00000000 ;, // 11
     dc   %00000000 ;, // 12
     dc   %00000000 ;, // 13
     dc   %00000000 ;, // 14
     dc   %00000000 ;, // 15
     dc   %01000100 ;, // 16
;        ________, // 17
;        ________, // 18
;        ________, // 19
;        ________, // 20


__CHAR_DUST_RIGHT_1
     dc __ | __ | ____ ; 00 <
     dc __ | __ | ____ ; 01
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
     dc      __ | _X__ ; 13
     dc      __ | ____ ; 14
     dc           ____ ; 15 <
     dc           X___ ; 16
     dc           ____ ; 17
     dc           ____ ; 18 <
     dc           _X__ ; 19
;     dc           ____ ; 20


__CHAR_DUST_LEFT_1

     dc __ | __ | ____ ; 00 <
     dc __ | __ | ____ ; 01
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
     dc      __ | __X_ ; 13
     dc      __ | ____ ; 14
     dc           ____ ; 15 <
     dc           ___X ; 16
     dc           ____ ; 17
     dc           ____ ; 18 <
     dc           __X_ ; 19
;≈     dc           ____ ; 20




__CHAR_MAGICWALL_2

     dc __ | _Y | ____ ; 00 <
     dc X_ | _Y | X_XX ; 01
     dc XX | YY | XXXX ; 02
     dc XX | __ | X_XX ; 03 <
     dc X_ | Y_ | X_XX ; 04
     dc XX | YY | XXXX ; 05
     dc XX | Y_ | X_XX ; 06 <
     dc X_ | Y_ | X_XX ; 07
     dc __ | YY | XXXX ; 08
     dc      _Y | X_XX ; 09 <
     dc      _Y | ____ ; 10
     dc      YY | XXXX ; 11
     dc      Y_ | XXX_ ; 12 <
     dc      Y_ | XXX_ ; 13
     dc      YY | XXXX ; 14
     dc           XXX_ ; 15 <
     dc           XXX_ ; 16
     dc           XXXX ; 17
     dc           XXX_ ; 18 <
     dc           XXX_ ; 19
     dc           XXXX ; 20


__CHAR_DOGE_00 ; doged

     dc __ | __ | ____ ; 00 <
     dc __ | __ | ____ ; 01
     dc X_ | __ | ____ ; 02
     dc XX | __ | ____ ; 03 <
     dc XX | Y_ | ____ ; 04
     dc XX | Y_ | _X__ ; 05
     dc _X | __ | ____ ; 06 <
     dc __ | YY | _XX_ ; 07
     dc __ | YY | XXX_ ; 08
     dc      __ | ____ ; 09 <
     dc      Y_ | _XX_ ; 10
     dc      Y_ | XXX_ ; 11
     dc      __ | ____ ; 12 <
     dc      __ | XXX_ ; 13
     dc      __ | XXX_ ; 14
     dc           ____ ; 15 <
     dc           _X__ ; 16
     dc           _X__ ; 17
     dc           ____ ; 18 <
     dc           ____ ; 19
     dc           ____ ; 20


__CHAR_DOGE_01 ; doged

     dc __ | __ | ____ ; 00 <
     dc __ | __ | ____ ; 01
     dc __ | __ | ____ ; 02
     dc X_ | __ | ____ ; 03 <
     dc XX | Y_ | ____ ; 04
     dc XX | Y_ | ____ ; 05
     dc _X | __ | ____ ; 06 <
     dc __ | YY | _X__ ; 07
     dc __ | YY | _X__ ; 08
     dc      __ | ____ ; 09 <
     dc      Y_ | XXX_ ; 10
     dc      Y_ | XXX_ ; 11
     dc      __ | ____ ; 12 <
     dc      __ | _X__ ; 13
     dc      __ | _X__ ; 14
     dc           ____ ; 15 <
     dc           ____ ; 16
     dc           ____ ; 17
     dc           ____ ; 18 <
     dc           ____ ; 19
     dc           ____ ; 20


__CHAR_DOGE_02 ;doged

     dc __ | __ | ____ ; 00 <
     dc __ | __ | ____ ; 01
     dc __ | __ | ____ ; 02
     dc __ | __ | ____ ; 03 <
     dc XX | __ | ____ ; 04
     dc XX | __ | ____ ; 05
     dc __ | __ | ____ ; 06 <
     dc __ | YY | ____ ; 07
     dc __ | YY | ____ ; 08
     dc      __ | ____ ; 09 <
     dc      __ | XXX_ ; 10
     dc      __ | XXX_ ; 11
     dc      __ | ____ ; 12 <
     dc      __ | ____ ; 13
     dc      __ | ____ ; 14
     dc           ____ ; 15 <
     dc           ____ ; 16
     dc           ____ ; 17
     dc           ____ ; 18 <
     dc           ____ ; 19
     dc           ____ ; 20

__CHAR_DOGE_03 ; doged

     dc __ | __ | ____ ; 00 <
     dc __ | __ | ____ ; 01
     dc __ | __ | ____ ; 02
     dc __ | __ | ____ ; 03 <
     dc XX | __ | ____ ; 04
     dc XX | __ | ____ ; 05
     dc XX | __ | ____ ; 06 <
     dc __ | YY | ____ ; 07
     dc __ | YY | ____ ; 08
     dc      __ | XXX_ ; 09 <
     dc      __ | XXX_ ; 10
     dc      __ | XXX_ ; 11
     dc      __ | XXX_ ; 12 <
     dc      __ | ____ ; 13
     dc      __ | ____ ; 14
     dc           ____ ; 15 <
     dc           ____ ; 16
     dc           ____ ; 17
     dc           ____ ; 18 <
     dc           ____ ; 19
     dc           ____ ; 20



__CHAR_DOGE_04 ; doged

     dc __ | __ | ____ ; 00 <
     dc __ | __ | ____ ; 01
     dc __ | __ | ____ ; 02
     dc X_ | Y_ | ____ ; 03 <
     dc XX | Y_ | ____ ; 04
     dc XX | Y_ | ____ ; 05
     dc XX | YY | _X__ ; 06 <
     dc _X | YY | _X__ ; 07
     dc __ | YY | _X__ ; 08
     dc      Y_ | XXX_ ; 09 <
     dc      Y_ | XXX_ ; 10
     dc      Y_ | XXX_ ; 11
     dc      __ | XXX_ ; 12 <
     dc      __ | _X__ ; 13
     dc      __ | _X__ ; 14
     dc           _X__ ; 15 <
     dc           ____ ; 16
     dc           ____ ; 17
     dc           ____ ; 18 <
     dc           ____ ; 19
     dc           ____ ; 20


__CHAR_DOGE_05

     dc __ | __ | ____ ; 00 <
     dc __ | __ | ____ ; 01
     dc X_ | __ | ____ ; 02
     dc XX | Y_ | _X__ ; 03 <
     dc XX | Y_ | _X__ ; 04
     dc XX | Y_ | _X__ ; 05
     dc XX | YY | XXX_ ; 06 <
     dc _X | YY | XXX_ ; 07
     dc __ | YY | XXX_ ; 08
     dc      YY | XXX_ ; 09 <
     dc      Y_ | XXX_ ; 10
     dc      Y_ | XXX_ ; 11
     dc      Y_ | XXX_ ; 12 <
     dc      __ | XXX_ ; 13
     dc      __ | XXX_ ; 14
     dc           XXX_ ; 15 <
     dc           _X__ ; 16
     dc           _X__ ; 17
     dc           _X__ ; 18 <
     dc           ____ ; 19
     dc           ____ ; 20

__CHAR_DOGE_FALLING ;

     dc __ | __ | ___X ; 00 <
     dc X_ | _Y | ___X ; 01
     dc X_ | _Y | ___X ; 02
     dc __ | __ | __X_ ; 03 <
     dc XX | YY | __XX ; 04
     dc XX | YY | __XX ; 05
     dc __ | __ | _X__ ; 06 <
     dc _X | YY | _XXX ; 07
     dc _X | YY | _XXX ; 08
     dc      __ | ____ ; 09 <
     dc      _Y | _XXX ; 10
     dc      _Y | _XXX ; 11
     dc      __ | ____ ; 12 <
     dc      __ | __XX ; 13
     dc      __ | __XX ; 14
     dc           ____ ; 15 <
     dc           ___X ; 16
     dc           ___X ; 17
     dc           ____ ; 18 <
     dc           ____ ; 19
     dc           ____ ; 20



__CHAR_AMOEBA_1

     dc __ | __ | ____ ; 00 <
     dc __ | __ | _X__ ; 01
     dc XX | YY | XXXX ; 02
     dc _X | __ | ____ ; 03 <
     dc __ | __ | XXX_ ; 04
     dc XX | YY | XXXX ; 05
     dc __ | __ | ____ ; 06 <
     dc X_ | __ | _X__ ; 07
     dc XX | YY | XXXX ; 08
     dc      _Y | ____ ; 09 <
     dc      __ | ____ ; 10
     dc      YY | XXXX ; 11
     dc      _Y | ____ ; 12 <
     dc      __ | ____ ; 13
     dc      YY | XXXX ; 14
     dc           ___X ; 15 <
     dc           ____ ; 16
     dc           XXXX ; 17
     dc           ___X ; 18 <
     dc           ____ ; 19
;     dc           XXXX ; 20


__CHAR_PEBBLE1
     dc XX | YY | XXXX ; 00 <
     dc __ | Y_ | ____ ; 01
     dc __ | __ | __X_ ; 02
     dc XX | YY | X_XX ; 03 <
     dc __ | __ | __X_ ; 04
     dc __ | __ | ____ ; 05
     dc XX | YY | _XXX ; 06 <
     dc __ | __ | ____ ; 07
     dc __ | __ | ____ ; 08
     dc      YY | XX_X ; 09 <
     dc      __ | ____ ; 10
     dc      __ | ____ ; 11
     dc      YY | XXXX ; 12 <
     dc      __ | ____ ; 13
     dc      __ | ____ ; 14
     dc           X_XX ; 15 <
     dc           ____ ; 16
     dc           ____ ; 17
     dc           XXX_ ; 18 <
;     dc           ____ ; 19
;     dc           ____ ; 20


__CHAR_AMOEBA_0

     dc __ | _Y | ____ ; 00 <
     dc __ | _Y | ____ ; 01
     dc XX | YY | XXXX ; 02
     dc __ | _Y | ____ ; 03 <
     dc __ | _Y | _X__ ; 04
     dc XX | YY | XXXX ; 05
     dc __ | __ | ___X ; 06 <
     dc __ | __ | ____ ; 07
     dc XX | YY | XXXX ; 08
     dc      __ | ___X ; 09 <
     dc      __ | _X__ ; 10
     dc      YY | XXXX ; 11
     dc      __ | ____ ; 12 <
     dc      __ | XXX_ ; 13
     dc      YY | XXXX ; 14
     dc           ____ ; 15 <
     dc           _X__ ; 16
     dc           XXXX ; 17
     dc           ____ ; 18 <
     dc           ____ ; 19
     dc           XXXX ; 20


__CHAR_AMOEBA_2

     dc X_ | __ | __X_ ; 00 <
     dc __ | __ | _XXX ; 01
     dc XX | YY | XX_X ; 02
     dc __ | __ | __X_ ; 03 <
     dc __ | __ | _XXX ; 04
     dc XX | YY | XX_X ; 05
     dc __ | __ | __X_ ; 06 <
     dc __ | __ | __X_ ; 07
     dc XX | YY | XX_X ; 08
     dc      __ | ____ ; 09 <
     dc      __ | ____ ; 10
     dc      YY | XXXX ; 11
     dc      __ | ____ ; 12 <
     dc      Y_ | ___X ; 13
     dc      YY | XXXX ; 14
     dc           ____ ; 15 <
     dc           ____ ; 16
     dc           XXXX ; 17
     dc           ____ ; 18 <
     dc           ____ ; 19
     dc           XXXX ; 20


__CHAR_AMOEBA_3

     dc __ | __ | _X__ ; 00 < <--
     dc __ | __ | _X__ ; 01 <--
     dc XX | YY | X_XX ; 02 <-- raised small square
     dc __ | Y_ | _X__ ; 03 < <--
     dc __ | Y_ | _X__ ; 04 <--
     dc XX | YY | X_XX ; 05
     dc _X | __ | ____ ; 06 <
     dc __ | _Y | ____ ; 07
     dc XX | YY | XXXX ; 08
     dc      __ | ____ ; 09 <
     dc      __ | __X_ ; 10
     dc      YY | XXXX ; 11
     dc      __ | ____ ; 12 <
     dc      __ | _XXX ; 13
     dc      YY | XXXX ; 14
     dc           ____ ; 15 <
     dc           _XXX ; 16
     dc           XXXX ; 17
     dc           ____ ; 18 <
     dc           __X_ ; 19
     dc           XXXX ; 20


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
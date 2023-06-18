; Character set definitions

CHAR_BLOCK_START

;CHARSET_START

oooo = %00000000
oooX = %00000001
ooXo = %00000010
ooXX = %00000011
oXoo = %00000100
oXoX = %00000101
oXXo = %00000110
oXXX = %00000111
XooO = %00001000
XooX = %00001001
XoXo = %00001010
XoXX = %00001011
XXoo = %00001100
XXoX = %00001101
XXXo = %00001110
XXXX = %00001111

ooooO = %00000000
ooooX = %00000001
oooXo = %00000010
oooXX = %00000011
ooXoo = %00000100
ooXoX = %00000101
ooXXo = %00000110
ooXXX = %00000111
oXooO = %00001000
oXooX = %00001001
oXoXo = %00001010
oXoXX = %00001011
oXXoo = %00001100
oXXoX = %00001101
oXXXo = %00001110
oXXXX = %00001111

Xoooo = %00010000
XoooX = %00010001
XooXo = %00010010
XooXX = %00010011
XoXoo = %00010100
XoXoX = %00010101
XoXXo = %00010110
XoXXX = %00010111
XXooO = %00011000
XXooX = %00011001
XXoXo = %00011010
XXoXX = %00011011
XXXoo = %00011100
XXXoX = %00011101
XXXXo = %00011110
XXXXX = %00011111


oo = %00000000
oX = %00010000
Xo = %00100000
XX = %00110000

oo = %00000000
oY = %01000000
Yo = %10000000
YY = %11000000



_CHAR_LADDER_0

    dc XX | oo | XXXX ; 00 <
    dc XX | YY | XXXX ; 01
    dc oo | YY | XXXX ; 02
    dc oo | oo | XooX ; 03 <
    dc XX | YY | XooX ; 04
    dc oo | oY | XooX ; 05
    dc oo | oo | XooX ; 06 <
    dc XX | YY | XooX ; 07
    dc oo | oo | XooX ; 08
    dc      oo | XooX ; 09 <
    dc      YY | XooX ; 10
    dc      oo | XooX ; 11
    dc      oo | XooX ; 12 <
    dc      YY | XooX ; 13
    dc      oo | XooX ; 14
    dc           XooX ; 15 <
    dc           XooX ; 16
    dc           XooX ; 17
    dc           XooX ; 18 <
    dc           XooX ; 19
    dc           XooX ; 20


_CHAR_LADDER_1

    dc XX | oo | XooX ; 00 <
    dc XX | YY | XooX ; 01
    dc oo | YY | XooX ; 02
    dc oo | oo | XooX ; 03 <
    dc XX | YY | XooX ; 04
    dc oo | oY | XooX ; 05
    dc oo | oo | XooX ; 06 <
    dc XX | YY | XXXX ; 07
    dc oo | oo | XXXX ; 08
    dc      oo | XXXX ; 09 <
    dc      YY | XooX ; 10
    dc      oo | XooX ; 11
    dc      oo | XooX ; 12 <
    dc      YY | XooX ; 13
    dc      oo | XooX ; 14
    dc           XooX ; 15 <
    dc           XooX ; 16
    dc           XooX ; 17
    dc           XooX ; 18 <
    dc           XooX ; 19
    dc           XooX ; 20

_CHAR_LADDER_2

    dc XX | oo | XooX ; 00 <
    dc XX | YY | XooX ; 01
    dc oo | YY | XooX ; 02
    dc oo | oo | XooX ; 03 <
    dc XX | YY | XooX ; 04
    dc oo | oY | XooX ; 05
    dc oo | oo | XooX ; 06 <
    dc XX | YY | XooX ; 07
    dc oo | oo | XooX ; 08
    dc      oo | XooX ; 09 <
    dc      YY | XooX ; 10
    dc      oo | XooX ; 11
    dc      oo | XooX ; 12 <
    dc      YY | XooX ; 13
    dc      oo | XXXX ; 14
    dc           XXXX ; 15 <
    dc           XXXX ; 16
    dc           XooX ; 17
    dc           XooX ; 18 <
    dc           XooX ; 19
    dc           XooX ; 20


_CHAR_ROCK
_CHAR_ROCK_SHAKE

    dc ooXXo ; 00 <
    dc ooooO ; 01
    dc ooXXo ; 02
    dc ooooO ; 03 <
    dc ooooO ; 04
    dc oXXXo ; 05
    dc ooooO ; 06 <
    dc ooooX ; 07
    dc oXXXX ; 08
    dc ooooX ; 09 <
    dc ooooO ; 10
    dc XXXXX ; 11
    dc ooooX ; 12 <
    dc ooooO ; 13
    dc XXXXX ; 14
    dc ooooX ; 15 <
    dc ooooO ; 16
    dc XXXXX ; 17
    dc ooooX ; 18 <
    dc ooooO ; 19
    dc XXXXX ; 20
    dc ooooX ; 21 <
    dc ooooO ; 22
    dc XXXXX ; 23
    dc ooooX ; 24 <
    dc ooooO ; 25
    dc XXXXX ; 26
    dc oooXo ; 27 <
    dc ooooO ; 28
    dc oXXXo ; 29


_CHAR_GEODOGE

    dc ooXXo ; 00 <
    dc ooXXo ; 01
    dc ooooO ; 02
    dc ooooO ; 03 <
    dc oXXXo ; 04
    dc ooooO ; 05
    dc ooooO ; 06 <
    dc oXXXX ; 07
    dc ooooX ; 08
    dc ooooX ; 09 <
    dc XXXXX ; 10
    dc ooXoX ; 11
    dc ooooX ; 12 <
    dc XXXXX ; 13
    dc oXXXo ; 14
    dc ooooX ; 15 <
    dc XXXXX ; 16
    dc oXXXo ; 17
    dc ooooX ; 18 <
    dc XXXXX ; 19
    dc oXXXo ; 20
    dc ooooX ; 21 <
    dc XXXXX ; 22
    dc ooXoo ; 23
    dc ooooX ; 24 <
    dc XXXXX ; 25
    dc ooooO ; 26
    dc oooXo ; 27 <
    dc oXXXo ; 28
    dc ooooO ; 29




_CHAR_ROCK_U

    dc ooooO ; 00 <
    dc XXoXX ; 01
    dc ooXoo ; 02
    dc ooooO ; 03 <
    dc XXoXX ; 04
    dc ooXoo ; 05
    dc ooooX ; 06 <
    dc XXoXX ; 07
    dc ooXoo ; 08
    dc ooooX ; 09 <
    dc XXXXX ; 10
    dc ooXoo ; 11
    dc ooooO ; 12 <
    dc XXXXX ; 13
    dc oXXXo ; 14
    dc ooooO ; 15 <
    dc XXXXX ; 16
    dc oXXXo ; 17
    dc ooooO ; 18 <
    dc XXXXX ; 19
    dc oXXXo ; 20
    dc ooooX ; 21 <
    dc XXXXX ; 22
    dc ooXoo ; 23
    dc ooooX ; 24 <
    dc XXXXX ; 25
    dc ooooO ; 26
    dc oooXo ; 27 <
    dc oXXXo ; 28
    dc ooooO ; 29



_CHAR_ROCK_R

    dc ooXXX ; 00 <
    dc ooXXX ; 01
    dc ooooO ; 02
    dc ooooO ; 03 <
    dc oXXXX ; 04
    dc ooooO ; 05
    dc ooooO ; 06 <
    dc oXXXX ; 07
    dc ooooO ; 08
    dc ooooO ; 09 <
    dc XXXXX ; 10
    dc ooXoo ; 11
    dc ooooO ; 12 <
    dc XXXXo ; 13
    dc oXXXX ; 14
    dc ooooO ; 15 <
    dc XXXXo ; 16
    dc oXXXX ; 17
    dc ooooO ; 18 <
    dc XXXXo ; 19
    dc oXXXX ; 20
    dc ooooO ; 21 <
    dc XXXXX ; 22
    dc ooXoo ; 23
    dc ooooO ; 24 <
    dc XXXXX ; 25
    dc ooooO ; 26
    dc ooooO ; 27 <
    dc oXXXX ; 28
    dc ooooO ; 29


_CHAR_ROCK_D

    dc ooXXo ; 00 <
    dc ooXXo ; 01
    dc ooooO ; 02
    dc ooooO ; 03 <
    dc oXXXo ; 04
    dc ooooO ; 05
    dc ooooO ; 06 <
    dc oXXXX ; 07
    dc ooooX ; 08
    dc ooooX ; 09 <
    dc XXXXX ; 10
    dc ooXoo ; 11
    dc ooooO ; 12 <
    dc XXXXX ; 13
    dc oXXXo ; 14
    dc ooooO ; 15 <
    dc XXXXX ; 16
    dc oXXXo ; 17
    dc ooooO ; 18 <
    dc XXXXX ; 19
    dc oXXXo ; 20
    dc ooooO ; 21 <
    dc XXXXX ; 22
    dc ooXoo ; 23
    dc ooooO ; 24 <
    dc XXoXX ; 25
    dc ooXoo ; 26
    dc ooooO ; 27 <
    dc XXoXX ; 28
    dc ooXoo ; 29



_CHAR_ROCK_L

    dc XXXXo ; 00 <
    dc XXXXo ; 01
    dc ooooO ; 02
    dc ooooO ; 03 <
    dc XXXXo ; 04
    dc ooooO ; 05
    dc ooooO ; 06 <
    dc XXXXX ; 07
    dc ooooX ; 08
    dc ooooX ; 09 <
    dc XXXXX ; 10
    dc ooXoo ; 11
    dc ooooO ; 12 <
    dc oXXXX ; 13
    dc XXXXo ; 14
    dc ooooO ; 15 <
    dc oXXXX ; 16
    dc XXXXo ; 17
    dc ooooO ; 18 <
    dc oXXXX ; 19
    dc XXXXo ; 20
    dc ooooX ; 21 <
    dc XXXXX ; 22
    dc ooXoo ; 23
    dc ooooX ; 24 <
    dc XXXXX ; 25
    dc ooooO ; 26
    dc oooXo ; 27 <
    dc XXXXo ; 28
    dc ooooO ; 29



_CHAR_ROCK_UR

    dc ooooO ; 00 <
    dc XXoXX ; 01
    dc ooXoo ; 02
    dc ooooO ; 03 <
    dc XXoXX ; 04
    dc ooXoo ; 05
    dc ooooO ; 06 <
    dc XXoXX ; 07
    dc ooXoo ; 08
    dc ooooO ; 09 <
    dc XXXXX ; 10
    dc ooXoo ; 11
    dc ooooO ; 12 <
    dc XXXXo ; 13
    dc oXXXX ; 14
    dc ooooO ; 15 <
    dc XXXXo ; 16
    dc oXXXX ; 17
    dc ooooO ; 18 <
    dc XXXXo ; 19
    dc oXXXX ; 20
    dc ooooO ; 21 <
    dc XXXXX ; 22
    dc ooXoo ; 23
    dc ooooO ; 24 <
    dc XXXXX ; 25
    dc ooooO ; 26
    dc ooooO ; 27 <
    dc oXXXX ; 28
    dc ooooO ; 29



_CHAR_ROCK_UD

    dc ooooX ; 00 <
    dc XXoXX ; 01
    dc ooXoo ; 02
    dc ooooX ; 03 <
    dc XXoXX ; 04
    dc ooXoo ; 05
    dc ooooO ; 06 <
    dc XXoXX ; 07
    dc ooXoo ; 08
    dc ooooO ; 09 <
    dc XXXXX ; 10
    dc ooXoo ; 11
    dc ooooO ; 12 <
    dc XXXXX ; 13
    dc oXXXo ; 14
    dc ooooO ; 15 <
    dc XXXXX ; 16
    dc oXXXo ; 17
    dc ooooO ; 18 <
    dc XXXXX ; 19
    dc oXXXo ; 20
    dc ooooO ; 21 <
    dc XXXXX ; 22
    dc ooXoo ; 23
    dc ooooO ; 24 <
    dc XXoXX ; 25
    dc ooXoo ; 26
    dc ooooO ; 27 <
    dc XXoXX ; 28
    dc ooXoo ; 29


_CHAR_ROCK_UL

    dc ooooO ; 00 <
    dc XXoXX ; 01
    dc ooXoo ; 02
    dc ooooO ; 03 <
    dc XXoXX ; 04
    dc ooXoo ; 05
    dc ooooO ; 06 <
    dc XXoXX ; 07
    dc ooXoo ; 08
    dc ooooO ; 09 <
    dc XXXXX ; 10
    dc ooXoo ; 11
    dc ooooO ; 12 <
    dc oXXXX ; 13
    dc XXXXo ; 14
    dc ooooO ; 15 <
    dc oXXXX ; 16
    dc XXXXo ; 17
    dc ooooO ; 18 <
    dc oXXXX ; 19
    dc XXXXo ; 20
    dc ooooO ; 21 <
    dc XXXXX ; 22
    dc ooXoo ; 23
    dc ooooX ; 24 <
    dc XXXXX ; 25
    dc ooooO ; 26
    dc oooXo ; 27 <
    dc XXXXo ; 28
    dc ooooO ; 29


_CHAR_ROCK_RD

    dc ooXXX ; 00 <
    dc ooXXX ; 01
    dc ooooO ; 02
    dc ooooO ; 03 <
    dc oXXXX ; 04
    dc ooooO ; 05
    dc ooooO ; 06 <
    dc oXXXX ; 07
    dc ooooO ; 08
    dc ooooO ; 09 <
    dc XXXXX ; 10
    dc ooXoo ; 11
    dc ooooO ; 12 <
    dc XXXXo ; 13
    dc oXXXX ; 14
    dc ooooO ; 15 <
    dc XXXXo ; 16
    dc oXXXX ; 17
    dc ooooO ; 18 <
    dc XXXXo ; 19
    dc oXXXX ; 20
    dc ooooO ; 21 <
    dc XXXXX ; 22
    dc ooXoo ; 23
    dc ooooO ; 24 <
    dc XXoXX ; 25
    dc ooXoo ; 26
    dc ooooO ; 27 <
    dc XXoXX ; 28
    dc ooXoo ; 29


_CHAR_ROCK_RL

    dc XXXXX ; 00 <
    dc XXXXX ; 01
    dc ooooO ; 02
    dc ooooO ; 03 <
    dc XXXXX ; 04
    dc ooooO ; 05
    dc ooooO ; 06 <
    dc XXXXX ; 07
    dc ooooO ; 08
    dc ooooO ; 09 <
    dc XXXXX ; 10
    dc ooXoo ; 11
    dc ooooO ; 12 <
    dc oXXXo ; 13
    dc XXXXX ; 14
    dc ooooO ; 15 <
    dc oXXXo ; 16
    dc XXXXX ; 17
    dc ooooO ; 18 <
    dc oXXXo ; 19
    dc XXXXX ; 20
    dc ooooO ; 21 <
    dc XXXXX ; 22
    dc ooXoo ; 23
    dc ooooO ; 24 <
    dc XXXXX ; 25
    dc ooooO ; 26
    dc ooooO ; 27 <
    dc XXXXX ; 28
    dc ooooO ; 29

_CHAR_ROCK_DL

    dc XXXXo ; 00 <
    dc XXXXo ; 01
    dc ooooO ; 02
    dc ooooO ; 03 <
    dc XXXXo ; 04
    dc ooooO ; 05
    dc ooooO ; 06 <
    dc XXXXX ; 07
    dc ooooX ; 08
    dc ooooX ; 09 <
    dc XXXXX ; 10
    dc ooXoo ; 11
    dc ooooO ; 12 <
    dc oXXXX ; 13
    dc XXXXo ; 14
    dc ooooO ; 15 <
    dc oXXXX ; 16
    dc XXXXo ; 17
    dc ooooO ; 18 <
    dc oXXXX ; 19
    dc XXXXo ; 20
    dc ooooO ; 21 <
    dc XXXXX ; 22
    dc ooXoo ; 23
    dc ooooO ; 24 <
    dc XXoXX ; 25
    dc ooXoo ; 26
    dc ooooO ; 27 <
    dc XXoXX ; 28
    dc ooXoo ; 29


_CHAR_ROCK_URD

    dc Xoooo ; 00 <
    dc XXoXX ; 01
    dc XoXoo ; 02
    dc Xoooo ; 03 <
    dc XXoXX ; 04
    dc XoXoo ; 05
    dc Xoooo ; 06 <
    dc XXoXX ; 07
    dc XoXoo ; 08
    dc Xoooo ; 09 <
    dc XXXXX ; 10
    dc ooXoo ; 11
    dc ooooO ; 12 <
    dc XXXXo ; 13
    dc oXXXX ; 14
    dc ooooO ; 15 <
    dc XXXXo ; 16
    dc oXXXX ; 17
    dc ooooO ; 18 <
    dc XXXXo ; 19
    dc oXXXX ; 20
    dc ooooO ; 21 <
    dc XXXXX ; 22
    dc ooXoo ; 23
    dc ooooO ; 24 <
    dc XXoXX ; 25
    dc ooXoo ; 26
    dc ooooO ; 27 <
    dc XXoXX ; 28
    dc ooXoo ; 29


_CHAR_ROCK_URL

    dc ooooO ; 00 <
    dc XXoXX ; 01
    dc ooXoo ; 02
    dc ooooO ; 03 <
    dc XXoXX ; 04
    dc ooXoo ; 05
    dc ooooO ; 06 <
    dc XXoXX ; 07
    dc ooXoo ; 08
    dc ooooO ; 09 <
    dc XXXXX ; 10
    dc ooXoo ; 11
    dc ooooO ; 12 <
    dc oXXXo ; 13
    dc XXXXX ; 14
    dc ooooO ; 15 <
    dc oXXXo ; 16
    dc XXXXX ; 17
    dc ooooO ; 18 <
    dc oXXXo ; 19
    dc XXXXX ; 20
    dc ooooO ; 21 <
    dc XXXXX ; 22
    dc ooXoo ; 23
    dc ooooO ; 24 <
    dc XXXXX ; 25
    dc ooooO ; 26
    dc ooooO ; 27 <
    dc XXXXX ; 28
    dc ooooO ; 29

_CHAR_ROCK_UDL

    dc ooooO ; 00 <
    dc XXoXX ; 01
    dc ooXoo ; 02
    dc ooooO ; 03 <
    dc XXoXX ; 04
    dc ooXoX ; 05
    dc ooooX ; 06 <
    dc XXoXX ; 07
    dc ooXoX ; 08
    dc ooooX ; 09 <
    dc XXXXX ; 10
    dc ooXoo ; 11
    dc ooooO ; 12 <
    dc oXXXX ; 13
    dc XXXXo ; 14
    dc ooooO ; 15 <
    dc oXXXX ; 16
    dc XXXXo ; 17
    dc ooooO ; 18 <
    dc oXXXX ; 19
    dc XXXXo ; 20
    dc ooooO ; 21 <
    dc XXXXX ; 22
    dc ooXoo ; 23
    dc ooooO ; 24 <
    dc XXoXX ; 25
    dc ooXoo ; 26
    dc ooooO ; 27 <
    dc XXoXX ; 28
    dc ooXoo ; 29

_CHAR_ROCK_RDL

    dc XXXXX ; 00 <
    dc XXXXX ; 01
    dc ooooO ; 02
    dc ooooO ; 03 <
    dc XXXXX ; 04
    dc ooooO ; 05
    dc ooooO ; 06 <
    dc XXXXX ; 07
    dc ooooO ; 08
    dc ooooO ; 09 <
    dc XXXXX ; 10
    dc ooXoo ; 11
    dc ooooO ; 12 <
    dc oXXXo ; 13
    dc XXXXX ; 14
    dc ooooO ; 15 <
    dc oXXXo ; 16
    dc XXXXX ; 17
    dc ooooO ; 18 <
    dc oXXXo ; 19
    dc XXXXX ; 20
    dc ooooO ; 21 <
    dc XXXXX ; 22
    dc ooXoo ; 23
    dc ooooO ; 24 <
    dc XXoXX ; 25
    dc ooXoo ; 26
    dc ooooO ; 27 <
    dc XXoXX ; 28
    dc ooXoo ; 29

_CHAR_ROCK_URDL

    dc ooooO ; 00 <
    dc XXoXX ; 01
    dc ooXoo ; 02
    dc ooooO ; 03 <
    dc XXoXX ; 04
    dc ooXoo ; 05
    dc ooooO ; 06 <
    dc XXoXX ; 07
    dc ooXoo ; 08
    dc ooooO ; 09 <
    dc XXXXX ; 10
    dc ooXoo ; 11
    dc ooooO ; 12 <
    dc oXXXo ; 13
    dc XXoXX ; 14
    dc ooooO ; 15 <
    dc oXXXo ; 16
    dc XXoXX ; 17
    dc ooooO ; 18 <
    dc oXXXo ; 19
    dc XXoXX ; 20
    dc ooooO ; 21 <
    dc XXXXX ; 22
    dc ooXoo ; 23
    dc ooooO ; 24 <
    dc XXoXX ; 25
    dc ooXoo ; 26
    dc ooooO ; 27 <
    dc XXoXX ; 28
    dc ooXoo ; 29

_CHAR_ROCK_URDL2

    dc ooooO ; 00 <
    dc XXoXX ; 01
    dc ooXoo ; 02
    dc ooooO ; 03 <
    dc XXoXX ; 04
    dc ooXoo ; 05
    dc ooooO ; 06 <
    dc XXoXX ; 07
    dc ooXoo ; 08
    dc ooooO ; 09 <
    dc XXoXX ; 10
    dc ooXoo ; 11
    dc ooooO ; 12 <
    dc ooooO ; 13
    dc XXXXX ; 14
    dc ooooO ; 15 <
    dc ooooO ; 16
    dc XXXXX ; 17
    dc ooooO ; 18 <
    dc ooooO ; 19
    dc XXXXX ; 20
    dc ooooO ; 21 <
    dc XXoXX ; 22
    dc ooXoo ; 23
    dc ooooO ; 24 <
    dc XXoXX ; 25
    dc ooXoo ; 26
    dc ooooO ; 27 <
    dc XXoXX ; 28
    dc ooXoo ; 29

;        ooXXXooO,ooXXXooO,oooooooo,
;        oXXXXXoo,oXXoXXoo,oooXoooo,
;        oXXXXXoo,oXoooXoo,ooXXXooO,
;        oXXXXXoo,oXoooXoo,ooXXXooO,
;        oXXXXXoo,oXoooXoo,ooXXXooO,
;        oXXXXXoo,oXoooXoo,ooXXXooO,
;        oXXXXXoo,oXoooXoo,ooXXXooO,
;        oXXXXXoo,oXXoXXoo,oooXoooo,
;        ooXXXooO,ooXXXooO,oooooooo,
;    },

;    {  27,
;        oooooooo,oooooooo,oooooooo,
;        oooooooo,oooooooo,oooooooo,
;        oooXoooo,oooXoooo,oooooooo,
;        ooXXXooO,ooXXXooO,oooooooo,
;        ooXoXooO,ooXXXooO,oooooooo,
;        ooXoXooO,ooXXXooO,oooooooo,
;        ooXXXooO,ooXXXooO,oooooooo,
;        oooXoooo,oooXoooo,oooooooo,
;        oooooooo,oooooooo,oooooooo,
;    },



;CHARSET_END

;CHARSET_START
CHAR_BLOCK2_START



_CHAR_SPARKLE_0

;     dc Xo | oo | oooo ; 00 <
;     dc Xo | oo | oooo ; 01
;     dc oo | oo | oooo ; 02
;     dc oX | Yo | oooo ; 03 <
;     dc oX | Yo | XooO ; 04
;     dc oo | oo | XooO ; 05
;     dc oo | oo | XooO ; 06 <
;     dc oo | oo | XooO ; 07
;     dc oo | oo | oooo ; 08
;     dc      oo | oooo ; 09 <
;     dc      oo | oooo ; 10
;     dc      oo | oooo ; 11
;     dc      oo | oooo ; 12 <
;     dc      oo | oooo ; 13
;    dc      oo | oooo ; 14
;    dc           oooo ; 15 <
;    dc           oooo ; 16
;    dc           oooo ; 17
;    dc           oooo ; 18 <
;    dc           oooo ; 19
;    dc           oooo ; 20


_CHAR_SPARKLE_1

;     dc oo | oo | oooo ; 00 <
;     dc oo | oo | oooo ; 01
;     dc oo | oo | oooo ; 02
;     dc Xo | oo | oooo ; 03 <
;     dc Xo | oo | oooo ; 04
;     dc oo | oo | oooo ; 05
;     dc oX | oo | oooo ; 06 <
;     dc oX | oo | oooX ; 07
;     dc oo | oo | oooX ; 08
;     dc      oY | oooX ; 09 <
;     dc      oY | oooX ; 10
;    dc      oo | oooo ; 11
;    dc      oo | oooo ; 12 <
;    dc      oo | oooo ; 13
;    dc      oo | oooo ; 14
;    dc           oooo ; 15 <
;    dc           oooo ; 16
;    dc           oooo ; 17
;    dc           oooo ; 18 <
;    dc           oooo ; 19
;    dc           oooo ; 20


_CHAR_SPARKLE_2

    dc oX | oo | oooo ; 00 <
    dc oX | oo | oooo ; 01
    dc oo | oo | oooo ; 02
    dc oo | oo | oooo ; 03 <
    dc oo | oo | oooo ; 04
    dc oo | oo | oooo ; 05
    dc Xo | oo | oooo ; 06 <
    dc Xo | oo | oooo ; 07
    dc oo | oo | oooo ; 08
    dc      oo | oooo ; 09 <
    dc      oo | oooo ; 10
    dc      oo | oooo ; 11
    dc      Yo | oooo ; 12 <
    dc      Yo | oXoo ; 13
    dc      oo | oXoo ; 14
    dc           oXoo ; 15 <
    dc           oXoo ; 16
;    dc           oooo ; 17
;    dc           oooo ; 18 <
;    dc           oooo ; 19
;    dc           oooo ; 20


_CHAR_SPARKLE_3

    dc oo | oY | oooo ; 00 <
    dc oo | oY | oooo ; 01
    dc oo | oo | oooo ; 02
    dc oo | oo | oooo ; 03 <
    dc oo | oo | oooo ; 04
    dc oo | oo | oooo ; 05
    dc oo | oo | oooo ; 06 <
    dc oo | oo | oooo ; 07
    dc oo | oo | oooo ; 08
    dc      oo | oooo ; 09 <
    dc      oo | oooo ; 10
    dc      oo | oooo ; 11
    dc      oo | oooo ; 12 <
    dc      oo | oooo ; 13
    dc      oo | oooo ; 14
    dc           oooo ; 15 <
    dc           ooXo ; 16
    dc           ooXo ; 17
    dc           ooXo ; 18 <
    dc           ooXo ; 19
;    dc           oooo ; 20




_CHAR_PEBBLE2

     dc XXXXX ; 00 <
     dc ooooO ; 01
     dc ooooO ; 02
     dc XXXXX ; 03 <
     dc ooooO ; 04
     dc ooooO ; 05
     dc XXXXX ; 06 <
     dc ooooO ; 07
     dc ooooO ; 08
     dc XXXXX ; 09 <
     dc ooooO ; 10
     dc ooooO ; 11
     dc XXXXX ; 12 <
     dc ooooO ; 13
     dc ooooO ; 14
     dc XXXXX ; 15 <
     dc ooooO ; 16
     dc oXooO ; 17
     dc XXXXX ; 18 <
     dc ooooO ; 19
     dc oXooO ; 20
     dc XXXXX ; 21 <
     dc ooooO ; 22
     dc ooooO ; 23
     dc XXXXX ; 24 <
     dc ooooO ; 25
     dc ooooO ; 26
     dc XXXXX ; 27 <
     dc ooooO ; 28
     dc ooooO ; 29


_CHAR_STEELWALL

     dc XXXXX ; 00 <
     dc ooooO ; 01
     dc XXXXX ; 02
     dc XXXXX ; 03 <
     dc XoXoX ; 04
     dc XXXXX ; 05
     dc XXXXX ; 06 <
     dc ooooO ; 07
     dc oXoXo ; 08
     dc XXXXX ; 09 <
     dc ooooO ; 10
     dc XXXXX ; 11
     dc XXXXX ; 12 <
     dc XXoXo ; 13
     dc XXXXX ; 14
     dc XXXXX ; 15 <
     dc ooooO ; 16
     dc ooXoX ; 17
     dc XXXXX ; 18 <
     dc ooooO ; 19
     dc XXXXX ; 20
     dc XXXXX ; 21 <
     dc XoXoX ; 22
     dc XXXXX ; 23
     dc XXXXX ; 24 <
     dc ooooO ; 25
     dc oXoXo ; 26
     dc XXXXX ; 27 <
     dc ooooO ; 28
     dc XXXXX ; 29



_CHAR_DIRT

    dc XXXXX ; 00 <
    dc ooooO ; 01
    dc ooooO ; 02
    dc XXXXX ; 03 <
    dc ooooO ; 04
    dc ooooO ; 05
    dc XXXXX ; 06 <
    dc ooooO ; 07
    dc ooooO ; 08
    dc XXXXX ; 09 <
    dc ooooO ; 10
    dc ooooO ; 11
    dc XXXXX ; 12 <
    dc ooooO ; 13
    dc ooooO ; 14
    dc XXXXX ; 15 <
    dc ooooO ; 16
    dc ooooO ; 17
    dc XXXXX ; 18 <
    dc ooooO ; 19
    dc ooooO ; 20
    dc XXXXX ; 21 <
    dc ooooO ; 22
    dc ooooO ; 23
    dc XXXXX ; 24 <
    dc ooooO ; 25
    dc ooooO ; 26
    dc XXXXX ; 27 <
    dc ooooO ; 28
    dc ooooO ; 29


_CHAR_BRICKWALL

     dc Xo | oY | oooo ; 00 <
     dc Xo | oY | XXXo ; 01
     dc XX | YY | XXXX ; 02
     dc oX | Yo | XXXo ; 03 <
     dc oX | Yo | XXXo ; 04
     dc XX | YY | XXXX ; 05
     dc Xo | oo | XXXo ; 06 <
     dc Xo | oY | XXXo ; 07
     dc XX | YY | XXXX ; 08
     dc      oY | XXXo ; 09 <
     dc      oY | oooo ; 10
     dc      YY | XXXX ; 11
     dc      Yo | XoXX ; 12 <
     dc      Yo | XoXX ; 13
     dc      YY | XXXX ; 14
     dc           XoXX ; 15 <
     dc           XoXX ; 16
     dc           XXXX ; 17
     dc           XoXX ; 18 <
     dc           XoXX ; 19
     dc           XXXX ; 20
     dc           XoXX ; 21 <
     dc           XoXX ; 22
     dc           XXXX ; 23
     dc           oooo ; 24
     dc           oooo ; 25
     dc           oooo ; 26
     dc           oooo ; 27
     dc           oooo ; 28
     dc           oooo ; 29









_CHAR_EXPLODETO_0

    ;  dc oo | oY | ooXo ; 00 <
    ;  dc XX | oY | XoXo ; 01
    ;  dc oo | oY | XoXo ; 02
    ;  dc XX | oo | XooO ; 03 <
    ;  dc XX | Yo | oooo ; 04
    ;  dc oo | Yo | oooo ; 05
    ;  dc XX | YY | ooXo ; 06 <
    ;  dc oo | oY | ooXo ; 07
    ;  dc oo | YY | ooXo ; 08
    ;  dc      Yo | oooo ; 09 <
    ;  dc      Yo | ooXo ; 10
    ;  dc      oo | XoXo ; 11
    ;  dc      oo | XoXo ; 12 <
    ;  dc      oo | XooO ; 13
    ;  dc      oo | oooX ; 14
    ;  dc           oooX ; 15 <
    ;  dc           oXoX ; 16
    ;  dc           oXoo ; 17
    ;  dc           oXoX ; 18 <
    ;  dc           oooX ; 19
    ;  dc           oooX ; 20





_CHAR_EXPLODETO_1

    ;  dc XX | oo | oooo ; 00 <
    ;  dc oo | Yo | oXoo ; 01
    ;  dc oo | Yo | oXoo ; 02
    ;  dc oo | Yo | oXoX ; 03 <
    ;  dc XX | oY | oooX ; 04
    ;  dc XX | oY | oooX ; 05
    ;  dc oo | oY | ooXo ; 06 <
    ;  dc XX | oo | XoXo ; 07
    ;  dc oo | oo | XoXo ; 08
    ;  dc      oY | XooO ; 09 <
    ;  dc      oY | oooo ; 10
    ;  dc      oY | oooo ; 11
    ;  dc      oo | ooXo ; 12 <
    ;  dc      oo | ooXo ; 13
    ;  dc      oo | ooXo ; 14
    ;  dc           oooo ; 15 <
    ;  dc           ooXo ; 16
    ;  dc           XoXo ; 17
    ;  dc           XoXo ; 18 <
    ;  dc           XooO ; 19
;     dc           oooo ; 20




_CHAR_EXPLODETO_3

     dc XX | oY | oooo ; 00 <
     dc XX | oY | XooO ; 01
     dc XX | oY | XooO ; 02
     dc oo | oo | XooO ; 03 <
     dc XX | oo | oooo ; 04
     dc oo | oo | oooo ; 05
     dc XX | oY | ooXo ; 06 <
     dc XX | oY | ooXo ; 07
     dc oo | oY | ooXo ; 08
     dc      oo | oooo ; 09 <
     dc      oo | ooXo ; 10
     dc      oo | ooXo ; 11
     dc      oo | ooXo ; 12 <
     dc      oo | oooo ; 13
     dc      oo | oooX ; 14
     dc           oooX ; 15 <
     dc           oXoX ; 16
     dc           oXoo ; 17
     dc           oXoo ; 18 <
;     dc           oooo ; 19
;     dc           oooo ; 20




_CHAR_EXPLODETO_4

     dc oo | oo | oooo ; 00 <
     dc oo | oo | oooo ; 01
     dc oo | oo | oooo ; 02
     dc XX | oo | oooo ; 03 <
     dc XX | oo | ooXo ; 04
     dc oo | oY | ooXo ; 05
     dc oo | oY | ooXo ; 06 <
     dc XX | oY | oooo ; 07
     dc oo | oo | oooo ; 08
     dc      oo | oooo ; 09 <
     dc      oo | ooXo ; 10
     dc      oo | XoXo ; 11
     dc      oo | XoXo ; 12 <
     dc      oo | XooO ; 13
     dc      oo | oooo ; 14
     dc           oooo ; 15 <
     dc           oooo ; 16
     dc           oooo ; 17
     dc           oooX ; 18 <
     dc           oooX ; 19
     dc           oooX ; 20




_CHAR_EXPLODETO_2

     dc XX | oo | ooXo ; 00 <
     dc XX | oo | ooXo ; 01
     dc oo | oY | ooXo ; 02
     dc XX | oY | oooo ; 03 <
     dc oo | oY | ooXo ; 04
     dc XX | Yo | XoXo ; 05
     dc XX | Yo | XoXo ; 06 <
     dc XX | Yo | XooO ; 07
     dc oo | oo | oooo ; 08
     dc      Yo | oooo ; 09 <
     dc      Yo | ooXo ; 10
     dc      Yo | XoXo ; 11
     dc      oo | XoXo ; 12 <
     dc      oo | XooO ; 13
     dc      oo | oooX ; 14
     dc           oooX ; 15 <
     dc           oXoX ; 16
     dc           oXoo ; 17
     dc           oXoX ; 18 <
     dc           oooX ; 19
     dc           oooX ; 20





; _CHAR_DIRT_GRABBED

;      dc XX | oo | oooo ; 00 <
;      dc oo | oo | oooo ; 01
;      dc oo | oo | oooo ; 02
;      dc XX | oY | oXXo ; 03 <
;      dc oo | oo | oooo ; 04
;      dc oo | oo | oooo ; 05
;      dc XX | oo | ooXo ; 06 <
;      dc oo | oo | oooo ; 07
;      dc oo | oo | oooo ; 08
;      dc      Yo | oXXo ; 09 <
;      dc      oo | oooo ; 10
;      dc      oo | oooo ; 11
;      dc      oo | oXXo ; 12 <
;      dc      oo | oooo ; 13
;      dc      oo | oooo ; 14
;      dc           oXoo ; 15 <
;      dc           oooo ; 16
;      dc           oooo ; 17
;      dc           oooo ; 18 <
;      dc           oooo ; 19
;      dc           oooo ; 20



_CHAR_DUST_ROCK_0
 dc 0
_CHAR_DUST_0

     dc ooooO ; 24 <
     dc ooooO ; 25
     dc ooooO ; 26
     dc ooooO ; 27 <
     dc ooooO ; 28
     dc ooooO ; 29
     dc oXooO ; 00 <
     dc ooooO ; 01
     dc ooooO ; 02
     dc XXXoo ; 03 <
     dc ooooO ; 04
     dc ooooO ; 05
     dc oXooO ; 06 <
     dc ooooO ; 07
     dc ooooO ; 08
     dc ooooO ; 09 <
     dc ooooO ; 10
     dc ooooO ; 11
     dc ooXoo ; 12 <
     dc ooooO ; 13
     dc ooooO ; 14
     dc oXXXo ; 15 <
     dc ooooO ; 16
     dc ooooO ; 17
     dc ooXoo ; 18 <
     dc ooooO ; 19
     dc ooooO ; 20
     dc ooooO ; 21 <
     dc ooooO ; 22
     dc ooooO ; 23

_CHAR_DUST_ROCK_1
 dc 0
_CHAR_DUST_1


     dc ooooO ; 27
     dc ooooO ; 28
     dc ooooO ; 29
     dc ooooO ; 27
     dc ooooO ; 28
     dc ooooO ; 29
     dc ooooO ; 00 <
     dc ooooO ; 01
     dc ooooO ; 02
     dc oXooO ; 03 <
     dc ooooO ; 04
     dc ooooO ; 05
     dc ooXoo ; 06 <
     dc ooooO ; 07
     dc ooooO ; 08
     dc oXXXo ; 09 <
     dc ooooO ; 10
     dc ooooO ; 11
     dc ooXoo ; 12 <
     dc ooooO ; 13
     dc ooooO ; 14
     dc ooooO ; 15 <
     dc ooooO ; 16
     dc ooooO ; 17
     dc ooXoo ; 18 <
     dc ooooO ; 19
     dc ooooO ; 20
     dc ooooO ; 21
     dc ooooO ; 22
     dc ooooO ; 23



_CHAR_DUST_ROCK_2
 dc 0

_CHAR_DUST_2



     dc ooooO ; 24
     dc ooooO ; 25 <
     dc ooooO ; 26
     dc ooooO ; 27
     dc ooooO ; 28 <
     dc ooooO ; 29
     dc ooooO ; 00 <
     dc ooooO ; 01
     dc ooooO ; 02
     dc ooooO ; 03 <
     dc ooooO ; 04
     dc ooooO ; 05
     dc ooooO ; 06 <
     dc ooooO ; 07
     dc ooooO ; 08
     dc ooXoo ; 09 <
     dc ooooO ; 10
     dc ooooO ; 11
     dc ooooO ; 12 <
     dc ooooO ; 13
     dc ooooO ; 14
     dc ooooO ; 15 <
     dc ooooO ; 16
     dc ooooO ; 17
     dc ooooO ; 18 <
     dc ooooO ; 19
     dc ooooO ; 20
     dc ooooO ; 21
     dc ooooO ; 22 <
     dc ooooO ; 23


;     dc           oooo ; 20

_CHAR_PARALLAXoTEMPLATE        ; squished in here - careful about count above/below chars

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
;        oooooooo, // 17
;        oooooooo, // 18
;        oooooooo, // 19
;        oooooooo, // 20


_CHAR_DUST_RIGHT_1
     dc ooooO ; 00 <
     dc ooooO ; 01
     dc ooooO ; 02
     dc ooooO ; 03 <
     dc ooooO ; 04
     dc ooooO ; 05
     dc ooooO ; 06 <
     dc ooooO ; 07
     dc ooooO ; 08
     dc ooooO ; 09 <
     dc ooooO ; 10
     dc ooooO ; 11
     dc ooooO ; 12 <
     dc ooXoo ; 13
     dc ooooO ; 14
     dc ooooO ; 15 <
     dc oXooO ; 16
     dc ooooO ; 17
     dc ooooO ; 18 <
     dc ooXoo ; 19
     dc ooooO ; 20
     dc ooooO ; 21
     dc ooooO ; 22 <
     dc ooooO ; 23
     dc ooooO ; 24
     dc ooooO ; 25 <
     dc ooooO ; 26
     dc ooooO ; 27
     dc ooooO ; 28 <
     dc ooooO ; 29



_CHAR_DUST_LEFT_1

     dc oooo ; 00 <
     dc oooo ; 01
     dc oooo ; 02
     dc oooo ; 03 <
     dc oooo ; 04
     dc oooo ; 05
     dc oooo ; 06 <
     dc oooo ; 07
     dc oooo ; 08
     dc oooo ; 09 <
     dc oooo ; 10
     dc oooo ; 11
     dc oooo ; 12 <
     dc ooXo ; 13
     dc oooo ; 14
     dc oooo ; 15 <
     dc oooX ; 16
     dc oooo ; 17
     dc oooo ; 18 <
     dc ooXo ; 19
     dc oooo ; 20 <
     dc oooo ; 21
     dc oooo ; 22
     dc oooo ; 23 <
     dc oooo ; 24
     dc oooo ; 25
     dc oooo ; 26 <
     dc oooo ; 27
     dc oooo ; 28
     dc oooo ; 29 <


_CHAR_DOGE_00 ; doged

     dc ooooO ; 00 <
     dc ooooO ; 01
     dc ooooO ; 02
     dc ooooO ; 03 <
     dc ooooO ; 04
     dc ooooO ; 05
     dc ooooO ; 06 <
     dc ooooO ; 07
     dc ooXoo ; 08
     dc ooooO ; 09 <
     dc ooXXo ; 10
     dc oXXXo ; 11
     dc ooooO ; 12 <
     dc ooXXo ; 13
     dc oXXXo ; 14
     dc ooooO ; 15 <
     dc oXXXo ; 16
     dc oXXXo ; 17
     dc ooooO ; 18 <
     dc ooXoo ; 19
     dc ooXoo ; 20
     ; dc ooooO ; 21 <
     ; dc ooooO ; 22
     ; dc ooooO ; 23
     ; dc ooooO ; 24 <
     ; dc ooooO ; 25
     ; dc ooooO ; 26
     ; dc ooooO ; 27 <
     ; dc ooooO ; 28
     ; dc ooooO ; 29

_CHAR_DOGE_01 ; doged

     dc ooooO ; 00 <
     dc ooooO ; 01
     dc ooooO ; 02
     dc ooooO ; 03 <
     dc ooooO ; 04
     dc ooooO ; 05
     dc ooooO ; 06 <
     dc ooooO ; 07
     dc ooooO ; 08
     dc ooooO ; 09 <
     dc ooXoo ; 10
     dc ooXoo ; 11
     dc ooooO ; 12 <
     dc oXXXo ; 13
     dc oXXXo ; 14
     dc ooooO ; 15 <
     dc ooXoo ; 16
     dc ooXoo ; 17
     ; dc ooooO ; 18 <
     ; dc ooooO ; 19
     ; dc ooooO ; 20
     ; dc ooooO ; 21 <
     ; dc ooooO ; 22
     ; dc ooooO ; 23
     ; dc ooooO ; 24 <
     ; dc ooooO ; 25
     ; dc ooooO ; 26
     ; dc ooooO ; 27 <
     ; dc ooooO ; 28
     ; dc ooooO ; 29

_CHAR_DOGE_02 ;doged

     dc ooooO ; 00 <
     dc ooooO ; 01
     dc ooooO ; 02
     dc ooooO ; 03 <
     dc ooooO ; 04
     dc ooooO ; 05
     dc ooooO ; 06 <
     dc ooooO ; 07
     dc ooooO ; 08
     dc ooooO ; 09 <
     dc ooooO ; 10
     dc ooooO ; 11
     dc ooooO ; 12 <
     dc oXXXo ; 13
     dc oXXXo ; 14
     dc ooooO ; 15 <
     dc ooooO ; 16
     dc ooooO ; 17
     ; dc ooooO ; 18 <
     ; dc ooooO ; 19
     ; dc ooooO ; 20
     ; dc ooooO ; 21 <
     ; dc ooooO ; 22
     ; dc ooooO ; 23
     ; dc ooooO ; 24 <
     ; dc ooooO ; 25
     ; dc ooooO ; 26
     ; dc ooooO ; 27 <
     ; dc ooooO ; 28
     ; dc ooooO ; 29

_CHAR_DOGE_03 ; doged

     dc ooooO ; 00 <
     dc ooooO ; 01
     dc ooooO ; 02
     dc ooooO ; 03 <
     dc ooooO ; 04
     dc ooooO ; 05
     dc ooooO ; 06 <
     dc ooooO ; 07
     dc ooooO ; 08
     dc ooooO ; 09 <
     dc ooooO ; 10
     dc ooooO ; 11
     dc oXXXo ; 12 <
     dc oXXXo ; 13
     dc oXXXo ; 14
     dc oXXXo ; 15 <
     dc ooooO ; 16
     dc ooooO ; 17
     dc ooooO ; 18 <
     dc ooooO ; 19
     dc ooooO ; 20
     ; dc ooooO ; 21 <
     ; dc ooooO ; 22
     ; dc ooooO ; 23
     ; dc ooooO ; 24 <
     ; dc ooooO ; 25
     ; dc ooooO ; 26
     ; dc ooooO ; 27 <
     ; dc ooooO ; 28
     ; dc ooooO ; 29

_CHAR_DOGE_04 ; doged

     dc ooooO ; 00 <
     dc ooooO ; 01
     dc ooooO ; 02
     dc ooooO ; 03 <
     dc ooooO ; 04
     dc ooooO ; 05
     dc ooooO ; 06 <
     dc ooooO ; 07
     dc ooooO ; 08
     dc ooXoo ; 09 <
     dc ooXoo ; 10
     dc ooXoo ; 11
     dc oXXXo ; 12 <
     dc oXXXo ; 13
     dc oXXXo ; 14
     dc oXXXo ; 15 <
     dc ooXoo ; 16
     dc ooXoo ; 17
     dc ooXoo ; 18 <
     dc ooooO ; 19
     dc ooooO ; 20
     dc ooooO ; 21 <
     dc ooooO ; 22
     dc ooooO ; 23
     ; dc ooooO ; 24 <
     ; dc ooooO ; 25
     ; dc ooooO ; 26
     ; dc ooooO ; 27 <
     ; dc ooooO ; 28
     ; dc ooooO ; 29

_CHAR_DOGE_05

     dc ooooO ; 00 <
     dc ooooO ; 01
     dc ooooO ; 02
     dc ooooO ; 03 <
     dc ooooO ; 04
     dc ooooO ; 05
     dc ooXoo ; 06 <
     dc ooXoo ; 07
     dc ooXoo ; 08
     dc oXXXo ; 09 <
     dc oXXXo ; 10
     dc oXXXo ; 11
     dc oXXXo ; 12 <
     dc oXXXo ; 13
     dc oXXXo ; 14
     dc oXXXo ; 15 <
     dc oXXXo ; 16
     dc oXXXo ; 17
     dc oXXXo ; 18 <
     dc ooXoo ; 19
     dc ooXoo ; 20
     dc ooXoo ; 21 <
     dc ooooO ; 22
     dc ooooO ; 23
     dc ooooO ; 24 <
     dc ooooO ; 25
     dc ooooO ; 26
     dc ooooO ; 27 <
     dc ooooO ; 28
     dc ooooO ; 29


; _CHAR_DOGE_FALLING

;      dc ooooX ; 00 <
;      dc ooooX ; 01
;      dc ooooX ; 02
;      dc ooooO ; 03 <
;      dc ooooO ; 04
;      dc ooooO ; 05
;      dc oooXo ; 06 <
;      dc oooXX ; 07
;      dc oooXX ; 08
;      dc ooXoo ; 09 <
;      dc ooXXX ; 10
;      dc ooXXX ; 11
;      dc ooooO ; 12 <
;      dc ooXXX ; 13
;      dc ooXXX ; 14
;      dc ooooO ; 15 <
;      dc oooXX ; 16
;      dc oooXX ; 17
;      dc ooooO ; 18 <
;      dc ooooX ; 19
;      dc ooooX ; 20
;      dc ooooO ; 21 <
;      dc ooooO ; 22
;      dc ooooO ; 23
;      dc ooooO ; 24 <
;      dc ooooO ; 25
;      dc ooooO ; 26
;      dc ooooO ; 27 <
;      dc ooooO ; 28
;      dc ooooO ; 29




_CHAR_PEBBLE1

     dc XXXXX ; 00 <
     dc ooooO ; 01
     dc ooooO ; 02
     dc XXXXX ; 03 <
     dc ooooO ; 04
     dc oooXo ; 05
     dc XXXXX ; 06 <
     dc ooooO ; 07
     dc oooXo ; 08
     dc XXXXX ; 09 <
     dc ooooO ; 10
     dc ooooO ; 11
     dc XXXXX ; 12 <
     dc ooooO ; 13
     dc ooooO ; 14
     dc XXXXX ; 15 <
     dc ooooO ; 16
     dc ooooO ; 17
     dc XXXXX ; 18 <
     dc ooooO ; 19
     dc ooooO ; 20
     dc XXXXX ; 21 <
     dc ooooO ; 22
     dc ooooO ; 23
     dc XXXXX ; 24 <
     dc ooooO ; 25
     dc ooooO ; 26
     dc XXXXX ; 27 <
     dc ooooO ; 28
     dc ooooO ; 29

; actually worm horiz body
_CHAR_WYRM_0

     dc oooXX ; 00 <
     dc ooooO ; 01
     dc oooXX ; 02
     dc XXXXX ; 03 <
     dc ooooO ; 04
     dc XXXXX ; 05
     dc XXXXX ; 06 <
     dc ooooO ; 07
     dc XXXXX ; 08
     dc XXoXX ; 09 <
     dc ooXoo ; 10
     dc XXXXX ; 11
     dc XXoXX ; 12 <
     dc oXXXo ; 13
     dc XXXXX ; 14
     dc XXoXX ; 15 <
     dc oXXXo ; 16
     dc XXXXX ; 17
     dc XXoXX ; 18 <
     dc ooXoo ; 19
     dc XXXXX ; 20
     dc XXXXX ; 21 <
     dc ooooO ; 22
     dc XXXXX ; 23
     dc XXXoo ; 24 <
     dc ooooO ; 25
     dc XXXoo ; 26
     dc ooooO ; 27 <
     dc ooooO ; 28
     dc ooooO ; 29


_CHAR_WYRM_2

     dc oXXXX ; 00 <
     dc ooooO ; 01
     dc oXXXX ; 02
     dc oXXXX ; 03 <
     dc ooooO ; 04
     dc oXXXX ; 05
     dc oXXXX ; 06 <
     dc ooooO ; 07
     dc oXXXX ; 08
     dc oXXXX ; 09 <
     dc ooXoo ; 10
     dc oXXXX ; 11
     dc ooooO ; 12 <
     dc oXXXX ; 13
     dc oXXXX ; 14
     dc oXoXX ; 15 <
     dc ooXoo ; 16
     dc oXXXX ; 17
     dc oXXXX ; 18 <
     dc ooXoo ; 19
     dc oXXXX ; 20
     dc oXXXX ; 21 <
     dc ooooO ; 22
     dc oXXXX ; 23
     dc oXXXX ; 24 <
     dc ooooO ; 25
     dc oXXXX ; 26
     dc oXXXX ; 27 <
     dc ooooO ; 28
     dc oXXXX ; 29


_CHAR_WYRM_3

     ; dc oo | oo | oXoo ; 00 < <--
     ; dc oo | oo | oXoo ; 01 <--
     ; dc XX | YY | XoXX ; 02 <-- raised small square
     ; dc oo | Yo | oXoo ; 03 < <--
     ; dc oo | Yo | oXoo ; 04 <--
     ; dc XX | YY | XoXX ; 05
     ; dc oX | oo | oooo ; 06 <
     ; dc oo | oY | oooo ; 07
     ; dc XX | YY | XXXX ; 08
     ; dc      oo | oooo ; 09 <
     ; dc      oo | ooXo ; 10
     ; dc      YY | XXXX ; 11
     ; dc      oo | oooo ; 12 <
     ; dc      oo | oXXX ; 13
     ; dc      YY | XXXX ; 14
     ; dc           oooo ; 15 <
     ; dc           oXXX ; 16
     ; dc           XXXX ; 17
     ; dc           oooo ; 18 <
     ; dc           ooXo ; 19
     ; dc           XXXX ; 20


    IF _ENABLE_WATER

_CHAR_WATER_0

     dc XX | oo | oooo ; 00 <
     dc oo | oo | oooo ; 01
     dc oo | oo | oXXX ; 02
     dc oo | oo | XXXX ; 03 <
     dc oo | oo | XooO ; 04
     dc oo | oo | oooo ; 05
     dc oo | oo | oooo ; 06 <
     dc oo | oo | oooo ; 07
     dc oo | oo | oooo ; 08
     dc      oo | oooo ; 09 <
     dc      oo | oooo ; 10
     dc      oo | oooo ; 11
     dc      oo | XXoo ; 12 <
     dc      oo | XXXX ; 13
     dc      oo | oXXX ; 14
     dc           oooX ; 15 <
     dc           oooo ; 16
     dc           oooo ; 17
     dc           oooo ; 18 <
     dc           oooo ; 19
     dc           oooo ; 20


_CHAR_WATER_1

     dc oo | oo | oooo ; 00 <
     dc XX | oo | ooXX ; 01
     dc oo | oo | XXXX ; 02
     dc oo | oo | XXoo ; 03 <
     dc oo | oo | oooo ; 04
     dc oo | oo | oooo ; 05
     dc oo | oo | oooo ; 06 <
     dc oo | oo | oooo ; 07
     dc oo | oo | oooo ; 08
     dc      oo | oooo ; 09 <
     dc      oo | oooo ; 10
     dc      oo | oooo ; 11
     dc      oo | XXoo ; 12 <
     dc      oo | XXXX ; 13
     dc      oo | ooXX ; 14
     dc           oooo ; 15 <
     dc           oooo ; 16
     dc           oooo ; 17
     dc           oooo ; 18 <
     dc           oooo ; 19
     dc           oooo ; 20


_CHAR_WATER_2

     dc oo | oo | oooo ; 00 <
     dc XX | oo | oooo ; 01
     dc oo | oo | XooO ; 02
     dc oo | oo | XXXo ; 03 <
     dc oo | oo | oXXX ; 04
     dc oo | oo | oooX ; 05
     dc oo | oo | oooo ; 06 <
     dc oo | oo | oooo ; 07
     dc oo | oo | oooo ; 08
     dc      oo | oooo ; 09 <
     dc      oo | oooo ; 10
     dc      oo | oooo ; 11
     dc      oo | oooX ; 12 <
     dc      oo | oXXX ; 13
     dc      oo | XXXo ; 14
     dc           XooO ; 15 <
     dc           oooo ; 16
     dc           oooo ; 17
     dc           oooo ; 18 <
     dc           oooo ; 19
     dc           oooo ; 20


_CHAR_WATER_3

     dc oo | oo | oooo ; 00 <
     dc XX | oo | oooo ; 01
     dc oo | oo | oooo ; 02
     dc oo | oo | XXoo ; 03 <
     dc oo | oo | XXXX ; 04
     dc oo | oo | ooXX ; 05
     dc oo | oo | oooo ; 06 <
     dc oo | oo | oooo ; 07
     dc oo | oo | oooo ; 08
     dc      oo | oooo ; 09 <
     dc      oo | oooo ; 10
     dc      oo | oooo ; 11
     dc      oo | oooX ; 12 <
     dc      oo | XXXX ; 13
     dc      oo | XXXo ; 14
     dc           oooo ; 15 <
     dc           oooo ; 16
     dc           oooo ; 17
     dc           oooo ; 18 <
     dc           oooo ; 19
     dc           oooo ; 20

    ENDIF ; ENABLE_WATER






CHAR_BLOCK_SIZE = * - CHAR_BLOCK_START
    echo "Char block = ", CHAR_BLOCK_START, "-", *, "(", [CHAR_BLOCK_SIZE]d, "bytes)"
;CHARSET_END

; EOF
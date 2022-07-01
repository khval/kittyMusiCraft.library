VERSION = 53
REVISION = 1

.macro DATE
.ascii "27.6.2022"
.endm

.macro VERS
.ascii "kittyMusiCraft.library 53.1"
.endm

.macro VSTRING
.ascii "kittyMusiCraft.library 53.1 (27.6.2022)"
.byte 13,10,0
.endm

.macro VERSTAG
.byte 0
.ascii "$VER: kittyMusiCraft.library 53.1 (27.6.2022)"
.byte 0
.endm

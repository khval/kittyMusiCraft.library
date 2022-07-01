VERSION		EQU	53
REVISION	EQU	1

DATE	MACRO
		dc.b '27.6.2022'
		ENDM

VERS	MACRO
		dc.b 'kittyMusiCraft.library 53.1'
		ENDM

VSTRING	MACRO
		dc.b 'kittyMusiCraft.library 53.1 (27.6.2022)',13,10,0
		ENDM

VERSTAG	MACRO
		dc.b 0,'$VER: kittyMusiCraft.library 53.1 (27.6.2022)',0
		ENDM

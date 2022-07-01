#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdint.h>
#include <stdbool.h>

#ifdef __amigaos4__
#include <proto/exec.h>
#include <proto/retroMode.h>
#endif

#include <amosKittens.h>

#include "cmdList.h"

struct cmdData AMOSPro_MusiCRAFT[]={
		{0x0002,"St Load",0,musicraftStLoad},
		{0x0012,"St Play",0,musicraftStPlay},
		{0x0024,"St Play",0,musicraftStPlay},
		{0x002C,"St Stop",0,musicraftStStop},
		{0x003A,"St Pause On",0,musicraftStPauseOn},
		{0x004C,"St Pause Off",0,musicraftStPauseOff},
		{0x005E,"St Voice",0,musicraftStVoice},
		{0x006E,"St Channel",0,musicraftStChannel},
		{0x0080,"St Vumeter Speed",0,musicraftStVumeterSpeed},
		{0x0098,"St Volume",0,musicraftStVolume},
		{0x00A8,"St Get Volume",0,musicraftStGetVolume},
		{0x00BC,"St Base",0,musicraftStBase},
		{0x00CA,"St Version",0,musicraftStVersion},
		{0x0000,NULL,0,0}};

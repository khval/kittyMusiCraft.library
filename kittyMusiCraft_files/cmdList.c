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
		{0x0006,"St Load",0,musicraftStLoad},
		{0x0016,"St Play",0,musicraftStPlay},
		{0x0028,"St Play",0,musicraftStPlay},
		{0x0030,"St Stop",0,musicraftStStop},
		{0x003E,"St Pause On",0,musicraftStPauseOn},
		{0x0050,"St Pause Off",0,musicraftStPauseOff},
		{0x0062,"St Voice",0,musicraftStVoice},
		{0x0072,"St Channel",0,musicraftStChannel},
		{0x0084,"St Vumeter Speed",0,musicraftStVumeterSpeed},
		{0x009C,"St Volume",0,musicraftStVolume},
		{0x00AC,"St Get Volume",0,musicraftStGetVolume},
		{0x00C0,"St Base",0,musicraftStBase},
		{0x00CE,"St Version",0,musicraftStVersion},
		{0x0000,NULL,0,0}};


/* :ts=4
 *  $VER: makeLookupTable.c $Revision$ (16-Mar-2020)
 *
 *  This file is part of kittymusicraft.
 *
 *  Copyright (c) 2020 LiveForIt Software.
 *  MIT License..
 *
 * $Id$
 *
 * $Log$
 *
 *
 */

#include <stdlib.h>
#include <stdint.h>
#include <stdbool.h>
#include <stdio.h>

#define __USE_INLINE__

#include <exec/exec.h>
#include <proto/exec.h>
#include <dos/dos.h>
#include <exec/types.h>
#include <libraries/kittycraft.h>
#include <proto/kittycraft.h>
#include <stdarg.h>

#include <proto/retroMode.h>
#include <amoskittens.h>
#include <cmdList.h>

/****** kittymusicraft/main/makeLookupTable ******************************************
*
*   NAME
*      makeLookupTable -- Description
*
*   SYNOPSIS
*      char * makeLookupTable(void);
*
*   FUNCTION
*
*   INPUTS
*
*   RESULT
*       The result ...
*
*   EXAMPLE
*
*   NOTES
*
*   BUGS
*
*   SEE ALSO
*
*****************************************************************************
*
*/

extern struct cmdData AMOSPro_MusiCRAFT[];

char * _kittymusicraft_makeLookupTable(struct kittyMusiCraftIFace *Self)
{
	struct cmdData *cmd;
	char *ptr;
	ptr = (char *) AllocVecTags( 0x10000, 
			AVT_Type, MEMF_SHARED, 
			AVT_ClearWithValue, 0,
			TAG_END );

	for (cmd=AMOSPro_MusiCRAFT;cmd -> fn;cmd++)
	{
		*((char *(**) KITTENS_CMD_ARGS) (ptr + cmd -> token)) = cmd -> fn;
	}

	return ptr;
}


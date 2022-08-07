/* :ts=4
 *  $VER: makeContext.c $Revision$ (22-Mar-2020)
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

#include <exec/exec.h>
#include <proto/exec.h>
#include <dos/dos.h>
#include <exec/types.h>
#include <libraries/kittymusic.h>
#include <proto/kittyMusic.h>
#include <proto/ptreplay.h>
#include <stdarg.h>

#include "context.h"


/****** kittymusicraft/main/makeContext ******************************************
*
*   NAME
*      makeContext -- Description
*
*   SYNOPSIS
*      void * makeContext(void);
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

void * _kittymusicraft_makeContext(struct kittyMusicIFace *Self)
{
	struct context *context;

	context =  malloc(sizeof(struct context));
	if (context)
	{
		bzero( context, sizeof(struct context) );
	}

	return context;
}


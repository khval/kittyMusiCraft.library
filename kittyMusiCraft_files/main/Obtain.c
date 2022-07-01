/* :ts=4
 *  $VER: Obtain.c $Revision$ (16-Mar-2020)
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


#include <exec/exec.h>
#include <proto/exec.h>
#include <dos/dos.h>
#include <exec/types.h>
#include <libraries/kittymusic.h>
#include <proto/kittymusic.h>
#include <stdarg.h>

/****** kittymusicraft/main/Obtain ******************************************
*
*   NAME
*      Obtain -- Description
*
*   SYNOPSIS
*      ULONG Obtain(void);
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

ULONG _kittymusicraft_Obtain(struct kittyMusicIFace *Self)
{
  return Self -> Data.RefCount++;
}


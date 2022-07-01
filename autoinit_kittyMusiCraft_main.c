/* :ts=4
 *  $VER: FreeContext.c $Revision$ (22-Mar-2020)
 *
 *  This file is part of kittymusicraft.
 *
 *  Copyright (c) 2022 LiveForIt Software.
 *  MIT License..
 *
 * $Id$
 *
 * $Log$
 *
 *
 */

#include <exec/types.h>
#include <libraries/kittyTurbo.h>

#include <interfaces/kittyMusiCraft.h>
#include <proto/exec.h>
#include <proto/dos.h>
#include <stdlib.h>

struct kittyMusiCraftIFace * IkittyMusiCraft = NULL;
static struct Library * __kittyMusiCraftBase = NULL;
static struct kittyMusiCraftIFace * __IkittyMusiCraft = NULL;

/****************************************************************************/

extern struct Library * kittyMusiCraftBase;

/****************************************************************************/

void kittyMusiCraft_main_constructor(void)
{
    if (IkittyMusiCraft != NULL)
    {
        return; /* Someone was quicker */
    }
    if (kittyMusiCraftBase == NULL) /* Library base is NULL, we need to open it */
    {
        /* We were called before the base constructor.
         * This means we will be called _after_ the base destructor.
         * So we cant drop the interface _after_ closing the last library base,
         * we just open the library here which ensures that.
         */
        __kittyMusiCraftBase = kittyMusiCraftBase = IExec->OpenLibrary("kittymusicraft.library", 0);
        if (kittyMusiCraftBase == NULL)
        {
            IDOS->PutErrStr("ERROR: Failed to open 'kittymusicraft.library'.\n");
            abort();
        }
    }

    __IkittyMusiCraft = IkittyMusiCraft = (struct kittyMusiCraftIFace *)IExec->GetInterface((struct Library *)kittyMusiCraftBase, "main", 1, NULL);
    if (IkittyMusiCraft == NULL)
    {
        IDOS->PutErrStr("ERROR: Failed to get 'main' V1 interface for 'kittymusicraft.library'.\n");
        abort();
    }
}
__attribute__((section(".ctors.zzzy"))) static void
(*kittyMusiCraft_main_constructor_ptr)(void) USED = kittyMusiCraft_main_constructor;

/****************************************************************************/

void kittyMusiCraft_main_destructor(void)
{
    if (__IkittyMusiCraft)
    {
        IExec->DropInterface ((struct Interface *)__IkittyMusiCraft);
    }
    if (__kittyMusiCraftBase)
    {
        IExec->CloseLibrary(__kittyMusiCraftBase);
    }
}
__attribute__((section(".dtors.zzzy"))) static void
(*kittyMusiCraft_main_destructor_ptr)(void) USED = kittyMusiCraft_main_destructor;

/****************************************************************************/


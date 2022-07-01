#ifndef KITTYMUSICRAFT_INTERFACE_DEF_H
#define KITTYMUSICRAFT_INTERFACE_DEF_H
/*
** This file is machine generated from idltool
** Do not edit
*/ 

#include <exec/types.i>
#include <exec/exec.i>
#include <exec/interfaces.i>

STRUCTURE kittyMusiCraftIFace, InterfaceData_SIZE
	    FPTR IkittyMusiCraft_Obtain
	    FPTR IkittyMusiCraft_Release
	    FPTR kittyMusiCraftIFace_Expunge_UNIMPLEMENTED
	    FPTR kittyMusiCraftIFace_Clone_UNIMPLEMENTED
	    FPTR IkittyMusiCraft_makeLookupTable
	    FPTR IkittyMusiCraft_FreeLookupTable
	    FPTR IkittyMusiCraft_makeContext
	    FPTR IkittyMusiCraft_FreeContext
	LABEL kittyMusiCraftIFace_SIZE

#endif

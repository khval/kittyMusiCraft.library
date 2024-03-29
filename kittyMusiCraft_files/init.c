/* :ts=4
 *  $VER: init.c $Revision$ (27-Jun-2022)
 *
 *  This file is part of kittyMusiCraft.
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


#include <exec/exec.h>
#include <proto/exec.h>
#include <dos/dos.h>
#include <exec/types.h>
#include <libraries/kittyTurbo.h>
#include <proto/kittyMusiCraft.h>
#include <stdarg.h>
#include <proto/dos.h>

/* Version Tag */
#include "kittyMusiCraft.library_rev.h"
STATIC CONST UBYTE USED verstag[] = VERSTAG;

struct _Library
{
    struct Library libNode;
    BPTR segList;
    /* If you need more data fields, add them here */
} ;

struct ExecIFace *IExec = NULL;
struct NewlibIFace * INewlib = NULL;
struct DOSIFace *IDOS = NULL;
struct PtrePlayIFace *IPTReplay = NULL;

struct Library *NewLibBase = NULL;
struct Library *DOSBase = NULL;
struct Library *PTReplayBase = NULL;

/*
 * The system (and compiler) rely on a symbol named _start which marks
 * the beginning of execution of an ELF file. To prevent others from 
 * executing this library, and to keep the compiler/linker happy, we
 * define an empty _start symbol here.
 *
 * On the classic system (pre-AmigaOS 4.x) this was usually done by
 * moveq #0,d0
 * rts
 *
 */
int32 _start(void);

int32 _start(void)
{
    /* If you feel like it, open DOS and print something to the user */
    return RETURN_FAIL;
}


/* Open the library */
STATIC struct Library *libOpen(struct LibraryManagerInterface *Self, ULONG version)
{
    struct _Library *libBase = (struct  _Library *)Self->Data.LibBase; 

    if (version > VERSION)
    {
        return NULL;
    }

    /* Add any specific open code here 
       Return 0 before incrementing OpenCnt to fail opening */


    /* Add up the open count */
    libBase->libNode.lib_OpenCnt++;
    return (struct Library *)libBase;

}


/* Close the library */
STATIC APTR libClose(struct LibraryManagerInterface *Self)
{
    struct _Library *libBase = (struct  _Library *)Self->Data.LibBase; 
    /* Make sure to undo what open did */


    /* Make the close count */
    ((struct Library *)libBase)->lib_OpenCnt--;

    return 0;
}

#define close_lib(b,i)			\
	if (b) IExec->CloseLibrary(b);	\
	if (i) IExec->DropInterface( (struct Interface *) i );	\
	b = NULL; i = NULL;			


void close_libs()
{
	struct ExecIFace *IExec = (struct ExecIFace *)(*(struct ExecBase **)4)->MainInterface;
	close_lib( PTReplayBase, IPTReplay);
	close_lib( DOSBase, IDOS);
	close_lib( NewLibBase, INewlib);
}

/* Expunge the library */
STATIC APTR libExpunge(struct LibraryManagerInterface *Self)
{
    /* If your library cannot be expunged, return 0 */
    struct ExecIFace *IExec
        = (struct ExecIFace *)(*(struct ExecBase **)4)->MainInterface;
    APTR result = (APTR)0;
    struct _Library *libBase = (struct  _Library *)Self->Data.LibBase; 
    if (libBase->libNode.lib_OpenCnt == 0)
    {
       result = (APTR)libBase->segList;
        /* Undo what the init code did */

	close_libs();

        IExec->Remove((struct Node *)libBase);
        IExec->DeleteLibrary((struct Library *)libBase);
    }
    else
    {
        result = (APTR)0;
        libBase->libNode.lib_Flags |= LIBF_DELEXP;
    }
    return result;
}


BOOL open_lib( const char *name, int ver , const char *iname, int iver, struct Library **base, struct Interface **interface)
{

	*interface = NULL;
	*base = IExec->OpenLibrary( name , ver);

	if (*base)
	{
		 *interface = IExec->GetInterface( *base,  iname , iver, TAG_END );
		if (!*interface) if (IDOS) IDOS -> Printf("Unable to getInterface %s for %s %d!\n",iname,name,ver);
	}
	else
	{
	   	if (IDOS) IDOS -> Printf("Unable to open the %s %ld!\n",name,ver);
	}

	return (*interface) ? TRUE : FALSE;
}

BOOL init()
{
	if ( ! open_lib( "dos.library", 53L , "main", 1, &DOSBase, (struct Interface **) &IDOS  ) ) return FALSE;
	if ( ! open_lib( "newlib.library", 53L , "main", 1, &NewLibBase, (struct Interface **) &INewlib  ) ) return FALSE;
	if ( ! open_lib( "ptreplay.library", 7 , "main", 1, &PTReplayBase, (struct Interface **) &IPTReplay  ) ) return FALSE;
	return TRUE;
}


/* The ROMTAG Init Function */
STATIC struct Library *libInit(struct Library *LibraryBase, APTR seglist, struct Interface *exec)
{
	struct _Library *libBase = (struct _Library *) LibraryBase;

	IExec = (struct ExecIFace *) exec;

	libBase->libNode.lib_Node.ln_Type = NT_LIBRARY;
	libBase->libNode.lib_Node.ln_Pri  = 0;
	libBase->libNode.lib_Node.ln_Name = "kittymusicraft.library";
	libBase->libNode.lib_Flags        = LIBF_SUMUSED|LIBF_CHANGED;
	libBase->libNode.lib_Version      = VERSION;
	libBase->libNode.lib_Revision     = REVISION;
	libBase->libNode.lib_IdString     = VSTRING;

	libBase->segList = (BPTR)seglist;

	if (init() == FALSE)
	{
		close_libs();
		return NULL;
	}

	return (struct Library *)libBase;
}

/* ------------------- Manager Interface ------------------------ */
/* These are generic. Replace if you need more fancy stuff */
STATIC uint32 _manager_Obtain(struct LibraryManagerInterface *Self)
{
	uint32 res;
	__asm__ __volatile__(
	"1:  lwarx  %0,0,%1\n"
	"addic  %0,%0,1\n"
	"stwcx.  %0,0,%1\n"
	"bne-  1b"
	: "=&r" (res)
	: "r" (&Self->Data.RefCount)
	: "cc", "memory");

	return res;
}

STATIC uint32 _manager_Release(struct LibraryManagerInterface *Self)
{
	uint32 res;
	__asm__ __volatile__(
	"1:  lwarx  %0,0,%1\n"
	"addic  %0,%0,-1\n"
	"stwcx.  %0,0,%1\n"
	"bne-  1b"
	: "=&r" (res)
	: "r" (&Self->Data.RefCount)
	: "cc", "memory");

	return res;
}

/* Manager interface vectors */
STATIC CONST APTR lib_manager_vectors[] =
{
	_manager_Obtain,
	_manager_Release,
	NULL,
	NULL,
	libOpen,
	libClose,
	libExpunge,
	NULL,
	(APTR)-1
};

/* "__library" interface tag list */
STATIC CONST struct TagItem lib_managerTags[] =
{
	{ MIT_Name,			(Tag)"__library"		},
	{ MIT_VectorTable,	(Tag)lib_manager_vectors},
	{ MIT_Version,		1						},
	{ TAG_DONE,			0						}
};

/* ------------------- Library Interface(s) ------------------------ */

#include "kittyMusiCraft_vectors.c"

/* Uncomment this line (and see below) if your library has a 68k jump table */
/* extern APTR VecTable68K[]; */

STATIC CONST struct TagItem main_v1_Tags[] =
{
	{ MIT_Name,			(Tag)"main"			},
	{ MIT_VectorTable,	(Tag)main_v1_vectors	},
	{ MIT_Version,		1					},
	{ TAG_DONE,			0					}
};

STATIC CONST CONST_APTR libInterfaces[] =
{
	lib_managerTags,
	main_v1_Tags,
	NULL
};

STATIC CONST struct TagItem libCreateTags[] =
{
	{ CLT_DataSize,		sizeof(struct _Library)	},
	{ CLT_InitFunc,		(Tag)libInit			},
	{ CLT_Interfaces,	(Tag)libInterfaces		},
	/* Uncomment the following line if you have a 68k jump table */
	/* { CLT_Vector68K, (Tag)VecTable68K }, */
	{TAG_DONE,		 0 }
};


/* ------------------- ROM Tag ------------------------ */
STATIC CONST struct Resident lib_res USED =
{
	RTC_MATCHWORD,
	(struct Resident *)&lib_res,
	(APTR)(&lib_res + 1),
	RTF_NATIVE|RTF_AUTOINIT, /* Add RTF_COLDSTART if you want to be resident */
	VERSION,
	NT_LIBRARY, /* Make this NT_DEVICE if needed */
	0, /* PRI, usually not needed unless you're resident */
	"kittymusicraft.library",
	VSTRING,
	(APTR)libCreateTags
};


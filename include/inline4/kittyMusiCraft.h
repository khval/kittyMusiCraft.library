#ifndef INLINE4_KITTYMUSICRAFT_H
#define INLINE4_KITTYMUSICRAFT_H

/*
** This file was auto generated by idltool 53.24.
**
** It provides compatibility to OS3 style library
** calls by substituting functions.
**
** Do not edit manually.
*/ 

#ifndef EXEC_TYPES_H
#include <exec/types.h>
#endif
#ifndef EXEC_EXEC_H
#include <exec/exec.h>
#endif
#ifndef EXEC_INTERFACES_H
#include <exec/interfaces.h>
#endif

#ifndef LIBRARIES_KITTYTURBO_H
#include <libraries/kittyTurbo.h>
#endif
#include <interfaces/kittyMusiCraft.h>

/* Inline macros for Interface "main" */
#define makeLookupTable() IkittyMusiCraft->makeLookupTable()
#define FreeLookupTable(table) IkittyMusiCraft->FreeLookupTable((table))
#define makeContext() IkittyMusiCraft->makeContext()
#define FreeContext(table) IkittyMusiCraft->FreeContext((table))

#endif /* INLINE4_KITTYMUSICRAFT_H */

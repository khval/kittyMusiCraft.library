#ifndef PROTO_KITTYMUSICRAFT_H
#define PROTO_KITTYMUSICRAFT_H

/*
**	$Id$
**
**	Prototype/inline/pragma header file combo
**
 *  Copyright (c) 2022 LiveForIt Software.
 *  MIT License..
*/

#ifndef EXEC_TYPES_H
#include <exec/types.h>
#endif
#ifndef LIBRARIES_KITTYTURBO_H
#include <libraries/kittyTurbo.h>
#endif

/****************************************************************************/

#ifndef __NOLIBBASE__
 #if defined(__cplusplus) && defined(__USE_AMIGAOS_NAMESPACE__)
  extern struct AmigaOS::Library * kittyMusiCraftBase;
 #else
  extern struct Library * kittyMusiCraftBase;
 #endif
#endif /* __NOLIBBASE__ */

/****************************************************************************/

#ifdef __amigaos4__
 #include <interfaces/kittyMusiCraft.h>
 #ifdef __USE_INLINE__
  #include <inline4/kittyMusiCraft.h>
 #endif /* __USE_INLINE__ */
 #ifndef CLIB_KITTYMUSICRAFT_PROTOS_H
  #define CLIB_KITTYMUSICRAFT_PROTOS_H 1
 #endif /* CLIB_KITTYMUSICRAFT_PROTOS_H */
 #ifndef __NOGLOBALIFACE__
  #if defined(__cplusplus) && defined(__USE_AMIGAOS_NAMESPACE__)
   extern struct AmigaOS::kittyMusiCraftIFace * IkittyMusiCraft;
  #else
   extern struct kittyMusiCraftIFace * IkittyMusiCraft;
  #endif
 #endif /* __NOGLOBALIFACE__ */
#else /* __amigaos4__ */
 #ifndef CLIB_KITTYMUSICRAFT_PROTOS_H
  #include <clib/kittyMusiCraft_protos.h>
 #endif /* CLIB_KITTYMUSICRAFT_PROTOS_H */
 #if defined(__GNUC__)
  #ifndef __PPC__
   #include <inline/kittyMusiCraft.h>
  #else /* __PPC__ */
   #include <ppcinline/kittyMusiCraft.h>
  #endif /* __PPC__ */
 #elif defined(__VBCC__)
  #ifndef __PPC__
   #include <inline/kittyMusiCraft_protos.h>
  #endif /* __PPC__ */
 #else /* __GNUC__ */
  #include <pragmas/kittyMusiCraft_pragmas.h>
 #endif /* __GNUC__ */
#endif /* __amigaos4__ */

/****************************************************************************/

#endif /* PROTO_KITTYMUSICRAFT_H */

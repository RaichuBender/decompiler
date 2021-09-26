/**********************************
*
*	 @file      typedefs.h
*	 @author    Thomas Gijsbers (@RaichuBender)
*	 @brief     
*	 @version   0.1
*	 @date      2021／09／24
*
*	 @copyright  © Copyright 2021 — Thomas Gijsbers
*	           	   All rights reserved.
*
**********************************/
#ifndef __TYPEDEFS_H__
#define __TYPEDEFS_H__

#include <stddef.h>

typedef unsigned char	   u8;
typedef unsigned short	   u16;
typedef unsigned long	   u32;
typedef unsigned long long u64;

typedef signed char		 s8;
typedef signed short	 s16;
typedef signed long		 s32;
typedef signed long long s64;

typedef float  f32;
typedef double f64;

typedef const char *ARG_LIST[];

#ifndef NULL
#define NULL (0)
#endif // NULL

#ifndef BOOL

typedef unsigned char BOOL;
#define TRUE (1)
#define FALSE (0)

#endif // BOOL

#define BOOLSTR(b) b ? "TRUE" : "FALSE"

typedef u8 BYTE;

typedef enum _ENDIANNESS
{
	LITTLE,
	BIG
} ENDIANNESS;

#endif // __TYPEDEFS_H__

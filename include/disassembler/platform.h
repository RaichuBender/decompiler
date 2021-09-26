/**********************************
*
*	 @file      platform.h
*	 @author    Thomas Gijsbers
*	 @brief     
*	 @version   0.1
*	 @date      2021／09／24
*
*	 @copyright	Ⓒ Copyright 2021 — Thomas Gijsbers
*	           	   All rights reserved.
*
**********************************/
#ifndef __PLATFORM_H__
#define __PLATFORM_H__

#include "typedefs.h"

typedef struct
{
	const char *identifier;
	const char *display_name;
	const char *user_description;

	const char *architecture;
	ENDIANNESS	endian;
	u32			address_size;
} PLATFORM;

#define NO_DESCRIPTION (0)

#endif // __PLATFORM_H__

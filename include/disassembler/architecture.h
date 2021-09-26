/**********************************
*
*	 @file      architecture.h
*	 @author    Thomas Gijsbers (@RaichuBender)
*	 @brief     
*	 @version   0.1
*	 @date      2021／09／24
*
*	 @copyright  © Copyright 2021 — Thomas Gijsbers
*	           	   All rights reserved.
*
**********************************/
#ifndef __ARCHITECTURE_H__
#define __ARCHITECTURE_H__

#include "typedefs.h"

typedef struct
{
	const char *identifier;
	const char *display_name;
	const char *user_description;
} ARCHITECTURE;

#define NO_DESCRIPTION (0)

#endif // __ARCHITECTURE_H__

/**********************************
*
*	 @file      program.h
*	 @author    Thomas Gijsbers (@RaichuBender)
*	 @brief     
*	 @version   0.1
*	 @date      2021／09／24
*
*	 @copyright  © Copyright 2021 — Thomas Gijsbers
*	           	   All rights reserved.
*
**********************************/
#ifndef __PROGRAM_H__
#define __PROGRAM_H__

#include "binary_file.h"
#include "typedefs.h"

typedef struct
{
	const char *identifier;
	const char *display_name;
	const char *user_description;

	u32		binary_count;
	BINARY *binary_data;
	BINARY *active_binary;
} PROGRAM;

#endif // __PROGRAM_H__

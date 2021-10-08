/**********************************
*
*	 @file      language.h
*	 @author    Thomas Gijsbers (@RaichuBender)
*	 @brief     
*	 @version   0.1
*	 @date      2021／09／24
*
*	 @copyright  © Copyright 2021 — Thomas Gijsbers
*	           	   All rights reserved.
*
**********************************/
#ifndef __LANGUAGE_H__
#define __LANGUAGE_H__

#include "instructions.h"
#include "typedefs.h"

typedef enum _REGISTER_PURPOSE
{
	GENERAL,
	PROGRAM_COUNTER,
	STACK_POINTER,
	FLAGS,
} REGISTER_PURPOSE;

typedef struct _REGISTER
{
	const char *	 name;
	u32				 mapping;
	u32				 size;	  // Unused by FLAG
	REGISTER_PURPOSE purpose; // Unused by FLAG
} REGISTER;

typedef struct _REGISTER_STORAGE
{
	u32		 reg_count;
	REGISTER regs[];
} REGISTER_STORAGE;

typedef struct _REGISTER FLAG_BIT;

typedef struct _LANGUAGE
{
	const char *	  identifier;
	const char *	  display_name;
	const char *	  user_description;
	u32				  reg_space_count;
	REGISTER_STORAGE *reg_spaces;
} LANGUAGE;

typedef struct _MODULE_INSTRUCTION_SET
{
	const char *name;
	MDL_INSTRUCTION instructions[256];
} MODULE_INSTRUCTION_SET;

typedef struct _RUNTIME_INSTRUCTION_SET
{
	const char *name;
	INSTRUCTION instructions[256];
} RUNTIME_INSTRUCTION_SET;

typedef struct _INSTR_BLOCK
{
	u64			start_adr;
	u64			byte_sz;
	u64			instr_sz;
	INSTRUCTION instructions[];
} INSTR_BLOCK;

#define NO_DESCRIPTION (0)

#endif //__LANGUAGE_H__

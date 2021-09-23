#ifndef __LANGUAGE_H__
#define __LANGUAGE_H__

#include "typedefs.h"
#include "instructions.h"

typedef struct _REGISTER_STORAGE REGISTER_STORAGE;
typedef struct _REGISTER		 REGISTER;

typedef struct _LANGUAGE
{
	const char *	  identifier;
	const char *	  display_name;
	const char *	  user_description;
	u32				  reg_space_count;
	REGISTER_STORAGE *reg_spaces;
} LANGUAGE;

typedef struct _REGISTER_STORAGE
{
	u32		 reg_count;
	REGISTER regs[];
} REGISTER_STORAGE;

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

typedef struct _REGISTER FLAG;

typedef struct _INSTRUCTION_SET
{
	const char *name;
	INSTRUCTION instructions[256];
} INSTRUCTION_SET;

#define NO_DESCRIPTION (0)

#endif //__LANGUAGE_H__

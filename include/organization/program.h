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

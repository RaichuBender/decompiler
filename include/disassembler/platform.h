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

#endif // __PLATFORM_H__

#ifndef __LANGUAGE_H__
#define __LANGUAGE_H__

#include "typedefs.h"

typedef struct _LANGUAGE
{
	const char *identifier;
	const char *display_name;
	const char *user_description;
} LANGUAGE;

#define NO_DESCRIPTION (0)

#endif //__LANGUAGE_H__

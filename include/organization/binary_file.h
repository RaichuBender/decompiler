#ifndef __BINARY_FILE_H__
#define __BINARY_FILE_H__

#include "patch.h"
#include "typedefs.h"

typedef struct
{
	const char * display_name;
	const char **user_description;

	const char imported_file_path[260];
	u64		   current_version;

	u64		patch_level;
	PATCH **user_applied_patches;
} BINARY;

#endif // __BINARY_FILE_H__

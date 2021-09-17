#ifndef __LANGUAGE_H__
#define __LANGUAGE_H__

typedef enum _ENDIANNESS
{
	LITTLE,
	BIG
} ENDIANNESS;

typedef struct _LANGUAGE
{
	const char * display_name;
	const char **user_description;

	ENDIANNESS endian;
	int		   address_size;
} LANGUAGE;

#endif //__LANGUAGE_H__

/**********************************
*
*	 @file      common.h
*	 @author    Thomas Gijsbers (@RaichuBender)
*	 @brief     
*	 @version   0.1
*	 @date      2021／09／24
*
*	 @copyright  © Copyright 2021 — Thomas Gijsbers
*	           	   All rights reserved.
*
**********************************/
#ifndef __COMMON_H__
#define __COMMON_H__

//				Maj   Mnr
#define VERSION 0x00, 0x01

// #define _DEBUG

// #define _OUTPUT_DBG_DOC
// #define _DBG_DUMP

#ifndef NULL
#define NULL (0)
#endif

// ## Lexer globals
extern char *storage;
typedef enum
{
	UNSPECIFIED = 0,
	REG_SPACE,
	REGISTER,
	FLAG,
	INSTR_SET,
	INSTR,
	INSTR_GROUPING,
	LOGIC,
} TOKEN_MODE;

#define SCOPE_MAX_DEPTH 2048
extern int		  token_scope;
extern TOKEN_MODE tmd[SCOPE_MAX_DEPTH];
extern char *	  scope_name[SCOPE_MAX_DEPTH];

#define NULL_TERM '\0'

#ifndef BOOL
typedef unsigned char BOOL;
#define TRUE  (1)
#define FALSE (0)
#endif

/**********************************
*
*	 @brief	Same as snprintf,
*			pretty much...
*
*    @param[in] bufsz	Buffer size
*    @param[in] fmt...	Format string
*
*    @return	formatted char buffer
*
**********************************/
#define FBUF(bufsz, fmt...) \
	({                      \
		char buf[bufsz];    \
		sprintf(buf, fmt);  \
		buf;                \
	})

#include "sys/debug.h"

/**********************************
*
*	 @name	ADD_TXT
*
*     @brief	Unconditionally append
*			(formatted) text to the
*			output file
*
*    @param[in]   fmt		Format string to be written
*    @param[in] __VA_ARGS__	Variables to be formatted
*
**********************************/
#define ADD_TXT(fmt...)             \
	{                               \
		pTxt += sprintf(pTxt, fmt); \
	}

#ifndef _DBG_DUMP


/**********************************
*
*    @name	DBG_DUMP
*
*     @brief	Append (formatted) debug
*			text to the output file,
*    		if enabled
*
*    @param[in]   fmt		Format string to be written
*    @param[in] __VA_ARGS__	Variables to be formatted
*
**********************************/
#define DBG_DUMP(fmt, ...)
#else // _DBG_DUMP

/**********************************
*
*    @name	DBG_DUMP
*    
*     @brief	Append (formatted) debug
*    		text to the output file,
*    		if enabled
*    
*    @param[in]   fmt		Format string to be written
*    @param[in] __VA_ARGS__ Variables to be formatted
*
**********************************/
#define DBG_DUMP(...) ADD_TXT(__VA_ARGS__)
#endif // _DBG_DUMP

#ifndef _OUTPUT_DBG_DOC


/**********************************
*
*	 @name	OUTPUT_DBG_DOC
*
*     @brief	Append (formatted)
*			documentation text to
*			the output file,
*			if enabled
*
*    @param[in]   fmt		Format string to be written
*    @param[in] __VA_ARGS__	Variables to be formatted
*
**********************************/
#define OUTPUT_DBG_DOC(fmt, ...)
#else // _DBG_PREV_MACRO


/**********************************
*
*	 @name	OUTPUT_DBG_DOC
*
*     @brief	Append (formatted)
*			documentation text to
*			the output file,
* 			if enabled
*
*    @param[in]   fmt		Format string to be written
*    @param[in] __VA_ARGS__	Variables to be formatted
*
**********************************/
#define OUTPUT_DBG_DOC(...) ADD_TXT(__VA_ARGS__)
#endif // _DBG_PREV_MACRO

typedef enum _FILE_TYPE
{
	INVALID = 0,
	TYPE_PLATFORM,
	TYPE_LANGUAGE,
	TYPE_MODE,
	TYPE_ARCHITECTURE
} FILE_TYPE;

typedef struct _MACRO
{
	// argv[0] acts as the macro's label
	int	   argc;
	char **argv;
	//
	char * expand;
} MACRO;


// Preprocessor output to be written
extern char prprc_out[4096 * 4096];		// TODO magic value
// Final output to be written
extern char final_out[4096 * 4096];		// TODO magic value

// Pointer to output text
extern char *	  pTxt;
// Common accross all types
extern char *	  identifier;
extern char *	  display_name;
extern char *	  user_description;
// Type specific
extern char *	  architecture;
extern char *	  language;
extern char *	  endian;
extern char *	  address_size;
// Block end markers
extern char *	  end_platform;
extern char *	  end_architecture;
extern char *	  end_language;
extern char *	  end_mode;
// Type detected from parsed file
extern FILE_TYPE  ftype;
extern char *	  type_hdr;
extern char *	  type_hdr_upper;
// Preprocessor macros
extern MACRO	  macro_list[1024];		// TODO magic value
extern int		  macro_count;
// Character before and after tokens
extern const char MACRO_SURROUND[27];	// TODO magic value


typedef enum _MACRO_TYPE
{
	EXPANDS_HAS_ARGS,
	EXPANDS_NO_ARGS_HAS_PARENTHESES,
	EXPANDS_NO_ARGS_NO_PARENTHESES,

	STUB_HAS_ARGS,
	STUB_NO_ARGS_HAS_PARENTHESES,
	STUB_NO_ARGS_NO_PARENTHESES,
} MACRO_TYPE;

#endif // __COMMON_H__

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

#include "sys/terminal_colors.h"

// #define _ASCII_MONOCHROME

#ifndef _SYNTAX

/**********************************
*
*    @name	WARN
*
*    @brief	Shows diagnostics
*			upon non-fatal error
*
*    @param[in]   fmt		Format string for warning message
*    @param[in] __VA_ARGS__	Variables to be formatted
*    @param[in]   in		Code line/fragment causing trouble
*    @param[in]   at		Idiot
*
**********************************/
#define WARN(fmt, ...)	;

/**********************************
*
*    @name	FATAL
*
*    @brief	Aborts execution
*			and shows diagnostics
*
*    @param[in]   fmt		Format string for error message
*    @param[in] __VA_ARGS__	Variables to be formatted
*    @param[in]   in		Code line/fragment causing the error
*    @param[in]   at		Idiot
*
**********************************/
#define FATAL(fmt, ...) ;

#else // _SYNTAX

/**********************************
*
*    @name	WARN
*
*    @brief	Shows diagnostics
*			upon non-fatal error
*
*    @param[in]   fmt		Format string for warning message
*    @param[in] __VA_ARGS__	Variables to be formatted
*    @param[in]   in		Code line/fragment causing trouble
*    @param[in]   at		Idiot
*
**********************************/
#ifndef _ASCII_MONOCHROME

#define WARN(fmt, ...)                                                                                        \
	{                                                                                                         \
		fprintf(stderr, CB_MAGENTA "\nWARNING  " CB_WHITE fmt C_BLUE "\n >> " C_MAGENTA " ⮞"              \
				" " C_CYAN "in: " C_MAGENTA "\"" C_WHITE "%s" C_MAGENTA "\"" C_BLUE "\n >> " C_MAGENTA " ⮞" \
				" " C_CYAN "at: " C_MAGENTA "\"" C_WHITE "%s" C_MAGENTA "\"\n\n" CB_MAGENTA "  ⏺ "          \
				" " CB_CYAN "%s\n\n" F_RESET __VA_OPT__(, ) __VA_ARGS__);                                     \
		ADD_TXT("\n/*\nWARNING  " fmt "\n >>  ⮞"                                                            \
				" in: \"%s\"\n >>  ⮞"                                                                       \
				" at: \"%s\"\n\n  ⏺ "                                                                       \
				" %s\n*/" __VA_OPT__(, ) __VA_ARGS__);                                                        \
	}

// TODO check if symbols render correctly on other terminal emulators (1 of 2)

#else // _ASCII_MONOCHROME

#define WARN(fmt, ...)                                                                               \
	{                                                                                                \
		fprintf(stderr, "\n"                                                                         \
						"+==========+============================+\n"                                \
						"| WARNING  | " fmt "\n"                                                     \
						"+====+=====+============================+\n"                                \
						"  ###| in: | \"%s\"\n"                                                      \
						"  ###| at: | \"%s\"\n"                                                      \
						"+====+=====+============================+\n"                                \
						"|  ~~ %s\n"                                                                 \
						"+=======================================+\n\n" __VA_OPT__(, ) __VA_ARGS__); \
                                                                                                     \
		ADD_TXT("\n/*\nWARNING:  " fmt "\n #### "                                                    \
				" in: \"%s\"\n #### "                                                                \
				" at: \"%s\"\n\n ~~ "                                                                \
				" %s\n*/" __VA_OPT__(, ) __VA_ARGS__);                                               \
	}

#endif // _ASCII_MONOCHROME

/**********************************
*
*	 @name	FATAL
*
*    @brief	Aborts execution and shows diagnostics
*
*    @param[in]   fmt		Format string for error message
*    @param[in] __VA_ARGS__	Variables to be formatted
*    @param[in]   in		Code line/fragment causing the error
*    @param[in]   at		Idiot 
*
**********************************/
#ifndef _ASCII_MONOCHROME
#define FATAL(fmt, ...)                                                                                               \
	{                                                                                                                 \
		fprintf(stderr, CB_RED "\nFATAL ERROR  " CB_WHITE fmt C_MAGENTA "\n >> " C_RED " ⮞"                         \
							   " " C_YELLOW "in: " C_RED "\"" C_WHITE "%s" C_RED "\"" C_MAGENTA "\n >> " C_RED " ⮞" \
							   " " C_YELLOW "at: " C_RED "\"" C_WHITE "%s" C_RED "\"\n\n" CB_RED "  ⏺ "             \
							   " " CB_YELLOW "%s\n\n" F_RESET __VA_OPT__(, ) __VA_ARGS__);                            \
		exit(-1);                                                                                                     \
	}

// TODO check if symbols render correctly on other terminal emulators (2 of 2)

#else // _ASCII_MONOCHROME

#define FATAL(fmt, ...)                                                                              \
	{                                                                                                \
		fprintf(stderr, "\n"                                                                         \
						"+==============+========================+\n"                                \
						"| FATAL ERROR  | " fmt "\n"                                                 \
						"+====+=====+===+========================+\n"                                \
						"  ###| in: | \"%s\"\n"                                                      \
						"  ###| at: | \"%s\"\n"                                                      \
						"+====+=====+============================+\n"                                \
						"|  ~~ %s\n"                                                                 \
						"+=======================================+\n\n" __VA_OPT__(, ) __VA_ARGS__); \
		exit(-1);                                                                                    \
	}

#endif // _ASCII_MONOCHROME

#endif // _SYNTAX

#define ASSERT(cond)                                                                               \
	{                                                                                              \
		if (!(cond))                                                                               \
			FATAL("assertion failed", ({                                                           \
					  char IN[64];                                                                 \
					  sprintf(IN, "%s:%d", __FILE__, __LINE__);                                    \
					  IN;                                                                          \
				  }),                                                                              \
				   CB_WHITE "ASSERT" C_YELLOW " ( " CB_CYAN #cond C_YELLOW " )", "That's not good..."); \
	}

/* Quickly disable assertiom by simply adding a 'd' in front */
#define dASSERT(cond)


#ifndef _TRACE_FILENAME

#define TRACE_CODE(code)                                    \
	fprintf(stderr, __FILE__ ":%d: %s\n", __LINE__, #code); \
	code;

#else // _TRACE_FILENAME

#define TRACE_CODE(code)            \
	fprintf(stderr, "%s\n", #code); \
	code;

#endif // _TRACE_FILENAME

#if 1

#define DBG_TRACE(sym)

#else

#define DBG_TRACE(sym)                                  \
	{                                                   \
		fprintf(stderr, "%s: *(0x%08x)\n", #sym, &sym); \
	}

#endif // 1

// HACK fix for preprocessor
#ifdef __PREACH_MODEST_H__

#define DBG_TRACEL(sym)                \
	{                                  \
		fprintf(stderr, "%s\n", #sym); \
	}

#else

extern int token_scope;
#define DBG_TRACEL(sym)                                 \
	{                                                   \
		ASSERT(token_scope >= 0);                       \
		fprintf(stderr, "%d\t%s\n", token_scope, #sym); \
	}

#endif

/**********************************
*
*	 @name	ADD_TXT
*
*    @brief	Unconditionally append
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
*    @brief	Append (formatted) debug
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
*    @brief	Append (formatted) debug
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
*    @brief	Append (formatted)
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
*    @brief	Append (formatted)
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
extern char prprc_out[4096 * 4096];
// Final output to be written
extern char final_out[4096 * 4096];

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
extern MACRO	  macro_list[1024];
extern int		  macro_count;
// Character before and after tokens
extern const char MACRO_SURROUND[27];

typedef enum _MACRO_TYPE
{
	EXPANDS_HAS_ARGS,
	EXPANDS_NO_ARGS_HAS_BRACKETS,
	EXPANDS_NO_ARGS_NO_BRACKETS,

	STUB_HAS_ARGS,
	STUB_NO_ARGS_HAS_BRACKETS,
	STUB_NO_ARGS_NO_BRACKETS,
} MACRO_TYPE;

#endif // __COMMON_H__

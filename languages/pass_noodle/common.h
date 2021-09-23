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
// ## -

#define NULL_TERM '\0'

#ifndef BOOL
typedef unsigned char BOOL;
#define TRUE  (1)
#define FALSE (0)
#endif

#define FBUF(bufsz, fmt...) \
	({                      \
		char buf[bufsz];    \
		sprintf(buf, fmt);  \
		buf;                \
	})

#define C_BLACK	   "\033[0;30m" // COLOR black (regular)
#define C_RED	   "\033[0;31m" // COLOR red (regular)
#define C_GREEN	   "\033[0;32m" // COLOR green (regular)
#define C_YELLOW   "\033[0;33m" // COLOR yellow (regular)
#define C_BLUE	   "\033[0;34m" // COLOR blue (regular)
#define C_MAGENTA  "\033[0;35m" // COLOR magenta (regular)
#define C_CYAN	   "\033[0;36m" // COLOR cyan (regular)
#define C_WHITE	   "\033[0;37m" // COLOR white (regular)

#define F_BOLD	   "\033[1m" // FORMAT bold
#define F_RESET	   "\033[0m" // FORMAT reset

#define CB_BLACK   C_BLACK F_BOLD	// COLOR black (bold)
#define CB_RED	   C_RED F_BOLD		// COLOR red (bold)
#define CB_GREEN   C_GREEN F_BOLD	// COLOR green (bold)
#define CB_YELLOW  C_YELLOW F_BOLD	// COLOR yellow (bold)
#define CB_BLUE	   C_BLUE F_BOLD	// COLOR blue (bold)
#define CB_MAGENTA C_MAGENTA F_BOLD // COLOR magenta (bold)
#define CB_CYAN	   C_CYAN F_BOLD	// COLOR cyan (bold)
#define CB_WHITE   C_WHITE F_BOLD	// COLOR white (bold)

// #define _ASCII_MONOCHROME

#ifndef _SYNTAX

/**
 * @name	WARN
 * @brief	Shows diagnostics upon non-fatal error
 * @param[in] 	fmt			Format string for warning message
 * @param[in] __VA_ARGS__	Variables to be formatted
 * @param[in] 	in			Code line/fragment causing trouble
 * @param[in] 	at			Idiot
 */
#define WARN(fmt, ...)	;

/**
 * @name	FATAL
 * @brief	Aborts execution and shows diagnostics
 * @param[in] 	fmt			Format string for error message
 * @param[in] __VA_ARGS__	Variables to be formatted
 * @param[in] 	in			Code line/fragment causing the error
 * @param[in] 	at			Idiot
 */
#define FATAL(fmt, ...) ;

#else // _SYNTAX

/**
 * @name	WARN
 * @brief	Shows diagnostics upon non-fatal error
 * @param[in] 	fmt			Format string for warning message
 * @param[in] __VA_ARGS__	Variables to be formatted
 * @param[in] 	in			Code line/fragment causing trouble
 * @param[in] 	at			Idiot
 */
#ifndef _ASCII_MONOCHROME
#define WARN(fmt, ...)                                                                                        \
	{                                                                                                         \
		fprintf(stderr, CB_MAGENTA                                                                            \
				"\nWARNING  " CB_WHITE fmt C_BLUE "\n >> " C_MAGENTA " ⮞"                                   \
				" " C_CYAN "in: " C_MAGENTA "\"" C_WHITE "%s" C_MAGENTA "\"" C_BLUE "\n >> " C_MAGENTA " ⮞" \
				" " C_CYAN "at: " C_MAGENTA "\"" C_WHITE "%s" C_MAGENTA "\"\n\n" CB_MAGENTA "  ⏺ "          \
				" " CB_CYAN "%s\n\n" F_RESET __VA_OPT__(, ) __VA_ARGS__);                                     \
		ADD_TXT("\n/*\nWARNING  " fmt "\n >>  ⮞"                                                            \
				" in: \"%s\"\n >>  ⮞"                                                                       \
				" at: \"%s\"\n\n  ⏺ "                                                                       \
				" %s\n*/" __VA_OPT__(, ) __VA_ARGS__);                                                        \
	}
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

/**
 * @name	FATAL
 * @brief	Aborts execution and shows diagnostics
 * @param[in] 	fmt			Format string for error message
 * @param[in] __VA_ARGS__	Variables to be formatted
 * @param[in] 	in			Code line/fragment causing the error
 * @param[in] 	at			Idiot
 */
#ifndef _ASCII_MONOCHROME
#define FATAL(fmt, ...)                                                                                               \
	{                                                                                                                 \
		fprintf(stderr, CB_RED "\nFATAL ERROR  " CB_WHITE fmt C_MAGENTA "\n >> " C_RED " ⮞"                         \
							   " " C_YELLOW "in: " C_RED "\"" C_WHITE "%s" C_RED "\"" C_MAGENTA "\n >> " C_RED " ⮞" \
							   " " C_YELLOW "at: " C_RED "\"" C_WHITE "%s" C_RED "\"\n\n" CB_RED "  ⏺ "             \
							   " " CB_YELLOW "%s\n\n" F_RESET __VA_OPT__(, ) __VA_ARGS__);                            \
		exit(-1);                                                                                                     \
	}
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

#define DBG_TRACE(sym)
// #define DBG_TRACE(sym)                                  \
// 	{                                                   \
// 		fprintf(stderr, "%s: *(0x%08x)\n", #sym, &sym); \
// 	}
#define DBG_TRACEL(sym)                \
	{                                  \
		fprintf(stderr, "%s\n", #sym); \
	}

/**
 * @name	ADD_TXT
 * @brief	Unconditionally append (formatted) text to the output file
 * @param[in] 	fmt			Format string to be written
 * @param[in] __VA_ARGS__	Variables to be formatted
 */
#define ADD_TXT(fmt...)             \
	{                               \
		pTxt += sprintf(pTxt, fmt); \
	}

#ifndef _DBG_DUMP

/**
 * @name	DBG_DUMP
 * @brief	Append (formatted) debug text to the output file,
 * 			if enabled
 * @param[in] 	fmt			Format string to be written
 * @param[in] __VA_ARGS__	Variables to be formatted
 */
#define DBG_DUMP(fmt, ...)
#else // _DBG_DUMP

/**
 * @name	DBG_DUMP
 * @brief	Append (formatted) debug text to the output file,
 * 			if enabled
 * @param[in] 	fmt			Format string to be written
 * @param[in] __VA_ARGS__	Variables to be formatted
 */
#define DBG_DUMP(...) ADD_TXT(__VA_ARGS__)
#endif // _DBG_DUMP

#ifndef _OUTPUT_DBG_DOC

/**
 * @name	OUTPUT_DBG_DOC
 * @brief	Append (formatted) documentation text to the output file,
 * 			if enabled
 * @param[in] 	fmt			Format string to be written
 * @param[in] __VA_ARGS__	Variables to be formatted
 */
#define OUTPUT_DBG_DOC(fmt, ...)
#else // _DBG_PREV_MACRO

/**
 * @name	OUTPUT_DBG_DOC
 * @brief	Append (formatted) documentation text to the output file,
 * 			if enabled
 * @param[in] 	fmt			Format string to be written
 * @param[in] __VA_ARGS__	Variables to be formatted
 */
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

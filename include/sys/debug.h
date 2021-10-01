#ifndef __DEBUG_H__
#define __DEBUG_H__

#include "sys/terminal_colors.h"


// #define _ASCII_MONOCHROME

#ifndef _DEBUG

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

#define ASSERT(cond) 


#else // _DEBUG

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

#endif // _DEBUG


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


#endif /* __DEBUG_H__ */

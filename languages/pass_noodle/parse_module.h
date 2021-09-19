#ifndef __PARSE_MODULE_H__
#define __PARSE_MODULE_H__

#define _OUTPUT_DBG_DOC
// #define _DBG_DUMP

#ifndef NULL
#define NULL (0)
#endif

#ifndef BOOL
typedef unsigned char BOOL;
#define TRUE (1)
#define FALSE (0)
#endif

#define ADD_TXT(fmt, ...)                                                                                              \
	{                                                                                                                  \
		pTxt += sprintf(pTxt, fmt __VA_OPT__(, ) __VA_ARGS__);                                                         \
	}

#ifndef _DBG_DUMP
#define DBG_DUMP(fmt, ...)
#else // _DBG_DUMP
#define DBG_DUMP(...) ADD_TXT(__VA_ARGS__)
#endif // _DBG_DUMP

#ifndef _OUTPUT_DBG_DOC
#define OUTPUT_DBG_DOC(fmt, ...)
#else // _DBG_PREV_MACRO
#define OUTPUT_DBG_DOC(...) ADD_TXT(__VA_ARGS__)
#endif // _DBG_PREV_MACRO

#define WARN(fmt, ...) ADD_TXT("/* WARN: " fmt " */", __VA_ARGS__)

typedef enum
{
	INVALID = 0,
	TYPE_PLATFORM,
	TYPE_LANGUAGE,
	TYPE_MODE,
	TYPE_ARCHITECTURE
} FILE_TYPE;

typedef struct
{
	// argv[0] acts as the macro's label
	int	   argc;
	char **argv;

	char *expand;
} MACRO;

char final_out[1024];

char *pTxt = final_out;

char *identifier = NULL;
char *display_name = NULL;
char *user_description = NULL;

char *architecture = NULL;
char *language = NULL;
char *endian = NULL;
char *address_size = NULL;
char *end_platform = NULL;

FILE_TYPE ftype = INVALID;
char *	  type_hdr;
char *	  type_hdr_upper;

MACRO macro_list[1024];
int	  macro_count;

static char *PROCESS_MACRO(char *yytext);
static void	 EXPAND_MACRO(char *macro_begin);
static void	 PROCESS_MACRO_EXPANSION(void);

static const char MACRO_SURROUND[] = " \t\n\r-_=+[]()\\*&^%!~'\"<>,./";

#define STRUCT_START(_TYPE_, _HEADER_)                                                                                 \
	{                                                                                                                  \
		ftype = TYPE_##_TYPE_;                                                                                         \
		type_hdr = #_HEADER_;                                                                                          \
		type_hdr_upper = #_TYPE_;                                                                                      \
                                                                                                                       \
		yytext = strchr(yytext, L'(') + 1;                                                                             \
                                                                                                                       \
		*(strchr(yytext, L')')) = '\0';                                                                                \
                                                                                                                       \
		identifier = malloc(strlen(yytext));                                                                           \
		strcpy(identifier, yytext);                                                                                    \
	}

#define USER_DESC()                                                                                                    \
	{                                                                                                                  \
		char *_yytext = strchr(yytext, L' ');                                                                          \
                                                                                                                       \
		if (_yytext == NULL)                                                                                           \
			_yytext = strchr(yytext, L'\t');                                                                           \
                                                                                                                       \
		*(strstr(++_yytext, "\n")) = '\0';                                                                             \
                                                                                                                       \
		while ((*_yytext == ' ') || (*_yytext == '\t'))                                                                \
			++_yytext;                                                                                                 \
                                                                                                                       \
		user_description = malloc(strlen(_yytext));                                                                    \
		strcpy(user_description, _yytext);                                                                             \
	}

#define PROPERTY_LITERAL(_NAME_)                                                                                       \
	{                                                                                                                  \
		char *_yytext = strchr(yytext, L' ');                                                                          \
                                                                                                                       \
		if (_yytext == NULL)                                                                                           \
			_yytext = strchr(yytext, L'\t');                                                                           \
                                                                                                                       \
		*(strchr(++_yytext, L'\n')) = '\0';                                                                            \
                                                                                                                       \
		while ((*_yytext == ' ') || (*_yytext == '\t'))                                                                \
			++_yytext;                                                                                                 \
                                                                                                                       \
		_NAME_ = malloc(strlen(_yytext));                                                                              \
		strcpy(_NAME_, _yytext);                                                                                       \
	}

#endif // __PARSE_MODULE_H__

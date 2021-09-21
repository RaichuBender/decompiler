#ifndef __PASS_NOODLE_H__
#define __PASS_NOODLE_H__

#include "common.h"

#define STRUCT_START(_TYPE_, _HEADER_)       \
	{                                        \
		DBG_TRACEL(_STRUCT_START);           \
		ftype		   = TYPE_##_TYPE_;      \
		type_hdr	   = #_HEADER_;          \
		type_hdr_upper = #_TYPE_;            \
                                             \
		yytext = strchr(yytext, L'(') + 1;   \
                                             \
		*(strchr(yytext, L')')) = '\0';      \
                                             \
		identifier = malloc(strlen(yytext)); \
		strcpy(identifier, yytext);          \
	}

#define USER_DESC()                                     \
	{                                                   \
		char *_yytext = strchr(yytext, L' ');           \
                                                        \
		if (_yytext == NULL)                            \
			_yytext = strchr(yytext, L'\t');            \
                                                        \
		*(strstr(++_yytext, "\n")) = '\0';              \
                                                        \
		while ((*_yytext == ' ') || (*_yytext == '\t')) \
			++_yytext;                                  \
                                                        \
		user_description = malloc(strlen(_yytext));     \
		strcpy(user_description, _yytext);              \
	}

#define PROPERTY_LITERAL(_NAME_)                        \
	{                                                   \
		DBG_TRACEL(_PROPERTY_LITERAL);                  \
		char *_yytext = strchr(yytext, L' ');           \
                                                        \
		if (_yytext == NULL)                            \
			_yytext = strchr(yytext, L'\t');            \
                                                        \
		*(strchr(++_yytext, L'\n')) = '\0';             \
                                                        \
		while ((*_yytext == ' ') || (*_yytext == '\t')) \
			++_yytext;                                  \
                                                        \
		_NAME_ = malloc(strlen(_yytext));               \
		strcpy(_NAME_, _yytext);                        \
	}

#endif // __PASS_NOODLE_H__

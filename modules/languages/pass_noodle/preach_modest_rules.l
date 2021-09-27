/**********************************
 /*
*	 @file      preach_modest.l
*	 @author    Thomas Gijsbers (@RaichuBender)
*	 @brief     Macro preprocessor lexer
*	 @version   0.1
*	 @date      2021／09／24
*
*	 @copyright  © Copyright 2021 — Thomas Gijsbers
*	           	   All rights reserved.
*
**********************************/
%{
#include "preach_modest.h"

#if 0
#define dbg_printf(fmt...)	printf(fmt)
#else
#define dbg_printf(fmt...)
#endif
%}

%%

MACRO:[a-zA-Z0-9_]+?\(\)(.*?\n.*)*?=BEGIN(.*?\n.*)*?=END	{
	DBG_TRACEL(macro1);
	dbg_printf("%s ::\n%s\n\n\n", "MACRO:[a-zA-Z0-9_]+?\\(\\)(.*?\\n.*)*?=BEGIN(.*?\\n.*)*?=END", yytext);
	MACRO *macro = &macro_list[macro_count];
	char *macro_begin = PROCESS_MACRO(yytext, EXPANDS_HAS_ARGS);
	EXPAND_MACRO(macro_begin);
	PROCESS_MACRO_EXPANSION();
	OUTPUT_DBG_DOC(" *\t@return *** PREVIEW ***\n\t%s\n", macro->expand);
	OUTPUT_DBG_DOC(" */\n");
	OUTPUT_DBG_DOC("#define  dummy_macro__%s  (...)\n\n", macro->argv[0]);
	++macro_count;
}

MACRO:[a-zA-Z0-9_]+?\(.*?\)(.*?\n.*)*?=BEGIN(.*?\n.*)*?=END	{
	DBG_TRACEL(macro2);
	dbg_printf("%s ::\n%s\n\n\n", "MACRO:[a-zA-Z0-9_]+?\\(.*?\\)(.*?\\n.*)*?=BEGIN(.*?\\n.*)*?=END", yytext);
	MACRO *macro = &macro_list[macro_count];
	char *macro_begin = PROCESS_MACRO(yytext, EXPANDS_NO_ARGS_HAS_BRACKETS);
	EXPAND_MACRO(macro_begin);
	PROCESS_MACRO_EXPANSION();
	OUTPUT_DBG_DOC(" *\t@return *** PREVIEW ***\n\t%s\n", macro->expand);
	OUTPUT_DBG_DOC(" */\n");
	OUTPUT_DBG_DOC("#define  dummy_macro__%s  (...)\n\n", macro->argv[0]);
	++macro_count;
}

MACRO:[a-zA-Z0-9_]+?(.*?\n.*)*?=BEGIN(.*?\n.*)*?=END	{
	DBG_TRACEL(macro3);
	dbg_printf("%s ::\n%s\n\n\n", "MACRO:[a-zA-Z0-9_]+?(.*?\\n.*)*?=BEGIN(.*?\\n.*)*?=END", yytext);
	MACRO *macro = &macro_list[macro_count];
	char *macro_begin = PROCESS_MACRO(yytext, EXPANDS_NO_ARGS_NO_BRACKETS);
	EXPAND_MACRO(macro_begin);
	PROCESS_MACRO_EXPANSION();
	OUTPUT_DBG_DOC(" *\t@return *** PREVIEW ***\n\t%s\n", macro->expand);
	OUTPUT_DBG_DOC(" */\n");
	OUTPUT_DBG_DOC("#define  dummy_macro__%s  (...)\n\n", macro->argv[0]);
	++macro_count;
	}

MACRO:[a-zA-Z0-9_]+?\(\).*?\n 	{
	DBG_TRACEL(macro4);
	dbg_printf("%s ::\n%s\n\n\n", "MACRO:[a-zA-Z0-9_]+?\\(\\).*?\\n", yytext);
	MACRO *macro = &macro_list[macro_count];
	PROCESS_MACRO(yytext, STUB_NO_ARGS_HAS_BRACKETS);
	OUTPUT_DBG_DOC(" *\t@return\tNothing.\n");
	OUTPUT_DBG_DOC(" */\n");
	OUTPUT_DBG_DOC("#define  dummy_macro__%s  (...)\n\n", macro->argv[0]);
	++macro_count;
}

MACRO:[a-zA-Z0-9_]+?\(.*?\).*?\n {
	DBG_TRACEL(macro5);
	dbg_printf("%s ::\n%s\n\n\n", "MACRO:[a-zA-Z0-9_]+?\\(.*?\\).*?\\n", yytext);
	MACRO *macro = &macro_list[macro_count];
	PROCESS_MACRO(yytext, STUB_HAS_ARGS);
	OUTPUT_DBG_DOC(" *\t@return\tNothing.\n");
	OUTPUT_DBG_DOC(" */\n");
	OUTPUT_DBG_DOC("#define  dummy_macro__%s  (...)\n\n", macro->argv[0]);
	++macro_count;
}

MACRO:[a-zA-Z0-9_]+?.*?\n		{
	DBG_TRACEL(macro6);
	dbg_printf("%s ::\n%s\n\n\n", "MACRO:[a-zA-Z0-9_]+?.*?\\n", yytext);
	MACRO *macro = &macro_list[macro_count];
	PROCESS_MACRO(yytext, STUB_NO_ARGS_NO_BRACKETS);
	OUTPUT_DBG_DOC(" *\t@return\tNothing.\n");
	OUTPUT_DBG_DOC(" */\n");
	OUTPUT_DBG_DOC("#define  dummy_macro__%s  (...)\n\n", macro->argv[0]);
	++macro_count;
}

\^%.+?\(\s*\).*?\n	{
	DBG_TRACEL(replace);
	dbg_printf("%s ::\n%s\n\n\n", "\\^%.+?\\(.*?\\)", yytext);
	REPLACE_MACRO(yytext);
}

\^%.+?\(.+?\).*?\n		{
	DBG_TRACEL(replace);
	dbg_printf("%s ::\n%s\n\n\n", "\\^%.+?\\(.*?\\)", yytext);
	REPLACE_MACRO(yytext);
}

\^%.+?\s*	{
	DBG_TRACEL(replace);
	dbg_printf("%s ::\n%s\n\n\n", "\\^%.+?\\(.*?\\)", yytext);
	REPLACE_MACRO(yytext);
}

.		{	ADD_TXT("%c", *yytext);	}
\n		{	ADD_TXT(yytext);	}

%%

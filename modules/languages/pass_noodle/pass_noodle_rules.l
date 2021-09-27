/*********************************
 /*
*	 @file      pass_noodle.l
*	 @author    Thomas Gijsbers (@RaichuBender)
*	 @brief     Module parser lexer
*	 @version   0.1
*	 @date      2021／09／24
*
*	 @copyright  © Copyright 2021 — Thomas Gijsbers
*	           	   All rights reserved.
*
**********************************/
%{
#include "pass_noodle.h"
#if 0
#define dbg_printf(fmt...)	printf(fmt)
#else
#define dbg_printf(fmt...)
#endif

	char *	   storage					   = NULL;
	int		   token_scope				   = 0;
	TOKEN_MODE tmd[SCOPE_MAX_DEPTH]		   = {UNSPECIFIED};
	char *	   scope_name[SCOPE_MAX_DEPTH] = {"\0"};

%}

%option prefix="module_"
%option noyywrap

%%

^#:[ \t]+.+?\n	{
	DBG_TRACEL(_USER_DESC); USER_DESC();
}

PLATFORM\s*\([a-zA-Z0-9_]+?\)	{
	STRUCT_START(PLATFORM, platform);
}

ARCHITECTURE\s*\([a-zA-Z0-9_]+?\)	{
	STRUCT_START(ARCHITECTURE, architecture);
}

LANGUAGE\s*\([a-zA-Z0-9_]+?\)	{
	STRUCT_START(LANGUAGE, language);
}

MODE\s*\([a-zA-Z0-9_]+?\)	{
	STRUCT_START(MODE, mode);
}

DisplayName:\s*.+?\n	{
	PROPERTY_LITERAL(display_name);
}

Architecture:\s*.+?\n	{
	PROPERTY_LITERAL(architecture);
}

Language:\s*.+?\n	{
	PROPERTY_LITERAL(language);
}

Endianness:\s*.+?\n	{
	PROPERTY_LITERAL(endian);
}

AddressSize:\s*.+?\n	{
	PROPERTY_LITERAL(address_size);
}

END_PLATFORM	{
	END_1(PLATFORM, platform);
}

END_ARCHITECTURE	{
	END_1(ARCHITECTURE, architecture);
}

END_LANGUAGE	{
	END_1(LANGUAGE, language);
}

END_MODE	{
	END_1(MODE, mode);
}

Size:\s*.+?\n	{
	LANG_MEMBER_1(SIZE, Size);
}

Mapping:\s*.+?\n	{
	LANG_MEMBER_2(MAPPING, Mapping);
}

Purpose:\s*.+?\n	{
	LANG_MEMBER_2(PURPOSE, Purpose);
}

REGISTER_STORAGE\s*?\(\s*.+\s*?\).*?$	{
	REGISTOR(yytext);
}

END_REGISTER_STORAGE	{
	INDENT(--token_scope);
	ADD_TXT("}\n");
	END_2();
}

INSTRUCTION_SET\s*?\(\s*.+\s*?\).*?$	{
	INSTRSET(yytext);
}

END_INSTRUCTION_SET	{
	INDENT(--token_scope);
	ADD_TXT("}\n")
	END_2();
}


REGISTER\s*\(\s*.+\s*\)	{
	REGI(REGISTER, Register);
}

FLAG\s*\(\s*.+\s*\)	{
	REGI(FLAG, Flag);
}

\}	{	// Closing bracket
	if (tmd[token_scope] == LOGIC)
	{
		ADD_TXT("\n");
		if (tmd[--token_scope] == INSTR)
		{
			INDENT(--token_scope);
			ADD_TXT("},\n")
			DECODE_INSTR();
		}
	}
	else
	{
		INDENT(--token_scope);
		ADD_TXT("},\n");
	}
}

REPR:.+?$	{
	DBG_TRACEL(_REPR); /* ++token_scope; */
	char *start = strchr(yytext, L':');
	while (((*start) == ' ') || ((*start) == '\t'))
		++start;

	REPR = malloc(strlen(start) + 1);
	strcpy(REPR, start);
}

PARAM:.+?$	{
	DBG_TRACEL(_PARAM); /* ++token_scope; */
	char *start = strchr(yytext, L':');
	while (((*start) == ' ') || ((*start) == '\t'))
		++start;

	PARAM = malloc(strlen(start) + 1);
	strcpy(PARAM, start);
}

INSTR_COUNT:.+?$	{
	DBG_TRACEL(_INSTR_COUNT); /* ++token_scope; */
	char *start = strchr(yytext, L':');
	while (((*start) == ' ') || ((*start) == '\t'))
		++start;

	INSTR_COUNT = malloc(strlen(start) + 1);
	strcpy(INSTR_COUNT, start);
}

CYCLES:.+?$	{
	DBG_TRACEL(_CYCLES); /* ++token_scope; */
	char *start = strchr(yytext, L':');
	while (((*start) == ' ') || ((*start) == '\t'))
		++start;

	CYCLES = malloc(strlen(start) + 1);
	strcpy(CYCLES, start);
}

^\s*.+?;$	{
	DBG_TRACEL(_LOGIC);

	if (tmd[token_scope] != LOGIC)
	{
		ADD_TXT("\n");
		tmd[++token_scope] = LOGIC;
	}

	INDENT(token_scope - 1);
	char *start = yytext;

	while (((*start) == ' ')||((*start) == '\t'))
		++start;

	ADD_TXT("/\/\t\t%s\n", start);
}

\".+?\"\s*:.*?GROUP\(\s*.+\s*\).*?$	{				// "{
	INSTRUCTION_GROUP(yytext);
}

\".+?\"\s*,\s*.+\s*:.*?GROUP\(\s*.+\s*\).*?$	{	// "{
	INSTRUCTION_GROUP_PARAM(yytext);
}

\".+?\":\s*.+?$	{									// "{
	INSTRUCTION_(yytext);
}

\".+?\"\s*,\s*.+\s*:\s*.+?$	{						// "{
	INSTRUCTION_PARAM(yytext);
}

\n	{}

.	{}

%%

// \#.+?\n	{	DBG_TRACEL(_COMMENT); }


/**********************************
*
*	 @file      pass_noodle.h
*	 @author    Thomas Gijsbers (@RaichuBender)
*	 @brief     Module parser primary header
*	 @version   0.1
*	 @date      2021／09／24
*
*	 @copyright  © Copyright 2021 — Thomas Gijsbers
*	           	   All rights reserved.
*
**********************************/
#ifndef __PASS_NOODLE_H__
#define __PASS_NOODLE_H__

#include "common.h"

typedef enum _INSTR_TYPE
{
	ILLIGAL = 0,
	SINGLE_REGULAR,
	SINGLE_PARAM,
	GROUPING_REGULAR,
	GROUPING_PARAM,
} INSTR_TYPE;

typedef enum _PARAM_KIND
{
	PARAM_NONE = 0,
	PARAM_REG,
	PARAM_IMM,
	PARAM_REG_ADR,
	PARAM_IMM_ADR,
	PARAM_REL_ADR,
	PARAM_IMM_ADR_OFS,
	PARAM_REG_ADR_OFS,
} PARAM_KIND;

typedef struct
{
	int			 param_idx;
	PARAM_KIND	 type;
	unsigned int reg_mem_mapping;
} PARAMETER;

typedef unsigned long long OPCODE;

char *REPR		  = NULL;
char *PARAM		  = NULL;
char *INSTR_COUNT = NULL;
char *CYCLES	  = NULL;

OPCODE		  opcode	  = 0;
char *		  operation	  = NULL;
char *		  mnemonic	  = INVALID;
int			  param_count = 0;
PARAM_KIND *  params	  = NULL;
unsigned int *param_idx	  = NULL;
INSTR_TYPE *  param_type  = NULL;
int			  instr_count = 0;
int			  cycles	  = 0;

void DECODE_INSTR(void);

#define STRUCT_START(_TYPE_, _HEADER_)             \
	{                                              \
		DBG_TRACEL(_STRUCT_##_TYPE_);              \
		ftype		   = TYPE_##_TYPE_;            \
		type_hdr	   = #_HEADER_;                \
		type_hdr_upper = #_TYPE_;                  \
                                                   \
		yytext = strchr(yytext, L'(') + 1;         \
		if (yytext == NULL)                        \
			FATAL("NULL", "NULL", "NULL", "NULL"); \
                                                   \
		*(strchr(yytext, L')')) = '\0';            \
                                                   \
		identifier = malloc(strlen(yytext) + 1);   \
		strcpy(identifier, yytext);                \
	}

#define USER_DESC()                                     \
	{                                                   \
		char *_yytext = strchr(yytext, L' ');           \
                                                        \
		if (_yytext == NULL)                            \
			_yytext = strchr(yytext, L'\t');            \
		if (_yytext == NULL)                            \
			FATAL("NULL", "NULL", "NULL", "NULL");      \
                                                        \
		*(strstr(++_yytext, "\n")) = '\0';              \
                                                        \
		while ((*_yytext == ' ') || (*_yytext == '\t')) \
			++_yytext;                                  \
                                                        \
		user_description = malloc(strlen(_yytext) + 1); \
		strcpy(user_description, _yytext);              \
	}

#define PROPERTY_LITERAL(_NAME_)                        \
	{                                                   \
		DBG_TRACEL(_PROPERTY_##_NAME_);                 \
		char *_yytext = strchr(yytext, L' ');           \
                                                        \
		if (_yytext == NULL)                            \
			_yytext = strchr(yytext, L'\t');            \
		if (_yytext == NULL)                            \
			FATAL("NULL", "NULL", "NULL", "NULL");      \
                                                        \
		*(strchr(++_yytext, L'\n')) = '\0';             \
                                                        \
		while ((*_yytext == ' ') || (*_yytext == '\t')) \
			++_yytext;                                  \
                                                        \
		_NAME_ = malloc(strlen(_yytext) + 1);           \
		strcpy(_NAME_, _yytext);                        \
	}

#define INDENT(_AMOUNT_)               \
	for (int i = _AMOUNT_; i > 0; --i) \
		ADD_TXT("\t");

#define REGI(_TYPE_, _Type_)                        \
	{                                               \
		DBG_TRACEL(_##_TYPE_);                      \
		char *name = strchr(yytext, L'(') + 1;      \
		if (name == NULL)                           \
			FATAL("NULL", "NULL", "NULL", "NULL");  \
                                                    \
		char *end = strchr(name, L')');             \
		if (end == NULL)                            \
			FATAL("NULL", "NULL", "NULL", "NULL");  \
                                                    \
		*(end) = 0;                                 \
		INDENT(token_scope);                        \
		ADD_TXT("/*" #_Type_ " %1$s: */\n", name);  \
                                                    \
		INDENT(token_scope);                        \
		ADD_TXT("{\n");                             \
                                                    \
		INDENT(++token_scope);                      \
		ADD_TXT("/*Name:    */ \"%1$s\",\n", name); \
                                                    \
		tmd[token_scope] = _TYPE_;                  \
	}

#define LANG_MEMBER_1(_NAME_, _Name_)                 \
	{                                                 \
		DBG_TRACEL(_##_NAME_);                        \
                                                      \
		char *v = strchr(yytext, L':') + 1;           \
		if (v == NULL)                                \
			FATAL("NULL", "NULL", "NULL", "NULL");    \
                                                      \
		while ((*v == ' ') || (*v == '\t'))           \
			++v;                                      \
		char *end = strchr(v, L'\n');                 \
		if (end == NULL)                              \
			end = strchr(v, L' ');                    \
		if (end == NULL)                              \
			end = strchr(v, L'\t');                   \
		if (end == NULL)                              \
			FATAL("NULL", "NULL", "NULL", "NULL");    \
                                                      \
		*end = 0;                                     \
                                                      \
		switch (tmd[token_scope])                     \
		{                                             \
		default:                                      \
		case UNSPECIFIED:                             \
			break;                                    \
                                                      \
		case REG_SPACE:                               \
			INDENT(token_scope);                      \
			ADD_TXT("/*" #_Name_ ":    */ %s,\n", v); \
			INDENT(token_scope++);                    \
			tmd[token_scope] = REG_SPACE;             \
			ADD_TXT("{\n");                           \
			break;                                    \
                                                      \
		case REGISTER:                                \
			INDENT(token_scope);                      \
			ADD_TXT("/*" #_Name_ ":    */ %s,\n", v); \
			break;                                    \
                                                      \
		case FLAG:                                    \
			break;                                    \
                                                      \
		case INSTR:                                   \
			break;                                    \
                                                      \
		case INSTR_GROUPING:                          \
			break;                                    \
		}                                             \
	}

#define LANG_MEMBER_2(_NAME_, _Name_)              \
	{                                              \
		DBG_TRACEL(_##_NAME_);                     \
		char *v = strchr(yytext, L':') + 1;        \
		if (v == NULL)                             \
			FATAL("NULL", "NULL", "NULL", "NULL"); \
                                                   \
		while ((*v == ' ') || (*v == '\t'))        \
			++v;                                   \
		char *end = strchr(v, L'\n');              \
		if (end == NULL)                           \
			end = strchr(v, L' ');                 \
		if (end == NULL)                           \
			end = strchr(v, L'\t');                \
		if (end == NULL)                           \
			FATAL("NULL", "NULL", "NULL", "NULL"); \
                                                   \
		*end = 0;                                  \
		INDENT(token_scope);                       \
		ADD_TXT("/*" #_Name_ ": */ %s,\n", v);     \
	}

void REGISTOR(char *yytext);
void INSTRSET(char *yytext);

#define END_1(_NAME_, _name_)        \
	{                                \
		DBG_TRACEL(_END_1_##_NAME_); \
		end_##_name_ = 0xDEADBEEF;   \
	}

#define END_2()                                \
	{                                          \
		DBG_TRACEL(_END_2);                    \
		char *token = scope_name[token_scope]; \
		INDENT(--token_scope);                 \
		if (token != NULL)                     \
			ADD_TXT("}; /* %s */\n\n", token)  \
		else                                   \
			ADD_TXT("};\n\n")                  \
	}

void INSTRUCTION_GROUP(char *yytext);
void INSTRUCTION_GROUP_PARAM(char *yytext);
void INSTRUCTION_(char *yytext);
void INSTRUCTION_PARAM(char *yytext);

#endif // __PASS_NOODLE_H__

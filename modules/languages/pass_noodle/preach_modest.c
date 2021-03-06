/**********************************
*
*	 @file      preach_modest.c
*	 @author    Thomas Gijsbers (@RaichuBender)
*	 @brief     Preprocessor parser main
*	 @version   0.1
*	 @date      2021／09／24
*
*	 @copyright  © Copyright 2021 — Thomas Gijsbers
*	           	   All rights reserved.
*
**********************************/

#ifndef _DEBUG

#include "preach_modest.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#else // _DEBUG

#include "preach_modest.gen.h"

#endif // _DEBUG

// Preprocessor output to be written
char prprc_out[4096 * 4096];

char *	   pTxt = prprc_out;
// Preprocessor macros
MACRO	   macro_list[1024];
int		   macro_count		= 0;
// Character before and after tokens
const char MACRO_SURROUND[] = {' ', '\t', '\n', '\r', '\0', '-', '_',  '=',	 '+', '[', ']', '(', ')', '\\',
							   '*', '&',  '^',	'%',  '!',	'~', '\'', '\"', '<', '>', ',', '.', '/'};

static char *adjust_format(char *yytext);
static void	 save_output(void);

int	   main_argc;
char **main_argv;

int main(int argc, const char *argv[])
{
	DBG_TRACE(main);
	// printf("\nRaichu's Decomp Spec Parser\nv%d.%d\n", VERSION);

	yylex();

	main_argc = argc;
	main_argv = (char **)argv;

	save_output();

	return 0;
}

#define DO_NOT_EDIT_TEXT "# This file was generated by the spec parser.\n# Do not edit this file!\n\n"

static void save_output(void)
{
	DBG_TRACE(save_output);

	// char *fmt_adjusted = adjust_format(prprc_out);
	char *file_name = main_argv[1];

	FILE *fp = fopen(file_name, "wb");
	fprintf(fp, DO_NOT_EDIT_TEXT "%s\n", prprc_out);
}

// Adjust text, so a format string '%' will be escaped to '%%'
static char *adjust_format(char *yytext)
{
	char *fmt_adjusted = malloc(4096 * 4096);
	int	  j			   = 0;
	for (int i = 0; yytext[i] != NULL_TERM; ++i)
	{
		char c			  = yytext[i];
		fmt_adjusted[j++] = c;

		if (c == '%')
			fmt_adjusted[j++] = '%';
	}
	fmt_adjusted[j] = NULL_TERM;

	return fmt_adjusted;
}

/**
 * @name	PROCESS_MACRO
 * @brief	Parse the macro declaration,
 * 			and prepare for substitution.
 *
 * @param[in] yytext	Pointer to macro declaration string
 *
 * @returns				Pointer to the end of the declaration string
 */
static char *PROCESS_MACRO(char *yytext, MACRO_TYPE t)
{
	DBG_TRACE(PROCESS_MACRO);
	int argc = 0;

	char *fmt_adjusted = adjust_format(yytext);

	DBG_DUMP("/* %s\n*/\n", fmt_adjusted);

	MACRO *macro = &macro_list[macro_count];

	char *label	  = strchr(fmt_adjusted, L':') + 1;
	char *arglist = strchr(label, L'(');
	*(arglist++)  = NULL_TERM;

	macro->argv		  = malloc(3 * sizeof(char *));
	macro->argv[argc] = malloc(strlen(label));
	strcpy(macro->argv[argc++], label);

	BOOL done = FALSE;
	for (char *arg = arglist; !done; arg = arglist)
	{
		// Strip whitespace before
		while ((*arg == ' ') || (*arg == '\t'))
			++arg;

		char *endarg = strchr(arg, L',');
		char *endall = strchr(arg, L')');

		done = (endarg == NULL) || (endarg > endall);
		if (done)
			endarg = endall;

		if (arg >= endarg)
		{
			char argNo[4];
			sprintf(argNo, "argv[%d]", argc);
			WARN("argument couldn't be parsed", label, argNo, "(arg >= endarg)");
			break;
		}

		if (endarg == NULL)
		{
			char argNo[4];
			sprintf(argNo, "argv[%d]", argc);
			WARN("argument couldn't be parsed", label, argNo, "(endarg == NULL)");
			break;
		}

		*endarg = NULL_TERM;
		arglist = endarg + 1;

		// Strip whitespace after
		while ((endarg[-1] == ' ') || (endarg[-1] == '\t'))
			*(--endarg) = NULL_TERM;

		macro->argv[argc] = malloc(strlen(arg));
		strcpy(macro->argv[argc++], arg);
	}

	macro->argc = argc;

	OUTPUT_DBG_DOC("/*!\t[macro]\n *\t@name\t%s\n", macro->argv[0]);
	if (macro->argc > 1)
		for (int i = 1; i < macro->argc; ++i)
			OUTPUT_DBG_DOC(" *\t\t@param\t%s\n", macro->argv[i]);

	return arglist;
}

/**
 * @name	EXPAND_MACRO
 * @brief	Prepare macro expansion
 *
 * @param[in]	macro_begin	Pointer to start of macro definition
 * 							(before "=BEGIN")
 */
static void EXPAND_MACRO(char *macro_begin)
{
	DBG_TRACE(EXPAND_MACRO);
	MACRO *macro = &macro_list[macro_count];

	char *expand = strstr(macro_begin, "=BEGIN");
	for (char *c = macro_begin; c < expand; ++c)
		if ((*c != ' ')
		&&  (*c != '\t')
		&&  (*c != '\n'))
			expand = NULL;

	if (expand == NULL)
		exit(-1);

	macro_begin = expand + 6;
	while ((*macro_begin == ' ') || (*macro_begin == '\t') || (*macro_begin == '\n'))
		++macro_begin;

	char *macro_end = strstr(macro_begin, "=END");

	if (macro_end == NULL)
		exit(-1);

	*macro_end = NULL_TERM;

	macro->expand = malloc(macro_end - macro_begin);

	strcpy(macro->expand, macro_begin);
}

/**
 * @name	PROCESS_MACRO_EXPANSION
 * @brief	Process the macro definition.
 * 			 -	This function assumes the expected
 * 				preparations have been done beforehand.
 * 				See flex rules for examples.
 */
static void PROCESS_MACRO_EXPANSION(void)
{
	DBG_TRACE(PROCESS_MACRO_EXPANSION);
	MACRO *macro = &macro_list[macro_count];

	/*	  Pointer to source text as is */
	char *unprocessed = macro->expand; /* The expand buffer will be discarded
										  and replaced by new post-proc buffer.	*/
	/*	  Pointer to destination buffer for macro expansion */
	char *processed	  = malloc(4096 * 4096); /* HACK  words can not express
													   TODO  calculate length alloc size at runtime	*/

	size_t len_unprocessed = strlen(unprocessed);
	char * end_unprocessed = unprocessed + len_unprocessed;

	/*	Macro substitution source offset */
	int iSrc = 0;
	/*	Macro substitution destination offset */
	int iDst = 0;

	for (; iSrc < len_unprocessed; ++iSrc)
	{
		/*   Has processing been done? */
		BOOL bIsPrcd = FALSE;

		// #if 0 // TODO
		struct
		{
			BOOL preceding;
			BOOL succeeding;
		}
		/* Whether characters directly surrounding the token are
		   white space or special characters. In essence we want to
		   ensure that we aren't substituting partial tokens with others.
			- E.g. `&BUILD;` is valid when substituting for 'BUILD',
					but  `&BUILDING;` isn't.	*/
		bValidChr = {FALSE, FALSE};
		/* Valid characters are defined in `const char MACRO_SURROUND[]` further above. */

		for (int iChk = 0; iChk < strlen(MACRO_SURROUND); ++iChk)
			if (unprocessed[iSrc - 1] == MACRO_SURROUND[iChk])
			{
				bValidChr.preceding = TRUE;
				goto valid_before; /* Could also just use `break` here,
									  but this'll prevent refactoring
									  tedium later down the line	*/
			}

		goto after_check;

	valid_before:
		if (bValidChr.preceding == FALSE)
			goto after_check;
		// #endif

		for (int iArg = 1; iArg < macro->argc; ++iArg)
		{
			static char SUBST[4]; // TODO currently limited to one digit (0-9)
			sprintf(SUBST, "%%%d$s", iArg);

			char *arg	 = macro->argv[iArg];
			int	  arglen = strlen(arg);

			// #if 0 // TODO
			for (int iChk = 0; iChk < strlen(MACRO_SURROUND); ++iChk)
				if (unprocessed[iSrc + arglen] == MACRO_SURROUND[iChk])
				{
					bValidChr.succeeding = TRUE;
					goto valid_after;
				}

		valid_after:
			// if ((bValidChr.succeeding) && (!memcmp(&unprocessed[iSrc], arg, arglen)))
			// #endif
			if (!memcmp(&unprocessed[iSrc], arg, arglen))
			{
				*(unsigned long *)(&processed[iDst]) = *(unsigned long *)SUBST;
				iDst += 4;
				iSrc += arglen - 1;
				bIsPrcd = TRUE;
				goto after_check;
			}
		}

	after_check:
		if (bIsPrcd == FALSE)
			processed[iDst++] = unprocessed[iSrc];
	}

	macro->expand = processed;
	free(unprocessed);
}

/**
 *
 */
static void REPLACE_MACRO(char *yytext)
{
	DBG_TRACE(REPLACE_MACRO);
	char * name_end = strchr(yytext, L'(');
	size_t sz		= name_end - (yytext + 2);

	// TODO macros can have zero arguments, so only perform
	//     check if the macro SHOULD have an open bracket.

#if 0 // Disabled for now
	if (name_end == NULL)
		FATAL("missing macro arguments", yytext, "(nullptr)", "Did you assign the macro correctly?\n");
#endif

	if (sz <= 0)
		FATAL("size of macro label must be bigger than zero", yytext, "(nullptr)",
			  "Did you assign the macro correctly?\n");

	char *name = malloc(sz);
	memcpy(name, yytext + 2, sz);
	name[sz] = NULL_TERM;

	MACRO *macro = malloc(sizeof(MACRO));

	size_t line_sz = strchr(yytext + 2, L'\n') - (yytext + 2);
	char * label   = malloc(line_sz);
	memcpy(label, yytext + 2, line_sz);
	char *arglist = strchr(label, L'(');
	*(arglist++)  = NULL_TERM;

	int argc		  = 0;
	macro->argv		  = malloc(3 * sizeof(char *));
	macro->argv[argc] = malloc(strlen(label));
	strcpy(macro->argv[argc++], label);

	BOOL done = FALSE;
	for (char *arg = arglist; !done; arg = arglist)
	{
		// Strip whitespace before
		while ((*arg == ' ') || (*arg == '\t'))
			++arg;

		char *endarg = strchr(arg, L',');
		char *endall = strchr(arg, L')');

		done = (endarg == NULL) || (endarg > endall);
		if (done)
			endarg = endall;

		if (arg >= endarg)
		{
			char argNo[4];
			sprintf(argNo, "->argv[%d]", argc);
			WARN("argument couldn't be parsed", label, argNo, "(arg >= endarg)");
			break;
		}

		if (endarg == NULL)
		{
			char argNo[4];
			sprintf(argNo, "->argv[%d]", argc);
			WARN("argument couldn't be parsed", label, argNo, "(endarg == NULL)");
			break;
		}

		*endarg = NULL_TERM;
		arglist = endarg + 1;

		// Strip whitespace after
		while ((endarg[-1] == ' ') || (endarg[-1] == '\t'))
			*(--endarg) = NULL_TERM;

		macro->argv[argc] = malloc(strlen(arg) + 1);
		strcpy(macro->argv[argc++], arg);
	}

	macro->argc = argc;

	if (macro_count <= 0)
		FATAL("macro not found", yytext, name, "There aren't any macros defined.");

	MACRO *m;
	int	   mC;
	for (int iM = 0; iM < macro_count; ++iM)
	{
		m = &macro_list[iM];

#pragma push
		// #define DBG_DUMP printf
		DBG_DUMP("Macro: %s\n", m->argv[0]);
#pragma pop

		if (0 == strcmp(name, m->argv[0]))
		{
			mC = iM;
			goto macro_found;
		}
	}

	size_t sMstrs = 0;
	for (int i = 0; i < macro_count; ++i)
	{
		m = &macro_list[i];
		sMstrs += strlen(m->argv[0]) + 1;
	}
	char *validMacros = malloc(sMstrs);
	char *txtOfs	  = validMacros;
	for (int i = 0; i < macro_count; ++i)
	{
		m	   = &macro_list[i];
		txtOfs = strcpy(txtOfs, m->argv[0]);
		txtOfs += strlen(txtOfs);
		*(txtOfs++) = '\n';
	}

	FATAL("macro not found\nValid macros are:\n%s", validMacros, yytext, name,
		  "Either the requested token was not defined, or an incorrect format was specified.\n");

macro_found:
	m = &macro_list[mC];
	if (macro->argc != m->argc)
		FATAL("argument mismatch", yytext, name, "Too many/not enough arguments specified in macro substitution.\n");

	ADD_TXT(m->expand, macro->argv[1], macro->argv[2]); /*, macro->argv[3], macro->argv[4], macro->argv[5],
				 macro->argv[6], macro->argv[7], macro->argv[8], macro->argv[9], macro->argv[10]);
 */
	// OUTPUT_DBG_DOC("%s: %s, %s", m->expand, m->argv[1], m->argv[2]);
}

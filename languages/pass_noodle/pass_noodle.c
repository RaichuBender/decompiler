/**
 * @file	pass_noodle.c
 * @brief		Module parser main
 *
 * @author	Thomas Gijsbers (@RaichuBender)
 */

#ifndef _SYNTAX

#include "parse_module.h"
#include <stdio.h>

#define ADD_TXT(...) ;

#else // _SYNTAX

#include "parse_module.gen.h"

#endif // _SYNTAX

int main(int argc, const char *argv[])
{
	yylex();

	switch (ftype)
	{
	case TYPE_PLATFORM:

		ADD_TXT("PLATFORM %1$s =\n{\n\t\"%1$s\",\n", identifier);

		if (display_name != NULL)
			ADD_TXT("\t\"%s\",\n", display_name)
		else
			ADD_TXT("\t\"%s\",\n", identifier)

		if (user_description != NULL)
			ADD_TXT("\t\"%s\",\n", user_description)
		else
			ADD_TXT("\tNO_DESCRIPTION,\n")

		ADD_TXT("\t\"%s\",\n", architecture);
		ADD_TXT("\t%s,\n", endian);
		ADD_TXT("\t%s,\n", address_size);
		ADD_TXT("};");

		if ((identifier == NULL) || (architecture == NULL) || (endian == NULL) || (address_size == NULL) ||
			(end_platform == NULL))
		{
			fprintf(stderr, "\n[raichu spec parse]  FATAL\n\tMissing elements.\n\n");
			exit(-1);
		}

		break;

	case TYPE_ARCHITECTURE:

		ADD_TXT("ARCHITECTURE %1$s =\n{\n\t\"%1$s\",\n", identifier);

		if (display_name != NULL)
			ADD_TXT("\t\"%s\",\n", display_name)
		else
			ADD_TXT("\t\"%s\",\n", identifier)

		if (user_description != NULL)
			ADD_TXT("\t\"%s\",\n", user_description)
		else
			ADD_TXT("\tNO_DESCRIPTION,\n")

		ADD_TXT("\t\"%s\",\n", language);
		ADD_TXT("};");

		if ((identifier == NULL) || (language == NULL))
		{
			fprintf(stderr, "\n[raichu spec parse]  FATAL\n\tMissing elements.\n\n");
			exit(-1);
		}

		break;

	case TYPE_LANGUAGE:

		ADD_TXT("LANGUAGE %1$s =\n{\n\t\"%1$s\",\n", identifier);

		if (display_name != NULL)
			ADD_TXT("\t\"%s\",\n", display_name)
		else
			ADD_TXT("\t\"%s\",\n", identifier)

		if (user_description != NULL)
			ADD_TXT("\t\"%s\",\n", user_description)
		else
			ADD_TXT("\tNO_DESCRIPTION,\n")

		ADD_TXT("};");

		if (identifier == NULL)
		{
			fprintf(stderr, "\n[raichu spec parse]  FATAL\n\tMissing elements.\n\n");
			exit(-1);
		}

		break;

	case TYPE_MODE:

		if ((identifier == NULL) || (architecture == NULL) || (endian == NULL) || (address_size == NULL) ||
			(end_platform == NULL))
		{
			fprintf(stderr, "\n[raichu spec parse]  FATAL\n\tMissing elements.\n\n");
			exit(-1);
		}

		break;

	default:

		fprintf(stderr, "\n[raichu spec parse]  FATAL\n\tUnrecognized spec file type.\n\n");
		exit(-1);
	}

	char file_name[260];
	sprintf(file_name, "src/%s.module.c", identifier);

	FILE *fp = fopen(file_name, "wb");
	fprintf(fp, "#include \"%s.h\"\n\n%s\n", type_hdr, final_out);

	char def_cmd[1024];
	sprintf(def_cmd,

			"echo	\"extern %3$s %1$s;\"	"
			"	>>	include/%2$s_def.inc.0	"

			"&&"

			"echo	\"%1$s,\"				"
			"	>>	include/%2$s_def.inc.	",

			identifier, type_hdr, type_hdr_upper);

	system(def_cmd);

	return 0;
}

/**
 * @name	PROCESS_MACRO
 * @brief		Parse the macro declaration,
 * 				and prepare for substitution.
 * @param[in] yytext	Pointer to macro declaration string
 * @returns		Pointer to the end of the declaration string
 */
static char *PROCESS_MACRO(char *yytext)
{
	int argc = 0;

	char adjust[2048];
	int	 j = 0;
	for (int i = 0; yytext[i] != '\0'; ++i)
	{
		char c = yytext[i];
		adjust[j++] = c;
		if (c == '%')
			adjust[j++] = '%';
	}
	adjust[j] = '\0';

	DBG_DUMP("/* %s\n*/\n", /*yytext*/ adjust);

	MACRO *macro = &macro_list[macro_count];

	char *label = strchr(/*yytext*/ adjust, L':') + 1;
	char *arglist = strchr(label, L'(');
	*(arglist++) = '\0';

	macro->argv = malloc(3 * sizeof(char *));
	macro->argv[argc] = malloc(strlen(label));
	strcpy(macro->argv[argc++], label);

	BOOL done = FALSE;
	for (char *arg = arglist; done == FALSE; arg = arglist)
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
			WARN("(arg >= endarg)");
			break;
		}

		if (endarg == NULL)
		{
			WARN("(endarg == NULL)");
			break;
		}

		*endarg = '\0';
		arglist = endarg + 1;

		// Strip whitespace after
		while ((endarg[-1] == ' ') || (endarg[-1] == '\t'))
			*(--endarg) = '\0';

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
 * @brief		Prepare macro expansion
 * @param	macro_begin	Pointer to start of macro definition
 * 						(before "=BEGIN")
 */
static void EXPAND_MACRO(char *macro_begin)
{
	MACRO *macro = &macro_list[macro_count];

	char *expand = strstr(macro_begin, "=BEGIN");
	for (char *c = macro_begin; c < expand; ++c)
		if ((*c != ' ') && (*c != '\t') && (*c != '\n'))
			expand = NULL;

	if (expand == NULL)
		exit(-1);

	macro_begin = expand + 6;
	while ((*macro_begin == ' ') || (*macro_begin == '\t') || (*macro_begin == '\n'))
		++macro_begin;

	char *macro_end = strstr(macro_begin, "=END");

	if (macro_end == NULL)
		exit(-1);

	*macro_end = '\0';

	macro->expand = malloc(macro_end - macro_begin);

	strcpy(macro->expand, macro_begin);
}

/**
 * @name	PROCESS_MACRO_EXPANSION
 * @brief		Process the macro definition,
 * 				provided it has been prepared
 */
static void PROCESS_MACRO_EXPANSION(void)
{
	MACRO *macro = &macro_list[macro_count];

	char *unprocessed = macro->expand;
	char *end_unprocessed = strlen(unprocessed);
	char *processed = malloc(2048);

	int iDst = 0;
	for (int iSrc = 0; iSrc < end_unprocessed; ++iSrc)
	{
		BOOL bIsPrcd = FALSE;
		BOOL bValidBefore = FALSE;
		BOOL bValidAfter = FALSE;

		for (int iChCr = 0; iChCr < strlen(MACRO_SURROUND); ++iChCr)
			if (unprocessed[iSrc - 1] == MACRO_SURROUND[iChCr])
			{
				bValidBefore = TRUE;
				goto valid_before;
			}

	valid_before:
		if (bValidBefore != FALSE)
			for (int iArg = 1; iArg < macro->argc; ++iArg)
			{
				static char SUBST[4] = "derp";
				sprintf(SUBST, "%%%d$s", iArg);

				char *arg = macro->argv[iArg];
				int	  arglen = strlen(arg) - 1;

				for (int iChCr = 0; iChCr < strlen(MACRO_SURROUND); ++iChCr)
					if (unprocessed[iSrc + arglen + 1] == MACRO_SURROUND[iChCr])
					{
						bValidAfter = TRUE;
						goto valid_after;
					}

			valid_after:
				if ((bValidAfter != FALSE) && (!memcmp(&unprocessed[iSrc], arg, arglen)))
				{
					*(unsigned long *)(&processed[iDst]) = *(unsigned long *)SUBST;
					iDst += 4;
					iSrc += arglen;
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

	// tmp preview
	/*	char *tmp = malloc(2048);
		sprintf(tmp, processed, "/dst_reg/", "/opcode/");
		ADD_TXT(tmp, "/src_reg/");	*/
}

/**********************************
*
*	 @file      pass_noodle.c
*	 @author    Thomas Gijsbers (@RaichuBender)
*	 @brief     Module parser main
*	 @version   0.1
*	 @date      2021／09／24
*
*	 @copyright  © Copyright 2021 — Thomas Gijsbers
*	           	   All rights reserved.
*
**********************************/

#ifndef _SYNTAX

#include "pass_noodle.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#else // _SYNTAX

#include "pass_noodle.gen.h"

#endif // _SYNTAX


#define LEX(_type_)  \
	{                \
		lt = _type_; \
		yylex();     \
	}


#define DO_NOT_EDIT_TEXT                                \
	"/* This file was generated by the spec parser.\n " \
	"  Do not edit this file! */\n\n"


/**********************************
*
*	 @brief	Seek past whitespace
*
*    @param[inout] pDST variable reference (?)
*						to seek from and update
*						it's address
*
*   	 @note	Does NOT seek for
*				newlines or comments
*
**********************************/
#define SKIP_WHITESPACE(pDST)                         \
	{                                                 \
		ASSERT(pDST != NULL);                         \
		while (((*pDST) == ' ') || ((*pDST) == '\t')) \
			++pDST;                                   \
	}


/**********************************
*
*	 @brief	Seek backwards, before whitespace.
*
*    @param[inout] pDST variable reference (?)
*						to seek from and update
*						it's address
*
*    	@note	Does NOT seek for
*				newlines or comments
*
**********************************/
#define SKIP_WHITESPACE_BCKWDS(pDST)                  \
	{                                                 \
		ASSERT(pDST != NULL);                         \
		while (((*pDST) == ' ') || ((*pDST) == '\t')) \
			--pDST;                                   \
	}


/**********************************
*
*	 @brief	Seek FOR whitespace
*
*    @param[inout] pDST variable reference (?)
*						to seek from and update
*						it's address
*
*    	@note	Does NOT seek for
*				newlines or comments
*
**********************************/
#define SEEK_WHITESPACE(pDST, pSEEK)       \
	{                                      \
		pDST	  = strchr(pSEEK, L' ');   \
		char *tmp = strchr(pSEEK, L'\t');  \
		if ((tmp != NULL) && (tmp < pDST)) \
			pDST = tmp;                    \
		ASSERT(pDST != NULL);              \
	}


/**********************************
*
*	 @brief	Seek for newline
*			'\n' character
*
*    @param[inout] pDST variable reference (?)
*						to seek from and update
*						it's address
*
*   	 @note	Does NOT seek for
*				any other type of
*				white space
*
**********************************/
#define SEEK_NEWLINE(pDST, pSEEK)    \
	{                                \
		pDST = strchr(pSEEK, L'\n'); \
		ASSERT(pDST != NULL);        \
	}

#define SEEK_NULL_TERM(pDST, pSEEK)  \
	{                                \
		pDST = strchr(pSEEK, L'\0'); \
		ASSERT(pDST != NULL);        \
	}


#define PREVIEW_INSTR(_TYPE_, _type_)         \
	INDENT(token_scope);                      \
	ADD_TXT("/** INSTRUCTION " #_type_ "\n"); \
	INDENT(token_scope);                      \
	ADD_TXT("  * %s */\n", yytext);           \
	INDENT(token_scope);                      \
	ADD_TXT("{\n");                           \
	++token_scope;                            \
	tmd[token_scope] = _TYPE_;


/*********************************
*
*	@brief
*
*	Global variables —
*	used for providing necessary
*	informatiom during parsing of
*	context sensitive tokens
*
*	Currently in the process
*	of implementing a fully
*	functional abstract syntax
*	tree with psuedo-C
*	decompilation.
*
**********************************/

/*********************************
*	Final output to be written
**********************************/
char final_out[4096 * 4096];

/*********************************
*	Pointer to output text buffer
**********************************/
char *pTxt = final_out;

/*********************************
*	Common accross all types
**********************************/
char *	  identifier	   = NULL;
char *	  display_name	   = NULL;
char *	  user_description = NULL;

/*********************************
*	Type specific
**********************************/
char *	  architecture	   = NULL;
char *	  language		   = NULL;
char *	  endian		   = NULL;
char *	  address_size	   = NULL;

/*********************************
*	Block end markers
**********************************/
char *	  end_platform	   = NULL;
char *	  end_architecture = NULL;
char *	  end_language	   = NULL;
char *	  end_mode		   = NULL;

/*********************************
*	Type detected from parsed file
**********************************/
FILE_TYPE ftype			   = INVALID;
char *	  type_hdr;
char *	  type_hdr_upper;

static void parse_level_0(void);
static void parse_level_1(void);
static void save_output(void);

char * level_0;

int	   main_argc;
char **main_argv;

/**********************************
 *	Temporary for grouped instructions
 **********************************/
char  grouping_buf[64][2048];
char *grouping_end[64];
/*	  Store pointer to restore	*/
char *pTxtCpy		   = NULL;
int	  grouping_counter = 0;

/*********************************
*
*    @brief	Main Entry
*
*    @param[in]	argc 
*    @param[in]	argv 
*
*    @return	int 
*
*********************************/
int main(int argc, const char *argv[])
{
	DBG_TRACE(main);
	// printf("\nRaichu's Decomp Spec Parser\nv%d.%d\n", VERSION);

	main_argc = argc;
	main_argv = (char **)argv;

	parse_level_0();
	save_output();

	return 0;
}


/**********************************
*
*	 @brief     
*
**********************************/
static void save_output(void)
{
	DBG_TRACE(save_output);

	char file_name[260];
	sprintf(file_name, "src/%s.ndl.c", identifier);
//  BUGBUG will segfault if directory src/ doesn't exist

	FILE *fp = fopen(file_name, "wb");
	fprintf(fp, DO_NOT_EDIT_TEXT
			"#include \"%s.h\"\n\n",
			type_hdr);
	fprintf(fp, "%s\n\n%s\n\n",
			"#define BYTES *8\n#define BITS *1\n",
			final_out);

	char def_cmd[1024];
	sprintf(def_cmd,						   //\n
			"echo	\"extern %3$s %1$s;\""	   //\n
			"	>>	include/%2$s_def.0.gen.h"  //\n
			"&&"							   //\n
			"echo	\"%1$s,\""				   //\n
			"	>>	include/%2$s_def.1.gen.h", //\n
			identifier, type_hdr, type_hdr_upper);

	system(def_cmd);
}


/**********************************
*
*	 @brief     
*
**********************************/
static inline void PARSE_PLATFORM_L0(void)
{
	DBG_TRACE(PARSE_PLATFORM_L0);

	if ((identifier == NULL) || (architecture == NULL) || (endian == NULL) || (address_size == NULL) ||
		(end_platform == NULL))
		FATAL("missing elements", "-", "-", "-");

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
}


/**********************************
*
*	 @brief     
*
**********************************/
static inline void PARSE_ARCHITECTURE_L0(void)
{
	DBG_TRACE(PARSE_ARCHITECTURE_L0);

	if ((identifier == NULL) || (language == NULL) || (end_architecture == NULL))
		FATAL("missing elements", "-", "-", "-");

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
}


/**********************************
*
*	 @brief     
*
**********************************/
static inline void PARSE_LANGUAGE_L0(void)
{
	DBG_TRACE(PARSE_LANGUAGE_L0);

	if ((identifier == NULL) || (end_language == NULL))
		FATAL("missing elements", "-", "-", "-");

	ADD_TXT("LANGUAGE %1$s =\n{\n\t\"%1$s\",\n", identifier);

	if (display_name != NULL)
		ADD_TXT("\t\"%s\",\n", display_name)
	else
		ADD_TXT("\t\"%s\",\n", identifier)

	if (user_description != NULL)
		ADD_TXT("\t\"%s\",\n", user_description)
	else
		ADD_TXT("\tNO_DESCRIPTION,\n")

	ADD_TXT("};\t// %s", identifier);
}


/**********************************
*
*	 @brief     
*
**********************************/
static inline void PARSE_MODE_L0(void)
{
	DBG_TRACE(PARSE_MODE_L0);
	// TODO
	if ((identifier == NULL) || (end_mode == NULL))
		FATAL("missing elements", "-", "-", "-");
}


/**********************************
*
*	 @brief     
*
**********************************/
static void parse_level_0(void)
{
	DBG_TRACE(parse_level_0);
	yylex();

	switch (ftype)
	{
	case TYPE_PLATFORM:
		PARSE_PLATFORM_L0();
		break;

	case TYPE_ARCHITECTURE:
		PARSE_ARCHITECTURE_L0();
		break;

	case TYPE_LANGUAGE:
		PARSE_LANGUAGE_L0();
		break;

	case TYPE_MODE:
		PARSE_MODE_L0();
		break;

	default:
		FATAL("unrecognized spec file type", "-", "-", "-");
	}
}


/**********************************
*
*	 @brief     
*
*    @param yytext 
*
**********************************/
void REGISTOR(char *yytext)
{
	DBG_TRACE(REGISTOR);

	char *space = strchr(yytext, L'(') + 1;
	char *end	= strchr(space, L')');
	if (end == NULL)
		return; // TODO bail out and show FATAL ERR

	*(end) = 0;

	free(scope_name[++token_scope]);

	scope_name[token_scope] = malloc(32);
	sprintf(scope_name[token_scope], "register_store_%s", space);

	ADD_TXT("REGISTER_STORAGE %s =\n{\n", scope_name[token_scope]);

	tmd[token_scope] = REG_SPACE;
}


/**********************************
*
*	 @brief     
*
*    @param yytext 
*
**********************************/
void INSTRSET(char *yytext)
{
	DBG_TRACE(INSTRSET);
	char *name			  = strchr(yytext, L'(') + 1;
	*(strchr(name, L')')) = 0;

	free(scope_name[++token_scope]);
	tmd[token_scope] = INSTR_SET;

	scope_name[token_scope] = malloc(32);
	sprintf(scope_name[token_scope], "%s", name);

	ADD_TXT("INSTRUCTION_SET %s =\n{\n", name);

	INDENT(token_scope);
	ADD_TXT("/*Name:    */ \"%s\",\n", name);

	INDENT(token_scope++);
	ADD_TXT("{\n");

	tmd[token_scope] = INSTR_SET;
}


/**********************************
*
*	 @brief     Query param type
*				by string ref
*
*    @param[in] str string
*				representation of
*				parameter or symbol
*				(register) type to
*				search for matching
*				param
*
*    @return	PARAM_KIND 
*
*  	 		@note	This might not
* 					be feasible to do
* 					during runtime
*
**********************************/
PARAM_KIND get_param_type(char *str)
{
	ASSERT(str != NULL);

#if 1 // TODO param type

	if ((0 == strcmp(str, "IMM8"  )) || (0 == strcmp(str, "imm8"  )))
		return PARAM_IMM;
	if ((0 == strcmp(str, "IMM8_R")) || (0 == strcmp(str, "imm8_r")))
		return PARAM_REL_ADR;
	if ((0 == strcmp(str, "IMM16" )) || (0 == strcmp(str, "imm16" )))
		return PARAM_IMM_ADR;

	return PARAM_NONE;

#else
	unsigned char cmp = 0;
	cmp	=  ((0 == strcmp(str, "REG"   )) || (0 == strcmp(str, "reg"   )))		||
		  (((0 == strcmp(str, "IMM8"  )) || (0 == strcmp(str, "imm8"  ))) << 1) ||
		  (((0 == strcmp(str, "(HL)"  )) || (0 == strcmp(str, "(hl)"  ))) << 2) ||
		  (((0 == strcmp(str, "IMM16" )) || (0 == strcmp(str, "imm16" ))) << 3) ||
		  (((0 == strcmp(str, "IMM8_R")) || (0 == strcmp(str, "imm8_r"))) << 4) ||
		  (((0 == strcmp(str, "IMM8"  )) || (0 == strcmp(str, "imm8"  ))) << 5) ||
		  (((0 == strcmp(str, "IMM8"  )) || (0 == strcmp(str, "imm8"  ))) << 6) ||
		  (((0 == strcmp(str, "IMM8"  )) || (0 == strcmp(str, "imm8"  ))) << 7);

	switch (cmp)
	{
	case (0):	return PARAM_NONE;
	case (1):	return PARAM_REG;
	case (2):	return PARAM_IMM;
	case (4):	return PARAM_REG_ADR;
	case (8):	return PARAM_IMM_ADR;
	case (16):	return PARAM_REL_ADR;
	case (32):	return PARAM_IMM_ADR_OFS;
	case (64):	return PARAM_REG_ADR_OFS;
	}
#endif
}


/*****************************************************
*	Instruction parameters in variadic array		 *
*****************************************************/
static inline char *PROC_PARAMS(char *in)
{

#if 1	// TODO params
	char *prm_start = strchr(in, L',') + 1;
	char *prm_end	= strchr(in, L':');

	ASSERT((prm_start != NULL) && (prm_end != NULL));

	SKIP_WHITESPACE(prm_start);
	// SKIP_WHITESPACE_BCKWDS(prm_end);
	(*prm_end) = 0;

	switch (get_param_type(prm_start))
	{
	case PARAM_IMM:		imm_chars = 2;	 break;	// operand imm8:    1
	case PARAM_REL_ADR:	imm_chars = 3;	 break; // operand imm8_r:  1s + pc_next
	case PARAM_IMM_ADR:	imm_chars = 4;	 break;	// operand imm16:   2, 1
	default:			imm_chars = 0;	 break;
	}

	return prm_end + 1;
#else
	/** Linked list to account for complex
	 * machine instructions	*/
	typedef struct _local_param_list
	{
		PARAMETER prm;
		void	 *pNext;
	} local_param_list;


	char *prm_start = strchr(next, L',');
	char *prm_end	= strchr(next, L':');


	local_param_list *pPrm_list = malloc(sizeof(local_param_list));
	local_param_list *pl		= pPrm_list;

	ASSERT((prm_start != NULL) && (prm_end != NULL));

	SKIP_WHITESPACE_BCKWDS(prm_end);
	(*prm_end) = 0;

	for ( ; (prm_start != NULL) && (prm_start++ < prm_end)
		  ; pl->pNext = malloc(sizeof(local_param_list))
		  , pl = pl->pNext )
	{
		SKIP_WHITESPACE(prm_start);

		PARAM_KIND get_param_type(char *str);

		pl->prm.param_idx		= 0;
		pl->prm.type			= get_param_type(prm_start);
		switch (pl->prm.type)
		{
		case PARAM_IMM:		PARAM = "%02x";	 break;	// operand 1
		case PARAM_IMM_ADR:	PARAM = "%04x";	 break;	// operand 2, 1
		case PARAM_REL_ADR:	PARAM = "%04x";	 break; // operand 1s = pc_next
		}
		pl->prm.reg_mem_mapping = 0;

		prm_start = strchr(prm_start, L',');
	}

	return prm_end + 1;

#endif // 0

}

/*****************************************************
*	Instruction type								 *
*****************************************************/
static inline char *PROC_TYPE(char *type_start)
{
	char *type_end;

	SKIP_WHITESPACE(type_start);
	SEEK_WHITESPACE(type_end, type_start);

	(*type_end) = 0;

	free(operation);
	operation = malloc(strlen(type_end) + 1);
	strcpy(operation, type_start);

	return type_end + 1;
}

/*****************************************************
*	Instruction's unique OP code					 *
*****************************************************/
static inline char *PROC_OP(char *op_start)
{
	char *op_end;

	SKIP_WHITESPACE(op_start);
	SEEK_WHITESPACE(op_end, op_start);

	(*op_end) = 0;

	opcode	  = strtoull(op_start, NULL, 16);

	return op_end + 1;
}

/*****************************************************
*	Bytes count of instruction (opcode + operands)	 *
*****************************************************/
static inline char *PROC_COUNT(char *cnt_start)
{
	char *cnt_end;

	SKIP_WHITESPACE(cnt_start);
	SEEK_WHITESPACE(cnt_end, cnt_start);

	(*cnt_end) = 0;

	instr_count = strtoul(cnt_start, NULL, 10);

	return cnt_end + 1;
}

/*****************************************************
*	Machine ticks in relative clock cycles			 *
*****************************************************/
static inline char *PROC_CYCLES(char *cy_start)
{
	char *cy_end;

	SKIP_WHITESPACE(cy_start);
	SEEK_NULL_TERM(cy_end, cy_start);

	(*cy_end) = 0;

	cycles = strtoul(cy_start, NULL, 10);

	return cy_end + 1;
}

int	  group_cnt;
int	  group_ofs;
char  REPR_ARR[64][32];
int	  instr_count_ARR[64];
int	  cycles_ARR[64];

/*********************************
*
*	 @brief		Parse instruction specification into
*				C structure format for easy access
*				during runtime
*
*    @param[in]	raw_str 
*    @param[in]	type 
*
**********************************/
void PROC_INSTR(char *raw_str, INSTR_TYPE type)
{
	fprintf(stderr, "%s\n", raw_str);

	char *start = strchr(raw_str, L'\"') + 1;
	ASSERT(start != NULL);

	char *end	= strchr(start, L'\"');
	ASSERT(end != NULL);

	(*end)	   = 0;
	char *next = end + 1;

/*****************************************************
*	Instruction mnemonic parsable string			 *
*****************************************************/
	REPR = malloc(strlen(start) + 1);
	strcpy(REPR, start);

	PARAM		= NULL;
	param_count = 0;


	switch (type)
	{
	case SINGLE_REGULAR:
		next = strchr(next, L':') + 1;
		imm_chars = 0;
		goto COMMON_SINGLE;

	case SINGLE_PARAM:
		next = PROC_PARAMS(next);

	COMMON_SINGLE:
		next = PROC_TYPE(next);
		next = PROC_OP(next);
		next = PROC_COUNT(next);
		next = PROC_CYCLES(next);

		free(raw_str);

		INDENT(token_scope);	ADD_TXT("/* REPR:        */  \"%s\",\n", REPR);
		INDENT(token_scope);	ADD_TXT("/* opcode:      */  0x%02x,\n", opcode);
		INDENT(token_scope);	ADD_TXT("/* operation:   */  %s,\n",	 operation);
		INDENT(token_scope);	ADD_TXT("/* instr_count: */  %d,\n",	 instr_count);
		INDENT(token_scope);	ADD_TXT("/* cycles:      */  %d,\n",	 cycles);
		INDENT(token_scope);	ADD_TXT("/* PARAM:       */  %d,\n",     imm_chars);

		return;


	case GROUPING_REGULAR:
		next = strchr(next, L':') + 1;
		imm_chars = 0;
		goto GROUPING_COMMON;

	case GROUPING_PARAM:
		next = PROC_PARAMS(next);

	GROUPING_COMMON:
		next = PROC_TYPE(next);
		char *group_start = strchr(next, L'(') + 1;
		char *group_end   = strchr(next, L')') - 1;
		SKIP_WHITESPACE(group_start);
		SKIP_WHITESPACE_BCKWDS(group_end);
		*(++group_end) = 0;


		char *op1_s = group_start;
		char *op1_e = strchr(op1_s, L',');
		ASSERT(op1_e != NULL);
		*(op1_e) = 0;
		next = op1_e + 1;

		opcode = strtoull(op1_s, NULL, 0);


		char *grcnt_s = next;
		char *grcnt_e = strchr(grcnt_s, L',');
		SKIP_WHITESPACE(grcnt_s);
		ASSERT(grcnt_e != NULL);
		*(grcnt_e) = 0;
		next = grcnt_e + 1;


		group_cnt = strtoul(grcnt_s, NULL, 0);

		char *grofs_s = next;
	
		group_ofs = strtoul(grofs_s, NULL, 0);
		grouping_counter = 0;

		free(raw_str);
		return;

	default:
		ASSERT(NULL != strchr(raw_str, L'\"'));
		break;
	}
	return;
}

void DECODE_REPR(BOOL bMulti)
{
	char *repr_s = strchr(REPR2, L':') + 1;
	char *repr_e = repr_s + strlen(repr_s);

	ASSERT((repr_s != NULL) && (repr_e != NULL))

	// if (bMulti == TRUE)
	// 	goto MULTI;

// SINGLE:
	SKIP_WHITESPACE(repr_s);
	SKIP_WHITESPACE_BCKWDS(repr_e);

	for (int i = 0; i < group_cnt; ++i)
		strcpy(REPR_ARR[i], repr_s);


// MULTI:
}
void DECODE_PARAM(BOOL bMulti)
{
	char *param_s = strchr(PARAM, L':') + 1;
	char *param_e = param_s + strlen(param_s);

	ASSERT((param_s != NULL) && (param_e != NULL))

	// if (bMulti == TRUE)
	// 	goto MULTI;

// SINGLE:
	SKIP_WHITESPACE(param_s);
	SKIP_WHITESPACE_BCKWDS(param_e);

	// for (int i = 0; i < group_cnt; ++i)
	// 	stcpy(REPR_ARR[i], param_s);	// TODO


// MULTI:
}
void DECODE_INSTR_COUNT(BOOL bMulti)
{
	char *count_s = strchr(INSTR_COUNT, L':') + 1;
	char *count_e = count_s + strlen(count_s);

	ASSERT((count_s != NULL) && (count_e != NULL))

	// if (bMulti == TRUE)
	// 	goto MULTI;

// SINGLE:
	SKIP_WHITESPACE(count_s);
	SKIP_WHITESPACE_BCKWDS(count_e);

	for (int i = 0; i < group_cnt; ++i)
		instr_count_ARR[i] = strtol(count_s, NULL, 0);


// MULTI:
}
void DECODE_CYCLES(BOOL bMulti)
{
	char *cycl_s = strchr(CYCLES, L':') + 1;
	char *cycl_e = cycl_s + strlen(cycl_s);

	ASSERT((cycl_s != NULL) && (cycl_e != NULL))

	// if (bMulti == TRUE)
	// 	goto MULTI;

// SINGLE:
	SKIP_WHITESPACE(cycl_s);
	SKIP_WHITESPACE_BCKWDS(cycl_e);

	for (int i = 0; i < group_cnt; ++i)
		cycles_ARR[i] = strtol(cycl_s, NULL, 0);


// MULTI:
}


/**********************************
*
*	 @brief     
*
**********************************/
void DECODE_INSTR(void)
{
	DBG_TRACEL(\n# ^ DECODE_INSTR ^ #\n\n);
	// if (opcode == 0xf6)	exit(-1);

	// if (grouping_counter == 0) return;

	for (	int op_c = opcode
		;	op_c < (opcode + group_ofs * group_cnt)
		;	op_c +=	({	INDENT(token_scope - 1);
						ADD_TXT("{\n");
						group_ofs;	})	)
	{
		// pTxt = grouping_buf[grouping_counter];
#define ADD_TXT(fmt...)             \
	{                               \
		pTxt += sprintf(pTxt, fmt); \
		fprintf(stderr, fmt);       \
	}
		char *tmp = malloc(256);
		sprintf(tmp, REPR, "B");//REPR_ARR[grouping_counter]);
		INDENT(token_scope);	ADD_TXT("/* REPR:        */  \"%s\",\n", tmp);	free(tmp);
		INDENT(token_scope);	ADD_TXT("/* opcode:      */  0x%02x,\n", op_c);
		INDENT(token_scope);	ADD_TXT("/* operation:   */  %s,\n",	 operation);
		INDENT(token_scope);	ADD_TXT("/* instr_count: */  1,\n",		 instr_count_ARR[grouping_counter]);
		INDENT(token_scope);	ADD_TXT("/* cycles:      */  4,\n",		 4);//cycles_ARR[grouping_counter]);
		INDENT(token_scope);	ADD_TXT("/* PARAM:       */  %d,\n",	 imm_chars);
		INDENT(token_scope - 1);ADD_TXT("},\n");
		// grouping_end[grouping_counter++] = pTxt;
#define ADD_TXT(fmt...)             \
	{                               \
		pTxt += sprintf(pTxt, fmt); \
	}
	}
	// grouping_buf[grouping_counter][0] = '\0';
	// grouping_end[grouping_counter]	  = NULL;
}

void INSTRUCTION_GROUP(char *yytext)
{
	DBG_TRACEL(_INSTRUCTION_GROUP);
	PREVIEW_INSTR(INSTR_GROUPING, gn);

	char *raw_str = malloc(strlen(yytext) + 8); // HACK larger buffer to circumvent segfault
	strcpy(raw_str, yytext);
	PROC_INSTR(raw_str, GROUPING_REGULAR);
}
void INSTRUCTION_GROUP_PARAM(char *yytext)
{
	DBG_TRACEL(_INSTRUCTION_GROUP_PARAM);
	PREVIEW_INSTR(INSTR_GROUPING, gp);

	char *raw_str = malloc(strlen(yytext) + 8); // HACK larger buffer to circumvent segfault
	strcpy(raw_str, yytext);
	PROC_INSTR(raw_str, GROUPING_PARAM);
}
void INSTRUCTION_(char *yytext)
{
	DBG_TRACEL(_INSTRUCTION);
	PREVIEW_INSTR(INSTR, sn);

	char *raw_str = malloc(strlen(yytext) + 8); // HACK larger buffer to circumvent segfault
	strcpy(raw_str, yytext);
	PROC_INSTR(raw_str, SINGLE_REGULAR);
}
void INSTRUCTION_PARAM(char *yytext)
{
	DBG_TRACEL(_INSTRUCTION_PARAM);
	PREVIEW_INSTR(INSTR, sp);

	char *raw_str = malloc(strlen(yytext) + 8); // HACK larger buffer to circumvent segfault
	strcpy(raw_str, yytext);
	PROC_INSTR(raw_str, SINGLE_PARAM);
}

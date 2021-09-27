/**********************************
*	 @file      main.c
*	 @author    Thomas Gijsbers (@RaichuBender)
*	 @brief     
*	 @version   0.1
*	 @date      2021／09／24
*
*	 @copyright  © Copyright 2021 — Thomas Gijsbers
*	               All rights reserved.
*
**********************************/

/*	#include "disassemble.h"
#include "language.h"
#include "sys/common.h"
#include <stdio.h>
#include <stdlib.h>

#define TEST_FILE ".pokeyellow.gbc"

BYTE *MEM;

/**********************************
*
*	 @brief		entry point
*
*    @param[in] argc	Argument count
*
*    @param[in] argv	Pointer to
*						argument buffer
*
*    @return int 
*
**********************************\/
int main(int argc, const char *argv[])
{
	FILE *fp = fopen(TEST_FILE, "rb");
	if (fp == NULL)
		exit(-1);

	fseek(fp, 0L, SEEK_END);
	int sz = ftell(fp);
	fseek(fp, 0L, SEEK_SET);

	MEM = malloc(sz);
	fread(MEM, 1, sz, fp);

	INSTRUCTION **ppINSTR;
	EVAL(disassemble_block(&ppINSTR, MEM, 0, 8));

	for (int i = 0; ppINSTR[i] != NULL; ++i)
		printf(	"%04x:  %02x    %s\n",
				ppINSTR[i]->addr,
				MEM[i],
				ppINSTR[i]->mnemonic	);

	return 0;
}	*/

#include "sys/terminal_colors.h"

#include <stdio.h>
#include <string.h>
#include "language.h"

extern INSTRUCTION_SET REGULAR;

BYTE *MEM;
#define TEST_FILE ".pokeyellow.gbc"


static const char OPERATION_COLOR[10][20] =
{
	/* INVALID    */ C_RED,
	/* NOTHING    */ CB_BLACK,
	/* SPECIAL    */ CB_WHITE,
	/* MOV_STOR   */ CB_YELLOW,
	/* ARITHMETIC */ CB_YELLOW,
	/* BIT_MANIP  */ CB_YELLOW,
	/* JUMP       */ CB_GREEN,
	/* CALL       */ CB_CYAN,
	/* RETURN     */ CB_MAGENTA,
	/* END        */ NULL,		// TODO
};

static inline get_size(FILE *fp);

int main(int argc, const char *argv[])
{
	FILE *fp = fopen(TEST_FILE, "rb");
	if (fp == NULL)
		exit(-1);

	int sz = get_size(fp);

	MEM = malloc(sz);
	fread(MEM, 0x400, sz / 0x400, fp);

	int mem_byte = -1;

	// TODO do proper size deduction
	char *source_mnemonic	 = malloc(256);
	char *formatted_mnemonic = malloc(256);

	while (++mem_byte < sz)
	{
		for (int poll_instructions = 0; poll_instructions < 256; ++poll_instructions)
		{
			if  (REGULAR.instructions[poll_instructions].opcode   != MEM[mem_byte])	continue;

#ifdef	_SKIP_NOP
			if ((REGULAR.instructions[poll_instructions].mnemonic == NULL)
			||  (REGULAR.instructions[poll_instructions].opcode   == 0))			break;
#else
			if 	(REGULAR.instructions[poll_instructions].mnemonic == NULL)			break;
#endif

			strcpy(source_mnemonic, REGULAR.instructions[poll_instructions].mnemonic);

		/********************
		*	@brief First	*	NOP
		********************/
			char *first = source_mnemonic;

		/********************
		*	@brief Second	*	ST0P 0
		********************/
			char *second = strchr(first, L' ');

			if (second != NULL)
			{
				*(second++) = '\0';

		/****************************
		*	@brief Comma or space	*
		****************************/
				char delmtr = ',';

		/********************
		*	@brief Third	*	LD (HL), A
		********************/
				char *third = strchr(second, L',');

				if (third == NULL)
				{
					third  = strchr(second, L' ');
					delmtr = ' ';
				}
				if (third == NULL)
					sprintf(formatted_mnemonic, "%s%s "  C_CYAN "%s" F_RESET,
							OPERATION_COLOR[REGULAR.instructions[poll_instructions].operation],
							first, second);
				else
				{
					*(third++) = '\0';
					sprintf(formatted_mnemonic, "%s%s " C_CYAN "%s" F_RESET "%c " C_GREEN "%s" F_RESET ,
							OPERATION_COLOR[REGULAR.instructions[poll_instructions].operation],
							first, second, delmtr, third);
				}
			}	// if (second != NULL)
			else
				// strcpy(formatted_mnemonic, source_mnemonic);
					sprintf(formatted_mnemonic, "%s%s "  F_RESET,
							OPERATION_COLOR[REGULAR.instructions[poll_instructions].operation],
							first);


			printf(C_MAGENTA "%02x" C_WHITE ":" CB_BLUE "%04x\t\t" F_RESET "%s\n" F_RESET, mem_byte >> 16, mem_byte & 0xffff,
					formatted_mnemonic);

SKIP_PRINT:
			mem_byte += REGULAR.instructions[poll_instructions].operand_count - 1;

		}
		// for (poll_instructions: 0 to 255)

	}
	// while (++mem_byte < sz)

}


/**********************************
*
*    @name	get_size
*
*	 @brief     In goes a FILE pointer,
*               out comes it's file size
*
*    @param[in] fp	pointer to FILE
*
*    @return	int: file size
* 
**********************************/
static inline get_size(FILE *fp)
{
	fseek(fp, 0L, SEEK_END);
	int sz = ftell(fp);
	fseek(fp, 0L, SEEK_SET);

	return sz;
}

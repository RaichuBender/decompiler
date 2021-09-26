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

int main(int argc, const char *argv[])
{
	FILE *fp = fopen(TEST_FILE, "rb");
	if (fp == NULL)
		exit(-1);

	fseek(fp, 0L, SEEK_END);
	int sz = ftell(fp);
	fseek(fp, 0L, SEEK_SET);

	MEM = malloc(sz);
	fread(MEM, 0x400, sz / 0x400, fp);

	int i = 0;
NEXT_I:
	while (i < sz)
	{
		for (int j = 0; j < 256; ++j)
		{
			// char  tb[256];
			// char *formatted_mnemonic = tb;
			char *formatted_mnemonic = malloc(256); // TODO size deduction
													// BUGBUG because this WILL cause segfaults

			if (REGULAR.instructions[j].opcode != 0)
				if (REGULAR.instructions[j].mnemonic != NULL)
					if (REGULAR.instructions[j].opcode == MEM[i])
					{
						// TODO pretty sure this copy is redundant
						strcpy(formatted_mnemonic, REGULAR.instructions[j].mnemonic);

					/********************
					*	@brief First	*	NOP
					********************/
						char *first = REGULAR.instructions[j].mnemonic;

					/********************
					*	@brief Second	*	STIP 0
					********************/
						char *second = strchr(first, L' ');
						if (second == NULL)
							formatted_mnemonic = first;
						else
						{
							*(second++) = 0;

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
							if (third != NULL)
								sprintf(formatted_mnemonic, "%s %s%c %s", first, second, delmtr, third);
							else
								sprintf(formatted_mnemonic, "%s %s", first, second);
						}

						printf(C_MAGENTA "%02x" C_WHITE ":" CB_BLUE "%04x " CB_CYAN "%s\n" F_RESET, i >> 16, i & 0xffff,
								formatted_mnemonic);
					}

			i += REGULAR.instructions[j].operand_count
			  + (REGULAR.instructions[j].operand_count == 0);

			goto NEXT_I;
		}

		++i;
	}
}

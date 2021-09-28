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
	/* SPECIAL    */ CB_BLUE,
	/* MOV_STOR   */ C_MAGENTA,
	/* ARITHMETIC */ CB_MAGENTA,
	/* BIT_MANIP  */ CB_WHITE,
	/* JUMP       */ CB_GREEN,
	/* CALL       */ CB_YELLOW,
	/* RETURN     */ CB_RED,
	/* END        */ NULL,		// TODO
};

static inline get_size(FILE *fp);

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
**********************************/
int main(int argc, const char *argv[])
{
	u16 dadr = 0;

	if (argc >= 2)
		dadr = strtoul(argv[1], NULL, 16);

	FILE *fp = fopen(TEST_FILE, "rb");
	if (fp == NULL)
		exit(-1);

	int sz = get_size(fp);

	MEM = malloc(sz);
	fread(MEM, 0x400, sz / 0x400, fp);

	int mem_byte = dadr - 1;

	// TODO do proper size deduction
	char *source_mnemonic	 = malloc(256);
	char *formatted_mnemonic = malloc(256);

	while (++mem_byte < sz)
	{
		for (int poll_instructions = 0; poll_instructions < 256; ++poll_instructions)
		{
			if  (poll_instructions == 255)
				if  (REGULAR.instructions[poll_instructions].opcode   != MEM[mem_byte])
				{
					printf(C_RED "%02x:%04x" C_RED "\t\t< ¡¡¡ invalid !!! >\n" F_RESET,
							mem_byte >> 16,
							((mem_byte > 0x3fff) << 14) | mem_byte & 0x7fff);
					break;
				}

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

			switch (REGULAR.instructions[poll_instructions].imm)
			{
			case (2):
				sprintf(formatted_mnemonic, formatted_mnemonic, *(u8  *)(&MEM[mem_byte + 1]));
				break;
			case (3):
				sprintf(formatted_mnemonic, formatted_mnemonic, *(s8  *)(&MEM[mem_byte + 1]) + (s16)mem_byte);
				break;
			case (4):
				sprintf(formatted_mnemonic, formatted_mnemonic, *(u16 *)(&MEM[mem_byte + 1]));
			}
			printf(C_MAGENTA "%02x" C_WHITE ":" CB_BLUE "%04x\t\t" F_RESET "%s\n" F_RESET, mem_byte >> 16, ((mem_byte > 0x3fff) << 14) | mem_byte & 0x7fff,
					formatted_mnemonic);
			// if (0==strcmp(REGULAR.instructions[poll_instructions].mnemonic, "RET"))
			// 	return 0;

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

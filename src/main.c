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

#include "sys/debug.h"

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

INSTRUCTION_SET *sort(INSTRUCTION_SET *insset);
static inline get_size(FILE *fp);

// #define _SKIP_NOP

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
		dadr = (strtoul(argv[1], NULL, 0) & 0xff) << 14;

	FILE *fp = fopen(TEST_FILE, "rb");
	if (fp == NULL)
		exit(-1);

	int sz = 0x4000;
	// int sz = get_size(fp);

	MEM = malloc(sz);
	fread(MEM, 0x400, sz / 0x400, fp);

	int mem_byte = dadr - 1;

	// TODO do proper size deduction
	char *source_mnemonic	 = malloc(256);
	char *formatted_mnemonic = malloc(256);

	INSTRUCTION_SET *sorted = sort(&REGULAR);

	for (; ++mem_byte < sz; )
	{
		u8  addr2 = (mem_byte >> 14) & 0xff;
		u16 addr4 = ((mem_byte >= 0x4000) << 14)  |  (mem_byte  & 0x3fff);

		if ((sorted->instructions[MEM[mem_byte]].opcode   == -1)
		||  (sorted->instructions[MEM[mem_byte]].mnemonic == NULL))
		{
			printf(C_RED "%02x:%04x" C_RED "\t\t0x%02x\t< ¡¡¡ invalid !!! >\n" F_RESET,
				   addr2, addr4, MEM[mem_byte]);
			// printf("\t\t// %02x:%04x\t\t0x%02x\t< ¡¡¡ invalid !!! >\n",
			// 	   addr2, addr4, MEM[mem_byte]);
			continue;
		}

#ifdef	_SKIP_NOP
		if  (sorted->instructions[MEM[mem_byte]].opcode   == 0)
			continue;
#endif
		strcpy(source_mnemonic, sorted->instructions[MEM[mem_byte]].mnemonic);

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
				sprintf(formatted_mnemonic, "%s%s\t" C_GREEN "%s" F_RESET,
						OPERATION_COLOR[sorted->instructions[MEM[mem_byte]].operation],
						first, second);
			else
			{
				*(third++) = '\0';
				sprintf(formatted_mnemonic, "%s%s\t" C_CYAN "%s" F_RESET "%c" C_GREEN "%s" F_RESET ,
						OPERATION_COLOR[sorted->instructions[MEM[mem_byte]].operation],
						first, second, delmtr, third);
			}
		}	// if (second != NULL)
		else
			// strcpy(formatted_mnemonic, source_mnemonic);
				sprintf(formatted_mnemonic, "%s%s"  F_RESET,
						OPERATION_COLOR[sorted->instructions[MEM[mem_byte]].operation],
						first);
		switch (sorted->instructions[MEM[mem_byte]].imm)
		{
			int dst_adr;
		case (2):
			dst_adr = *(u8  *)(&MEM[mem_byte + 1]);
			sprintf(formatted_mnemonic, formatted_mnemonic, dst_adr);
			// sprintf(formatted_mnemonic, sorted->instructions[MEM[mem_byte]].logic, dst_adr);
			break;
		case (3):
			dst_adr = *(s8  *)(&MEM[mem_byte + 1]) + (s16)(addr4 + 2);
			sprintf(formatted_mnemonic, formatted_mnemonic, dst_adr);
			// sprintf(formatted_mnemonic, sorted->instructions[MEM[mem_byte]].logic, dst_adr);
			break;
		case (4):
			dst_adr = *(u16 *)(&MEM[mem_byte + 1]);
			sprintf(formatted_mnemonic, formatted_mnemonic, dst_adr);
			// sprintf(formatted_mnemonic, sorted->instructions[MEM[mem_byte]].logic, dst_adr);
		// 	break;
		// default:
		// 	sprintf(formatted_mnemonic, sorted->instructions[MEM[mem_byte]].logic);
		}

		printf(C_MAGENTA "%02x" C_WHITE ":" CB_BLUE "%04x\t\t" F_RESET "%s\n" F_RESET,
				addr2, addr4,
				formatted_mnemonic);
		// printf(/*C_MAGENTA "%02x" C_WHITE ":" CB_BLUE "%04x\t\t" F_RESET "%s\n" F_RESET,*/
		// 		"lbl_%04x: %s\n",
		// 		/*addr2,*/ addr4,
		// 		formatted_mnemonic);
		// if (0==strcmp(sorted->instructions[MEM[mem_byte]].mnemonic, "RET"))
		// 	putc('\n', stdout);
		// // 	return 0;
		// if (0==strcmp(sorted->instructions[MEM[mem_byte]].mnemonic, "STOP 0"))
		// 	return 0;
		// if ((0x7fff & (addr4 + sorted->instructions[MEM[mem_byte]].operand_count)) < addr4)
		// 	return 0;

SKIP_PRINT:
		ASSERT(sorted->instructions[MEM[mem_byte]].operand_count != 0);
		mem_byte += (sorted->instructions[MEM[mem_byte]].operand_count - 1);
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

/**********************************
*
*	 @file      disassemble.c
*	 @author    Thomas Gijsbers (@RaichuBender)
*	 @brief     
*	 @version   0.1
*	 @date      2021／09／24
*
*	 @copyright  © Copyright 2021 — Thomas Gijsbers
*	           	   All rights reserved.
*
**********************************/
#if 0
#include "disassemble.h"
#include "sys/common.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>


#if 0	// TODO !!!
BYTE   MEM[0x8000][64] = {0};
BYTE **MEM_BLOCKS = MEM;
#endif

/**********************************
*
*	 @brief		Disassemble a code
*				block by specifying
*				the @p size
*
*	 @param[out] pppINSTR	Pointer to resulting
*							instruction sequence,
*							@a NULL if none
*
*	 @param[in] MEM			Pointer to the start
*							of the binary's
*							memory 
*
*	 @param[in] loc			Offset of the
*							instruction data
*
*	 @param[in] size		Size of instruction
*							data in bytes
*
*	 @return	Integer containing bytes
*				advanced. If instructions
*				are aligned, this is equal
*				to @p size
*
***********************************/
int disassemble_block(MDL_INSTRUCTION ***pppINSTR, BYTE *MEM, u32 loc, size_t size)
{
	if (pppINSTR == NULL)
		return -1;

	MDL_INSTRUCTION **ret_buf	  = NULL;
	int			  advance	  = 0;
	u32			  instr_count = 0;

	for (int i = 0; advance < size; ++i)
	{
		MDL_INSTRUCTION *pINSTR = disassemble_single(MEM, loc + advance);
		if (pINSTR == NULL)
			return -1;

		advance += pINSTR->operand_count;

		MDL_INSTRUCTION **buf = malloc((instr_count + 2) * sizeof(MDL_INSTRUCTION *));

		if (ret_buf != NULL)
		{
			for (int j = 0; j < instr_count; ++j)
				buf[j] = ret_buf[j];

			free(ret_buf);
		}

		buf[instr_count++] = pINSTR;
		buf[instr_count]   = NULL;
		ret_buf			   = buf;
	}

	(*pppINSTR) = ret_buf;

	return advance;
}


/**********************************
*
*	 @brief 	Disassemble a single
*				instruction from @p loc
*
*	 @param[in]	MEM		Pointer to the start
*						of the binary's memory
*
*	 @param[in]	loc		Offset of the instruction data
*
*	 @return	Pointer to disassembled
*				instruction structure
*
**********************************/
MDL_INSTRUCTION *disassemble_single(BYTE *MEM, u32 loc)
{
	MDL_INSTRUCTION *pINSTR = decode_opcode(MEM + loc);

	return pINSTR;
}

u16 tmpadr = 0;
char tmprp[8][5] = {"B","C","D","E","H","L","(HL)","A"};


/**********************************
*
*	 @brief		Disassemble instruction 
*				from @p raw_bytes pointer
*
*    @param[in]	raw_bytes	Pointer to instruction
*							in memory to decode
*
*    @return	Pointer to resulting
*				decoded instruction data
*
**********************************/
MDL_INSTRUCTION *decode_opcode(BYTE *raw_bytes)
{
	if (raw_bytes == NULL)
		return NULL;

	MDL_INSTRUCTION *pINSTR = malloc(sizeof(MDL_INSTRUCTION));
	char *		 mnm	= malloc(32);
	sprintf(mnm, "LD %s, %s", tmprp[tmpadr], "A");

	pINSTR->mnemonic		= mnm;
	pINSTR->operand_count	= 1;
#if 0
	pINSTR->addr			= tmpadr++;
	pINSTR->attributes.type = LOAD;
#endif
	return pINSTR;
}
#endif

#include "disassemble.h"

#include <stdio.h>
#include <string.h>
#include "sys/debug.h"
#include "sys/common.h"
#include "sys/terminal_colors.h"
#include "language.h"

static const char OPERATION_COLOR[10][20] =
{
#if 1
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
#else
	"", "", "", "",
	"", "", "", "",
	"", "",
#endif
};

#define MNEMONIC_FMT_VALID	   bTermCol ? MNEMONIC_FMT_VALID_C : MNEMONIC_FMT_VALID_G
#define MNEMONIC_FMT_INVALID   bTermCol ? MNEMONIC_FMT_INVALID_C : MNEMONIC_FMT_INVALID_G
#define MNM_ONE				   bTermCol ? MNM_ONE_C : MNM_ONE_G
#define MNM_TWO				   bTermCol ? MNM_TWO_C : MNM_TWO_G
#define MNM_THREE			   bTermCol ? MNM_THREE_C : MNM_THREE_G

#define MNEMONIC_FMT_VALID_C   C_MAGENTA "%02x" C_WHITE ":" CB_BLUE "%04x\t\t" F_RESET "%s\n" F_RESET
#define MNEMONIC_FMT_INVALID_C C_RED "%02x:%04x" C_RED "\t\t0x%02x\t< ¡¡¡ invalid !!! >\n" F_RESET

#define MNEMONIC_FMT_VALID_G   "%02x:%04x\t\t%s\n"
#define MNEMONIC_FMT_INVALID_G "%02x:%04x\t\t0x%02x\t< ¡¡¡ invalid !!! >\n"

#define MNM_ONE_C			   "%s%s" F_RESET
#define MNM_TWO_C			   "%s%s\t" C_GREEN "%s" F_RESET
#define MNM_THREE_C			   "%s%s\t" C_CYAN "%s" F_RESET "%c" C_GREEN "%s" F_RESET

#define MNM_ONE_G			   "%s%s"
#define MNM_TWO_G			   "%s%s\t%s"
#define MNM_THREE_G			   "%s%s\t%s%c%s"

static inline BOOL	 check_valid(u8 addr2, u16 addr4);
static inline void	 format_instruction(u8 addr2, u16 addr4);
static inline void	 print_formatted(u8 addr2, u16 addr4);

u16						 dadr;
size_t					 file_sz;
int						 byte_ptr;
char *					 source_mnemonic;
char *					 formatted_mnemonic;
RUNTIME_INSTRUCTION_SET *rtinsst;
BOOL					 bTermCol = TRUE;

/**********************************
*
*	 @brief     
*
*    @param addr2 
*    @param addr4 
*
*    @return BOOL 
*
**********************************/
static inline BOOL check_valid(u8 addr2, u16 addr4)
{
	if ((rtinsst->instructions[MEM[byte_ptr]].opcode == -1) || (rtinsst->instructions[MEM[byte_ptr]].mnemonic == NULL))
	{
		printf(MNEMONIC_FMT_INVALID,
				addr2, addr4,
				MEM[byte_ptr]);

		return FALSE;
	}
	return TRUE;
}

/**********************************
*
*	 @brief     
*
*    @param addr2 
*    @param addr4 
*
**********************************/
static inline void format_instruction(u8 addr2, u16 addr4)
{
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
			sprintf(formatted_mnemonic, MNM_TWO,
					OPERATION_COLOR[rtinsst->instructions[MEM[byte_ptr]].operation],
					first, second);
		else
		{
			*(third++) = '\0';
			sprintf(formatted_mnemonic, MNM_THREE,
					OPERATION_COLOR[rtinsst->instructions[MEM[byte_ptr]].operation],
					first, second, delmtr, third);
		}
	}	// if (second != NULL)
	else
		// strcpy(formatted_mnemonic, source_mnemonic);
		sprintf(formatted_mnemonic, MNM_ONE,
				OPERATION_COLOR[rtinsst->instructions[MEM[byte_ptr]].operation],
				first);

	switch (rtinsst->instructions[MEM[byte_ptr]].imm)
	{
		int dst_adr;
	case (2):
		dst_adr = *(u8  *)(&MEM[byte_ptr + 1]);
		sprintf(formatted_mnemonic, formatted_mnemonic, dst_adr);
		break;

	case (3):
		dst_adr = *(s8  *)(&MEM[byte_ptr + 1]) + (s16)(addr4 + 2);
		sprintf(formatted_mnemonic, formatted_mnemonic, dst_adr);
		break;

	case (4):
		dst_adr = *(u16 *)(&MEM[byte_ptr + 1]);
		sprintf(formatted_mnemonic, formatted_mnemonic, dst_adr);
	}
}

/**********************************
*
*	 @brief     
*
*    @param addr2 
*    @param addr4 
*
**********************************/
static inline void print_formatted(u8 addr2, u16 addr4)
{
	printf(MNEMONIC_FMT_VALID,
			addr2, addr4,
			formatted_mnemonic);
}

/**********************************
*
*	 @brief     
*
**********************************/
void disassemble(void)
{
	for (; ++byte_ptr < file_sz; )
	{
		u8  addr2 = (byte_ptr >> 14) & 0xff;
		u16 addr4 = ((byte_ptr >= 0x4000) << 14)  |  (byte_ptr  & 0x3fff);

		if (!check_valid(addr2, addr4))	 continue;
		strcpy(source_mnemonic, rtinsst->instructions[MEM[byte_ptr]].mnemonic);
		format_instruction(addr2, addr4);
		print_formatted(addr2, addr4);

SKIP_PRINT:
		ASSERT(rtinsst->instructions[MEM[byte_ptr]].operand_count != 0);
		byte_ptr += (rtinsst->instructions[MEM[byte_ptr]].operand_count - 1);

		if (rtinsst->instructions[MEM[byte_ptr]].operation == RETURN)	 return;
	}
	// while (++byte_ptr < file_sz)
}

/**********************************
*
*	 @file      decompile.c
*	 @author    Thomas Gijsbers (@RaichuBender)
*	 @brief     
*	 @version   0.1
*	 @date      2021／09／24
*
*	 @copyright  © Copyright 2021 — Thomas Gijsbers
*	           	   All rights reserved.
*
**********************************/
#include "disassemble.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "sys/debug.h"
#include "sys/common.h"
#include "sys/terminal_colors.h"
#include "language.h"

// #define DC_FMT_VALID   "/* %02x:%04x */\t\t%s\n"
#define DC_FMT_VALID   CB_BLACK "/* %02x */" C_BLUE " lbl_%04x" F_RESET ":\t\t" CB_YELLOW "%s" F_RESET
#define DC_FMT_INVALID CB_BLACK "// %02x:%04x\t\t0x%02x\t" C_RED "< ¡¡¡ invalid !!! >\n" F_RESET

static inline BOOL	 dc_check_valid(u8 addr2, u16 addr4);

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
static inline BOOL dc_check_valid(u8 addr2, u16 addr4)
{
	if ((rtinsst->instructions[MEM[byte_ptr]].opcode == -1)
	||  (rtinsst->instructions[MEM[byte_ptr]].mnemonic == NULL))
	{
		printf(DC_FMT_INVALID,
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
**********************************/
void decompile(void)
{
	// char dc_fmt[1024];
	char *dc_fmt = malloc(1024);

	for (; ++byte_ptr < file_sz; )
	{
		u8  addr2 = (byte_ptr >> 14) & 0xff;
		u16 addr4 = ((byte_ptr >= 0x4000) << 14)  |  (byte_ptr  & 0x3fff);

		if (!dc_check_valid(addr2, addr4))	 continue;

		// char *dc_fmt = rtinsst->instructions[MEM[byte_ptr]].logic;

		switch (rtinsst->instructions[MEM[byte_ptr]].imm)
		{
			int dst_adr;
		case (2):
			dst_adr = *(u8  *)(&MEM[byte_ptr + 1]);
			sprintf(dc_fmt, rtinsst->instructions[MEM[byte_ptr]].logic, dst_adr);
			break;

		case (3):
			dst_adr = *(s8  *)(&MEM[byte_ptr + 1]) + (s16)(addr4 + 2);
			sprintf(dc_fmt, rtinsst->instructions[MEM[byte_ptr]].logic, dst_adr);
			break;

		case (4):
			dst_adr = *(u16 *)(&MEM[byte_ptr + 1]);
			sprintf(dc_fmt, rtinsst->instructions[MEM[byte_ptr]].logic, dst_adr);
			break;

		default:
			sprintf(dc_fmt, rtinsst->instructions[MEM[byte_ptr]].logic);
		}

		printf(DC_FMT_VALID,
			   addr2, addr4,
			   dc_fmt);

SKIP_PRINT:
		ASSERT(rtinsst->instructions[MEM[byte_ptr]].operand_count != 0);
		byte_ptr += (rtinsst->instructions[MEM[byte_ptr]].operand_count - 1);

		if (rtinsst->instructions[MEM[byte_ptr]].operation == RETURN)	 return;
	}
	// while (++byte_ptr < file_sz)

	free(dc_fmt);
}

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

#include "disassemble.h"

#include <stdio.h>
#include <string.h>
#include "sys/debug.h"
#include "sys/common.h"

#include "language.h"

// extern char *ui_text;
// #define printf(fmt...) ui_text += sprintf(ui_text, fmt);


static inline BOOL	 check_valid			(u8 addr2, u16 addr4);
static inline void	 format_instruction		(u8 addr2, u16 addr4);
static inline void   color_syntax_regular	(u8 addr2, u16 addr4);
static inline void   color_syntax_symbolic	(u8 addr2, u16 addr4);
static inline void	 print_valid			(u8 addr2, u16 addr4);
static inline void   proc_instruction		(u8 addr2, u16 addr4);

u16						 dadr;
size_t					 file_sz;
int						 byte_ptr;
char 					*source_mnemonic;
char 					*formatted_mnemonic;
RUNTIME_INSTRUCTION_SET *rtinsst;
// BOOL					 bTermCol = FALSE;
BOOL					 bTermCol = TRUE;
// BOOL					 bRetRet  = FALSE;
BOOL					 bRetRet  = TRUE;

extern char *symsym[0x40][0x10000];

#define THIS_INSTRUCTION	rtinsst->instructions[MEM[byte_ptr]]


/**********************************
*
*	 @brief     
*
*    @param addr2 
*    @param addr4 
*
**********************************/
static inline void
print_invalid(	u8 addr2, u16 addr4	)
{
	char b0h = (MEM[byte_ptr] >> 4);
	char b0l = (MEM[byte_ptr] &  7);
	b0h += (b0h > 9) ? 'a'-0xa : '0';
	b0l += (b0l > 9) ? 'a'-0xa : '0';

	printf(MNEMONIC_FMT_INVALID,
			addr2, addr4,
			b0h, b0l,
			' ', ' ',
			' ', ' ',
			MEM[byte_ptr]);
}

/**********************************
*
*	 @brief     
*
*    @param addr2 
*    @param addr4 
*
**********************************/
static inline void
print_valid(	u8 addr2, u16 addr4	)
{
	if (symsym[addr2][addr4] != NULL)
		printf("%s:\n", symsym[addr2][addr4]);

	char b0h = ' ', b0l = ' ';
	char b1h = ' ', b1l = ' ';
	char b2h = ' ', b2l = ' ';

	switch (THIS_INSTRUCTION.operand_count)
	{
	case 3:
		b2h = (MEM[byte_ptr + 2] >> 4);
		b2l = (MEM[byte_ptr + 2] &  15);
		b2h += (b2h > 9) ? 'a'-0xa : '0';
		b2l += (b2l > 9) ? 'a'-0xa : '0';
	case 2:
		b1h = (MEM[byte_ptr + 1] >> 4);
		b1l = (MEM[byte_ptr + 1] &  15);
		b1h += (b1h > 9) ? 'a'-0xa : '0';
		b1l += (b1l > 9) ? 'a'-0xa : '0';
	case 1:
		b0h = (MEM[byte_ptr] >> 4);
		b0l = (MEM[byte_ptr] &  15);
		b0h += (b0h > 9) ? 'a'-0xa : '0';
		b0l += (b0l > 9) ? 'a'-0xa : '0';

		printf(MNEMONIC_FMT_VALID,
				addr2, addr4,
				b0h, b0l,
				b1h, b1l,
				b2h, b2l,
				formatted_mnemonic);
		return;
	
	default:
		return;
	}

	// printf(MNEMONIC_FMT_VALID,
	// 		addr2, addr4,
	// 		formatted_mnemonic);
}


/**********************************
*
*	 @brief     
*
*    @param addr2 
*    @param addr4 
*
**********************************/
static inline void
format_instruction(	u8 addr2, u16 addr4	)
{
	char *first	 = source_mnemonic;
	char *second = strchr(first, L' ');

	if (second != NULL)
	{
		*(second++)	 = '\0';
		char  delmtr = ',';
		char *third	 = strchr(second, L',');

		if (third == NULL)
		{
			third  = strchr(second, L' ');
			delmtr = ' ';
		}
		if (third == NULL)
		{
			sprintf(formatted_mnemonic, MNM_TWO,
					OPERATION_COLOR[THIS_INSTRUCTION.operation],
					first, second);
		}
		else
		{
			*(third++) = '\0';
			sprintf(formatted_mnemonic, MNM_THREE,
					OPERATION_COLOR[THIS_INSTRUCTION.operation],
					first, second, delmtr, third);
		}
	}
	else // if not (second != NULL)
	{
		sprintf(formatted_mnemonic, MNM_ONE,
				OPERATION_COLOR[THIS_INSTRUCTION.operation],
				first);
	}
}


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
static inline BOOL
check_valid(	u8 addr2, u16 addr4	)
{
	if ((THIS_INSTRUCTION.opcode   == -1  )
	||  (THIS_INSTRUCTION.mnemonic_regular == NULL))
	{
		print_invalid(addr2, addr4);

		return FALSE;
	}
	return TRUE;
}


/**********************************
*
*	 @brief     
*
*	 @param addr2 
*	 @param addr4 
*
**********************************/
static inline void proc_instruction(u8 addr2, u16 addr4)
{
	int dst_adr;

	switch (THIS_INSTRUCTION.imm)
	{
	case (2):
		dst_adr = *(u8 *)(&MEM[byte_ptr + 1]);
		goto REGULAR;

	case (3):
		dst_adr = *(s8 *)(&MEM[byte_ptr + 1]) + (s16)(addr4 + 2);
		break;

	case (4):
	default:
		dst_adr = *(u16 *)(&MEM[byte_ptr + 1]);
		break;
	}

	if (THIS_INSTRUCTION.bIsSymbolic != FALSE)
		goto SYMBOLIC;

REGULAR:
	strcpy(source_mnemonic, THIS_INSTRUCTION.mnemonic_regular);
	format_instruction(addr2, addr4);
	sprintf(formatted_mnemonic, formatted_mnemonic, dst_adr);
	return;


SYMBOLIC:
	if (symsym[addr2][dst_adr] != NULL)
		sprintf(source_mnemonic, THIS_INSTRUCTION.mnemonic_symbolic, symsym[addr2][dst_adr]);
	else if (symsym[0][dst_adr] != NULL)
		sprintf(source_mnemonic, THIS_INSTRUCTION.mnemonic_symbolic, symsym[0][dst_adr]);
	else
		goto REGULAR;

	format_instruction(addr2, addr4);
	return;
}

/**********************************
*
*	 @brief     Disassemble a
*				code block
*
**********************************/
void disassemble(void)
{
	//  Split absolute address into relative hardware address
	//		and mapped memory page
	u8	addr2 = (byte_ptr >> 14) & 0xff;
	u16 addr4 = ((byte_ptr >= 0x4000) << 14) | (byte_ptr & 0x3fff);

	if (!check_valid(addr2, addr4))
		goto CONTINUE; /*	No further processing if the instruction is
							illegal / outside of defined range			*/

	proc_instruction(addr2, addr4);	// BUGBUG !!!
	print_valid(addr2, addr4);


	ASSERT(THIS_INSTRUCTION.operand_count != 0);
	byte_ptr += (THIS_INSTRUCTION.operand_count - 1);

	//	 If disassembling subroutines individually...
	if (bRetRet)
		//	 ...then abort at first encountered unconditional return.
		if (THIS_INSTRUCTION.operation == RETURN)
			return;

CONTINUE:
	if (++byte_ptr < file_sz)
		disassemble();
}

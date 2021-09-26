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
#include "sys/common.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// TODO !!!
// BYTE   MEM[0x8000][64] = {0};
// BYTE **MEM_BLOCKS = MEM;


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
int disassemble_block(INSTRUCTION ***pppINSTR, BYTE *MEM, u32 loc, size_t size)
{
	if (pppINSTR == NULL)
		return -1;

	INSTRUCTION **ret_buf	  = NULL;
	int			  advance	  = 0;
	u32			  instr_count = 0;

	for (int i = 0; advance < size; ++i)
	{
		INSTRUCTION *pINSTR = disassemble_single(MEM, loc + advance);
		if (pINSTR == NULL)
			return -1;

		advance += pINSTR->operand_count;

		INSTRUCTION **buf = malloc((instr_count + 2) * sizeof(INSTRUCTION *));

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
INSTRUCTION *disassemble_single(BYTE *MEM, u32 loc)
{
	INSTRUCTION *pINSTR = decode_opcode(MEM + loc);

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
INSTRUCTION *decode_opcode(BYTE *raw_bytes)
{
	if (raw_bytes == NULL)
		return NULL;

	INSTRUCTION *pINSTR = malloc(sizeof(INSTRUCTION));
	char *		 mnm	= malloc(32);
	sprintf(mnm, "LD %s, %s", tmprp[tmpadr], "A");

	pINSTR->mnemonic		= mnm;
	pINSTR->operand_count	= 1;
	// pINSTR->addr			= tmpadr++;
	// pINSTR->attributes.type = LOAD;

	return pINSTR;
}

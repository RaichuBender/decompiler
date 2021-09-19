#include "disassemble.h"
#include <stdio.h>
#include <stdlib.h>

// !!! TODO !!!
// BYTE   MEM[0x8000][64] = {0};
// BYTE **MEM_BLOCKS = MEM;

static int decode_opcode(INSTRUCTION *pINSTR, BYTE *raw_bytes);

/**
 * @name		disassemble_block
 * @brief		Disassemble a code block by specifying the size
 *
 * @param pppDASM Pointer to resulting string sequence of disassembled instructions,
 * 				NULL if none
 * @param loc	Offset of the instruction data
 * @param size	Size of instruction data in bytes
 *
 * @returns		Integer containing bytes advanced
 * 				Use to check size difference
 */
int disassemble_block(BYTE *MEM, const char ***pppDASM, int loc, size_t size)
{
	if (pppDASM == NULL)
		return -1;

	const char **ret_list = malloc(size);

	for (int i = 0; (i < size) && (loc < size); ++i)
		loc += disassemble_single(MEM, &ret_list[i], loc);

	*pppDASM = ret_list;

	return loc;
}

/**
 * @name		disassemble_single
 * @brief		Disassemble a single instruction from loc
 *
 * @param ppDASM	The resulting disassembly string
 * @param loc	Offset of the instruction data
 *
 * @returns		Integer containing bytes advanced
 */
int disassemble_single(BYTE *MEM, const char **ppDASM, int loc)
{
	if (ppDASM == NULL)
		return -1;

	INSTRUCTION *pINSTR = malloc(sizeof(INSTRUCTION));
	BYTE *		 pDATA = MEM + loc;

	int advance_pc = decode_opcode(pINSTR, pDATA);

	*ppDASM = pINSTR->mnemonic;
	return advance_pc;
}

static int decode_opcode(INSTRUCTION *pINSTR, BYTE *raw_bytes)
{
	// pINSTR = malloc(sizeof(INSTRUCTION));

	pINSTR->mnemonic = "TO IMPLEMENT";
	pINSTR->operand_count = 1;
	pINSTR->attributes.type = NO_OP;

	return 1;
}

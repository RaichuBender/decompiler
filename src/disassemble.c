#include "disassemble.h"
#include <stdio.h>
#include <stdlib.h>

// !!! TODO !!!
BYTE   MEM[0x8000][64] = {0};
BYTE **MEM_BLOCKS = MEM;

static int decode_opcode(INSTRUCTION *pInst, BYTE *raw_bytes);

/**
 * @name		disassemble_single
 * @brief		Disassemble a single instruction from loc
 *
 * @param pDasm	The resulting disassembly string
 * @param loc	Offset of the instruction data
 *
 * @returns		Integer containing bytes advanced
 */
int disassemble_single(char *pDasm, OFFSET loc)
{
	INSTRUCTION *pInst;
	u64			 data = *(u64 *)(MEM_BLOCKS[loc.space] + loc.adr);

	int advance_pc = decode_opcode(pInst, &data);

	sprintf(pDasm, pInst->mnemonic, /* TODO */ 0);
	return advance_pc;
}

/**
 * @name		disassemble_block
 * @brief		Disassemble a code block by specifying the size
 *
 * @param loc	Offset of the instruction data
 * @param size	Size of instruction data in bytes
 *
 * @returns		Pointer to string sequence of disassembled instructions,
 * 				NULL if none
 */
char **disassemble_block(OFFSET loc, size_t size)
{
	char **ret_list = malloc(size);

	for (int i = 0; (i < size) && (loc.adr < size); ++i)
		loc.adr += disassemble_single(ret_list[i++], loc);

	return ret_list;
}

static int decode_opcode(INSTRUCTION *pInst, BYTE *raw_bytes)
{
	pInst = malloc(sizeof(INSTRUCTION));
	return /* TODO */ 0;
}

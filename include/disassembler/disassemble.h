#ifndef __DISASSEMBLE_H__
#define __DISASSEMBLE_H__

#include "instructions.h"
#include "typedefs.h"

typedef u8	BYTE;
typedef u64 POINTER;

extern BYTE **MEM_BLOCKS;

typedef struct
{
	u32		space;
	POINTER adr;
} OFFSET;

int disassemble_single(BYTE *MEM, const char **pDasm, int loc);
int disassemble_block(BYTE *MEM, const char ***ppDasm, int loc, size_t size);

#endif // __DISASSEMBLE_H__

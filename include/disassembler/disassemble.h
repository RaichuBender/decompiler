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

int	   disassemble_single(char *pDasm, OFFSET loc);
char **disassemble_block(OFFSET loc, size_t size);

#endif // __DISASSEMBLE_H__

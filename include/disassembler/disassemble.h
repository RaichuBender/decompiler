/**********************************
*
*	 @file      disassemble.h
*	 @author    Thomas Gijsbers
*	 @brief     
*	 @version   0.1
*	 @date      2021／09／24
*
*	 @copyright	Ⓒ Copyright 2021 — Thomas Gijsbers
*	           	   All rights reserved.
*
**********************************/
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

int disassemble_block(INSTRUCTION ***pppINSTR, BYTE *MEM, u32 loc, size_t size);
INSTRUCTION *disassemble_single(BYTE *MEM, u32 loc);
INSTRUCTION *decode_opcode(BYTE *raw_bytes);

#endif // __DISASSEMBLE_H__

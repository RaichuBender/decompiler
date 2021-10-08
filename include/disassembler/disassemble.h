/**********************************
*
*	 @file      disassemble.h
*	 @author    Thomas Gijsbers (@RaichuBender)
*	 @brief     
*	 @version   0.1
*	 @date      2021／09／24
*
*	 @copyright  © Copyright 2021 — Thomas Gijsbers
*	           	   All rights reserved.
*
**********************************/
#ifndef __DISASSEMBLE_H__
#define __DISASSEMBLE_H__

#if 0
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

int disassemble_block(MDL_INSTRUCTION ***pppINSTR, BYTE *MEM, u32 loc, size_t size);
MDL_INSTRUCTION *disassemble_single(BYTE *MEM, u32 loc);
MDL_INSTRUCTION *decode_opcode(BYTE *raw_bytes);
#endif

#include "sys/common.h"
#include "language.h"

extern BYTE *MEM;

extern u16						dadr;
extern size_t					file_sz;
extern int						byte_ptr;
extern char *					source_mnemonic;
extern char *					formatted_mnemonic;
extern RUNTIME_INSTRUCTION_SET *rtinsst;

void disassemble(void);

#endif // __DISASSEMBLE_H__

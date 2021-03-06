/**********************************
*
*	 @file      instructions.h
*	 @author    Thomas Gijsbers (@RaichuBender)
*	 @brief     
*	 @version   0.1
*	 @date      2021／09／24
*
*	 @copyright  © Copyright 2021 — Thomas Gijsbers
*	           	   All rights reserved.
*
**********************************/
#ifndef __INSTRUCTIONS_H__
#define __INSTRUCTIONS_H__

#include "typedefs.h"

// typedef enum _LOGIC_TYPE
// {
// 	NO_OP,
// 	ARITHMETIC,
// 	LOAD,
// 	STORE,
// 	BRANCH,
// } LOGIC_TYPE;

typedef u32 REGISTER_INDEX;
typedef u32 OPERAND_INDEX;

typedef enum _AFFECTS
{
	PARAM_NONE,
	PARAM_REG,
	OP,
	CONST,
	PARAM_REG_ADR,
	OP_ADR,
	CONST_ADR,
	FLAG
} AFFECTS;

typedef struct _INSTRUCTION_ATTR
{
	// LOGIC_TYPE type;
	AFFECTS	   aff1;
	AFFECTS	   aff2;
	u32		   index1;
	u32		   index2;
} INSTRUCTION_ATTR;

typedef enum _OPERATION
{
	INVALID = 0,
	NOTHING,
	SPECIAL,
	MOV_STOR,
	ARITHMETIC,
	BIT_MANIP,
	JUMP,
	COND_JUMP,
	CALL,
	COND_CALL,
	RETURN,
	COND_RETURN,
	END
} OPERATION;

// typedef struct _LOGIC
// {
// 	OPERATION operation;
// 	u32		  operand1;
// 	u32		  operand2;
// } LOGIC;

typedef struct _MDL_INSTRUCTION
{
	const char *mnemonic_regular;
	const char *mnemonic_symbolic;
	u8			opcode;
	OPERATION	operation;
	u32			operand_count;
	u32			cycles;
	int			imm;
	BOOL		bIsSymbolic;
	char *		logic;
// INSTRUCTION_ATTR attributes;
// u32			logic_count;
// LOGIC *		logic;
} MDL_INSTRUCTION;

typedef struct _INSTRUCTION
{
	const char *mnemonic_regular;
	const char *mnemonic_symbolic;
	u8			opcode;
	OPERATION	operation;
//	u64			addr;
	u32			operand_count;
	u32			cycles;
	int			imm;
	BOOL		bIsSymbolic;
	char *		logic;
// INSTRUCTION_ATTR attributes;
// u32			logic_count;
// LOGIC *		logic;
} INSTRUCTION;
#endif //__INSTRUCTIONS_H__

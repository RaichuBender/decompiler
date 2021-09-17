#ifndef __INSTRUCTIONS_H__
#define __INSTRUCTIONS_H__

#include "typedefs.h"

typedef enum
{
	NO_OP,
	ARITHMETIC,
	LOAD,
	STORE,
	BRANCH,
} LOGIC_TYPE;

typedef u32 REGISTER_INDEX;
typedef u32 OPERAND_INDEX;

typedef enum
{
	NONE,
	REG,
	OP,
	CONST,
	REG_ADR,
	OP_ADR,
	CONST_ADR
} AFFECTS;

typedef struct
{
	LOGIC_TYPE type;
	AFFECTS	   aff1;
	AFFECTS	   aff2;
	u32		   index1;
	u32		   index2;
} INSTRUCTION_ATTR;

typedef enum
{
	NOTHING,
	ADD,
	SUBTRACT,
	BIT_MANIP,
	JUMP,
	CALL,
	RETURN,
	END
} OPERATION;

typedef struct
{
	OPERATION operation;
	u32		  operand1;
	u32		  operand2;
} LOGIC;

typedef struct
{
	const char *mnemonic;
#ifdef _UNINDEXED
	u8 opcode;
#endif // _UNINDEXED
	s32				 operand_count;
	s32				 cycles;
	INSTRUCTION_ATTR attributes;
	LOGIC *			 logic;
} INSTRUCTION;

#endif //__INSTRUCTIONS_H__

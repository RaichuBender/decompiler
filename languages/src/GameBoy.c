#include "instructions.h"
#include "language.h"

LANGUAGE GAMEBOY = {
	"GameBoy", /* Display Name */
	LITTLE,	   /* Endianness   */
	16		   /* Address Size */
			   //
};

INSTRUCTION GAMEBOY_OPCODES[256];

LOGIC L_NOP[] = {
	{NOTHING}, //
	{END}	   //
};

INSTRUCTION NOP = {
	"NOP",	 /* Mnemonic */
	1,		 /* Operand Count */
	4,		 /* Cycles */
	{NO_OP}, /* Attributes: Type */
	L_NOP	 /* Logic */
};

// int INIT_OPCODES(void)
// {
// 	GAMEBOY_OPCODES[0].mnemonic = "NOP";
// 	GAMEBOY_OPCODES[0].operand_count = 1;
// 	GAMEBOY_OPCODES[0].cycles = 4;
// 	GAMEBOY_OPCODES[0].attributes.type = NO_OP;
// 	GAMEBOY_OPCODES[0].logic = NOP;

// 	return 0;
// }

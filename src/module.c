#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include "language.h"

#include "log_module.h"

#define ASSIGN_INST(_idx0_, _idx1_)                                                                      \
	{                                                                                                    \
		sorted->instructions[_idx0_].mnemonic_regular  = insset->instructions[_idx1_].mnemonic_regular;  \
		sorted->instructions[_idx0_].mnemonic_symbolic = insset->instructions[_idx1_].mnemonic_symbolic; \
		sorted->instructions[_idx0_].opcode			   = insset->instructions[_idx1_].opcode;            \
		sorted->instructions[_idx0_].operation		   = insset->instructions[_idx1_].operation;         \
		sorted->instructions[_idx0_].operand_count	   = insset->instructions[_idx1_].operand_count;     \
		sorted->instructions[_idx0_].cycles			   = insset->instructions[_idx1_].cycles;            \
		sorted->instructions[_idx0_].imm			   = insset->instructions[_idx1_].imm;               \
		sorted->instructions[_idx0_].bIsSymbolic	   = insset->instructions[_idx1_].bIsSymbolic;       \
		sorted->instructions[_idx0_].logic			   = insset->instructions[_idx1_].logic;             \
	}

/**********************************
*
*	 @brief     
*
*	 @param insset 
*
*	 @return MODULE_INSTRUCTION_SET* 
*
**********************************/
RUNTIME_INSTRUCTION_SET *load_module(MODULE_INSTRUCTION_SET *insset)
{
	RUNTIME_INSTRUCTION_SET *sorted = malloc(sizeof(RUNTIME_INSTRUCTION_SET));

	sorted->name = insset->name;

	// TODO NOP
	ASSIGN_INST(0, 0);

	for (int sort = 1; sort < 256; ++sort)
	{
		for (int poll = 1; poll < 256; ++poll)
		{
			if ((poll == 255)
			&&  (insset->instructions[poll].opcode != sort))
			{
				sorted->instructions[sort].opcode = -1;
				break;
			}

			if (insset->instructions[poll].opcode == sort)
			{
				// memcpy(&sorted->instructions[sort],
				// 	   &insset->instructions[poll],
				// 	   sizeof(MDL_INSTRUCTION));
				ASSIGN_INST(sort, poll);
				break;
			}
		}
	}

	log_instset(sorted, "regular");

	return sorted;
}

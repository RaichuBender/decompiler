#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include "language.h"


/**********************************
*
*	 @brief     
*
*    @param instset 
*	 @param fn 
*
**********************************/
void log_instset(INSTRUCTION_SET *instset, const char *fn)
{
	char name[260];
	sprintf(name, "%s-opcodes.log", fn);

	FILE *fp = fopen(name, "wb");

	fprintf(fp, "   ");
	for (int i = 0; i < 16; ++i)
		fprintf(fp, " x%1x                        ", i);
	fprintf(fp, "\n   ");
	for (int i = 0; i < 16; ++i)
		fprintf(fp, "___________________________");
	fprintf(fp, "\n");

	for (int y = 0; y < 0x10; ++y)
	{
		fprintf(fp, "%1xx ", y);
		for (int x = 0; x < 0x10; ++x)
		{
			char *mnm = instset->instructions[(y<<4)|x].mnemonic;

			fprintf(fp, "| %s", mnm);

			int sp;

			if (mnm == NULL)
				sp = strlen("(null)");
			else
				sp = strlen(mnm);

			for (; sp < 24; ++sp)
				fputc(' ', fp);

			fputc('|', fp);
		}

		fputc('\n', fp);
	}

	fclose(fp);
}


/**********************************
*
*	 @brief     
*
*	 @param insset 
*
*	 @return INSTRUCTION_SET* 
*
**********************************/
INSTRUCTION_SET *sort(INSTRUCTION_SET *insset)
{
	INSTRUCTION_SET *sorted = malloc(sizeof(INSTRUCTION_SET));

	// TODO NOP
	memcpy(&sorted->instructions[0],
		   &insset->instructions[0],
		   sizeof(INSTRUCTION));

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
				memcpy(&sorted->instructions[sort],
					   &insset->instructions[poll],
					   sizeof(INSTRUCTION));
				break;
			}
		}
	}

	log_instset(sorted, "regular");

	return sorted;
}

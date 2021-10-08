#ifndef LOG_MODULE_H
#define LOG_MODULE_H

#include "language.h"

// #define _LOGGING
#ifdef _LOGGING

/**********************************
*
*	 @brief     
*
*    @param instset 
*	 @param fn 
*
**********************************/
void log_instset(MODULE_INSTRUCTION_SET *instset, const char *fn)
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

#else  // _LOGGING

#define log_instset(...) 

#endif // _LOGGING

#endif /* LOG_MODULE_H */

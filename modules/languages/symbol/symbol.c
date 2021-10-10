/**********************************
*     
*     	 @file      symbol.c
*     	 @author    Thomas Gijsbers(@RaichuBender)
*     	 @brief     
*     	 @version   0.1
*     	 @date      2021／10／09
*     
*     	 @copyright   © Copyright 2021 — Thomas Gijsbers
*     	                All rights reserved.
*     
*     
**********************************/
#include "symbol.gen.h"

char *labels[0x40][0x10000];

int main(int argc, const char *argv[])
{
	yylex();

	FILE *fp = fopen("src/symsym.c", "wb");

	fprintf(fp, "#define NULL (0)\nchar *symsym[0x40][0x10000] =\n{\n");

	for (int j = -1; ++j < 0x40;)
		for (int i = -1; ++i < 0x10000;)
			if (labels[j][i] != NULL)
				fprintf(fp, "\n\"%s\",\n", labels[j][i]);
			else
				fprintf(fp, "NULL, ");

	fprintf(fp, "\n};\n");

	return 0;
}

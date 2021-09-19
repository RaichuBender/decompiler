#include "disassemble.h"
#include "language.h"
#include "typedefs.h"
#include <stdio.h>
#include <stdlib.h>

// extern BYTE MEM[0x8000][64];

BYTE *MEM;

/**
 * @name main
 * @brief The main function
 * @param argc Argument count
 * @param argv Arguments
 */
s32 main(s32 argc, ARG_LIST argv)
{
	FILE *fp = fopen("pokeyellow.gbc", "rb");
	
	if (fp == NULL)
		exit(-1);

	fseek(fp, 0L, SEEK_END);
	int sz = ftell(fp);
	fseek(fp, 0L, SEEK_SET);

	MEM = malloc(sz);

	fread(MEM, 1, sz, fp);

	char **dasm;

	disassemble_block(MEM, &dasm, 0, 8);

	for (int i = 0; i != 8; ++i)
		printf("%s\n", dasm[i]);

	return 0;
}

/*	Yes, talk about overdoing things...
	I used this file to test
	syntax highlighting. */

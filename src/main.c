#include "disassemble.h"
#include "language.h"
#include "sys/common.h"
#include <stdio.h>
#include <stdlib.h>

#define TEST_FILE ".pokeyellow.gbc"

BYTE *MEM;

int main(int argc, const char *argv[])
{
	FILE *fp = fopen(TEST_FILE, "rb");
	if (fp == NULL)
		exit(-1);

	fseek(fp, 0L, SEEK_END);
	int sz = ftell(fp);
	fseek(fp, 0L, SEEK_SET);

	MEM = malloc(sz);
	fread(MEM, 1, sz, fp);

	INSTRUCTION **ppINSTR;
	EVAL(disassemble_block(&ppINSTR, MEM, 0, 8));

	for (int i = 0; ppINSTR[i] != NULL; ++i)
		printf("%04x:  %02x    %s\n", ppINSTR[i]->addr, MEM[i], ppINSTR[i]->mnemonic);

	return 0;
}

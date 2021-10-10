#include "disassemble.h"
#include <stdio.h>
#include <stdlib.h>
#include "cmdline.h"


void cmdline_main(void)
{
CMD_LOOP_BEGIN

	ON_MATCH("ds\n")	DISASSEMBLE;
	ON_MATCH("dc\n")	DECOMPILE;
	ON_MATCH("loc\n")	LOC;
	ON_MATCH("j\n")		LOC;
	ON_MATCH("cls\n")	CLS;

	ON_MATCH("help\n")	HELP;
	ON_MATCH("h\n")		HELP;


	ON_MATCH("exit\n")	EXIT;
	ON_MATCH("q\n")		EXIT;

CMD_LOOP_END



DISASSEMBLE:
	printf("\nDisassemble code block 0x%04x:\n", byte_ptr);
	disassemble();
	printf("End disassembly block.\n\n");
	RETURN;


DECOMPILE:
	printf("\nDecompile code block 0x%04x:\n", byte_ptr);
	decompile();
	printf("End decompilation block.\n\n");
	RETURN;


LOC:
	printf("Enter location to jump to: ");
	GET_UL(byte_ptr);
	RETURN;


CLS:
	system("clear");
	RETURN;


HELP:
	printf("This will display help.\n\n");
	RETURN;


EXIT:
	return;
}

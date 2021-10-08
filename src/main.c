/**********************************
*	 @file      main.c
*	 @author    Thomas Gijsbers (@RaichuBender)
*	 @brief     
*	 @version   0.1
*	 @date      2021／09／24
*
*	 @copyright  © Copyright 2021 — Thomas Gijsbers
*	               All rights reserved.
*
**********************************/

#include "sys/debug.h"

#include <stdio.h>
#include <string.h>
#include "args.h"
#include "disassemble.h"
#include "language.h"
#include "cmdline.h"

extern MODULE_INSTRUCTION_SET REGULAR;

BYTE *MEM;
#define TEST_FILE ".pokeyellow.gbc"


RUNTIME_INSTRUCTION_SET *load_module(MODULE_INSTRUCTION_SET *insset);

static inline FILE * open_binary(void);
static inline size_t get_file_size(FILE *fp);


/**********************************
*
*    @name	get_file_size
*
*	 @brief     In goes a FILE pointer,
*               out comes it's file size
*
*    @param[in] fp	pointer to FILE
*
*    @return	int: file size
* 
**********************************/
static inline size_t get_file_size(FILE *fp)
{
	fseek(fp, 0L, SEEK_END);
	size_t sz = ftell(fp);
	fseek(fp, 0L, SEEK_SET);

	return sz;
}


/**********************************
*
*	 @brief		entry point
*
*    @param[in] argc	Argument count
*
*    @param[in] argv	Pointer to
*						argument buffer
*
*    @return int 
*
**********************************/
int main(int argc, const char *argv[])
{
	parse_cmdline(argc, argv);
	dadr = 0;

	FILE *fp = open_binary();

	file_sz = get_file_size(fp);
	MEM = malloc(file_sz);
	fread(MEM, 0x400, file_sz / 0x400, fp);

	byte_ptr = dadr - 1;

	// TODO do proper size deduction
	source_mnemonic	   = malloc(256);
	formatted_mnemonic = malloc(256);

	rtinsst = load_module(&REGULAR);
	cmdline_main();

	return 0;
}

/**********************************
*
*     @brief     
*
*     @return FILE* 
*
**********************************/
static inline FILE *open_binary(void)
{
	char *fn;
	FILE *fp;

	if (bLoadDefault != FALSE)
		fn = TEST_FILE;
	else
		fn = binary_file;

	fp = fopen(fn, "rb");

	if (fp == NULL)
	{
		char share[260];
		char *fn2 = share;
		sprintf(fn2, "%s%s", "/usr/share/decompiler/", fn);
		fp = fopen(fn2, "rb");

		if (fp == NULL)
		{
			fprintf(stderr, "File not found ( '%s' | '%s' )\n", fn, fn2);
			exit(-1);
		}
	}

	return fp;
}

/**********************************
*
*	 @file      disassemble.h
*	 @author    Thomas Gijsbers (@RaichuBender)
*	 @brief     
*	 @version   0.1
*	 @date      2021／09／24
*
*	 @copyright  © Copyright 2021 — Thomas Gijsbers
*	           	   All rights reserved.
*
**********************************/
#ifndef __DISASSEMBLE_H__
#define __DISASSEMBLE_H__

#include "sys/common.h"
#include "language.h"

#ifndef _GUI
#	include "sys/terminal_colors.h"
#else // _GUI
#	include "sys/gui_colors.h"
#endif// _GUI

extern BYTE *MEM;

extern u16						dadr;
extern size_t					file_sz;
extern int						byte_ptr;
extern char *					source_mnemonic;
extern char *					formatted_mnemonic;
extern RUNTIME_INSTRUCTION_SET *rtinsst;
extern BOOL						bTermCol;

void disassemble(void);
void decompile(void);


#ifndef  _NOCOLOR

	static const char OPERATION_COLOR[13][20] = {
		/* INVALID    */ C_RED,
		/* NOTHING    */ CB_BLACK,
		/* SPECIAL    */ CB_BLUE,
		/* MOV_STOR   */ C_MAGENTA,
		/* ARITHMETIC */ CB_MAGENTA,
		/* BIT_MANIP  */ CB_WHITE,
		/* JUMP       */ CB_GREEN,
		/* COND_JUMP  */ CB_GREEN,
		/* CALL       */ CB_YELLOW,
		/* COND_CALL  */ CB_YELLOW,
		/* RETURN     */ CB_RED,
		/* COND_RETURN*/ CB_RED,
		/* END        */ NULL, // TODO
	};

#	define MNEMONIC_FMT_VALID		bTermCol ? MNEMONIC_FMT_VALID_C		: MNEMONIC_FMT_VALID_G
#	define MNEMONIC_FMT_INVALID		bTermCol ? MNEMONIC_FMT_INVALID_C	: MNEMONIC_FMT_INVALID_G
#	define MNM_ONE					bTermCol ? MNM_ONE_C				: MNM_ONE_G
#	define MNM_TWO					bTermCol ? MNM_TWO_C				: MNM_TWO_G
#	define MNM_THREE				bTermCol ? MNM_THREE_C				: MNM_THREE_G

#	define MNEMONIC_FMT_VALID_C		C_MAGENTA	"%02x"		C_WHITE	":"	CB_BLUE "%04x\t\t"		F_RESET "%s\n"	F_RESET
#	define MNEMONIC_FMT_INVALID_C	C_RED		"%02x:%04x"	C_RED	"\t\t0x%02x\t< ¡¡¡ invalid !!! >\n"			F_RESET

#	define MNEMONIC_FMT_VALID_G		"%02x:%04x\t\t%s\n"
#	define MNEMONIC_FMT_INVALID_G	"%02x:%04x\t\t0x%02x\t< ¡¡¡ invalid !!! >\n"

#	define MNM_ONE_C				"%s%s"		F_RESET
#	define MNM_TWO_C				"%s%s\t"	C_GREEN "%s"	F_RESET
#	define MNM_THREE_C				"%s%s\t"	C_CYAN "%s"		F_RESET "%c"	C_GREEN "%s"	F_RESET

#	define MNM_ONE_G				"%s%s"
#	define MNM_TWO_G				"%s%s\t%s"
#	define MNM_THREE_G				"%s%s\t%s%c%s"

#else // _NOCOLOR

	static const char OPERATION_COLOR[13][20] = { "" };

#	define MNEMONIC_FMT_VALID		"%02x:%04x\t\t%s\n"
#	define MNEMONIC_FMT_INVALID		"%02x:%04x\t\t0x%02x\t< ¡¡¡ invalid !!! >\n"

#	define MNM_ONE					"%s%s"
#	define MNM_TWO					"%s%s\t%s"
#	define MNM_THREE				"%s%s\t%s%c%s"

#endif// _NOCOLOR

#endif // __DISASSEMBLE_H__

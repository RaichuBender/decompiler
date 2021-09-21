#ifndef __PREACH_MODEST_H__
#define __PREACH_MODEST_H__

#include "common.h"

static char *PROCESS_MACRO(char *yytext, MACRO_TYPE t);
static void	 EXPAND_MACRO(char *macro_begin);
static void	 PROCESS_MACRO_EXPANSION(void);
static void	 REPLACE_MACRO(char *yytext);

#endif // __PREACH_MODEST_H__

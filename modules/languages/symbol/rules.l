/*********************************
 /*
*	 @file      rules.l
*	 @author    Thomas Gijsbers (@RaichuBender)
*	 @brief     Module parser lexer
*	 @version   0.1
*	 @date      2021／10／09
*
*	 @copyright  © Copyright 2021 — Thomas Gijsbers
*	           	   All rights reserved.
*
**********************************/
%{

extern char *labels[0x40][0x10000];

%}

%%

^[0-9a-fA-F]{2}:[0-9a-fA-F]{4}[ ]=[ ].+	{
	char *addr2 = yytext;
	char *addr4 = strchr(addr2, L':');
	*(addr4++) = '\0';

	char *lbl = strchr(addr4, L' ');
	*(lbl++) = '\0';
	*(lbl++) = '\0';
	*(lbl++) = '\0';

	char *tmp = malloc(strlen(lbl) + 1);
	strcpy(tmp, lbl);
	labels[strtoul(addr2, NULL, 16)][strtoul(addr4, NULL, 16)] = tmp;
}

\n	{}

.	{}

%%

// \#.+?\n	{	DBG_TRACEL(_COMMENT); }

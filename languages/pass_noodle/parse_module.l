%{
#include "parse_module.h"

%}

%%

MACRO:[a-zA-Z0-9_]+?\(.*?\)(.*?\n.*)*?=BEGIN(.*?\n.*)*?=END	{
									MACRO *macro = &macro_list[macro_count];
									char *macro_begin = PROCESS_MACRO(yytext);
									EXPAND_MACRO(macro_begin);
									PROCESS_MACRO_EXPANSION();
									OUTPUT_DBG_DOC(" *\t@returns *** PREVIEW *** - \n\t%s\n", macro->expand);
									OUTPUT_DBG_DOC(" */\n");	}

MACRO:[a-zA-Z0-9_]+?\(.*?\).*?\n {	PROCESS_MACRO(yytext);
									OUTPUT_DBG_DOC(" *\t@returns\tNothing.\n");
									OUTPUT_DBG_DOC(" */\n");	}

^#:[ \t]+.+?\n						USER_DESC()

PLATFORM\s*\([a-zA-Z0-9_]+?\)		STRUCT_START(PLATFORM,		platform	)
ARCHITECTURE\s*\([a-zA-Z0-9_]+?\)	STRUCT_START(ARCHITECTURE,	architecture)
LANGUAGE\s*\([a-zA-Z0-9_]+?\)		STRUCT_START(LANGUAGE,		language	)
MODE\s*\([a-zA-Z0-9_]+?\)			STRUCT_START(MODE,			mode		)

DisplayName:\s*.+?\n				PROPERTY_LITERAL(display_name	)
Architecture:\s*.+?\n				PROPERTY_LITERAL(architecture	)
Language:\s*.+?\n					PROPERTY_LITERAL(language		)
Endianness:\s*.+?\n					PROPERTY_LITERAL(endian			)
AddressSize:\s*.+?\n				PROPERTY_LITERAL(address_size	)

END_PLATFORM		{end_platform = 0xDEADBEEF;}
END_ARCHITECTURE	{end_platform = 0xDEADBEEF;}
END_LANGUAGE		{end_platform = 0xDEADBEEF;}
END_MODE			{end_platform = 0xDEADBEEF;}

\n		{ }
.		{ }

%%

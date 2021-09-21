%{
#include "pass_noodle.h"

#if 0
#define dbg_printf(fmt...)	printf(fmt)
#else
#define dbg_printf(fmt...)
#endif
%}

%%

^#:[ \t]+.+?\n						{	DBG_TRACEL(user_desc); USER_DESC();	}
\#.+?\n								{	}

PLATFORM\s*\([a-zA-Z0-9_]+?\)		{	STRUCT_START(PLATFORM,		platform	);	}
ARCHITECTURE\s*\([a-zA-Z0-9_]+?\)	{	STRUCT_START(ARCHITECTURE,	architecture);	}
LANGUAGE\s*\([a-zA-Z0-9_]+?\)		{	STRUCT_START(LANGUAGE,		language	);	}
MODE\s*\([a-zA-Z0-9_]+?\)			{	STRUCT_START(MODE,			mode		);	}

DisplayName:\s*.+?\n				{	PROPERTY_LITERAL(display_name	);	}
Architecture:\s*.+?\n				{	PROPERTY_LITERAL(architecture	);	}
Language:\s*.+?\n					{	PROPERTY_LITERAL(language		);	}
Endianness:\s*.+?\n					{	PROPERTY_LITERAL(endian			);	}
AddressSize:\s*.+?\n				{	PROPERTY_LITERAL(address_size	);	}

END_PLATFORM					{	end_platform		= 0xDEADBEEF;	}
END_ARCHITECTURE				{	end_architecture	= 0xDEADBEEF;	}
END_LANGUAGE					{	end_language		= 0xDEADBEEF;	}
END_MODE						{	end_mode			= 0xDEADBEEF;	}

\".+?\":\s*.+?$ 				{	char buf[1024];
									sprintf(buf, yytext, "_DUMMY_");
									ADD_TXT("/* %s */\n", buf);	}

\n								{	}
.								{	}

%%

// ".+?"\s*?:\s*?GROUP\s*?\(\s*?.+?\s*?,\s*?.+?\s*?\)	{}

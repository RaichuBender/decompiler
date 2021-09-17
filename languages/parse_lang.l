%{

	char final_out[1024];
	char *pTxt = final_out;

	char *display_name	= NULL;
	char *endian		= NULL;
	char *address_size	= NULL;
	char *end_lang		= NULL;

#define ADD_TXT(fmt, ...) { pTxt += sprintf(pTxt, fmt __VA_OPT__(,) __VA_ARGS__  ); }

%}

%%

\n#.+?\n	{ }

LANG\([a-zA-Z0-9_]+?\) {
	*(strchr(yytext, L')')) = '\0';

	display_name = malloc(strlen(yytext));
	strcpy(display_name, yytext);
}

Endianness:\s*.+?\n {
	*(strchr(yytext, L'\n')) = '\0';

	endian = malloc(strlen(yytext));
	strcpy(endian, yytext);
}

AddressSize:\s*.+?\n {
	*(strchr(yytext, L'\n')) = '\0';

	address_size = malloc(strlen(yytext));
	strcpy(address_size, yytext);
}

ENDLANG {
	end_lang = 0xDEADBEEF;
}

\n		{ }
.		{ }

%%

int main()
{
	yylex();

	if ((display_name == NULL)
	||	(endian == NULL)
	||	(address_size == NULL)
	||	(end_lang == NULL))
	{
		fprintf(stderr, "\n[language parse]  FATAL\n\tMissing elements.\n\n");
		exit(-1);
	}

	ADD_TXT(  "LANGUAGE %1$s =\n{\n\t/* display_name: */\t\"%1$s\",\n\t",
			  strchr(display_name, L'(') + 1  );

	ADD_TXT(  "/* endian: */\t\t%s,\n\t",
			  strchr(endian, L':') + 1  );

	ADD_TXT(  "/* address_size: */\t%s,\n",
			  strchr(address_size, L':') + 1  );

	ADD_TXT(  "};"  );

	char file_name[260];
	display_name = strchr(  display_name, L'('  ) + 1;
	sprintf(  file_name, "src/%s.lang.c", display_name  );

	FILE *fp = fopen(  file_name, "wb"  );
	fprintf(  fp, "#include \"language.h\"\n\n%s\n", final_out  );

	char def_cmd[1024];
	sprintf(  def_cmd,
			  "touch include/languages_def.inc.0 && \
			   echo \"extern LANGUAGE %1$s;\" >> include/languages_def.inc.0 && \
			   touch include/languages_def.inc.1 && \
			   echo \"%1$s,\" >> include/languages_def.inc.1",
			  display_name  );

	system(  def_cmd  );

	return 0;
}

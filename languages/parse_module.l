%{
// #define _VERBOSE
#define ADD_TXT(fmt, ...) { pTxt += sprintf(pTxt, fmt __VA_OPT__(,) __VA_ARGS__  ); }

	typedef enum
	{
		INVALID = 0,
		TYPE_PLATFORM,
		TYPE_LANGUAGE,
		TYPE_MODE,
		TYPE_ARCHITECTURE
	} FILE_TYPE;

	FILE_TYPE ftype = INVALID;

	char final_out[1024];
	char *pTxt = final_out;

	char *identifier		= NULL;
	char *display_name		= NULL;
	char *user_description	= NULL;

	char *architecture	= NULL;
	char *language		= NULL;
	char *endian		= NULL;
	char *address_size	= NULL;
	char *end_platform	= NULL;

	char *type_hdr;
	char *type_hdr_upper;

%}

%%

^#.+?\n	{ }

^::[ \t]*.+?[ \t]*:\n {
	char *_yytext = strchr(yytext, L' ');

	if (_yytext == NULL)
		_yytext = strchr(yytext, L'\t');

	*(strstr(++_yytext, " :\n")) = '\0';

	while ((*_yytext == ' ') || (*_yytext == '\t'))
		++_yytext;

	user_description = malloc(strlen(_yytext));
	strcpy(user_description, _yytext);
}

PLATFORM\s*\([a-zA-Z0-9_]+?\) {
	ftype = TYPE_PLATFORM;
	type_hdr = "platform";
	type_hdr_upper = "PLATFORM";

	yytext = strchr(yytext, L'(') + 1;

	*(strchr(yytext, L')')) = '\0';

	identifier = malloc(strlen(yytext));
	strcpy(identifier, yytext);
}

ARCHITECTURE\s*\([a-zA-Z0-9_]+?\) {
	ftype = TYPE_ARCHITECTURE;
	type_hdr = "architecture";
	type_hdr_upper = "ARCHITECTURE";

	yytext = strchr(yytext, L'(') + 1;

	*(strchr(yytext, L')')) = '\0';

	identifier = malloc(strlen(yytext));
	strcpy(identifier, yytext);
}

LANGUAGE\s*\([a-zA-Z0-9_]+?\) {
	ftype = TYPE_LANGUAGE;
	type_hdr = "language";
	type_hdr_upper = "LANGUAGE";

	yytext = strchr(yytext, L'(') + 1;

	*(strchr(yytext, L')')) = '\0';

	identifier = malloc(strlen(yytext));
	strcpy(identifier, yytext);
}

MODE\s*\([a-zA-Z0-9_]+?\) {
	ftype = TYPE_MODE;
	type_hdr = "mode";
	type_hdr_upper = "MOVE";

	yytext = strchr(yytext, L'(') + 1;

	*(strchr(yytext, L')')) = '\0';

	identifier = malloc(strlen(yytext));
	strcpy(identifier, yytext);
}

DisplayName:\s*.+?\n {
	char *_yytext = strchr(yytext, L' ');

	if (_yytext == NULL)
		_yytext = strchr(yytext, L'\t');

	*(strchr(++_yytext, L'\n')) = '\0';

	while ((*_yytext == ' ') || (*_yytext == '\t'))
		++_yytext;

	display_name = malloc(strlen(_yytext));
	strcpy(display_name, _yytext);
}

Architecture:\s*.+?\n {
	char *_yytext = strchr(yytext, L' ');

	if (_yytext == NULL)
		_yytext = strchr(yytext, L'\t');

	*(strchr(++_yytext, L'\n')) = '\0';

	while ((*_yytext == ' ') || (*_yytext == '\t'))
		++_yytext;

	architecture = malloc(strlen(_yytext));
	strcpy(architecture, _yytext);
}

Language:\s*.+?\n {
	char *_yytext = strchr(yytext, L' ');

	if (_yytext == NULL)
		_yytext = strchr(yytext, L'\t');

	*(strchr(++_yytext, L'\n')) = '\0';

	while ((*_yytext == ' ') || (*_yytext == '\t'))
		++_yytext;

	language = malloc(strlen(_yytext));
	strcpy(language, _yytext);
}

Endianness:\s*.+?\n {
	char *_yytext = strchr(yytext, L' ');

	if (_yytext == NULL)
		_yytext = strchr(yytext, L'\t');

	*(strchr(++_yytext, L'\n')) = '\0';

	while ((*_yytext == ' ') || (*_yytext == '\t'))
		++_yytext;

	endian = malloc(strlen(_yytext));
	strcpy(endian, _yytext);
}

AddressSize:\s*.+?\n {
	char *_yytext = strchr(yytext, L' ');

	if (_yytext == NULL)
		_yytext = strchr(yytext, L'\t');

	*(strchr(++_yytext, L'\n')) = '\0';

	while ((*_yytext == ' ') || (*_yytext == '\t'))
		++_yytext;

	address_size = malloc(strlen(_yytext));
	strcpy(address_size, _yytext);
}

END_PLATFORM {
	end_platform = 0xDEADBEEF;
}

END_ARCHITECTURE {
	end_platform = 0xDEADBEEF;
}

END_LANGUAGE {
	end_platform = 0xDEADBEEF;
}

END_MODE {
	end_platform = 0xDEADBEEF;
}

\n		{ }
.		{ }

%%

int main()
{
	yylex();

	switch (ftype)
	{
	case TYPE_PLATFORM:

#ifdef    _VERBOSE

		ADD_TXT(  "PLATFORM %1$s =\n{\n\t/* identifier: */\t\"%1$s\",\n\t",
				identifier  );

		if (display_name != NULL) {
		ADD_TXT(  "/* display_name: */\t\"%s\",\n\t",
				display_name  );
		} else {
		ADD_TXT(  "/* display_name: */\t\"%s\",\n\t",
				identifier  );
		}

		if (user_description != NULL) {
		ADD_TXT(  "/* description: */\t\"%s\",\n\t",
				user_description  );
		} else {
		ADD_TXT(  "(0),\n\t");
		}

		ADD_TXT(  "/* architecture: */\t\"%s\",\n\t",
				architecture  );

		ADD_TXT(  "/* endian: */\t\t%s,\n\t",
				endian  );

		ADD_TXT(  "/* address_size: */\t%s,\n",
				address_size  );

		ADD_TXT(  "};"  );

#else  // _VERBOSE

		ADD_TXT(  "PLATFORM %1$s =\n{\n\t\"%1$s\",\n\t",
				identifier  );

		if (display_name != NULL) {
		ADD_TXT(  "\"%s\",\n\t",
				display_name  );
		} else {
		ADD_TXT(  "\"%s\",\n\t",
				identifier  );
		}

		if (user_description != NULL) {
		ADD_TXT(  "\"%s\",\n\t",
				user_description  );
		} else {
		ADD_TXT(  "(0),\n\t");
		}

		ADD_TXT(  "\"%s\",\n\t",
				architecture  );

		ADD_TXT(  "%s,\n\t",
				endian  );

		ADD_TXT(  "%s,\n",
				address_size  );

		ADD_TXT(  "};"  );

#endif // _VERBOSE

		if ((identifier == NULL)
		||	(architecture == NULL)
		||	(endian == NULL)
		||	(address_size == NULL)
		||	(end_platform == NULL))
		{
			fprintf(stderr, "\n[raichu spec parse]  FATAL\n\tMissing elements.\n\n");
			exit(-1);
		}

		break;

	case TYPE_ARCHITECTURE:

#ifdef    _VERBOSE

		ADD_TXT(  "ARCHITECTURE %1$s =\n{\n\t/* identifier: */\t\"%1$s\",\n\t",
				identifier  );

		if (display_name != NULL) {
		ADD_TXT(  "/* display_name: */\t\"%s\",\n\t",
				display_name  );
		} else {
		ADD_TXT(  "/* display_name: */\t\"%s\",\n\t",
				identifier  );
		}

		if (user_description != NULL) {
		ADD_TXT(  "/* description: */\t\"%s\",\n\t",
				user_description  );
		} else {
		ADD_TXT(  "(0),\n\t");
		}

		ADD_TXT(  "/* language: */\t\"%s\",\n",
				language  );

		ADD_TXT(  "};"  );

#else  // _VERBOSE

		ADD_TXT(  "ARCHITECTURE %1$s =\n{\n\t\"%1$s\",\n\t",
				identifier  );

		if (display_name != NULL) {
		ADD_TXT(  "\"%s\",\n\t",
				display_name  );
		} else {
		ADD_TXT(  "\"%s\",\n\t",
				identifier  );
		}

		if (user_description != NULL) {
		ADD_TXT(  "\"%s\",\n\t",
				user_description  );
		} else {
		ADD_TXT(  "(0),\n\t");
		}

		ADD_TXT(  "\"%s\",\n",
				language  );

		ADD_TXT(  "};"  );

#endif // _VERBOSE

		if ((identifier == NULL)
		||	(language == NULL))
		{
			fprintf(stderr, "\n[raichu spec parse]  FATAL\n\tMissing elements.\n\n");
			exit(-1);
		}

		break;

	case TYPE_LANGUAGE:

#ifdef    _VERBOSE

		ADD_TXT(  "LANGUAGE %1$s =\n{\n\t/* identifier: */\t\"%1$s\",\n\t",
				identifier  );

		if (display_name != NULL) {
		ADD_TXT(  "/* display_name: */\t\"%s\",\n",
				display_name  );
		} else {
		ADD_TXT(  "/* display_name: */\t\"%s\",\n",
				identifier  );
		}

		ADD_TXT(  "};"  );

#else  // _VERBOSE

		ADD_TXT(  "LANGUAGE %1$s =\n{\n\t\"%1$s\",\n\t",
				identifier  );

		if (display_name != NULL) {
		ADD_TXT(  "\"%s\",\n",
				display_name  );
		} else {
		ADD_TXT(  "\"%s\",\n",
				identifier  );
		}

		ADD_TXT(  "};"  );

#endif // _VERBOSE

		if (identifier == NULL)
		{
			fprintf(stderr, "\n[raichu spec parse]  FATAL\n\tMissing elements.\n\n");
			exit(-1);
		}

		break;

	case TYPE_MODE:

		if ((identifier == NULL)
		||	(architecture == NULL)
		||	(endian == NULL)
		||	(address_size == NULL)
		||	(end_platform == NULL))
		{
			fprintf(stderr, "\n[raichu spec parse]  FATAL\n\tMissing elements.\n\n");
			exit(-1);
		}

		break;

	default:
		fprintf(stderr, "\n[raichu spec parse]  FATAL\n\tUnrecognized spec file type.\n\n");
		exit(-1);
	}


	char file_name[260];
	sprintf(  file_name, "src/%s.lang.c", identifier  );

	FILE *fp = fopen(  file_name, "wb"  );
	fprintf(  fp, "#include \"%s.h\"\n\n%s\n", type_hdr, final_out  );

	char def_cmd[1024];
	sprintf(  def_cmd,

			  "echo \"extern %3$s %1$s;\" >> include/%2$s_def.inc.0 && \
			   echo \"%1$s,\" >> include/%2$s_def.inc.1",

			  identifier,
			  type_hdr,
			  type_hdr_upper  );

	system(  def_cmd  );

	return 0;
}

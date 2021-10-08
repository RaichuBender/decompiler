#include "args.h"
#include <strings.h>
#include <stdlib.h>

char *serialized_argv = NULL;

char *project_file = NULL;
char *binary_file  = NULL;

BOOL bLoadDefault = TRUE;

static inline void serialize_args(int argc, const char *argv[]);

static inline void open_project(void);
static inline void open_binary(void);
static inline void open_binary_nocmd(void);

/**********************************
*
*     @brief     
*
*     @param argc 
*     @param argv 
*
**********************************/
void parse_cmdline(int argc, const char *argv[])
{
	if (argc < 2)
		return;

	bLoadDefault = FALSE;
	serialize_args(argc, argv);

	if (strstr(serialized_argv, "-p"))		return open_project();
	if (strstr(serialized_argv, ".proj"))	return open_project();
	if (strstr(serialized_argv, "-b"))		return open_binary();

	open_binary_nocmd();
}

/**********************************
*
*     @brief     
*
*     @param argc 
*     @param argv 
*
**********************************/
static inline void serialize_args(int argc, const char *argv[])
{
	size_t length = 0;

	for (int arg = 1; arg < argc; ++arg)
		length += strlen(argv[arg]) + 2;

	serialized_argv = malloc(length);
	char *srlz = serialized_argv;

	for (int arg = 1; arg < argc; ++arg)
		srlz += sprintf(srlz, "%s ", argv[arg]);

	*(srlz - 1) = '\0';
}

/**********************************
*
*     	 @brief     
*
*
**********************************/
static inline void open_project(void)
{
	project_file = malloc(strlen(serialized_argv) + 1);
	strcpy(project_file, serialized_argv);
	project_file = strstr(project_file, "-p") + 2;
	char *end	 = strchr(project_file, L' ');

	if (end != NULL)
		*end = '\0';
}

/**********************************
*
*     	 @brief     
*
*
**********************************/
static inline void open_binary(void)
{
	binary_file = malloc(strlen(serialized_argv) + 1);
	strcpy(binary_file, serialized_argv);
	binary_file = strstr(binary_file, "-b") + 2;
	char *end	= strchr(binary_file, L' ');

	if (end != NULL)
		*end = '\0';
}

/**********************************
*
*     	 @brief     
*
*
**********************************/
static inline void open_binary_nocmd(void)
{
	binary_file = serialized_argv;
}

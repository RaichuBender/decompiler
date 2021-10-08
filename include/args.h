#ifndef ARGS_H
#define ARGS_H

#include "sys/common.h"

extern char *serialized_argv;

extern char *project_file;
extern char *binary_file;

extern BOOL bLoadDefault;

void parse_cmdline(int argc, const char *argv[]);

#endif /* ARGS_H */

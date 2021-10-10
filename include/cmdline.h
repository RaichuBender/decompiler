#ifndef __CMDLINE_H__
#define __CMDLINE_H__

#define CMD_LOOP_BEGIN                     \
	char str_read[64];                     \
	do                                     \
	{                                      \
		printf("0x%04x > ", byte_ptr); \
		fgets(str_read, 64, stdin);

#define CMD_LOOP_END \
	} while (1);

#define ON_MATCH(_in_)           \
	if (!strcmp(str_read, _in_)) \
	goto

#define GET_UL(_dst_)           \
	fgets(str_read, 64, stdin); \
	_dst_ = strtoul(str_read, NULL, 0);

#define RETURN	return cmdline_main();


void cmdline_main(void);

#endif /* __CMDLINE_H__ */

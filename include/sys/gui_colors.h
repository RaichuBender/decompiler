#ifndef __GUI_COLORS_H__
#define __GUI_COLORS_H__

/****     TODO     ****/

/**********************************
*
*	 @brief	Terminal colors
*
**********************************/

#define C_BLACK	   "\033[0;30m"		// COLOR black (regular)
#define C_RED	   "\033[0;31m"		// COLOR red (regular)
#define C_GREEN	   "\033[0;32m"		// COLOR green (regular)
#define C_YELLOW   "\033[0;33m"		// COLOR yellow (regular)
#define C_BLUE	   "\033[0;34m"		// COLOR blue (regular)
#define C_MAGENTA  "\033[0;35m"		// COLOR magenta (regular)
#define C_CYAN	   "\033[0;36m"		// COLOR cyan (regular)
#define C_WHITE	   "\033[0;37m"		// COLOR white (regular)

#define F_BOLD	   "\033[1m"		// FORMAT bold
#define F_RESET	   "\033[0m"		// FORMAT reset

#define CB_BLACK   C_BLACK   F_BOLD	// COLOR black (bold)
#define CB_RED	   C_RED     F_BOLD	// COLOR red (bold)
#define CB_GREEN   C_GREEN   F_BOLD	// COLOR green (bold)
#define CB_YELLOW  C_YELLOW  F_BOLD	// COLOR yellow (bold)
#define CB_BLUE	   C_BLUE    F_BOLD	// COLOR blue (bold)
#define CB_MAGENTA C_MAGENTA F_BOLD // COLOR magenta (bold)
#define CB_CYAN	   C_CYAN    F_BOLD	// COLOR cyan (bold)
#define CB_WHITE   C_WHITE   F_BOLD	// COLOR white (bold)

#endif // __GUI_COLORS_H__

/**********************************
*
*	 @file      common.h
*	 @author    Thomas Gijsbers
*	 @brief     
*	 @version   0.1
*	 @date      2021／09／24
*
*	 @copyright	Ⓒ Copyright 2021 — Thomas Gijsbers
*	           	   All rights reserved.
*
**********************************/
#ifndef __COMMON_H__
#define __COMMON_H__

#include "typedefs.h"

/**
 * @name	EVAL
 * @brief	Evaluate (return) value and abort execution
 * 			upon \a NULL or \p -1
 * 
 * @param[in]	val The expression or variablle to check
 * 
 * @returns		The evaluated value (if not invalid)
 */
#define EVAL(val)                                 \
	({                                            \
		auto var = (val);                         \
		if (0 >= (s64)var)                        \
		{                                         \
			fprintf(stderr,                       \
					"\033[0;37m\033[1m%s:%d: "    \
					"\033[0;31m\033[1mERROR: "    \
					"\033[0;37mEVAL failed for: " \
					"\033[0;37m\033[1m" #val " "  \
					"\033[0m\033[0;37m("          \
					"%d)\033[0m\n",               \
					__FILE__, __LINE__, var);     \
			exit(-1);                             \
		}                                         \
		var;                                      \
	})

#endif // __COMMON_H__

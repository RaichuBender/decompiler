/**********************************
*
*	 @file      language_def.h
*	 @author    Thomas Gijsbers (@RaichuBender)
*	 @brief     
*	 @version   0.1
*	 @date      2021／09／24
*
*	 @copyright  © Copyright 2021 — Thomas Gijsbers
*	           	   All rights reserved.
*
**********************************/
#ifndef __LANGUAGE_DEF_H__
#define __LANGUAGE_DEF_H__

#include "language.h"
#include "languages_def.0.gen.h"

LANGUAGE language_module_list[] =
{
#	include "languages_def.1.gen.h"
};

#endif // __LANGUAGE_DEF_H__

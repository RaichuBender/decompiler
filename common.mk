#**********************************
#
#	 @file      common.mk
#	 @author    Thomas Gijsbers
#	 @brief     Common definitions
#				across most rules
#	 @version   0.1
#	 @date      2021／09／24
#
#	 @copyright	Ⓒ Copyright 2021 — Thomas Gijsbers
#	           	   All rights reserved.
#
#**********************************
CC	:=	gcc

INCLUDE	:=	-I$(ROOTPARH)include	\
	-I$(ROOTPARH)include/sys	\
	-I$(ROOTPARH)include/organization	\
	-I$(ROOTPARH)include/disassembler

MAKE	+=	--no-print-directory

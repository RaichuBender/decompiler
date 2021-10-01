#**********************************
#
#	 @file      common.mk
#	 @author    Thomas Gijsbers (@RaichuBender)
#	 @brief     Common definitions
#				across most rules
#	 @version   0.1
#	 @date      2021／09／24
#
#	 @copyright  © Copyright 2021 — Thomas Gijsbers
#	           	   All rights reserved.
#
#**********************************
# ADD_SUFFIX	 = TRUE

DBG_SUFFIX	:= _d
REL_SUFFIX	:= _r
STATIC_LINK_SUFFIX	 = _static

PROFILE	 = DEBUG
# PROFILE	 = RELEASE

# STATIC_LINK	 = TRUE

CC	 =	gcc

INCLUDE	:=	-I$(ROOTPARH)include	\
	-I$(ROOTPARH)include/sys	\
	-I$(ROOTPARH)include/organization	\
	-I$(ROOTPARH)include/disassembler

MAKE	+=	--no-print-directory


ifeq ($(PROFILE),RELEASE)

ifeq ($(ADD_SUFFIX),TRUE)
EXE_SFX	:= $(REL_SUFFIX)
endif

CFLAGS	:= -O2 -s
else #eq ($(PROFILE),RELEASE)

ifeq ($(ADD_SUFFIX),TRUE)
EXE_SFX	:= $(DBG_SUFFIX)
endif

CFLAGS	:= -O0 -g -D_DEBUG
endif #eq ($(PROFILE),RELEASE)


ifeq ($(STATIC_LINK),TRUE)
ifeq ($(ADD_SUFFIX),TRUE)
EXE_SFX	:= $(EXE_SFX)$(STATIC_LINK_SUFFIX)
endif
CFLAGS	+= -static
endif

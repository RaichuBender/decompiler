#**********************************
#
#	 @file      objects.mk
#	 @author    Thomas Gijsbers (@RaichuBender)
#	 @brief     Root folder object rules
#	 @version   0.1
#	 @date      2021／09／24
#
#	 @copyright  © Copyright 2021 — Thomas Gijsbers
#	           	   All rights reserved.
#
#**********************************
SOURCES	:=	$(wildcard src/*.c)
OBJECTS	:=	$(patsubst src/%,obj/%,$(SOURCES))
OBJECTS	:=	$(OBJECTS:%.c=%.o)

UI_SOURCES	:=	$(wildcard src/ui/*.c)
UI_OBJECTS	:=	$(patsubst src/ui/%,obj/%,$(UI_SOURCES))
UI_OBJECTS	:=	$(UI_OBJECTS:%.c=%.o)

LANG_SOURCES :=	$(wildcard modules/languages/src/*.c)
LANG_OBJECTS :=	$(patsubst modules/languages/src/%,modules/languages/obj/%,$(LANG_SOURCES))
LANG_OBJECTS :=	$(LANG_OBJECTS:%.c=%.o)

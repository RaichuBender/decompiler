#**********************************
#
#	 @file      Makefile
#	 @author    Thomas Gijsbers
#	 @brief     Root folder Makefile
#	 @version   0.1
#	 @date      2021／09／24
#
#	 @copyright	Ⓒ Copyright 2021 — Thomas Gijsbers
#	           	   All rights reserved.
#
#**********************************
include common.mk

# EXE	:=	bin/main
EXE	:=	main

LIB	:=	-Llib
OUT	:=	bin obj

SOURCES	:=	$(wildcard src/*.c)
OBJECTS	:=	$(patsubst src/%,obj/%,$(SOURCES))
OBJECTS	:=	$(OBJECTS:%.c=%.o)

LANG_SOURCES :=	$(wildcard modules/languages/src/*.c)
LANG_OBJECTS :=	$(patsubst modules/languages/src/%,modules/languages/obj/%,$(LANG_SOURCES))
LANG_OBJECTS :=	$(LANG_OBJECTS:%.c=%.o)

CFLAGS	:= -O0 -g
#CFLAGS	:= -O2 -s -static


default:	$(OUT)
	@$(MAKE) -C modules/languages
	@$(MAKE) all

all:		$(EXE)

$(EXE):		$(OBJECTS) $(LANG_OBJECTS)
	$(CC) -o $@	$^ $(CFLAGS) $(INCLUDE) $(LIB)

obj/%.o:	src/%.c
	$(CC) -o $@ -c	$^ $(CFLAGS) $(INCLUDE) $(LIB)

$(OUT):
	@-mkdir $@

.PHONY:		pkg clean clean-all

PKG			:= build
$(PKG):
	-mkdir $@

pkg:		$(PKG)
	-mkdir -p $</bin
	mv $(EXE) $</$(EXE)
	cp .pokeyellow.gbc $</.pokeyellow.gbc # TODO placeholder
	@$(MAKE) clean

clean:
	@-rm -rf $(EXE) $(OUT)
	@$(MAKE) -C modules/languages clean

clean-all:
	@-rm -rf $(EXE) $(OUT) $(PKG)
	@$(MAKE) -C modules/languages clean-all

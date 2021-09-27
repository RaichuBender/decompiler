#**********************************
#
#	 @file      Makefile
#	 @author    Thomas Gijsbers (@RaichuBender)
#	 @brief     
#	 @version   0.1
#	 @date      2021／09／24
#
#	 @copyright  © Copyright 2021 — Thomas Gijsbers
#	           	   All rights reserved.
#
#**********************************
ROOTPARH	:=	../../

include ../../common.mk

INCLUDE	+=	-Iinclude
LIB	:=
OUT	:=	obj tmp

OUTPUT	:=	../../lib/languages.so

SOURCES	:=	$(wildcard src/*.c)
OBJECTS	:=	$(patsubst src/%,obj/%,$(SOURCES))
OBJECTS	:=	$(OBJECTS:%.c=%.o)

CFLAGS	+= -fPIC


default:	$(OUT)
	@$(MAKE) -f noodles.mk
	@$(MAKE) all

all:		$(OUTPUT)
$(OUTPUT):	$(OBJECTS)
	$(CC) -o $@ -shared	$^ $(CFLAGS) $(INCLUDE) $(LIB)

obj/%.o:	src/%.c
	$(CC) -o $@ -c		$^ $(CFLAGS) $(INCLUDE) $(LIB)

$(OUT):
	@-mkdir $@

.PHONY:		clean clean-all
clean:
	@-rm -rvf $(EXE) $(OUT)
	@$(MAKE) -f noodles.mk clean

clean-all:
	@-rm -rvf $(EXE) $(OUT)
	@$(MAKE) -f noodles.mk clean-all

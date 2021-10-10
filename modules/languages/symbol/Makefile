#**********************************
#
#	 @file      Makefile
#	 @author    Thomas Gijsbers (@RaichuBender)
#	 @brief     
#	 @version   0.1
#	 @date      2021／10／09
#
#	 @copyright  © Copyright 2021 — Thomas Gijsbers
#	           	   All rights reserved.
#
#**********************************
EXE	:=	../symbol_parse
INCLUDE	:= -I. -I../../../include -I../include

CFLAGS	:= -lfl -D_DEBUG -Wno-int-conversion

default:		symbol

symbol:		symbol.gen.h
	$(MAKE) $(EXE)

symbol.gen.h:	rules.l
	flex -o $@ $^

$(EXE):		symbol.o
	$(CC) -O2 -s $^ -o $@ $(INCLUDE) $(CFLAGS)

%.o:			%.c
	$(CC) -O2 -s $^ -o $@ $(INCLUDE) $(CFLAGS) -c

.PHONY:clean clean-all
clean:
	-rm -vf *.o *.gen.h
clean-all:clean
	-rm -vf $(EXE)

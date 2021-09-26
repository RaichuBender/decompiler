#**********************************
#
#	 @file      Makefile
#	 @author    Thomas Gijsbers
#	 @brief     
#	 @version   0.1
#	 @date      2021／09／24
#
#	 @copyright	Ⓒ Copyright 2021 — Thomas Gijsbers
#	           	   All rights reserved.
#
#**********************************
EXE_PA	:=	../pass_noodle_tool
EXE_PR	:=	../preach_modest_tool

INCLUDE	:= -I. -I../../../include -I../include

default:		pass_noodle preach_modest

pass_noodle:		pass_noodle.gen.h
	$(MAKE) $(EXE_PA)

preach_modest:		preach_modest.gen.h
	$(MAKE) $(EXE_PR)

pass_noodle.gen.h:	pass_noodle.l
	flex -o $@ $^

preach_modest.gen.h:	preach_modest.l
	flex -o $@ $^

$(EXE_PA):		pass_noodle.o
	$(CC) -O2 -s $^ -o $@ $(INCLUDE) -lfl -D_SYNTAX -Wno-int-conversion

$(EXE_PR):		preach_modest.o
	$(CC) -O2 -s $^ -o $@ $(INCLUDE) -lfl -D_SYNTAX -Wno-int-conversion

%.o:			%.c
	$(CC) -O2 -s $^ -o $@ $(INCLUDE) -lfl -D_SYNTAX -Wno-int-conversion -c

.PHONY:clean clean-all
clean:
	-@rm -vf *.o *.gen.h
clean-all:clean
	-@rm -vf $(EXE_PA) $(EXE_PR)

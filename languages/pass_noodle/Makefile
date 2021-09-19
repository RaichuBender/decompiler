SOURCES	:=	$(wildcard *.c)
OBJECTS	:=	$(SOURCES:%.c=%.o)

EXE	:=	../parse_module

pass_noodle:		parse_module.gen.h
	$(MAKE) $(EXE)

parse_module.gen.h:	parse_module.l
	flex -o $@ $^

$(EXE):			$(OBJECTS)
	$(CC) -O2 -s $^ -o $@ -lfl -D_SYNTAX -Wno-int-conversion

%.o:			%.c
	$(CC) -O2 -s $^ -o $@ -lfl -D_SYNTAX -Wno-int-conversion -c

.PHONY:clean clean-all
clean:
	-@rm -vf *.o parse_module.gen.h
clean-all:clean
	-@rm -vf ../parse_module

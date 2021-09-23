EXE_PA	:=	../parse_module
EXE_PR	:=	../preprocess

default:		pass_noodle preach_modest

pass_noodle:		parse_module.gen.h #language.gen.h
	$(MAKE) $(EXE_PA)

preach_modest:		preprocess.gen.h
	$(MAKE) $(EXE_PR)

parse_module.gen.h:	parse_module.l
	flex -o $@ $^

# language.gen.h:		language.l
# 	flex -o $@ --prefix=language_ $^

preprocess.gen.h:	preprocess.l
	flex -o $@ $^

$(EXE_PA):		pass_noodle.o #language.o
	$(CC) -O2 -s $^ -o $@ -lfl -D_SYNTAX -Wno-int-conversion

$(EXE_PR):		preach_modest.o
	$(CC) -O2 -s $^ -o $@ -lfl -D_SYNTAX -Wno-int-conversion

%.o:			%.c
	$(CC) -O2 -s $^ -o $@ -lfl -D_SYNTAX -Wno-int-conversion -c

.PHONY:clean clean-all
clean:
	-@rm -vf *.o *.gen.h
clean-all:clean
	-@rm -vf ../parse_module ../preprocess

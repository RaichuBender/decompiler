include common.mk

# EXE	:=	bin/main
EXE	:=	main

LIB	:=	-Llib
OUT	:=	bin obj

SOURCES	:=	$(wildcard src/*.c)
OBJECTS	:=	$(patsubst src/%,obj/%,$(SOURCES))
OBJECTS	:=	$(OBJECTS:%.c=%.o)

LANG_SOURCES :=	$(wildcard languages/src/*.c)
LANG_OBJECTS :=	$(patsubst languages/src/%,languages/obj/%,$(LANG_SOURCES))
LANG_OBJECTS :=	$(LANG_OBJECTS:%.c=%.o)

default:	$(OUT)
	@$(MAKE) -C languages
	@$(MAKE) all

all:		$(EXE)

$(EXE):		$(OBJECTS) $(LANG_OBJECTS)
	$(CC) -o $@	$^ $(CFLAGS) $(INCLUDE) $(LIB)

obj/%.o:	src/%.c
	$(CC) -o $@ -c	$^ $(CFLAGS) $(INCLUDE) $(LIB)

$(OUT):
	@-mkdir $@

.PHONY:		clean clean-all
clean:
	@-rm -rf $(EXE) $(OUT)
	@$(MAKE) -C languages clean

clean-all:
	@-rm -rf $(EXE) $(OUT)
	@$(MAKE) -C languages clean-all

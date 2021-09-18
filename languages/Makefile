ROOTPARH	:=	../

include ../common.mk

INCLUDE	+=	-Iinclude
LIB	:=
OUT	:=	obj tmp

OUTPUT	:=	../lib/languages.so

SOURCES	:=	$(wildcard src/*.c)
OBJECTS	:=	$(patsubst src/%,obj/%,$(SOURCES))
OBJECTS	:=	$(OBJECTS:%.c=%.o)

CFLAGS	:=	-fPIC

default:	$(OUT)
	@$(MAKE) -f modules.mk
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
	@$(MAKE) -f modules.mk clean

clean-all:
	@-rm -rvf $(EXE) $(OUT)
	@$(MAKE) -f modules.mk clean-all

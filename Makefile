#**********************************
#
#	 @file      Makefile
#	 @author    Thomas Gijsbers (@RaichuBender)
#	 @brief     Root folder Makefile
#	 @version   0.1
#	 @date      2021／09／24
#
#	 @copyright  © Copyright 2021 — Thomas Gijsbers
#	           	   All rights reserved.
#
#**********************************
include common.mk

# EXE	:=	bin/main
EXE_BASE	:=	main
EXE	:= $(EXE_BASE)$(EXE_SFX)

LIB	:=	-Llib
OUT	:=	bin obj

SOURCES	:=	$(wildcard src/*.c)
OBJECTS	:=	$(patsubst src/%,obj/%,$(SOURCES))
OBJECTS	:=	$(OBJECTS:%.c=%.o)

LANG_SOURCES :=	$(wildcard modules/languages/src/*.c)
LANG_OBJECTS :=	$(patsubst modules/languages/src/%,modules/languages/obj/%,$(LANG_SOURCES))
LANG_OBJECTS :=	$(LANG_OBJECTS:%.c=%.o)


default:	$(OUT)
	@$(MAKE) -C modules/languages
	@$(MAKE) $(EXE)

.PHONY:		all pkg clean clean-all

#	Moreso for testing and deployment
# This will make all targets, including
# debug and stripped/static versions.
# This could be quite wasteful in the
# future, so be mindful of what you do
all:

	@$(MAKE) default	-E'override PROFILE:=DEBUG'	-E'override STATIC_LINK:=FALSE'	-E'override ADD_SUFFIX:=TRUE'
	@$(MAKE) clean		-E'override PROFILE:=DEBUG'	-E'override STATIC_LINK:=FALSE'	-E'override ADD_SUFFIX:=TRUE'

	@$(MAKE) default	-E'override PROFILE:=RELEASE'	-E'override STATIC_LINK:=FALSE'	-E'override ADD_SUFFIX:=TRUE'
	@$(MAKE) clean		-E'override PROFILE:=RELEASE'	-E'override STATIC_LINK:=FALSE'	-E'override ADD_SUFFIX:=TRUE'

	@$(MAKE) default	-E'override PROFILE:=DEBUG'	-E'override STATIC_LINK:=TRUE'	-E'override ADD_SUFFIX:=TRUE'
	@$(MAKE) clean		-E'override PROFILE:=DEBUG'	-E'override STATIC_LINK:=TRUE'	-E'override ADD_SUFFIX:=TRUE'

	@$(MAKE) default	-E'override PROFILE:=RELEASE'	-E'override STATIC_LINK:=TRUE'	-E'override ADD_SUFFIX:=TRUE'
	@$(MAKE) clean		-E'override PROFILE:=RELEASE'	-E'override STATIC_LINK:=TRUE'	-E'override ADD_SUFFIX:=TRUE'

$(EXE):		$(OBJECTS) $(LANG_OBJECTS)
	$(CC) -o $@	$^ $(CFLAGS) $(INCLUDE) $(LIB)

obj/%.o:	src/%.c
	$(CC) -o $@ -c	$^ $(CFLAGS) $(INCLUDE) $(LIB)

$(OUT):
	@-mkdir $@


PKG			:= build
$(PKG):
	-mkdir $@

pkg:		$(PKG)
	-mkdir -p $</bin
	mv $(EXE) $</$(EXE)
	cp .pokeyellow.gbc $</.pokeyellow.gbc # TODO placeholder
	@$(MAKE) clean

clean:
	@-rm -rf $(OUT)
#	@$(MAKE) -C modules/languages clean
	@$(MAKE) -C modules/languages clean-all

clean-all:
	@-rm -rf $(EXE_BASE)* $(OUT) $(PKG)
	@$(MAKE) -C modules/languages clean-all

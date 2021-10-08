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

BINDIR	:=	bin/
OBJDIR	:=	obj/
EXE_BASE:=	main
EXE	:= $(BINDIR)$(EXE_BASE)$(EXE_SFX)

include objects.mk

ifeq ($(STATIC_LINK),TRUE)
OBJECTS	+=	$(LANG_OBJECTS)
else
LIB	:=	-Llib -llanguages
endif

OUT	:=	$(BINDIR) $(OBJDIR)

default:	$(OUT)
	@$(MAKE) -C modules/languages
	@$(MAKE) $(EXE)

.PHONY:		all dbg pkg all-pkg clean clean-all r rs pkg r-pkg rs-pkg deploy build install uninstall

include todo.mk

install:
	-rm -r /usr/bin/decompiler /usr/lib/liblanguages.so /usr/share/decompiler
	cp bin/main /usr/bin/decompiler
	ln -s lib/liblanguages.so /usr/lib/liblanguages.so
	mkdir /usr/share/decompiler
	cp .pokeyellow.gbc /usr/share/decompiler

uninstall:
	-rm -r /usr/bin/decompiler /usr/lib/liblanguages.so /usr/share/decompiler

$(EXE):		$(OBJECTS)
	$(CC) -o $@	$^ $(CFLAGS) $(INCLUDE) $(LIB)
	-ln -s bin/main main

obj/%.o:	src/%.c
	$(CC) -o $@ -c	$^ $(CFLAGS) $(INCLUDE) $(LIB)

$(OUT):
	@-mkdir $@


PKG			= build
$(PKG):
	-mkdir $@

pkg:		$(PKG)
#	-mkdir -p $</bin
	mv $(EXE) $</$(EXE)
	cp .pokeyellow.gbc $(PKG)/.pokeyellow.gbc # TODO placeholder
	@$(MAKE) clean

clean:
	@-rm -rf $(OUT)
#	@$(MAKE) -C modules/languages clean
	@$(MAKE) -C modules/languages clean-all

clean-all:
	@-rm -rf $(EXE_BASE)* $(OUT) $(PKG)
	@$(MAKE) -C modules/languages clean-all

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

BINDIR		:=	bin/
OBJDIR		:=	obj/
EXE_BASE	:=	main
EXE		:= $(BINDIR)$(EXE_BASE)$(EXE_SFX)

include objects.mk

ifeq ($(STATIC_LINK),TRUE)
OBJECTS		+=	$(LANG_OBJECTS)
else
LIB		:=	-Llib -llanguages $(shell pkg-config --libs gtk4) -rdynamic
endif

OBJECTS		+=	$(UI_OBJECTS)

OUT		:=	$(BINDIR) $(OBJDIR)

PRECOMPILE	:=	include/ui.h.gch include/sys/common.h.gch

default:	dbg
d:	$(OUT)
	@$(MAKE) -C modules/languages
	@$(MAKE) $(PRECOMPILE)
	@$(MAKE) $(EXE)

dbg:
#	@$(MAKE) d -E'override PROFILE:=DEBUG' -E'override STATIC_LINK:=FALSE'
	@$(MAKE) d -E'override PROFILE:=DBG_O2' -E'override STATIC_LINK:=FALSE'

.PHONY:		all dbg pkg all-pkg clean clean-all clean-derived force-clean-all r rs pkg r-pkg rs-pkg deploy build install uninstall

include todo.mk

install:
	-rm -r /usr/local/bin/decompiler /usr/lib/liblanguages.so /usr/local/lib/liblanguages.so /usr/local/share/decompiler ~/.local/share/applications/decompiler.desktop
	cp bin/main /usr/local/bin/decompiler
	cp lib/liblanguages.so /usr/local/lib
	ln -s /usr/local/lib/liblanguages.so /usr/lib/liblanguages.so
	mkdir -p /usr/local/share/decompiler
	cp .pokeyellow.gbc /usr/local/share/decompiler
	cp decompiler.desktop ~/.local/share/applications

uninstall:
	-rm -r /usr/local/bin/decompiler /usr/lib/liblanguages.so /usr/local/lib/liblanguages.so /usr/local/share/decompiler ~/.local/share/applications/decompiler.desktop

$(EXE):		$(OBJECTS)
	$(CC) -o $@	$^ $(CFLAGS) $(INCLUDE) $(LIB)
	-ln -s bin/main main

obj/%.o:	src/%.c
	$(CC) -o $@ -c	$^ $(CFLAGS) $(INCLUDE) $(LIB)

include/ui.h.gch:	 include/ui.h
	$(CC) $< $(CFLAGS) $(INCLUDE) $(shell pkg-config --cflags gtk4) -rdynamic

include/sys/common.h.gch:	 include/sys/common.h
	$(CC) $< $(CFLAGS) $(INCLUDE)

obj/%.o:	src/ui/%.c
	$(CC) -o $@ -c	$^ $(CFLAGS) $(INCLUDE) $(shell pkg-config --cflags gtk4) $(LIB)


$(OUT):
	@-mkdir $@


PKG		= build
$(PKG):
	-mkdir $@

pkg:		$(PKG)
	mv $(EXE) $</$(EXE)
	cp .pokeyellow.gbc $(PKG)/.pokeyellow.gbc # TODO placeholder
	@$(MAKE) clean

force-clean-all:
	@echo "\n\n"'⚠️ ⚠️ ⚠️  WARNING ⚠️ ⚠️ ⚠️'"\n"
	@echo This will completely uninstall the program from this machine!
	@echo Press ^C to abort now
	@echo ... otherwise any other key to continue
	@read dum
	@$(MAKE)	clean	clean-all	clean-derived	uninstall

clean-after-install:
	@$(MAKE)	clean	clean-all	clean-derived

clean:
	-rm -rvf $(OUT)
#	@$(MAKE) -C modules/languages clean
	@$(MAKE) -C modules/languages clean-all

clean-all:
	-rm -rvf $(EXE_BASE)* $(OUT) $(PKG)
	@$(MAKE) -C modules/languages clean-all

clean-derived:
	-rm -vf $(PRECOMPILE) include/*.gch include/*.pch

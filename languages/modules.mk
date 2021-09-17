ROOTPARH	:=	../

include ../common.mk

LANGMODS	:=	$(wildcard modules/*.langmod)
LANGMODS	:=	$(patsubst modules/%,tmp/%,$(LANGMODS))
LANGMODS	:=	$(LANGMODS:%.langmod=%.lmtmp)

# .PHONY:		$(LANGMODS)

default:	parse_lang
	@echo ''
	@echo 'Parsing languages'
	@echo ''
	@echo '--------------------'
	@-rm -vf include/languages_def.inc.*
	@$(MAKE) -f modules.mk $(LANGMODS)
	@rm -f $(LANGMODS)
	@echo ''
	@echo '--------------------'
	@echo 'Parsing SUCCES'
	@echo ''

tmp/%.lmtmp:	modules/%.langmod
	./parse_lang < $^
	@touch $@

parse_lang:	parse_lang.l
	flex -o $@.tmp.c $@.l
	$(CC) $@.tmp.c -o $@ -lfl -Wno-int-conversion
	-@rm $@.tmp.c


.PHONY:		clean
clean:
	@-rm -vf src/*.lang.c parse_lang parse_lang.tmp.c include/languages_def.inc*

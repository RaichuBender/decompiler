include ../common.mk

LANGMODS	:=	$(wildcard modules/*.langmod)
LANGMODS	:=	$(patsubst modules/%,tmp/%,$(LANGMODS))
LANGMODS	:=	$(LANGMODS:%.langmod=%.lmtmp)

# .PHONY:		$(LANGMODS)

default:	parse_lang
	@echo ''
	@echo 'Parsing language'
	@-rm -vf include/languages_def.inc.*
	@$(MAKE) -f modules.mk $(LANGMODS)
	@rm -f $(LANGMODS)

tmp/%.lmtmp:	modules/%.langmod
	./parse_lang < $^
	@touch $@

parse_lang:	parse_lang.l
	flex -o $@.c $^
	$(CC) $@.c -o $@ -lfl -Wno-int-conversion
	@-rm $@.c


.PHONY:		clean
clean:
	@-rm -vf src/*.lang.c parse_lang include/languages_def.inc*

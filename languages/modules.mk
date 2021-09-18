ROOTPARH	:=	../

include ../common.mk

MODULE_SPECS	:=	$(wildcard modules/*module modules/**/*module)
MODULE_SPECS	:=	$(patsubst modules/%,tmp/%,$(MODULE_SPECS))
MODULE_SPECS	:=	$(MODULE_SPECS:%module=%.lmtmp)

# .PHONY:		$(MODULE_SPECS)

default:	parse_module
	@echo ''
	@echo 'Parsing module specs...'
	@echo ''
	@echo '--------------------'
	@-rm -vf include/*_def.inc*
	@$(MAKE) -f modules.mk $(MODULE_SPECS)
	@rm -f $(MODULE_SPECS)
	@echo ''
	@echo '--------------------'
	@echo 'Parsing SUCCES!'
	@echo ''

tmp/%.lmtmp:	modules/%module
	./parse_module < $^
	@touch $@

parse_module:	parse_module.l
	flex -o $@.tmp.c $@.l
	$(CC) -O2 -s $@.tmp.c -o $@ -lfl -Wno-int-conversion
	-@rm $@.tmp.c


.PHONY:		clean clean-all
clean:
	@-rm -vf parse_module.tmp.c

clean-all:
	@-rm -rvf src/*.lang.c parse_module parse_module.tmp.c include/*_def.inc*

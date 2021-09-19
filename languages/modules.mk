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

parse_module:
	@$(MAKE) -C pass_noodle


.PHONY:		clean clean-all
clean:
	@-$(MAKE) -C pass_noodle clean

clean-all:
	@-rm -rvf src/*.module.c include/*_def.inc*
	@-$(MAKE) -C pass_noodle clean-all

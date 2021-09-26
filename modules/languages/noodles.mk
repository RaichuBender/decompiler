#**********************************
#
#	 @file      noodles.mk
#	 @author    Thomas Gijsbers (@RaichuBender)
#	 @brief     
#	 @version   0.1
#	 @date      2021／09／24
#
#	 @copyright  © Copyright 2021 — Thomas Gijsbers
#	           	   All rights reserved.
#
#**********************************
ROOTPARH	:=	../../

include ../../common.mk

MODULE_SPECS	:=	$(wildcard noodles/*ndl noodles/**/*ndl)
MODULE_SPECS	:=	$(patsubst noodles/%,tmp/%,$(MODULE_SPECS))
MODULE_SPECS	:=	$(MODULE_SPECS:%ndl=%.lmtmp)

default:	pass_noodle_tool
	@echo ''
	@echo 'Parsing ndl specs...'
	@echo ''
	@echo '--------------------'
	@-rm -vf include/*_def.inc*
	@$(MAKE) -f noodles.mk $(MODULE_SPECS)
	@rm -f $(MODULE_SPECS)
	@echo ''
	@echo '--------------------'
	@echo 'Parsing SUCCES!'
	@echo ''

tmp/%.lmtmp:	noodles/%ndl
	./preach_modest_tool $^.preproc < $^
	./pass_noodle_tool $^ < $^.preproc
	@touch $@

pass_noodle_tool:
	@$(MAKE) -C pass_noodle


.PHONY:		clean clean-all
clean:
	@-$(MAKE) -C pass_noodle clean

clean-all:
	@-rm -rvf src/*.ndl.c include/*.gen.h noodles/*.preproc
	@-$(MAKE) -C pass_noodle clean-all

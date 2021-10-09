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

all-pkg:	all
	@$(MAKE) pkg	-E'override PROFILE:=DEBUG'	-E'override STATIC_LINK:=FALSE'	-E'override ADD_SUFFIX:=TRUE'
	@$(MAKE) pkg	-E'override PROFILE:=RELEASE'	-E'override STATIC_LINK:=FALSE'	-E'override ADD_SUFFIX:=TRUE'
	@$(MAKE) pkg	-E'override PROFILE:=DEBUG'	-E'override STATIC_LINK:=TRUE'	-E'override ADD_SUFFIX:=TRUE'
	@$(MAKE) pkg	-E'override PROFILE:=RELEASE'	-E'override STATIC_LINK:=TRUE'	-E'override ADD_SUFFIX:=TRUE'

r:
	@$(MAKE) default	-E'override PROFILE:=RELEASE'	-E'override STATIC_LINK:=FALSE'	-E'override ADD_SUFFIX:=TRUE'
rs:
	@$(MAKE) default	-E'override PROFILE:=RELEASE'	-E'override STATIC_LINK:=TRUE'	-E'override ADD_SUFFIX:=TRUE'

r-pkg:	r
	@$(MAKE) pkg	-E'override PROFILE:=RELEASE'	-E'override STATIC_LINK:=FALSE'	-E'override ADD_SUFFIX:=TRUE'
rs-pkg:	rs
	@$(MAKE) pkg	-E'override PROFILE:=RELEASE'	-E'override STATIC_LINK:=TRUE'	-E'override ADD_SUFFIX:=TRUE'

dbg:
	@$(MAKE) d -E'override PROFILE:=DEBUG' -E'override STATIC_LINK:=FALSE'

deploy:
	$(MAKE) rs-pkg -E'override PKG:=release' -E'override EXE:=decompiler'

final:
	-mkdir -p build/bin
	$(MAKE) rs-pkg -E'override PKG:=build/bin' -E'override EXE:=decompiler'

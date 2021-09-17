CC	:=	gcc

INCLUDE	:=	-I$(ROOTPARH)include	\
	-I$(ROOTPARH)include/sys	\
	-I$(ROOTPARH)include/organization	\
	-I$(ROOTPARH)include/disassembler

MAKE	+=	--no-print-directory

// 00:049d		LD	A, (0xd6ff)
// 00:04a0		DEC	A
// 00:04a1		RET	NZ
// 00:04a2		LD	A, (0xd735)
// 00:04a5		<<CB>>	0x77
// 00:04a7		RET	NZ
// 00:04a8		LD	A, (0xcc57)
// 00:04ab		AND	A
// 00:04ac		RET	NZ
// 00:04ad		LD	A, (0xd35d)
// 00:04b0		CP	0x1c
// 00:04b2		JR	NZ, 0x04b9
// 00:04b3		DEC	B
// 00:04b4		LDH	A, (0xffb4)
// 00:04b6		AND	0x70
// 00:04b8		RET	NZ
// 00:04b9		CALL	0x0b7f
// 00:04bc		RET


extern g0b7f();

extern unsigned char gcc57;
extern unsigned char gd35d;
extern unsigned char gd6ff;
extern unsigned char gd735;
extern unsigned char gffb4;


g049d(p1)
	unsigned char p1;
{
	if (gd6ff != 1)
		return;

	// Currently, CB instructions are a WIP
	if (CB(gd735, 0x77) != 0)
		return;

	if ((gcc57 & gcc57) != 0)
		return;

	if (gd35d == 0x1c)
	{
		--p1;
		if ((gffb4 & 0x70) != 0)
			return;
	}

	return g0b7f(p1);
}

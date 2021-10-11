typedef unsigned char  u8;
typedef unsigned short u16;

typedef unsigned char BOOL;
#define FALSE (0)
#define TRUE  (1)

#define NULL  (0)

u8	MtMoon3TrainerHeaders[];
u8 *MtMoonB2F_ScriptPointers[];
u8	wMtMoonB2FCurScript;
u8	CoordsData_49d37;
u8 *wd72e;
u8	wEventFlags[320];

#if 0
MtMoonB2F_Script:
12:5c8a         CALL    0x3c29
12:5c8d         LD      HL, 0x5fb8
12:5c8e         CP      A, B
12:5c8f         LD      E, A
12:5c90         LD      DE, 0x5cf7
12:5c91         RST     0x0030
12:5c92         LD      E, H
12:5c93         LD      A, (0xd606)
12:5c96         CALL    0x30fc
12:5c99         LD      (0xd606), A
12:5c9c         LD      A, (0xd7f5)
12:5c9f         <<CB>>  0x4f
12:5ca1         RET     Z
12:5ca2         LD      HL, 0x5cb6
12:5ca3         OR      (HL)
12:5ca4         LD      E, H
12:5ca5         CALL    0x34bc
12:5ca8         JR      NC, 0x5cb0
12:5ca9         LD      B, 0x21
12:5caa         LD      HL, 0xd72d
12:5cab         DEC     L
12:5cac         RST     0x0010
12:5cad         <<CB>>  0xe6
12:5caf         RET
MtMoonB2F_Script.asm_49d31:
12:5cb0         LD      HL, 0xd72d
12:5cb1         DEC     L
12:5cb2         RST     0x0010
12:5cb3         <<CB>>  0xa6
12:5cb5         RET
#endif

#if 0
MtMoonB2F_Script:
12:5c8a         CALL    EnableAutoTextBoxDrawing
12:5c8d         LD      HL, MtMoon3TrainerHeaders
12:5c8e         CP      A, B
12:5c8f         LD      E, A
12:5c90         LD      DE, MtMoonB2F_ScriptPointers
12:5c91         RST     0x0030
12:5c92         LD      E, H
12:5c93         LD      A, (wMtMoonB2FCurScript)
12:5c96         CALL    ExecuteCurMapScriptInTable
12:5c99         LD      (wMtMoonB2FCurScript), A
12:5c9c         LD      A, (wEventFlags[175])
12:5c9f         <<CB>>  0x4f
12:5ca1         RET     Z
12:5ca2         LD      HL, CoordsData_49d37
12:5ca3         OR      (HL)
12:5ca4         LD      E, H
12:5ca5         CALL    ArePlayerCoordsInArray
12:5ca8         JR      NC, MtMoonB2F_Script.asm_49d31
12:5ca9         LD      B, 0x21
12:5caa         LD      HL, wd72e
12:5cab         DEC     L
12:5cac         RST     0x0010
12:5cad         <<CB>>  0xe6
12:5caf         RET
MtMoonB2F_Script.asm_49d31:
12:5cb0         LD      HL, wd72e
12:5cb1         DEC     L
12:5cb2         RST     0x0010
12:5cb3         <<CB>>  0xa6
12:5cb5         RET
#endif

u8 *MtMoonB2F_Script(u8 p1)
{
	u8	 tmp	= EnableAutoTextBoxDrawing();
	BOOL bb		= tmp == p1;
	u8	 script = rst30(MtMoon3TrainerHeaders, MtMoonB2F_ScriptPointers, tmp, bb);

	wMtMoonB2FCurScript = ExecuteCurMapScriptInTable(wMtMoonB2FCurScript, script);

	u8 flags = wEventFlags[175];

	if ((flags & 1) == FALSE)
		return NULL;

	u8 *ret;
	if (ArePlayerCoordsInArray(&CoordsData_49d37, flags | CoordsData_49d37))
	{
		ret = rst10(wd72e - 1, 33);
		*ret &= 0b00010000;
		return ret;
	}
	else
	{
		ret = rst10(wd72e - 1, p1);
		*ret |= 0b11101111;
		return ret;
	}
}

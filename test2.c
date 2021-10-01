typedef unsigned char  u8;
typedef unsigned short u16;

typedef unsigned char BOOL;
#define FALSE (0)
#define TRUE  (1)

typedef union
{
	struct { u8 C; u8 B; };  u16 BC;
	struct { u8 E; u8 D; };  u16 DE;
	struct { u8 L; u8 H; };  u16 HL;
	struct { u8 F; u8 A; };  u16 AF;
	u8 *ptr;
} REGPAIR;

typedef u8	REG;
typedef u8 *REGPTR;

struct FLAGREG
{
	BOOL _UNUSED : 4;
	BOOL HF		 : 1;	// Half-Carry flag
	BOOL CF		 : 1;	// Carry flag
	BOOL NF		 : 1;	// Negative flag (subtract)
	BOOL ZF		 : 1;	// Zero flag
} F;


/**********************************
*
*	 @brief		Do thing
*
*	 @param[inout]	HL		REGPTR
*	 @param[in]		D		REG
*	 @param[in]		thing	BOOL: CF
*
*	 @return	REGPAIR BC
*
**********************************/
REGPAIR do_thing(REGPTR HL, REG D, BOOL thing)
{
	REGPAIR BC;
	if (thing)
	{
		BC.B = 0xfe;
		D -= 2;

		if (D != 0)
		{
			BC.BC = 0x7214;
			--D;
		}
	}

	(*HL) = D;
	return BC;
}

typedef unsigned char	u8;
typedef unsigned short	u16;

typedef unsigned char BOOL;
#define FALSE	(0)
#define TRUE	(1)

union REGISTER_TUPLE
{
	u16 pair;
	u8 single[2];
};

union REGISTER_TUPLE __reg_space [4];

#define AF	(	__reg_space[0].pair		)
#define BC	(	__reg_space[1].pair		)
#define DE	(	__reg_space[2].pair		)
#define HL	(	__reg_space[3].pair		)


#define F	(	__reg_space[0].single[0]	)
#define A	(	__reg_space[0].single[1]	)

#define C	(	__reg_space[1].single[0]	)
#define B	(	__reg_space[1].single[1]	)

#define E	(	__reg_space[2].single[0]	)
#define D	(	__reg_space[2].single[1]	)

#define L	(	__reg_space[3].single[0]	)
#define H	(	__reg_space[3].single[1]	)

__stack__;

struct PREDEF { u8 __wip; };

struct PREDEF TrainerEngagePredef;
u8 InternalClockTradeAnimPredef;
u8 PrizeRoomBagIsFullTextPtr;
u8 UsedCutPredef;
u8 wCurrentMenuItem;
u8 u8_ccd3;
u8 wSlotMachineRerollCounter;
u8 wWhichPokemon__;
u8 wNumSetBits;
u8 wWhichPrizeWindow;
u8 wWhichPrize;

u8 wPrize_arr_3[3];

u8 u8_d5a4;
u8 u8_ffa1;

u8 RST_0038(void *, u8);

/**********************************
*
*	 @brief     
*
*    @param[in] someAdr __reg_BC
*    @param[in] pop_DE	__stack_pop (2)
*
*    @return	u8		__reg_A
*
**********************************/
u8 HandlePrizeChoice(void *someAdr, u8 pop_DE[2])
{
	BOOL Zf, Cf;

	u8 *adr = someAdr;

	wWhichPrize = wCurrentMenuItem;
	wNumSetBits = wPrize_arr_3[pop_DE[0]];

	BOOL bCont;
	if (wWhichPrizeWindow == 2)
		bCont = GetItemName(--B);
	else
// HandlePrizeChoice.getMonName
		bCont = GetMonName(B);

// HandlePrizeChoice.givePrize
	HL = &TrainerEngagePredef;
	if (bCont == FALSE)
		return A;

	L = B;
	PrintText();
	YesNoChoice();
	A = wCurrentMenuItem;
	A &= A;

	if (A != 0)
	{
		HL = &UsedCutPredef;
		DE = pop_DE[1];
		L  = B;
		return PrintText();
	}

	D = (HL);
	LoadCoinsToSubtract();
	if (HasEnoughCoins())
	{
		HL		  = &InternalClockTradeAnimPredef;
		__stack__ = adr;
		L		  = B;
		return PrintText();
	}

	C = B;
	if (wWhichPrizeWindow == 0)
	{
		BC = (wNumSetBits << 8) | 0xfa;

		adr = &wSlotMachineRerollCounter;

		if (!GiveItem(0x01))
		{
			HL = &PrizeRoomBagIsFullTextPtr;
			Zf = (B >> 5) & 1;
			return PrintText();
		}

		 A = ~A;
	}
	else
	{
// HandlePrizeChoice.giveMon
		u8 giveMonTmp = wWhichPokemon__ = wNumSetBits;
		GetPrizeMonLevel();

		do
		{
			giveMonTmp = GivePokemon(A, giveMonTmp);

			if (u8_ccd3 == 0)
				Cf = WaitForTextScrollButtonPress();
		} while (Cf);

		if (!Cf)
			return giveMonTmp;
	}

// HandlePrizeChoice.subtractCoins
	LoadCoinsToSubtract();
	return RST_0038(&u8_ffa1, A & C);

	DE = &u8_d5a4;
	A &= H;
	__stack__ = DE;
	C		  = 0x02;
	*adr  = A;

	Predef(++adr, 0x0c);

	return PrintPrizePrice();
}

HandlePrizeChoice(){
/* 14:6826 */		LD	A, m_cc26
/* 14:6829 */		LD	m_d138, A
/* 14:682c */		LD	D, 0x00
/* 14:682d */		NOP
/* 14:682e */		LD	E, A
/* 14:682f */		LD	HL, 0xd13c
/* 14:6830 */		INC	A
/* 14:6831 */		POP	DE
/* 14:6832 */		ADD	HL, DE
/* 14:6833 */		LD	A, (HL)
/* 14:6834 */		LD	m_d11d, A
/* 14:6837 */		LD	A, m_d12e
/* 14:683a */		CP	0x02
/* 14:683c */		JR NZ, HandlePrizeChoice.getMonName
/* 14:683d */		DEC	B
/* 14:683e */		fn_2ec4();
/* 14:6841 */		JR HandlePrizeChoice.givePrize
HandlePrizeChoice.getMonName:
/* 14:6843 */		fn_2e93();
HandlePrizeChoice.givePrize:
/* 14:6846 */		LD	HL, 0x68c0
/* 14:6847 */		RET	NZ
/* 14:6848 */		LD	L, B
/* 14:6849 */		fn_3c36();
/* 14:684c */		fn_35ef();
/* 14:684f */		LD	A, m_cc26
/* 14:6852 */		AND	A
/* 14:6853 */		JR NZ, HandlePrizeChoice.printOhFineThen
/* 14:6854 */		LD	D, (HL)
/* 14:6855 */		CALL LoadCoinsToSubtract
/* 14:6858 */		fn_35ce();
/* 14:685b */		JR	C, 0x68a5
/* 14:685c */		LD	C, B
/* 14:685d */		LD	A, m_d12e
/* 14:6860 */		CP	0x02
/* 14:6862 */		JR NZ, HandlePrizeChoice.giveMon
/* 14:6863 */		LD	C, 0xfa
/* 14:6864 */		LD	A, m_d11d
/* 14:6867 */		LD	B, A
/* 14:6868 */		LD	A, 0x01
/* 14:6869 */		LD	BC, 0xcd4f
/* 14:686a */		LD	C, A
/* 14:686b */		fn_3e3f();
/* 14:686e */		JR	NC, 0x689f
/* 14:686f */		CPL
/* 14:6870 */		JR HandlePrizeChoice.subtractCoins
HandlePrizeChoice.giveMon:
/* 14:6872 */		LD	A, m_d11d
/* 14:6875 */		LD	m_cf90, A
/* 14:6878 */		PUSH	AF
/* 14:6879 */		CALL GetPrizeMonLevel
/* 14:687c */		LD	C, A
/* 14:687d */		POP	AF
/* 14:687e */		LD	B, A
/* 14:687f */		fn_3e59();
/* 14:6882 */		PUSH	AF
/* 14:6883 */		LD	A, m_ccd3
/* 14:6886 */		AND	A
/* 14:6887 */		if (Z)	fn_3852();
/* 14:6888 */		LD	D, D
/* 14:6889 */		JR	C, 0x687c
/* 14:688a */		POP	AF
/* 14:688b */		RET	NC
HandlePrizeChoice.subtractCoins:
/* 14:688c */		CALL LoadCoinsToSubtract
/* 14:688f */		LD	HL, 0xffa1
/* 14:6890 */		AND	C
/* 14:6891 */		RST	0x0038
/* 14:6892 */		LD	DE, 0xd5a4
/* 14:6893 */		AND	H
/* 14:6894 */		PUSH	DE
/* 14:6895 */		LD	C, 0x02
/* 14:6896 */		LD	(BC), A
/* 14:6897 */		LD	A, 0x0c
/* 14:6898 */		INC	C
/* 14:6899 */		fn_3eb4();
/* 14:689c */		JP PrintPrizePrice
HandlePrizeChoice.bagFull:
/* 14:689f */		LD	HL, 0x68cb
/* 14:68a0 */		<<CB>>	0x68
/* 14:68a2 */		JP	0x3c36
HandlePrizeChoice.notEnoughCoins:
/* 14:68a5 */		LD	HL, 0x68c5
/* 14:68a6 */		PUSH	BC
/* 14:68a7 */		LD	L, B
/* 14:68a8 */		JP	0x3c36
HandlePrizeChoice.printOhFineThen:
/* 14:68ab */		LD	HL, 0x68d1
/* 14:68ac */		POP	DE
/* 14:68ad */		LD	L, B
/* 14:68ae */		JP	0x3c36
}
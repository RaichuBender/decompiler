typedef unsigned char  u8;
typedef unsigned short u16;
typedef u8			   BOOL;
#define FALSE (0)
#define TRUE  (1)
BOOL ZF, NF, HF, CF;
u8	 A, F, B, C, D, E, H, L;
u16	 AF, BC, DE, HL, PC, SP;
u8	 STACK[0x10000];
fn_01ab()
{
	ZF = A == 0x11;
	CF = A < 0x11;
	HF = ((u8)A) < ((u8)0x11);
	NF = TRUE;
lbl_01ad:
	if (ZF != FALSE)
		goto lbl_01b2;
lbl_01ae:
	++BC;
lbl_01af:
	A ^= A;
	ZF = (A ^ A) == 0;
	CF = FALSE;
	HF = FALSE;
	NF = FALSE;
lbl_01b0:
	goto lbl_01b4;
lbl_01b2:
	A = 0x01;
lbl_01b3:
	BC = 0xfee0;
lbl_01b4:
	var_fffe = A;
lbl_01b6:
	fn_1d10();
lbl_01b9:
	A = var_ffb8;
lbl_01bb:
	STACK[--SP] = AF;
lbl_01bc:
	A = 0x03;
lbl_01bd:
	++BC;
lbl_01be:
	fn_3e7e();
lbl_01c1:
	fn_402d();
lbl_01c4:
	AF = STACK[SP++];
lbl_01c5:
	fn_3e7e();
	return;
lbl_01c8:
	A = var_ffb8;
lbl_01ca:
	STACK[--SP] = AF;
lbl_01cb:
	A = 0x03;
lbl_01cc:
	++BC;
lbl_01cd:
	fn_3e7e();
lbl_01d0:
	fn_4000();
lbl_01d3:
	AF = STACK[SP++];
lbl_01d4:
	fn_3e7e();
	return;
lbl_01d7:
	A = 0xff;
lbl_01d8:
	RST0x0038();
	return;
lbl_01d9:
	var_cd6b = A;
lbl_01dc:
	fn_0ecb();
lbl_01df:
	B = 0x03;
lbl_01e0:
	++BC;
lbl_01e1:
	HL = 0x407c;
lbl_01e2:
	A = H;
lbl_01e3:
	B = B;
lbl_01e4:
	fn_3e84();
lbl_01e7:
	HL = 0xd72b;
lbl_01e8:
	--HL;
lbl_01e9:
	RST0x0010();
	return;
lbl_01ea:
	CB(0x46);
lbl_01ec:
	if (ZF != FALSE)
		goto lbl_01f3;
lbl_01ed:
	++B;
	ZF = B == 1;
	CF = B == 0;
	HF = ((u8)B) == 0;
	NF = TRUE;
lbl_01ee:
	A = 0x03;
lbl_01ef:
	++BC;
lbl_01f0:
	var_d13b = A;
lbl_01f3:
	HL = 0xd72d;
lbl_01f4:
	++L;
	ZF = L == 1;
	CF = L == 0;
	HF = ((u8)L) == 0;
	NF = TRUE;
lbl_01f5:
	RST0x0010();
	return;
lbl_01f6:
	CB(0x6e);
lbl_01f8:
	CB(0xae);
lbl_01fa:
	if (ZF != FALSE)
		fn_0fd0();
lbl_01fb:
	if (CF == FALSE)
		return;
lbl_01fc:
	RRCA;
lbl_01fd:
	if (ZF == FALSE)
		fn_0750();
lbl_01fe:
	D = B;
lbl_01ff:
	RLCA;
lbl_0200:
	HL = 0xd731;
lbl_0201:
	SP = 0x7ed7;
lbl_0202:
	RST0x0010();
	return;
lbl_0203:
	A = (HL);
lbl_0204:
	A &= 0x18;
	ZF = (A & 0x18) == 0;
	CF = FALSE;
	HF = TRUE;
	NF = FALSE;
lbl_0206:
	if (ZF != FALSE)
		goto lbl_021d;
lbl_0207:
	++D;
	ZF = D == 1;
	CF = D == 0;
	HF = ((u8)D) == 0;
	NF = TRUE;
lbl_0208:
	B = 0x1c;
lbl_0209:
	--E;
	ZF = CF = E == -1;
	HF		= ((u8)E) == 0xf;
	NF		= FALSE;
lbl_020a:
	HL = 0x4567;
lbl_020b:
	H = A;
lbl_020c:
	B = L;
lbl_020d:
	fn_3e84();
lbl_0210:
	fn_231c();
lbl_0213:
	HL = 0xd731;
lbl_0214:
	SP = 0xcbd7;
lbl_0215:
	RST0x0010();
	return;
lbl_0216:
	CB(0x9e);
lbl_0218:
	HL = 0xd72d;
lbl_0219:
	++L;
	ZF = L == 1;
	CF = L == 0;
	HF = ((u8)L) == 0;
	NF = TRUE;
lbl_021a:
	RST0x0010();
	return;
lbl_021b:
	CB(0xa6);
lbl_021d:
	fn_342a();
lbl_0220:
	B = 0x03;
lbl_0221:
	++BC;
lbl_0222:
	HL = 0x40d2;
lbl_0223:
	if (CF == FALSE)
		fn_cd40();
	return;
lbl_0224:
	B = B;
lbl_0225:
	fn_3e84();
lbl_0228:
	HL = 0xd731;
lbl_0229:
	SP = 0xcbd7;
lbl_022a:
	RST0x0010();
	return;
lbl_022b:
	CB(0x66);
lbl_022d:
	CB(0xa6);
lbl_022f:
	HL = 0xd72c;
lbl_0230:
	--L;
	ZF = CF = L == -1;
	HF		= ((u8)L) == 0xf;
	NF		= FALSE;
lbl_0231:
	RST0x0010();
	return;
lbl_0232:
	CB(0xae);
lbl_0234:
	fn_231c();
lbl_0237:
	HL = 0xd125;
lbl_0238:
	++H;
	ZF = H == 1;
	CF = H == 0;
	HF = ((u8)H) == 0;
	NF = TRUE;
lbl_0239:
	DE = STACK[SP++];
lbl_023a:
	CB(0xee);
lbl_023c:
	CB(0xf6);
lbl_023e:
	A ^= A;
	ZF = (A ^ A) == 0;
	CF = FALSE;
	HF = FALSE;
	NF = FALSE;
lbl_023f:
	var_cd6b = A;
lbl_0242:
	fn_1e64();
lbl_0245:
	fn_1e64();
lbl_0248:
	fn_342a();
lbl_024b:
	fn_1e6f();
lbl_024e:
	fn_0fe1();
lbl_0251:
	A = var_cfc4;
lbl_0254:
	A &= A;
	ZF = (A & A) == 0;
	CF = FALSE;
	HF = TRUE;
	NF = FALSE;
lbl_0255:
	if (ZF == FALSE)
		goto lbl_03c3;
lbl_0256:
	fn_cd03();
	return;
lbl_0259:
	D = C;
lbl_025a:
	--C;
	ZF = CF = C == -1;
	HF		= ((u8)C) == 0xf;
	NF		= FALSE;
lbl_025b:
	B = 0x07;
lbl_025c:
	RLCA;
lbl_025d:
	HL = 0x6321;
lbl_025e:
	HL = 0xcd63;
lbl_025f:
	H = E;
lbl_0260:
	fn_3e84();
lbl_0263:
	A = var_da45;
lbl_0266:
	A &= A;
	ZF = (A & A) == 0;
	CF = FALSE;
	HF = TRUE;
	NF = FALSE;
lbl_0267:
	if (ZF == FALSE)
		fn_054a();
	return;
lbl_0268:
	C = D;
lbl_0269:
	++B;
	ZF = B == 1;
	CF = B == 0;
	HF = ((u8)B) == 0;
	NF = TRUE;
lbl_026a:
	HL = 0xd72c;
lbl_026b:
	--L;
	ZF = CF = L == -1;
	HF		= ((u8)L) == 0xf;
	NF		= FALSE;
lbl_026c:
	RST0x0010();
	return;
lbl_026d:
	CB(0x5e);
lbl_026f:
	CB(0x9e);
lbl_0271:
	if (ZF == FALSE)
		fn_054a();
	return;
lbl_0272:
	C = D;
lbl_0273:
	++B;
	ZF = B == 1;
	CF = B == 0;
	HF = ((u8)B) == 0;
	NF = TRUE;
lbl_0274:
	A = var_d731;
lbl_0277:
	A &= 0x18;
	ZF = (A & 0x18) == 0;
	CF = FALSE;
	HF = TRUE;
	NF = FALSE;
lbl_0279:
	if (ZF == FALSE)
		fn_0794();
	return;
lbl_027a:
	A -= H;
	ZF = A == H;
	CF = A < H;
	HF = ((u8)A) < ((u8)H);
	NF = TRUE;
lbl_027b:
	RLCA;
lbl_027c:
	A = var_d058;
lbl_027f:
	A &= A;
	ZF = (A & A) == 0;
	CF = FALSE;
	HF = TRUE;
	NF = FALSE;
lbl_0280:
	if (ZF == FALSE)
		goto lbl_040b;
lbl_0281:
	--BC;
lbl_0282:
	--B;
	ZF = CF = B == -1;
	HF		= ((u8)B) == 0xf;
	NF		= FALSE;
lbl_0283:
	A = var_d72f;
lbl_0286:
	CB(0x7f);
lbl_0288:
	if (ZF != FALSE)
		goto lbl_028e;
lbl_0289:
	--B;
	ZF = CF = B == -1;
	HF		= ((u8)B) == 0xf;
	NF		= FALSE;
lbl_028a:
	A = var_ffb4;
lbl_028c:
	goto lbl_0290;
lbl_028e:
	A = var_ffb3;
lbl_0290:
	CB(0x5f);
lbl_0292:
	if (ZF != FALSE)
		goto lbl_029a;
lbl_0293:
	B = 0xaf;
lbl_0294:
	A ^= A;
	ZF = (A ^ A) == 0;
	CF = FALSE;
	HF = FALSE;
	NF = FALSE;
lbl_0295:
	var_ff8c = A;
lbl_0297:
	goto lbl_02c5;
lbl_029a:
	CB(0x47);
lbl_029c:
	if (ZF != FALSE)
		goto lbl_0319;
lbl_029d:
	HL += DE;
	CF = (HL + DE) < HL;
	HF = ((u8)(HL + DE)) < ((u8)HL);
	NF = FALSE;
lbl_029e:
	++BC;
lbl_029f:
	A = var_d72f;
lbl_02a2:
	CB(0x57);
lbl_02a4:
	if (ZF == FALSE)
		goto lbl_02f8;
	// 00:02a5		0xf8	< ¡¡¡ invalid !!! >
lbl_02a6:
	(BC) = A;
lbl_02a7:
	fn_309d();
lbl_02aa:
	if (ZF == FALSE)
		goto lbl_02ee;
lbl_02ab:
	B = D;
lbl_02ac:
	fn_3ef9();
lbl_02af:
	A = var_ffeb;
lbl_02b1:
	A &= A;
	ZF = (A & A) == 0;
	CF = FALSE;
	HF = TRUE;
	NF = FALSE;
lbl_02b2:
	if (ZF != FALSE)
		goto lbl_0242;
lbl_02b3:
	B = D;
lbl_02b4:
	(BC) = A;
lbl_02b5:
	A ^= A;
	ZF = (A ^ A) == 0;
	CF = FALSE;
	HF = FALSE;
	NF = FALSE;
lbl_02b6:
	var_d435 = A;
lbl_02b9:
	fn_095e();
lbl_02bc:
	fn_0ffe();
lbl_02bf:
	A = var_ff8c;
lbl_02c1:
	A &= A;
	ZF = (A & A) == 0;
	CF = FALSE;
	HF = TRUE;
	NF = FALSE;
lbl_02c2:
	if (ZF != FALSE)
		goto lbl_0242;
lbl_02c3:
	B = D;
lbl_02c4:
	(BC) = A;
lbl_02c5:
	A = 0x35;
lbl_02c6:
	++(HL);
	ZF = (HL) == 1;
	CF = (HL) == 0;
	HF = ((u8)(HL)) == 0;
	NF = TRUE;
lbl_02c7:
	fn_3eb4();
lbl_02ca:
	fn_231c();
lbl_02cd:
	A = var_cd60;
lbl_02d0:
	CB(0x57);
lbl_02d2:
	if (ZF == FALSE)
		goto lbl_02ee;
lbl_02d3:
	A = (DE);
lbl_02d4:
	CB(0x47);
lbl_02d6:
	if (ZF == FALSE)
		goto lbl_02ee;
lbl_02d7:
	D = 0xfa;
lbl_02d8:
	A = var_c45c;
lbl_02db:
	var_cf0e = A;
lbl_02de:
	fn_2817();
lbl_02e1:
	A = var_cc47;
lbl_02e4:
	A &= A;
	ZF = (A & A) == 0;
	CF = FALSE;
	HF = TRUE;
	NF = FALSE;
lbl_02e5:
	if (ZF != FALSE)
		goto lbl_02ee;
lbl_02e6:
	RLCA;
lbl_02e7:
	A ^= A;
	ZF = (A ^ A) == 0;
	CF = FALSE;
	HF = FALSE;
	NF = FALSE;
lbl_02e8:
	var_cc47 = A;
lbl_02eb:
	goto lbl_01d7;
lbl_02ee:
	A = var_d058;
lbl_02f1:
	A &= A;
	ZF = (A & A) == 0;
	CF = FALSE;
	HF = TRUE;
	NF = FALSE;
lbl_02f2:
	if (ZF == FALSE)
		goto lbl_040b;
lbl_02f3:
	--BC;
lbl_02f4:
	--B;
	ZF = CF = B == -1;
	HF		= ((u8)B) == 0xf;
	NF		= FALSE;
lbl_02f5:
	goto lbl_0242;
lbl_02f8:
	fn_231c();
lbl_02fb:
	HL = 0xcd60;
lbl_02fc:
	H = B;
lbl_02fd:
	fn_96cb();
lbl_0300:
	A ^= A;
	ZF = (A ^ A) == 0;
	CF = FALSE;
	HF = FALSE;
	NF = FALSE;
lbl_0301:
	var_d434 = A;
lbl_0304:
	A = 0x01;
lbl_0305:
	BC = 0x4bea;
lbl_0306:
	var_cc4b = A;
lbl_0309:
	A = var_d527;
lbl_030c:
	A &= A;
	ZF = (A & A) == 0;
	CF = FALSE;
	HF = TRUE;
	NF = FALSE;
lbl_030d:
	if (ZF != FALSE)
		goto lbl_0316;
lbl_030e:
	RLCA;
lbl_030f:
	var_d528 = A;
lbl_0312:
	A ^= A;
	ZF = (A ^ A) == 0;
	CF = FALSE;
	HF = FALSE;
	NF = FALSE;
lbl_0313:
	var_d527 = A;
lbl_0316:
	goto lbl_0242;
lbl_0319:
	A = var_ffb4;
lbl_031b:
	CB(0x7f);
lbl_031d:
	if (ZF != FALSE)
		goto lbl_0328;
lbl_031e:
	HL += BC;
	CF = (HL + BC) < HL;
	HF = ((u8)(HL + BC)) < ((u8)HL);
	NF = FALSE;
lbl_031f:
	A = 0x01;
lbl_0320:
	BC = 0x03ea;
lbl_0321:
	var_c103 = A;
lbl_0324:
	A = 0x04;
lbl_0325:
	--B;
	ZF = CF = B == -1;
	HF		= ((u8)B) == 0xf;
	NF		= FALSE;
lbl_0326:
	goto lbl_034d;
lbl_0328:
	CB(0x77);
lbl_032a:
	if (ZF != FALSE)
		goto lbl_0335;
lbl_032b:
	HL += BC;
	CF = (HL + BC) < HL;
	HF = ((u8)(HL + BC)) < ((u8)HL);
	NF = FALSE;
lbl_032c:
	A = 0xff;
lbl_032d:
	RST0x0038();
	return;
lbl_032e:
	var_c103 = A;
lbl_0331:
	A = 0x08;
lbl_0332:
	var_1818 = SP;
lbl_0335:
	CB(0x6f);
lbl_0337:
	if (ZF != FALSE)
		goto lbl_0342;
lbl_0338:
	HL += BC;
	CF = (HL + BC) < HL;
	HF = ((u8)(HL + BC)) < ((u8)HL);
	NF = FALSE;
lbl_0339:
	A = 0xff;
lbl_033a:
	RST0x0038();
	return;
lbl_033b:
	var_c105 = A;
lbl_033e:
	A = 0x02;
lbl_033f:
	(BC) = A;
lbl_0340:
	goto lbl_034d;
lbl_0342:
	CB(0x67);
lbl_0344:
	if (ZF != FALSE)
		goto lbl_02f8;
lbl_0345:
	A |= D;
	ZF = (A | D) == 0;
	CF = FALSE;
	HF = FALSE;
	NF = FALSE;
lbl_0346:
	A = 0x01;
lbl_0347:
	BC = 0x05ea;
lbl_0348:
	var_c105 = A;
lbl_034b:
	A = 0x01;
lbl_034c:
	BC = 0x29ea;
lbl_034d:
	var_d529 = A;
lbl_0350:
	A = var_d72f;
lbl_0353:
	CB(0x7f);
lbl_0355:
	if (ZF == FALSE)
		goto lbl_0384;
lbl_0356:
	++L;
	ZF = L == 1;
	CF = L == 0;
	HF = ((u8)L) == 0;
	NF = TRUE;
lbl_0357:
	A = var_cc4b;
lbl_035a:
	A &= A;
	ZF = (A & A) == 0;
	CF = FALSE;
	HF = TRUE;
	NF = FALSE;
lbl_035b:
	if (ZF != FALSE)
		goto lbl_0384;
lbl_035c:
	DAA;
lbl_035d:
	A = var_d529;
lbl_0360:
	B = A;
lbl_0361:
	A = var_d528;
lbl_0364:
	ZF = A == B;
	CF = A < B;
	HF = ((u8)A) < ((u8)B);
	NF = TRUE;
lbl_0365:
	if (ZF != FALSE)
		goto lbl_0384;
lbl_0366:
	++E;
	ZF = E == 1;
	CF = E == 0;
	HF = ((u8)E) == 0;
	NF = TRUE;
lbl_0367:
	A = 0x08;
lbl_0368:
	var_34ea = SP;
lbl_036b:
	if (CF == FALSE)
		fn_6021();
lbl_036c:
	HL = 0xcd60;
lbl_036d:
	H = B;
lbl_036e:
	fn_d6cb();
lbl_0371:
	A ^= A;
	ZF = (A ^ A) == 0;
	CF = FALSE;
	HF = FALSE;
	NF = FALSE;
lbl_0372:
	var_cc4b = A;
lbl_0375:
	A = var_d529;
lbl_0378:
	var_d527 = A;
lbl_037b:
	fn_0480();
lbl_037e:
	if (C)
		goto lbl_0416;
lbl_037f:
	D = 0x04;
lbl_0380:
	--B;
	ZF = CF = B == -1;
	HF		= ((u8)B) == 0xf;
	NF		= FALSE;
lbl_0381:
	goto lbl_0242;
lbl_0384:
	A = var_d529;
lbl_0387:
	var_d527 = A;
lbl_038a:
	fn_231c();
lbl_038d:
	A = var_d6ff;
lbl_0390:
	ZF = A == 0x02;
	CF = A < 0x02;
	HF = ((u8)A) < ((u8)0x02);
	NF = TRUE;
lbl_0392:
	if (ZF != FALSE)
		goto lbl_03ae;
lbl_0393:
	A = (DE);
lbl_0394:
	fn_0a1c();
lbl_0397:
	if (CF == FALSE)
		goto lbl_03b4;
lbl_0398:
	--DE;
lbl_0399:
	STACK[--SP] = HL;
lbl_039a:
	HL = 0xd735;
lbl_039b:
	++(HL);
	ZF = (HL) == 1;
	CF = (HL) == 0;
	HF = ((u8)(HL)) == 0;
	NF = TRUE;
lbl_039c:
	RST0x0010();
	return;
lbl_039d:
	CB(0x56);
lbl_039f:
	HL = STACK[SP++];
lbl_03a0:
	if (ZF != FALSE)
		goto lbl_0242;
lbl_03a1:
	B = D;
lbl_03a2:
	(BC) = A;
lbl_03a3:
	STACK[--SP] = HL;
lbl_03a4:
	fn_071a();
lbl_03a7:
	HL = STACK[SP++];
lbl_03a8:
	if (C)
		fn_051a();
	return;
lbl_03a9:
	A = (DE);
lbl_03aa:
	++B;
	ZF = B == 1;
	CF = B == 0;
	HF = ((u8)B) == 0;
	NF = TRUE;
lbl_03ab:
	goto lbl_0242;
lbl_03ae:
	fn_0cca();
lbl_03b1:
	if (C)
		goto lbl_0242;
lbl_03b2:
	B = D;
lbl_03b3:
	(BC) = A;
lbl_03b4:
	A = 0x08;
lbl_03b5:
	var_c4ea = SP;
lbl_03b8:
	RST0x0008();
	return;
lbl_03b9:
	HL = 0x4c08;
lbl_03ba:
	var_064c = SP;
lbl_03bd:
	CCF;
lbl_03be:
	fn_3e84();
lbl_03c1:
	goto lbl_03c9;
lbl_03c3:
	fn_0ff0();
lbl_03c6:
	fn_231c();
lbl_03c9:
	HL = 0xcd60;
lbl_03ca:
	H = B;
lbl_03cb:
	fn_96cb();
lbl_03ce:
	A ^= A;
	ZF = (A ^ A) == 0;
	CF = FALSE;
	HF = FALSE;
	NF = FALSE;
lbl_03cf:
	var_d434 = A;
lbl_03d2:
	fn_049d();
lbl_03d5:
	fn_0b7f();
lbl_03d8:
	A = var_cfc4;
lbl_03db:
	A &= A;
	ZF = (A & A) == 0;
	CF = FALSE;
	HF = TRUE;
	NF = FALSE;
lbl_03dc:
	if (ZF == FALSE)
		fn_05db();
	return;
	// 00:03dd		0xdb	< ¡¡¡ invalid !!! >
lbl_03de:
	++B;
	ZF = B == 1;
	CF = B == 0;
	HF = ((u8)B) == 0;
	NF = TRUE;
lbl_03df:
	fn_0457();
lbl_03e2:
	A = var_d78f;
lbl_03e5:
	CB(0x7f);
lbl_03e7:
	if (ZF != FALSE)
		goto lbl_03f8;
lbl_03e8:
	RRCA;
lbl_03e9:
	B = 0x07;
lbl_03ea:
	RLCA;
lbl_03eb:
	HL = 0x6330;
lbl_03ec:
	if (CF == FALSE)
		goto lbl_0451;
lbl_03ed:
	H = E;
lbl_03ee:
	fn_3e84();
lbl_03f1:
	A = var_da45;
lbl_03f4:
	A &= A;
	ZF = (A & A) == 0;
	CF = FALSE;
	HF = TRUE;
	NF = FALSE;
lbl_03f5:
	if (ZF == FALSE)
		fn_054a();
	return;
lbl_03f6:
	C = D;
lbl_03f7:
	++B;
	ZF = B == 1;
	CF = B == 0;
	HF = ((u8)B) == 0;
	NF = TRUE;
lbl_03f8:
	A = var_d056;
lbl_03fb:
	A &= A;
	ZF = (A & A) == 0;
	CF = FALSE;
	HF = TRUE;
	NF = FALSE;
lbl_03fc:
	if (ZF == FALSE)
		fn_04bd();
	return;
lbl_03fd:
	ZF = A == L;
	CF = A < L;
	HF = ((u8)A) < ((u8)L);
	NF = TRUE;
lbl_03fe:
	--B;
	ZF = CF = B == -1;
	HF		= ((u8)B) == 0xf;
	NF		= FALSE;
lbl_03ff:
	A = 0x13;
lbl_0400:
	++DE;
lbl_0401:
	fn_3eb4();
lbl_0404:
	A = var_d12c;
lbl_0407:
	A &= A;
	ZF = (A & A) == 0;
	CF = FALSE;
	HF = TRUE;
	NF = FALSE;
lbl_0408:
	if (ZF == FALSE)
		fn_0762();
	return;
lbl_0409:
	H = D;
lbl_040a:
	RLCA;
lbl_040b:
	fn_0480();
lbl_040e:
	HL = 0xd735;
lbl_040f:
	++(HL);
	ZF = (HL) == 1;
	CF = (HL) == 0;
	HF = ((u8)(HL)) == 0;
	NF = TRUE;
lbl_0410:
	RST0x0010();
	return;
lbl_0411:
	CB(0x96);
lbl_0413:
	if (CF == FALSE)
		fn_04bd();
	return;
lbl_0414:
	ZF = A == L;
	CF = A < L;
	HF = ((u8)A) < ((u8)L);
	NF = TRUE;
lbl_0415:
	--B;
	ZF = CF = B == -1;
	HF		= ((u8)B) == 0xf;
	NF		= FALSE;
lbl_0416:
	HL = 0xd72c;
lbl_0417:
	--L;
	ZF = CF = L == -1;
	HF		= ((u8)L) == 0xf;
	NF		= FALSE;
lbl_0418:
	RST0x0010();
	return;
lbl_0419:
	CB(0xb6);
lbl_041b:
	HL = 0xd732;
lbl_041c:
	(HL -) = A;
lbl_041d:
	RST0x0010();
	return;
lbl_041e:
	CB(0x9e);
lbl_0420:
	HL = 0xd125;
lbl_0421:
	++H;
	ZF = H == 1;
	CF = H == 0;
	HF = ((u8)H) == 0;
	NF = TRUE;
lbl_0422:
	DE = STACK[SP++];
lbl_0423:
	CB(0xee);
lbl_0425:
	CB(0xf6);
lbl_0427:
	A ^= A;
	ZF = (A ^ A) == 0;
	CF = FALSE;
	HF = FALSE;
	NF = FALSE;
lbl_0428:
	var_ffb4 = A;
lbl_042a:
	A = var_d35d;
lbl_042d:
	ZF = A == 0xa6;
	CF = A < 0xa6;
	HF = ((u8)A) < ((u8)0xa6);
	NF = TRUE;
lbl_042f:
	if (ZF == FALSE)
		goto lbl_0436;
lbl_0430:
	++B;
	ZF = B == 1;
	CF = B == 0;
	HF = ((u8)B) == 0;
	NF = TRUE;
lbl_0431:
	HL = 0xd79a;
lbl_0432:
	if (CF)
		A -= (D + 1);
	else
		A -= D;
	ZF = A == D;
	CF = A < D;
	HF = ((u8)A) < ((u8)D);
	NF = TRUE;
lbl_0433:
	RST0x0010();
	return;
lbl_0434:
	CB(0xfe);
lbl_0436:
	HL = 0xd72d;
lbl_0437:
	++L;
	ZF = L == 1;
	CF = L == 0;
	HF = ((u8)L) == 0;
	NF = TRUE;
lbl_0438:
	RST0x0010();
	return;
lbl_0439:
	CB(0xee);
lbl_043b:
	A = var_d35d;
lbl_043e:
	ZF = A == 0x28;
	CF = A < 0x28;
	HF = ((u8)A) < ((u8)0x28);
	NF = TRUE;
lbl_0440:
	if (ZF != FALSE)
		goto lbl_044f;
lbl_0441:
	C = A;
lbl_0442:
	--B;
	ZF = CF = B == -1;
	HF		= ((u8)B) == 0xf;
	NF		= FALSE;
lbl_0443:
	HL = 0x4ae8;
	// 00:0444		0xe8	< ¡¡¡ invalid !!! >
lbl_0445:
	C = D;
lbl_0446:
	B = 0x0f;
lbl_0447:
	RRCA;
lbl_0448:
	fn_3e84();
lbl_044b:
	A = D;
lbl_044c:
	A &= A;
	ZF = (A & A) == 0;
	CF = FALSE;
	HF = TRUE;
	NF = FALSE;
lbl_044d:
	if (ZF != FALSE)
		fn_0475();
	return;
lbl_044e:
	H = 0x0e;
lbl_044f:
	C = 0x0a;
lbl_0450:
	A = (BC);
lbl_0451:
	fn_372f();
lbl_0454:
	goto lbl_01d7;
lbl_0457:
	A = var_d72f;
lbl_045a:
	CB(0x7f);
lbl_045c:
	if (ZF == FALSE)
		goto lbl_0474;
lbl_045d:
	D = 0x21;
lbl_045e:
	HL = 0xd13a;
lbl_045f:
	A = (HL -);
lbl_0460:
	DE = STACK[SP++];
lbl_0461:
	++(HL);
	ZF = (HL) == 1;
	CF = (HL) == 0;
	HF = ((u8)(HL)) == 0;
	NF = TRUE;
lbl_0462:
	A = var_d72b;
lbl_0465:
	CB(0x47);
lbl_0467:
	if (ZF != FALSE)
		goto lbl_0474;
lbl_0468:
	--BC;
lbl_0469:
	HL = 0xd13b;
lbl_046a:
	--SP;
lbl_046b:
	DE = STACK[SP++];
lbl_046c:
	++(HL);
	ZF = (HL) == 1;
	CF = (HL) == 0;
	HF = ((u8)(HL)) == 0;
	NF = TRUE;
lbl_046d:
	if (ZF == FALSE)
		goto lbl_0474;
lbl_046e:
	++B;
	ZF = B == 1;
	CF = B == 0;
	HF = ((u8)B) == 0;
	NF = TRUE;
lbl_046f:
	HL = 0xd72b;
lbl_0470:
	--HL;
lbl_0471:
	RST0x0010();
	return;
lbl_0472:
	CB(0x86);
lbl_0474:
	return;
}

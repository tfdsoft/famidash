#if !__VS_SYSTEM
/*	Looks like this:
 *	X->	0	3	6	9	12	15	18	21	24	27
 *	Y
 *	1										(5)
 *	4
 *	7
 *	11				(6)		(0)		(1)
 *	14
 *	17				(2)		(3)		(4)
 */

const uint8_t loNTAddrTableTitleScreen[]={
    LSB(NTADR_A(9, 11)),	// -1 = 6
    LSB(NTADR_A(15, 11)),	// 0
    LSB(NTADR_A(21, 11)),	// 1 
    LSB(NTADR_A(9, 17)),	// 2
    LSB(NTADR_A(15, 17)),	// 3
    LSB(NTADR_A(21, 17)),	// 4
    LSB(NTADR_A(27, 1)),	// 5
    LSB(NTADR_A(9, 11)),	// 6
    LSB(NTADR_A(15, 11))	// 7 = 0
};

const uint8_t hiNTAddrTableTitleScreen[]={
    MSB(NTADR_A(9, 11)),	// -1 = 6
    MSB(NTADR_A(15, 11)),	// 0
    MSB(NTADR_A(21, 11)),	// 1
    MSB(NTADR_A(9, 17)),	// 2
    MSB(NTADR_A(15, 17)),	// 3
    MSB(NTADR_A(21, 17)),	// 4
    MSB(NTADR_A(27, 1)),	// 5
    MSB(NTADR_A(9, 11)),	// 6
    MSB(NTADR_A(15, 11))	// 7 = 0
};

#define TITLE_BTN_LEVELMAIN		0
#define TITLE_BTN_LEVELCOMM		1
#define TITLE_BTN_SOUNDTEST		2
#define TITLE_BTN_SETTINGS		3
#define TITLE_BTN_INSTRUCTIONS	4
#define	TITLE_BTN_FUNSETTINGS	5
#define	TITLE_BTN_CUSTOMIZE		6

#define TITLE_BTN_MAX 6

#else
/*	Looks like this:
 *	X->	0	3	6	9	12	15	18	21	24	27
 *	Y
 *	1
 *	4
 *	7
 *	11				(2)		(0)		(1)
 *	14
 *	17
 */

const uint8_t loNTAddrTableTitleScreen[]={
    LSB(NTADR_A(9, 11)),	// -1 = 2
    LSB(NTADR_A(15, 11)),	// 0
    LSB(NTADR_A(21, 11)),	// 1 
    LSB(NTADR_A(9, 11)),	// 2
    LSB(NTADR_A(15, 11))	// 3 = 0
};

const uint8_t hiNTAddrTableTitleScreen[]={
    MSB(NTADR_A(9, 11)),	// -1 = 2
    MSB(NTADR_A(15, 11)),	// 0
    MSB(NTADR_A(21, 11)),	// 1
    MSB(NTADR_A(9, 11)),	// 2
    MSB(NTADR_A(15, 11))	// 3 = 0
};

#define TITLE_BTN_LEVELMAIN		0
#define TITLE_BTN_LEVELCOMM		1
#define	TITLE_BTN_CUSTOMIZE		2

#define TITLE_BTN_MAX 2

#endif

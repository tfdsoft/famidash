/*	Looks like this:
 *	X->	0	4	8	13	18	22
 *	Y
 *	0
 *	4
 *	8				(3)
 *	11
 *	14		(0)		(1)		(2)
 */

const uint8_t loNTAddrTableCustomizeScreen[] = {
	LSB(NTADR_A(13, 8)),		// -1 = 3
	LSB(NTADR_A(4, 14)),		// 0
	LSB(NTADR_A(13, 14)),		// 1
	LSB(NTADR_A(22, 14)),		// 2
	LSB(NTADR_A(13, 8)),		// 3
	LSB(NTADR_A(4, 14))			// 4 = 0
};

const uint8_t hiNTAddrTableCustomizeScreen[] = {
	MSB(NTADR_A(13, 8)),		// -1 = 3
	MSB(NTADR_A(4, 14)),		// 0
	MSB(NTADR_A(13, 14)),		// 1
	MSB(NTADR_A(22, 14)),		// 2
	MSB(NTADR_A(13, 8)),		// 3
	MSB(NTADR_A(4, 14))			// 4 = 0
};

#define CUSTOMIZE_BTN_COLOR1	0
#define CUSTOMIZE_BTN_COLOR2	1
#define CUSTOMIZE_BTN_COLOR3	2
#define CUSTOMIZE_BTN_ICON		3

#define CUSTOMIZE_BTN_MAX 3

// limit stuff to certain amounts
#define byte(x) (((x)&0xFF))
#define word(x) (((x)&0xFFFF))

// redefined from neslib

#define LSB(x)	((byte(x)))
#define MSB(x)	((byte(x>>8)))
#define SB3(x)	((byte(x##L>>16)))
#define SB4(x)	((byte(x##L>>24)))

#define LSW(x)	((word(x)))
#define MSW(x)	((word((x##L)>>16)))

// add byte with No Overflow Check
#define addNOC_b(a, b) byte(byte(a)+b)
// add word with No Overflow Check beyond the 16 bits
#define addNOC_w(a, b) word(word(a)+b)

// add to the low byte of a word, not overflowing into high
#define addloNOC(a, b) (addNOC_b(a, b))|(a & 0xFF00)

// subtract byte with No Overflow Check
#define subNOC_b(a, b) byte(byte(a)-b)
// subtract word with No Overflow Check beyond the 16 bits
#define subNOC_w(a, b) word(word(a)-b)

// subtract from the low byte of a word, not overflowing into high
#define subloNOC(a, b) (subNOC_b(a, b))|(a & 0xFF00)

/*
	Array macros by alexmush, 2024
	There's 4 types:
		load
		increment
		decrement
		store
	Increment/decrement also load the byte afterward for easy usage,
	If those loads are not used, they are automatically optimized out
	by cc65, so no need to worry
	
	For arrays of more than 1 byte, each function comes in a variation
	for both individual bytes and the whole number
*/

// Arrays of 1 byte

#define idx8_load(arr, idx) ( \
	__A__ = idx, \
	__asm__("tay"), \
	__asm__("ldx #0 \n lda %v, y", arr), \
	__A__)

#define idx8_dec(arr, idx) ( \
	__AX__ = idx << 8, \
	__asm__("dec %v,x", arr), \
	__asm__("lda %v,x", arr), \
	__A__)

#define idx8_inc(arr, idx) ( \
	__AX__ = idx << 8, \
	__asm__("inc %v,x", arr), \
	__asm__("lda %v,x", arr), \
	__A__)

#define idx8_store(arr, idx, val) ( \
	__A__ = idx, \
	__asm__("tay"), \
	__A__ = val, \
	__asm__("sta %v, y", arr))

// Arrays of 2 bytes
// 2 types of OPs:
// Normal (0 ≤ idx ≤ 255)
// No Overflow Check (NOC) (0 ≤ idx ≤ *127*)
// The latter type is way faster

#define idx16_load_lo(arr, idx) (*(((uint8_t * const)arr)+((idx<<1))))
#define idx16_load_hi(arr, idx) (*(((uint8_t * const)(arr+1))+((idx<<1))))

// So far, we've been able to get away without an idx16_load_NOC by
// using array[idx & 0x7F]

#define idx16_load_lo_NOC(arr, idx) ( \
	__A__ = idx<<1, \
	__asm__("tay"), \
	__asm__("lda %v, y", arr), \
	__A__)
#define idx16_load_hi_NOC(arr, idx) ( \
	__A__ = idx<<1, \
	__asm__("tay"), \
	__asm__("lda %v+1, y", arr), \
	__A__)

#define idx16_inc_NOC(arr, idx) ( \
	__A__ = idx << 1, \
	__AX__ <<= 8, \
	__asm__("inc %v,x", arr), \
	__asm__("bne %s", __LINE__), \
	__asm__("inc %v+1,x", arr), \
	__asm__("%s:", __LINE__), \
	__AX__ >>= 8, \
	__asm__("tay"), \
	__asm__("lda %v,y", arr), \
	__asm__("ldx %v+1,y", arr), \
	__AX__)
#define idx16_inc_lo_NOC(arr, idx) ( \
	__A__ = idx << 1, \
	__AX__ <<= 8, \
	__asm__("inc %v,x", arr), \
	__AX__ >>= 8, \
	__asm__("tay"), \
	__asm__("lda %v,y", arr), \
	__asm__("ldx %v+1,y", arr), \
	__AX__)
#define idx16_inc_hi_NOC(arr, idx) ( \
	__A__ = idx << 1, \
	__AX__ <<= 8, \
	__asm__("inc %v+1,x", arr), \
	__AX__ >>= 8, \
	__asm__("tay"), \
	__asm__("lda %v,y", arr), \
	__asm__("ldx %v+1,y", arr), \
	__AX__)

#define idx16_dec_NOC(arr, idx) ( \
	__A__ = idx << 1, \
	__AX__ <<= 8, \
	__asm__("lda %v+1,x", arr), \
	__asm__("bne %s", __LINE__), \
	__asm__("dec %v+1,x", arr), \
	__asm__("%s:", __LINE__), \
	__asm__("dec %v,x", arr), \
	__AX__ >>= 8, \
	__asm__("tay"), \
	__asm__("lda %v,y", arr), \
	__asm__("ldx %v+1,y", arr), \
	__AX__)
#define idx16_dec_lo_NOC(arr, idx) ( \
	__A__ = idx << 1, \
	__AX__ <<= 8, \
	__asm__("dec %v,x", arr), \
	__AX__ >>= 8, \
	__asm__("tay"), \
	__asm__("lda %v,y", arr), \
	__asm__("ldx %v+1,y", arr), \
	__AX__)
#define idx16_dec_hi_NOC(arr, idx) ( \
	__A__ = idx << 1, \
	__AX__ <<= 8, \
	__asm__("dec %v+1,x", arr), \
	__AX__ >>= 8, \
	__asm__("tay"), \
	__asm__("lda %v,y", arr), \
	__asm__("ldx %v+1,y", arr), \
	__AX__)

#define idx16_store_NOC(arr, idx, word) ( \
	__A__ = idx<<1, \
	__asm__("tay"), \
	__AX__ = word, \
	__asm__("sta %v,y", arr), \
	__AX__ >>= 8, \
	__asm__("sta %v+1, y", arr))

#define idx16_store_lo_NOC(arr, idx, byte) ( \
	__A__ = idx<<1, \
	__asm__("tay"), \
	__A__ = byte, \
	__asm__("sta %v,y", arr))

#define idx16_store_hi_NOC(arr, idx, byte) ( \
	__A__ = idx<<1, \
	__asm__("tay"), \
	__A__ = byte, \
	__asm__("sta %v+1,y", arr))
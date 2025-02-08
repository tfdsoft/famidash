
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
	/* The parts after this are auto-optimized out by cc65 if not needed */ \
	__AX__ >>= 8, \
	__asm__("tay"), \
	__asm__("lda %v,y", arr), \
	__asm__("ldx %v+1,y", arr), \
	__AX__)
#define idx16_inc_lo_NOC(arr, idx) ( \
	__A__ = idx << 1, \
	__AX__ <<= 8, \
	__asm__("inc %v,x", arr), \
	/* The parts after this are auto-optimized out by cc65 if not needed */ \
	__AX__ >>= 8, \
	__asm__("tay"), \
	__asm__("lda %v,y", arr), \
	__asm__("ldx %v+1,y", arr), \
	__AX__)
#define idx16_inc_hi_NOC(arr, idx) ( \
	__A__ = idx << 1, \
	__AX__ <<= 8, \
	__asm__("inc %v+1,x", arr), \
	/* The parts after this are auto-optimized out by cc65 if not needed */ \
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
	/* The parts after this are auto-optimized out by cc65 if not needed */ \
	__AX__ >>= 8, \
	__asm__("tay"), \
	__asm__("lda %v,y", arr), \
	__asm__("ldx %v+1,y", arr), \
	__AX__)
#define idx16_dec_lo_NOC(arr, idx) ( \
	__A__ = idx << 1, \
	__AX__ <<= 8, \
	__asm__("dec %v,x", arr), \
	/* The parts after this are auto-optimized out by cc65 if not needed */ \
	__AX__ >>= 8, \
	__asm__("tay"), \
	__asm__("lda %v,y", arr), \
	__asm__("ldx %v+1,y", arr), \
	__AX__)
#define idx16_dec_hi_NOC(arr, idx) ( \
	__A__ = idx << 1, \
	__AX__ <<= 8, \
	__asm__("dec %v+1,x", arr), \
	/* The parts after this are auto-optimized out by cc65 if not needed */ \
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


/*
	Lo-hi array macros by alexmush, 2024
	TODO: more comment here
*/

#define lohi_arr16_decl(name, size) \
uint8_t name##_lo[size]; \
uint8_t name##_hi[size]

#define	lohi_arr16_load(arr, idx) ( \
	__A__ = idx, \
	__asm__("tay"), \
	__asm__("lda %v, y \n ldx %v, y", arr##_lo, arr##_hi), \
	__AX__)

#define	lohi_arr16_store(arr, idx, value) ( \
	__A__ = idx, \
	__asm__("tay"), \
	__AX__ = value, \
	__asm__("sta %v, y \n txa \n sta %v, y", arr##_lo, arr##_hi), \
	__AX__)

#define lohi_arr24_decl(name, size) \
uint8_t name##_lo[size]; \
uint8_t name##_md[size]; \
uint8_t name##_hi[size];

#define	lohi_arr24_load(arr, idx) ( \
	__A__ = idx, \
	__asm__("tay"), \
	__asm__("lda %v, y \n ldx #0", arr##_hi), \
	__asm__("sta sreg \n stx sreg+1"), \
	__asm__("lda %v, y \n ldx %v, y", arr##_lo, arr##_md), \
	__EAX__)

#define	lohi_arr24_store(arr, idx, value) ( \
	__A__ = idx, \
	__asm__("tay"), \
	__EAX__ = value, \
	__asm__("sta %v, y \n txa \n sta %v, y", arr##_lo, arr##_md), \
	__asm__("lda sreg"), \
	__asm__("sta %v, y", arr##_hi) \
	)

#define lohi_arr32_decl(name, size) \
uint8_t name##_lo[size]; \
uint8_t name##_md[size]; \
uint8_t name##_hi[size]; \
uint8_t name##_ex[size]

#define	lohi_arr32_load(arr, idx) ( \
	__A__ = idx, \
	__asm__("tay"), \
	__asm__("lda %v, y \n ldx %v, y", arr##_hi, arr##_ex), \
	__asm__("sta sreg \n stx sreg+1"), \
	__asm__("lda %v, y \n ldx %v, y", arr##_lo, arr##_md), \
	__EAX__)

#define	lohi_arr32_load_loword(arr, idx) ( \
	__A__ = idx, \
	__asm__("tay"), \
	__asm__("lda %v, y \n ldx %v, y", arr##_lo, arr##_md), \
	__AX__)

#define	lohi_arr32_load_hiword(arr, idx) ( \
	__A__ = idx, \
	__asm__("tay"), \
	__asm__("lda %v, y \n ldx %v, y", arr##_hi, arr##_ex), \
	__AX__)

#define lohi_arr32_load_to(arr, idx, target) ( \
	__A__ = idx, \
	__asm__("tay"), \
	__asm__("lda %v, y \n ldx %v, y", arr##_lo, arr##_md), \
	low_word(target) = __AX__, \
	__asm__("lda %v, y \n ldx %v, y", arr##_hi, arr##_ex), \
	high_word(target) = __AX__)

#define	lohi_arr32_store(arr, idx, value) ( \
	__A__ = idx, \
	__asm__("tay"), \
	__EAX__ = value, \
	__asm__("sta %v, y \n txa \n sta %v, y", arr##_lo, arr##_md), \
	__asm__("lda sreg \n ldx sreg+1"), \
	__asm__("sta %v, y \n txa \n sta %v, y", arr##_hi, arr##_ex) \
	)

#define	lohi_arr32_store_split(arr, idx, value) ( \
	__A__ = idx, \
	__asm__("tay"), \
	__AX__ = LSW(value), \
	__asm__("sta %v, y \n txa \n sta %v, y", arr##_lo, arr##_md), \
	__AX__ = MSW(value), \
	__asm__("sta %v, y \n txa \n sta %v, y", arr##_hi, arr##_ex) \
	)

#define	lohi_arr32_store_from(arr, idx, value) ( \
	__A__ = idx, \
	__asm__("tay"), \
	__AX__ = low_word(value), \
	__asm__("sta %v, y \n txa \n sta %v, y", arr##_lo, arr##_md), \
	__AX__ = high_word(value), \
	__asm__("sta %v, y \n txa \n sta %v, y", arr##_hi, arr##_ex) \
	)


#define	lohi_arr32_store_loword(arr, idx, value) ( \
	__A__ = idx, \
	__asm__("tay"), \
	__AX__ = value, \
	__asm__("sta %v, y \n txa \n sta %v, y", arr##_lo, arr##_md), \
	)

#define	lohi_arr32_store_hiword(arr, idx, value) ( \
	__A__ = idx, \
	__asm__("tay"), \
	__AX__ = value, \
	__asm__("sta %v, y \n txa \n sta %v, y", arr##_hi, arr##_ex) \
	)

/*
	Faster indirect indexing because cc65 is *that* stupid
	by alexmush, 2025
*/

#define ind16_load_NOC(ptr, idx2) (\
	__AX__ = (uintptr_t)ptr, \
	__asm__("sta ptr1 \n stx ptr1+1"), \
	__A__ = idx2 << 1, \
	__asm__("tay \n iny"), \
	__asm__("lda (ptr1), y \n tax"), \
	__asm__("dey \n lda (ptr1), y"), \
	__AX__)


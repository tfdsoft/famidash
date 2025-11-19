#define fourth_byte(a) *((unsigned char*)&a+3)
#define third_byte(a) *((unsigned char*)&a+2)
#define high_byte(a) *((unsigned char*)&a+1)
#define low_byte(a) *((unsigned char*)&a)

#define POKE(addr, val)    (*(unsigned char*) (addr) = (val))
#define PEEK(addr)         (*(unsigned char*) (addr))

#define args888(a,b,c)    ((unsigned long)((a&0xff)+((b&0xff)<<8)+((c&0xff)<<16)))
#define args88(a,b)    ((a)|(b<<8))

#ifndef NULL
#define NULL ((void *) 0)
#endif


#define NT_ADR_A(x,y) (0x2000 + ((y<<5) + x))

#define set_2k_chr_0(b) set_chr_mode_0(b)
#define set_2k_chr_1(b) set_chr_mode_1(b)
#define set_1k_chr_0(b) set_chr_mode_2(b)
#define set_1k_chr_1(b) set_chr_mode_3(b)
#define set_1k_chr_2(b) set_chr_mode_4(b)
#define set_1k_chr_3(b) set_chr_mode_5(b)
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
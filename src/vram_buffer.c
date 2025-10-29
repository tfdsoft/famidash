

__attribute__((retain)) static uint8_t __zp VRAM_INDEX;
//__attribute__((retain)) static uint8_t 

// immediately after PAL_BUF
#define VRAM_BUF ((volatile char*)0x120) 





__attribute__((noinline)) void __post_vram_update(){
	VRAM_BUF[0] = 0xff;
	VRAM_INDEX = 1;
}

__attribute__((noinline)) void set_vram_buffer(void){
	set_vram_update((const char*)VRAM_BUF);
	__post_vram_update();
}



__attribute__((noinline)) void one_vram_buffer(char data, int ppu_addr){
	//__rc2 = high_byte(ppu_addr);
	/*__attribute__((leaf)) __asm__ volatile (
		"ldy VRAM_INDEX \n"

		"sta "STR(VRAM_BUF)"+2, y \n" // data
		"lda __rc2 \n"
		"sta "STR(VRAM_BUF)", y \n"   // address hi
		"txa \n"
		"sta "STR(VRAM_BUF)"+1, y \n" // adderess lo
		"iny \n"
		"iny \n"
		"iny \n"
		"lda #$ff \n" //=NT_UPD_EOF
		"sta "STR(VRAM_BUF)", y \n"
		"sty VRAM_INDEX \n"
		: 
		:"a"(data),"x"(low_byte(ppu_addr)),"rc2"(high_byte(ppu_addr))
		:"y","p","rc2"
	);*/

	VRAM_BUF[VRAM_INDEX+2] = data;
	VRAM_BUF[VRAM_INDEX] = high_byte(ppu_addr);
	VRAM_BUF[VRAM_INDEX+1] = low_byte(ppu_addr);
	VRAM_INDEX += 3;
	VRAM_BUF[VRAM_INDEX] = 0xff;
}





__attribute((noinline)) 
void multi_vram_buffer_horz(const uint8_t *data, char len, int ppu_addr){
	uint8_t tmp, run;
	//     A - len
	//     X - <ppu_address
	// __rc2 - <data
	// __rc3 - >data
	// __rc4 - >ppu_address
	VRAM_BUF[VRAM_INDEX+2] = tmp = len;

	// multi_vram_buffer_common:
	VRAM_BUF[VRAM_INDEX] = (0x40 | high_byte(ppu_addr));
	VRAM_BUF[VRAM_INDEX] = low_byte(ppu_addr);
	for (run=0; run < len; run++){
		VRAM_BUF[(VRAM_INDEX+run+3)] = data[run];
	}
	VRAM_INDEX = (len + 3);
	VRAM_BUF[VRAM_INDEX] = 0xff;
}
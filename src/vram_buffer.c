

__attribute__((retain)) static uint8_t __zp VRAM_INDEX;
//__attribute__((retain)) static uint8_t 

// immediately after PAL_BUF
#define VRAM_BUF ((volatile char*)0x140) 





__attribute__((noinline)) void __post_vram_update(){
	VRAM_BUF[0] = 0xff;
	VRAM_INDEX = 0;
}

__attribute__((noinline)) void set_vram_buffer(void){
	set_vram_update((const char*)VRAM_BUF);
	__post_vram_update();
}



__attribute__((noinline))
void one_vram_buffer(char data, int ppu_addr){
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
	VRAM_BUF[VRAM_INDEX] = high_byte(ppu_addr);
	VRAM_BUF[VRAM_INDEX+1] = low_byte(ppu_addr);
	VRAM_BUF[VRAM_INDEX+2] = data;
	VRAM_INDEX += 3;
	VRAM_BUF[VRAM_INDEX] = 0xff;
	
}

__attribute__((noinline))
void one_vram_buffer_repeat(
	char data, uint8_t len, int ppu_addr
){
	VRAM_BUF[VRAM_INDEX] = (0x40 | high_byte(ppu_addr));
	VRAM_BUF[VRAM_INDEX+1] = low_byte(ppu_addr);
	VRAM_BUF[VRAM_INDEX+2] = (len|0x80);
	VRAM_BUF[VRAM_INDEX+3] = data;
	VRAM_INDEX += 4;
	VRAM_BUF[VRAM_INDEX] = 0xff;
}



__attribute((noinline)) 
void multi_vram_buffer_horz(
	const char *data, uint8_t len, uint16_t ppu_addr
){
	uint8_t run;
	//     A - len
	//     X - <ppu_address
	// __rc2 - <data
	// __rc3 - >data
	// __rc4 - >ppu_address
	VRAM_BUF[VRAM_INDEX+2] = len;

	// multi_vram_buffer_common:
	VRAM_BUF[VRAM_INDEX] = (0x40 | high_byte(ppu_addr));
	VRAM_BUF[VRAM_INDEX+1] = low_byte(ppu_addr);
	for (run=0; run < len; run++){
		VRAM_BUF[(VRAM_INDEX+run+3)] = data[run];
	}
	VRAM_INDEX = (len + 3);
	VRAM_BUF[VRAM_INDEX] = 0xff;
	//VRAM_INDEX--;
}



__attribute((noinline)) 
void str_vram_buffer(
	const char *data, uint16_t ppu_addr
){
	uint8_t run = 0;

	// multi_vram_buffer_common:
	VRAM_BUF[VRAM_INDEX] = (0x40 | high_byte(ppu_addr));
	VRAM_BUF[VRAM_INDEX+1] = low_byte(ppu_addr);
	while (data[run] != 0){
		VRAM_BUF[(VRAM_INDEX+run+3)] = data[run];
		run++;
	}
	VRAM_BUF[VRAM_INDEX+2] = run;

	VRAM_INDEX += (run + 3);
	VRAM_BUF[VRAM_INDEX] = 0xff;
}







// ONLY CALL IN NMI!!!!!!
__attribute__((noinline)) void flush_vram_update2(){
	__attribute__((leaf)) __asm__ volatile(
			// save important stuff
			"tsx \n"
			"stx __rc3 \n" // save stack

			// calculate stack offset
			"ldx #$3f \n" // buffer is at $0140
			"txs \n"

		"1: \n" // flush_vram_update2:
			//"ldy #0 \n"

		"2: \n" // .LupdName:
			// First byte is upper PPU address or #$ff if done
			"pla \n" //"lda (NAME_UPD_ADR),y \n"
			//"iny \n"
			"cmp #$40 \n"	// bits 6 and 7 indicate sequential ops
			"bcc 4f \n"

			// save upper address byte for arithmetic
			"tax \n"
			"lda PPU_CTRL_VAR \n"
			"cpx #$80 \n"
			"bmi 5f \n"
			"cpx #$ff \n"
			"beq 10f \n"

		"3: \n"	// .LupdVertSeq:
			// Set control bit for vertical traversal
			"ora #$04 \n"
			"bne 6f \n" // always taken

		"4: \n" // .LupdSingle:
			"sta $2006 \n" // PPU_ADDR
			"pla \n" //"lda (NAME_UPD_ADR),y \n" // address lo
			//"iny \n" 
			"sta $2006 \n" // PPU_ADDR
			"pla \n" //"lda (NAME_UPD_ADR),y \n" // data
			//"iny \n" 
			"sta $2007 \n" // PPU_DATA 
			"clc \n"
			"bcc 2b \n" // always taken. Assumes index never wraps

		"5: \n"	// .LupdHorzSeq:
			// Clear control bit for vertical traversal
			"and #$fb \n" 

		"6: \n"	// .LupdNameSeq:
			// store new control value
			"sta $2000 \n" // PPU_CTRL 

			// mask out top 2 bits of upper address byte
			"txa \n" 
			"and #$3f \n" 

			"sta $2006 \n" // PPU_ADDR
			"pla \n" //"lda (NAME_UPD_ADR),y \n" // address lo
			//"iny \n" 
			"sta $2006 \n" // PPU_ADDR
			"pla \n" //"lda (NAME_UPD_ADR),y \n" 
			//"iny \n" 

			"bmi 8f \n"

			// store size in counter
			"tax \n"

		"7: \n"	//.LupdNameLoop:

			"pla \n"
			"sta $2007 \n" // PPU_DATA 
			"dex \n"
			"bne 7b \n"

			"lda PPU_CTRL_VAR \n"
			"sta $2000 \n"

			"jmp 2b \n"

		"8: \n" //.LupdRepeatedByte:
			"and #$7f \n"
			"tax \n"
			"pla \n"

		"9: \n" //.LupdRepeatedByteLoop:
			"sta $2007 \n"
			"dex \n"
			"bne 9b \n"

			"lda PPU_CTRL_VAR \n"
			"sta $2000 \n"
			
			"jmp 2b \n"

		"10: \n" // exit
			// restore stack
			"ldx __rc3 \n"
			"txs \n"

			"jmp __post_vram_update \n" 
	);
}
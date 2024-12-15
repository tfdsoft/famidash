; Huffmunch
; Brad Smith, 2019
; https://github.com/bbbradsmith/huffmunch

.importzp huffmunch_zpblock

; in: Y:X = stream index, hm_node = pointer to data block
; out: Y:X = output byte length of current stream, hm_node = total stream count in data
.export huffmunch_load

; out: reads 1 byte from stream, result in A (X,Y,flags clobbered)
.export huffmunch_read

hm_node   = <(huffmunch_zpblock + 0) ; pointer to current node of tree
hm_stream = <(huffmunch_zpblock + 2) ; pointer to bitstream
hm_tree   = <(huffmunch_zpblock + 4) ; pointer to tree base
hm_byte   = <(huffmunch_zpblock + 6) ; current byte of bitstream
hm_status = <(huffmunch_zpblock + 7) ; bits 0-2 = bits left in hm_byte, bit 7 = string with suffix
hm_length = <(huffmunch_zpblock + 8) ; bytes left in current string
.assert (huffmunch_zpblock + 9) <= 256, error, "huffmunch_zpblock requires 9 bytes on zero page"

; NOTE: only hm_node and hm_stream need to be on ZP
;       the rest could go elsewhere, but still recommended for ZP

.segment "CODE"

.proc huffmunch_load
	; hm_node = header
	; Y:X = index
	hm_temp = hm_byte ; temporary 16-bit value in hm_status:hm_byte
	; 1. hm_stream = (index * 2)
	sty hm_stream+1
	txa
	asl
	sta hm_stream+0
	rol hm_stream+1
	; 2. hm_temp = stream count * 2
	ldy #1
	lda (hm_node), Y
	pha
	sta hm_temp+1
	dey
	lda (hm_node), Y
	pha ; stack = stream count 0,1
	asl
	sta hm_temp+0
	rol hm_temp+1
	; 3. hm_node = header + 2
	lda hm_node+1
	pha
	lda hm_node+0
	pha ; stack = header 0, 1, stream count 0, 1
	clc
	adc #2
	sta hm_node+0
	bcc :+
		inc hm_node+1
	:
	; 4. hm_tree = header + 2 + (4 * stream count) [ready]
	lda hm_node+0
	clc
	adc hm_temp+0
	sta hm_tree+0
	lda hm_node+1
	adc hm_temp+1
	sta hm_tree+1
	lda hm_tree+0
	clc
	adc hm_temp+0
	sta hm_tree+0
	lda hm_tree+1
	adc hm_temp+1
	sta hm_tree+1
	; 5. hm_node = header + 2 + (index * 2)
	lda hm_node+0
	clc
	adc hm_stream+0
	sta hm_node+0
	lda hm_node+1
	adc hm_stream+1
	sta hm_node+1
	; 6. hm_stream = header + stream address [ready]
	; Y = 0
	pla
	clc
	adc (hm_node), Y
	sta hm_stream+0
	iny
	pla ; stack = stream count 0, 1
	adc (hm_node), Y
	sta hm_stream+1
	; 7. hm_node = header + 2 + (index * 2) + (2 * stream count)
	lda hm_node+0
	clc
	adc hm_temp+0
	sta hm_node+0
	lda hm_node+1
	adc hm_temp+1
	sta hm_node+1
	; 8. Y:X = stream length [ready]
	; Y = 1
	lda (hm_node), Y
	pha ; stack = stream length 1, stream count 0, 1
	dey
	lda (hm_node), Y
	tax
	pla ; stack = stream count 0, 1
	tay
	; 9. hm_node = total stream count [ready]
	pla
	sta hm_node+0
	pla
	sta hm_node+1
	; 10. initialize other data [ready]
	lda #0
	sta hm_byte ; hm_byte doesn't need initialization, just for consistency
	sta hm_status
	sta hm_length
	rts
.endproc

.proc huffmunch_read
	ldy #0
	lda hm_length ; string bytes pending
	beq string_empty
emit_byte:
	dec hm_length
	lda (hm_node), Y
	inc hm_node+0
	bne :+
		inc hm_node+1
	:
	rts
string_empty:
	; hm_length = 0
	; Y = 0
	bit hm_status
	bpl walk_tree
	; follow suffix
	lda (hm_node), Y
	clc
	adc hm_tree+0
	tax
	iny
	lda (hm_node), Y
	adc hm_tree+1
	sta hm_node+1
	stx hm_node+0
	dey ; ldy #0
	lda (hm_node), Y
	iny
	cmp #2
	beq leaf2
	tax
	lda hm_status
	and #$7F ; clear high bit, no more suffix
	sta hm_status
	cpx #1
	beq leaf1
	; 0 is the only other valid value
leaf0:
	; hm_length = 0
	; hm_status has high bit clear
	; (next read will walk_tree)
	; Y = 1
	lda (hm_node), Y
	rts
leaf1:
	; hm_status high bit is clear (no suffix)
leaf2:
	; hm_status high bit is set (suffix) if leaf2
	; Y = 1
	lda (hm_node), Y
	sta hm_length ; length must be > 0
	lda hm_node+0
	clc
	adc #2
	sta hm_node+0
	bcc :+
		inc hm_node+1
	:
	ldy #0
	jmp emit_byte
walk_tree:
	; hm_length = 0
	; Y = 0
	lda hm_tree+0 ; return to head of tree
	sta hm_node+0
	lda hm_tree+1
	sta hm_node+1
walk_node:
	; Y = 0
	lda (hm_node), Y
	cmp #3
	bcs node3
	iny
	cmp #2
	beq node2
	cmp #1
	beq node1
node0:
	; Y = 1
	jmp leaf0
node1 = leaf1
node2:
	; Y = 1
	lda hm_status
	ora #$80 ; set suffix flag
	sta hm_status
	jmp leaf2
node3:
	; Y = 0
	tax ; x = 3-255
	; read bit
	lda hm_status
	bne :+
		lda #8
		sta hm_status
		lda (hm_stream), Y
		sta hm_byte
		inc hm_stream+0
		bne :+
		inc hm_stream+1
	:
	dec hm_status
	asl hm_byte ; big-endian bit order
	bcs walk_right
walk_left:
	cpx #255
	beq walk_left_long
	inc hm_node+0
	bne :+
		inc hm_node+1
	:
	jmp walk_node
walk_left_long:
	lda hm_node+0
	clc
	adc #3
	sta hm_node+0
	bcc :+
		inc hm_node+1
	:
	jmp walk_node
walk_right:
	cpx #255
	beq walk_right_long
	txa
	clc
	adc hm_node+0
	sta hm_node+0
	bcc :+
		inc hm_node+1
	:
	jmp walk_node
walk_right_long:
	iny ; Y = 1
	lda (hm_node), Y
	clc
	adc hm_node+0
	tax
	iny ; Y = 2
	lda (hm_node), Y
	adc hm_node+1
	sta hm_node+1
	stx hm_node+0
	ldy #0
	jmp walk_node
.endproc

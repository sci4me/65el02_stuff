.include "65el02.inc"
.include "monitor.inc"

.macpack generic

.export putc
.proc putc
	pha ; TODO maybe remove me?
	phx
	phy

	; TODO replace $0300
	ldx $0300+Monitor::cursor_x
	ldy $0300+Monitor::cursor_y
	sty $0300+Monitor::row

	cmp #10
	beq :+
		sta $0300+Monitor::display,x
:	

	inx
; 	cpx #79
; 	bgt :+
; 	cmp #10
; 	bne @end
; :		ldx #0
; 		cpy #49
; 		blt @morerows
; 			blit_shift $0300, #0, #1, #0, #0, #MONITOR_W, #MONITOR_H-1
; 			phx
; 			pha
; 			lda #32
; 			ldx #79
; :			sta $0300+Monitor::display,x
; 			dex
; 			bne :-
; 			pla
; 			plx
; 			bra @end
; @morerows:	
; 			iny
; 			sty $0300+Monitor::cursor_y
; 			sty $0300+Monitor::row
; @end:
	stx $0300+Monitor::cursor_x

	ply
	plx
	pla
	rts
.endproc


.export puts
.proc puts
	pha
	phx

	ldx #0
	txi
	a8
:	nxa
	beq :+
	jsr putc
	bra :-
:	a16

	plx
	pla
	rts
.endproc
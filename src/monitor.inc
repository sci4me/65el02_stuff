.define MONITOR_W 80
.define MONITOR_H 50


.struct Monitor
	row			.byte

	cursor_x	.byte
	cursor_y	.byte
	cursor_mode	.byte

	kb_start	.byte
	kb_pos		.byte
	kb_key 		.byte

	blit_mode 	.byte
	blit_sx		.byte
	blit_sy 	.byte
	blit_ox		.byte
	blit_oy		.byte
	blit_w		.byte
	blit_h		.byte

	padding		.byte 2

	display		.byte $50
.endstruct

.enum CursorMode
	HIDDEN
	SOLID
	BLINK
.endenum

.enum BlitMode
	FILL	= 1
	INVERT	= 2
	SHIFT	= 3
.endenum


.macro blit_fill rb, c, ox, oy, w, h
	; assumes monitor is the selected bus ID
	lda c
	sta rb+Monitor::blit_sx
	stz rb+Monitor::blit_ox
    stz rb+Monitor::blit_oy
    lda w
    sta rb+Monitor::blit_w
    lda h
    sta rb+Monitor::blit_h
    lda BlitMode::FILL
    sta rb+Monitor::blit_mode
:   wai
    cmp rb+Monitor::blit_mode
    beq :-
.endmacro

.macro blit_invert rb, c, ox, oy, w, h
	; assumes monitor is the selected bus ID
	lda c
	sta rb+Monitor::blit_sx
	stz rb+Monitor::blit_ox
    stz rb+Monitor::blit_oy
    lda w
    sta rb+Monitor::blit_w
    lda h
    sta rb+Monitor::blit_h
    lda BlitMode::INVERT
    sta rb+Monitor::blit_mode
:   wai
    cmp rb+Monitor::blit_mode
    beq :-
.endmacro

.macro blit_shift rb, sx, sy, dx, dy, w, h
	; assumes monitor is the selected bus ID
	lda sx
	sta rb+Monitor::blit_sx
	lda sy
	sta rb+Monitor::blit_sy
	lda dx
	sta rb+Monitor::blit_ox
	lda dy
	sta rb+Monitor::blit_oy
	lda w
	sta rb+Monitor::blit_w
	lda h
	sta rb+Monitor::blit_h
	lda BlitMode::SHIFT
	sta rb+Monitor::blit_mode
:	wai
	cmp rb+Monitor::blit_mode
	beq :-
.endmacro
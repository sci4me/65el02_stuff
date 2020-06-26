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
	blit_dx		.byte
	blit_dy		.byte
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


.macro blit_fill rb, c, dx, dy, w, h
	; assumes monitor is the selected bus ID
	pha
	lda c
	sta rb+Monitor::blit_sx
	stz rb+Monitor::blit_dx
    stz rb+Monitor::blit_dy
    lda w
    sta rb+Monitor::blit_w
    lda h
    sta rb+Monitor::blit_h
    lda #BlitMode::FILL
    sta rb+Monitor::blit_mode
:   wai
    cmp rb+Monitor::blit_mode
    beq :-
    pla
.endmacro

.macro blit_invert rb, dx, dy, w, h
	; assumes monitor is the selected bus ID
	pha
	lda dx
	sta rb+Monitor::blit_dx
	lda dy
    sta rb+Monitor::blit_dy
    lda w
    sta rb+Monitor::blit_w
    lda h
    sta rb+Monitor::blit_h
    lda #BlitMode::INVERT
    sta rb+Monitor::blit_mode
:   wai
    cmp rb+Monitor::blit_mode
    beq :-
    pla
.endmacro

.macro blit_shift rb, sx, sy, dx, dy, w, h
	; assumes monitor is the selected bus ID
	pha
    stz rb+Monitor::blit_dx
    stz rb+Monitor::blit_dy
    stz rb+Monitor::blit_sx
    lda #1
    sta rb+Monitor::blit_sy
    lda #80
    sta rb+Monitor::blit_w
    lda #49
    sta rb+Monitor::blit_h
    lda #BlitMode::SHIFT
    sta rb+Monitor::blit_mode
:   wai
    cmp rb+Monitor::blit_mode
    beq :-
	pla
.endmacro
.define LOADED_CODE_START $0500

.define FRONT_PANEL_DISK_ID 	$00
.define FRONT_PANEL_DISPLAY_ID	$01


.macro a8
	sep #$20
	.a8
.endmacro

.macro a16
	rep #$20
	.a16
.endmacro

.macro i8
	sep #$10
	.i8
.endmacro

.macro i16
	rep #$10
	.i16
.endmacro


.macro mmu arg
	.byte $EF
	.byte arg
.endmacro

.enum MMUOp
	SET_ID 			= $00
	GET_ID 			= $80
	SET_MAP  		= $01
	GET_MAP  		= $81
	ENABLE_RB		= $02
	DISABLE_RB  	= $82
	SET_MAP_EXT 	= $03
	GET_MAP_EXT 	= $83
	ENABLE_RB_EXT 	= $04
	DISABLE_RB_EXT 	= $84
	SET_BRK			= $05
	GET_BRK 		= $85
	SET_POR			= $06
	GET_POR			= $86
.endenum
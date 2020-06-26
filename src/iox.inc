.struct IOX
	read		.word
	write		.word
.endstruct

.enum IOXColor
	WHITE 	= $0001
	ORANGE 	= $0002
	MAGENTA = $0004
	LBLUE	= $0008
	YELLOW 	= $0010
	LIME 	= $0020
	PINK 	= $0040
	GRAY    = $0080
	LGRAY   = $0100
	CYAN 	= $0200
	PURPLE 	= $0400
	BLUE 	= $0800
	BROWN 	= $1000
	GREEN 	= $2000
	RED 	= $4000
	BLACK 	= $8000
.endenum
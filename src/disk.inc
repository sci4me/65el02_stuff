.struct Disk
	buffer		.byte $80
	sector		.word
	command		.byte		
.endstruct

.enum DiskOP
	IDLE
	READ_NAME
	WRITE_NAME
	READ_SERIAL
	READ_SECTOR
	WRITE_SECTOR
	FAILURE = $FF
.endenum
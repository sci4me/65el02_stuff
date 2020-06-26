DISK=disk_68abff63ed2f2f86.img
RP_DIR="/home/sci4me/.local/share/multimc/instances/Nostalgia/.minecraft/saves/sci4me's world/redpower"

.PHONY: all

all:
	cl65 -t none --cpu 65816 --config rpc8e.cfg -o $(DISK) src/test.s src/monitor.s
	rm -f src/*.o
	padel02 $(DISK)
	mv $(DISK) $(RP_DIR)
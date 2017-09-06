#make -C
abc.img:boot loader.bin img
	cp boot/boot boot.bin
	cp loader/loader.bin loader.bin
	cp tools/img img
	./img -a abc.img boot.bin loader.bin
	rm boot.bin loader.bin img
boot:
	make -C boot
loader.bin:
	make -C loader
img:
	make -C tools

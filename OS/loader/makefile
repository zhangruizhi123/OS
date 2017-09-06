#loader用于加载根目录下的内核kernel.bin
CFLAGS=-fno-stack-protector
loader.bin: loader.o stdio.o main.o ffunicode.o ffsystem.o ff.o diskio.o string.o elf.o
	ld  -s -Ttext 0x8000 -o loader.bin loader.o string.o stdio.o elf.o  main.o ffunicode.o ffsystem.o ff.o diskio.o

loader.o: loader.asm
	nasm -f elf -o loader.o loader.asm
stdio.o: stdio.c loader.h
	gcc $(CFLAGS) -c stdio.c
main.o : main.c
	gcc $(CFLAGS) -c main.c
string.o: string.c
	gcc $(CFLAGS) -c string.c
elf.o: elf.c
	gcc $(CFLAGS) -c elf.c
#-------------------fs------
ffunicode.o: fs/ffunicode.c
	gcc $(CFLAGS) -c fs/ffunicode.c
ffsystem.o: fs/ffsystem.c
	gcc $(CFLAGS) -c fs/ffsystem.c
diskio.o: fs/diskio.c
	gcc $(CFLAGS) -c fs/diskio.c
ff.o: fs/ff.c
	gcc $(CFLAGS) -c fs/ff.c
clear:
	rm *.o

CFLAGS=-fno-stack-protector
kernel.bin: kernel.o stdio.o time.o main.o ffunicode.o ffsystem.o ff.o diskio.o string.o elf.o 8259a.o
	#当不使用会变语言启动时需要指定编译的入口函数,这里选择汇编函数启动
	#ld  -s -Ttext 0x1400000  -e main -o kernel.bin kernel.o string.o stdio.o time.o main.o ffunicode.o ffsystem.o ff.o diskio.o 
	ld  -s -Ttext 0x1400000 -o kernel.bin kernel.o string.o stdio.o time.o main.o ffunicode.o ffsystem.o ff.o diskio.o  8259a.o
kernel.o: kernel.asm
	nasm -f elf -o kernel.o kernel.asm
stdio.o: stdio.c kernel.h
	gcc $(CFLAGS) -c stdio.c
main.o : main.c
	gcc $(CFLAGS) -c main.c
time.o : time.c
	gcc $(CFLAGS) -c time.c
string.o: string.c
	gcc $(CFLAGS) -c string.c
elf.o: elf.c
	gcc $(CFLAGS) -c elf.c
8259a.o: 8259a.c
	gcc $(CFLAGS) -c 8259a.c
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

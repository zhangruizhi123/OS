nasm -f elf -o kernel.o kernel.asm
gcc -c main.c
ld -s -Ttext 0x8000 -o kernel.bin kernel.o main.o

rm *.o
objdump -d -s stdio.o
objdump -d -s kernel.bin
objdump -d -s bar.o
objdump -d -s kernel.o
objdump -d -s main.o



si DS

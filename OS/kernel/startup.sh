nasm -f elf -o kernel.o kernel.asm
gcc -c stdio.c
gcc -c main.c
ld -s -Ttext 0x8000 -o kernel.bin kernel.o stdio.o main.o 
rm *.o


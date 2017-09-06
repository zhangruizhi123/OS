#include "elf.h"
#include "fs/ff.h"
#include "stdio.h"
#include "string.h"
void loadK() {
	char*str=(char*)(SRAM_START_ADDR);
	str[0]='A';
	print_str("word\n", 5);
	FATFS FatFs;
	FIL fil; /* File object */
	FRESULT fr; /* FatFs return code */
	int br = 0;
	f_mount(&FatFs, "", 0);
	fr = f_open(&fil, "message.txt", FA_READ | FA_WRITE);
	fr = f_read(&fil, str, 512, &br);
	print_str(str, strlen(str));
	f_close(&fil);
}

/************  bar.c *****************/
#include "stdio.h"
#include "string.h"
#include "time.h"
#include "fs/ff.h"

//void iar();
//void time();
int main(int argc, char*argv[]) {

	int i = 0, j = 0, result = 0;
	char*str = (char*) (0x1000000);
	time_t tm;
	char dde[] = "This is my C OS.\n";
	setColor(0x0a);
	print_str(dde, strlen(dde));
	strcpy(str, dde);
	strcat(str, "zhang");
	strcat(str, "ruizhi\n");
	print_str(str, strlen(str));

	sprintf(str, "nihao %d haha name:%s sex:%C height:%X\n", 25, "zhangsan",
			'M', 175);
	print_str(str, strlen(str));
	while (1) {
		sys_read_time(&tm);
		sprintf(str, "%d-%d-%d  %d:%d:%d ", tm.year, tm.month, tm.day, tm.hour,
				tm.minute, tm.second);
		print_pstr(30,1,str, strlen(str));
	}

	while (1);
	return 0;

}
/*
 void iar()
 {
 //ICW1
 out_byte(0x20,0x11);
 out_byte(0xA0,0x11);
 //ICW2
 out_byte(0x21,0x20);
 out_byte(0xa1,0x28);
 //ICW3
 out_byte(0x21,0x04);
 out_byte(0xa1,0x02);
 //ICW4
 out_byte(0x21,0x01);
 out_byte(0xa1,0x01);
 //OCW1
 out_byte(0x21,0xFE);
 out_byte(0xa1,0xFF);
 }
 */
void file() {
	//FATFS FatFs;
	//FIL fil,fil2;        /* File object */
	//FRESULT fr;     /* FatFs return code */
	//int br=0;
	//----------------------------------
	/*f_mount(&FatFs, "", 0);
	 fr = f_open(&fil2, "message.txt", FA_READ|FA_WRITE);
	 fr = f_read(&fil2, str, 512, &br);
	 print_str(str,stlen(str));
	 f_close(&fil);
	 */
	//-----------------------------
}
/*
 void time()
 {


 time_t tm;
 while(1)
 {
 sys_read_time(&tm);
 print_number(20,16,tm.year);
 print_number(20,17,tm.month);
 print_number(20,18,tm.day);
 print_number(20,19,tm.hour);
 print_number(20,20,tm.minute);
 print_number(20,21,tm.second);
 print_number(20,22,tm.week);
 }
 }
 */

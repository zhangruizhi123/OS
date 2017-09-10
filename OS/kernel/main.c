/************  bar.c *****************/
#include "stdio.h"
#include "string.h"
#include "time.h"
#include "fs/ff.h"

#include "8259a.h"

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

	sprintf(str, "))) %d haha name:%s sex:%C height:%X\n", 25, "zhangsan",
			'M', 175);
	print_str(str, strlen(str));

	init_8259a();
	writeCloc();
	int c=0;
	//int b=1/c;
	while (1) {
		sys_read_time(&tm);
		sprintf(str, "%d-%d-%d  %d:%d:%d ", tm.year, tm.month, tm.day, tm.hour,
				tm.minute, tm.second);
		print_pstr(30,1,str, strlen(str));
	}
	while (1);
	return 0;

}



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

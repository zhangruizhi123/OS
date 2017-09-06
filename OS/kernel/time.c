#include "time.h"
#include "kernel.h"

void sys_read_time(time_t*tm)
{
	//port 0x70 0x71 0x74 0x75
	/*
	0x00 秒 	0x07 日
	0x01 闹钟秒 	0x08 月
	0x02 分 	0x09 年
	0x03 闹钟分 	0x0A 寄存器 A
	0x04 时 	0x0B 寄存器 B
	0x05 闹钟时 	0x0C 寄存器 C
	0x06 星期 	0x0D 寄存器 D
	*/
	int port1=0x70;//controller
	int port2=0x71;//data
	char year=0,yearH,month=0,day=0,hour=0,minute=0,second=0,week=0;
	out_byte(port1,0x09);
	year=in_byte(port2);
	out_byte(port1,0x32);
	yearH=in_byte(port2);
	tm->year=(year&0xf)+((year>>4)&0x0f)*10+(yearH&0xf)*100+((yearH>>4)&0x0f)*1000;

	out_byte(port1,0x08);
	month=in_byte(port2);
	tm->month=(month&0xf)+((month>>4)&0x0f)*10;
	
	out_byte(port1,0x07);
	day=in_byte(port2);
	tm->day=(day&0xf)+((day>>4)&0x0f)*10;

	out_byte(port1,0x04);
	hour=in_byte(port2);
	tm->hour=(hour&0xf)+((hour>>4)&0x0f)*10;

	out_byte(port1,0x02);
	minute=in_byte(port2);
	tm->minute=(minute&0xf)+((minute>>4)&0x0f)*10;

	out_byte(port1,0x00);
	second=in_byte(port2);
	tm->second=(second&0xf)+((second>>4)&0x0f)*10;

	out_byte(port1,0x06);
	week=in_byte(port2);
	tm->week=(week&0xf)+((week>>4)&0x0f)*10;

}

void sys_write_time(time_t tm)
{
	//port 0x70 0x71 0x74 0x75
	/*
	0x00 秒 	0x07 日
	0x01 闹钟秒 	0x08 月
	0x02 分 	0x09 年
	0x03 闹钟分 	0x0A 寄存器 A
	0x04 时 	0x0B 寄存器 B
	0x05 闹钟时 	0x0C 寄存器 C
	0x06 星期 	0x0D 寄存器 D
	*/
	int port1=0x70;//controller
	int port2=0x71;//data
	char year=((((tm.year%100)/10)<<4)&0xf0)|((tm.year%10)&0x0f);
	char yearH=(((tm.year/1000)<<4)&0xf0)|(((tm.year%1000)/100)&0x0f);
	char month=(((tm.month/10)<<4)&0xf0)|((tm.month%10)&0x0f);
	char day=(((tm.day/10)<<4)&0xf0)|((tm.day%10)&0x0f);
	char hour=(((tm.hour/10)<<4)&0xf0)|((tm.hour%10)&0x0f);
	char minute=(((tm.minute/10)<<4)&0xf0)|((tm.minute%10)&0x0f);
	char second=(((tm.second/10)<<4)&0xf0)|((tm.second%10)&0x0f);
	char week=(((tm.week/10)<<4)&0xf0)|((tm.week%10)&0x0f);;
	out_byte(port1,0x09);
	out_byte(port2,year);
	out_byte(port1,0x32);
	out_byte(port2,yearH);

	out_byte(port1,0x08);
	out_byte(port2,month);
	
	out_byte(port1,0x07);
	out_byte(port2,day);

	out_byte(port1,0x04);
	out_byte(port2,hour);

	out_byte(port1,0x02);
	out_byte(port2,minute);

	out_byte(port1,0x00);
	out_byte(port2,second);

	out_byte(port1,0x06);
	out_byte(port2,week);
}

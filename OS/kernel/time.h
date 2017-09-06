#ifndef _SYS_TIME_H_
#define _SYS_TIME_H_

typedef struct Time_t{
	short year;
	char month;
	char day;
	char hour;
	char minute;
	char second;
	char week;
}time_t;
//获取系统时间信息
void sys_read_time(time_t*tm);
//设在系统时间
void sys_write_time(time_t tm);

#endif


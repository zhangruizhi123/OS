#include "stdio.h"
#include "string.h"

//80列25行
#define DEFAULT_COLOR 0x0f
//字体的颜色
static int CONSOLE_COLOR;
//当前行
static int CONSOLE_ROW;
//当前列
static int CONSOLE_CLOMU;
//打印一个字符
void print_char(int x,int y,char code)
{
	int sum=y*160+x*2;
	if(CONSOLE_COLOR==0x00)
	{
		CONSOLE_COLOR=DEFAULT_COLOR;
	}
	myprint(sum,code,CONSOLE_COLOR);
}
//设置字体颜色
void setColor(int color)
{
	CONSOLE_COLOR=color;
}
//打印一个字符串
void print_str(char*str,int len)
{
	
	char*p=str;
	int i=0;
	if(CONSOLE_CLOMU>=80)
	{
		CONSOLE_ROW++;
		CONSOLE_CLOMU=0;
	}
	if(CONSOLE_ROW>=25)
	{
		CONSOLE_ROW=0;
	}
	for(i=0;i<len;i++)
	{
		int sum=i*2;
		if(*p=='\n')
		{
			CONSOLE_ROW++;
			CONSOLE_CLOMU=0;
		}else{
			print_char(CONSOLE_CLOMU,CONSOLE_ROW,*p);
			CONSOLE_CLOMU++;
		}
		p++;
	}
}


//从指定位置开始打印字符串
void print_pstr(int x,int y,char*str,int len)
{
	int i=0;
	for(i=0;i<len;i++)
	{
		if(x>=80)
		{
			x=0;y++;
		}
		if(y>=25)
		{
			y=0;
		}
		print_char(x,y,str[i]);
		x++;
	}
}
//打印一个数字
void print_number(int x,int y,int number)
{
	int i=0;
	char temp=0,result=0;
	print_char(x,y,'0');
	print_char(x+1,y,'X');
	for(i=0;i<8;i++)
	{
		temp=number&0x0f;
		number=number>>4;
		if(temp<10)
		{
			result=temp+'0';
		}
		else
		{
			result=temp+'A'-10;
		}
		print_char(x+9-i,y,result);
	}
}

void initgrap()
{
	out_byte(0x03ce,5);
	out_byte(0x03cf,2);
	out_byte(0x03ce,8);
	out_byte(0x03cf,0x0f0);
}
void point(int x,int y,int color)
{
	os_point(y*320+x,color);
}

/**
*写入扇区
* data 要写入的数据
* start 开始的扇区
* size  写入扇区的个数
**/
int writeDisk(char*data,int start,char size)
{
	//write command
	int command=0x30;
	int i=0,flag=0,sum=0,d=0,result=0;
	char byte=0;
	out_byte(0x1f2,size);
	for(i=0;i<4;i++)
	{
		if(i==3)
		{
			byte=(start&0xff)|0xe0;
		}else
		{
			byte=start&0xff;
		}
		out_byte(0x1f3+i,byte);
		start>>=8;
	}
	out_byte(0x1f7,command);
	flag=in_byte(0x1f7);
	while((flag&0x88)!=0x08)
	{
		flag=in_byte(0x1f7);
	}
	sum=size*256;
	for(i=0;i<sum;i++)
	{
		byte=data[i*2+1];
		d=0xff&byte;
		byte=data[i*2];
		d<<=8;
		d=d|byte;
		out_word(0x1f0,d);
	}
	result=in_byte(0x1f7);
	return 0;
}

/**
* 读取扇区
* data 要读取的数据
* start 开始的扇区
* size  读取扇区的个数
**/
int readDisk(char*data,int start,char size)
{
	//read command
	int command=0x20;
	int i=0,flag=0,sum=0,d=0,result=0;
	char byte=0;
	out_byte(0x1f2,size);
	for(i=0;i<4;i++)
	{
		if(i==3)
		{
			byte=(start&0xff)|0xe0;
		}else
		{
			byte=start&0xff;
		}
		out_byte(0x1f3+i,byte);
		start>>=8;
	}
	out_byte(0x1f7,command);
	flag=in_byte(0x1f7);
	while((flag&0x88)!=0x08)
	{
		flag=in_byte(0x1f7);
	}
	sum=size*256;
	for(i=0;i<sum;i++)
	{
		d=in_word(0x1f0);
		byte=d&0xff;
		data[i*2]=byte;
		d>>=8;
		byte=d&0xff;
		data[i*2+1]=byte;
	}
	result=in_byte(0x1f7);
	return 0;
}

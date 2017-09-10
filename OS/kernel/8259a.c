#include "8259a.h"
#include "kernel.h"
#include "stdio.h"
#include "string.h"
//初始化全局中断向量表
//其中的选择子是段在LDT中的偏移
IDT idtP[INT_SIZE]={0};
IDTR ldtR;
//对8259a芯片初始化
void init_8259a()
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

	 //设在中断 RTC寄存器B 阻止NMI
	 out_byte(0x70,0x8b);
	 //设在寄存器B，禁止周期性中断开放更新中断
	 out_byte(0x71,0x12);
	 //
	 out_byte(0x70,0x0c);
	 in_byte(0x71);
}
//对指定位子的idt进行写操作
void writeIDT(IDT*idt,int index,int low,int height)
{
	char str[100]={0};
	idt[index].low=low;
	idt[index].height=height;
	sprintf(str,"%x   %x   %x  \n",index,idt[index].low,idt[index].height);
	print_str(str, strlen(str));
}
//对时钟中断的IDT初始化
void writeCloc()
{
	int low=0x080000,height=0x08E00;
	int func=(int)_R8259AHandler;
	//int func=(int)hwint20;
	//取低16位
	low=low|(func&0x0ffff);
	//取高16位
	height=height|(func&0xffff0000);
	writeIDT(idtP,0x20,low,height);

	height=0x08E00;
	low=0x080000;
	func=(int)hwd00;
	height=height|(func&0xffff0000);
	low=low|(func&0x0ffff);
	writeIDT(idtP,0x00,low,height);
	writeIDT(idtP,0x01,low,height);
	writeIDT(idtP,0x02,low,height);

	writeLDTR(&ldtR,sizeof(idtP)-1,(int)&idtP);
	int*p=(int*)&ldtR;
	load_IDT(p);
}
//将int和short转换成LDTR寄存器
void writeLDTR(IDTR*r,short lim,int addr)
{
	r->limit[0]=(char)(lim&0x0ff);
	r->limit[1]=(char)((lim>>8)&0x0ff);
	r->address[0]=(char)(addr&0xff);
	r->address[1]=(char)((addr>>8)&0xff);
	r->address[2]=(char)((addr>>16)&0xff);
	r->address[3]=(char)((addr>>24)&0xff);
}
void hwint20()
{
	char str[]="000666666666666";
	print_str(str, strlen(str));
}

void spurious_irq(int type)
{
	char str[]="88888888";
	print_str(str, strlen(str));
}

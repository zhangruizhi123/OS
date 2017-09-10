#ifndef _SYS_8259a_H_
#define _SYS_8259a_H_
#define INT_SIZE 256
//对8259a的8个字节定义
typedef struct idt{
	int low;
	int height;
}IDT;

typedef struct idtR{
	char limit[2];
	char address[4];
}IDTR;
void init_8259a();
void spurious_irq(int type);

void writeIDT(IDT*idt,int index,int low,int height);
void writeLDTR(IDTR*r,short lim,int addr);
void writeCloc();
void hwint20();
#endif

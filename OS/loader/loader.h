#ifndef _SYS_KERNEL_H_
#define _SYS_KERNEL_H_

/*定义内存非配函数的初始地址,从5M开始一共15M*/
#define SRAM_START_ADDR 0x0500000
/*定义内存的大小*/
#define SRAM_SIZE	0x0‭F00000‬
/*定义内存的结束地址*/
#define SRAM_END_ADDR	0x1400000

/*对于代码的加载最好是放在20M以上的内存中*/

/**
*引用外部的函数
*对于一般的汇编函数可以在这里定义
*/


/*

80 X 25
 字体属性格式
7  6 5 4 3 2 1 0
BL R G B I R G B

闪烁 背景色 高亮 前景色
红底绿字: 01000010B
*/
//外部汇编函数，打印一个字符
extern myprint(int addr,int dd,int color);

/*read port byte*/
//读取一个端口，以字节为单位
extern int in_byte(int port);

/*read port word*/
//读取一个端口，以字为单位
extern int in_word(int port);

/*write port byte*/
//写入一个端口，以字节为单位
extern void out_byte(int port,int value);

/*write port word*/
//写入一个端口，以字为单位
extern void out_word(int port,int value);
//230X240 256色
extern void os_point(int index,int color);

extern int getStack();
#endif


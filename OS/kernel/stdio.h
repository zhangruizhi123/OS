#ifndef _SYS_STDIO_H_
#define _SYS_STDIO_H_
#include "kernel.h"

/**
*不定参数的原理，当获取到不定参数的前一个参数时,就可以用指针取出后面的参数
*
*/

typedef void* va_list;
#define _INTSIZEOF(n) ((sizeof(n)+sizeof(int)-1)&~(sizeof(int) - 1))
#define va_start(ap,v) ( ap = (va_list)&v + _INTSIZEOF(v) )
#define va_arg(ap,t) ( *(t *)((ap += _INTSIZEOF(t)) - _INTSIZEOF(t)) )
#define va_end(ap) ( ap = (va_list)0 )



/*

80 X 25
 字体属性格式
7  6 5 4 3 2 1 0
BL R G B I R G B

闪烁 背景色 高亮 前景色
红底绿字: 01000010B
*/
//设置字体颜色
void setColor(int color);

//打印一个字符
void print_char(int x,int y,char code);

//打印一个数字
void print_number(int x,int y,int number);

//打印一个字符串
void print_str(char*str,int len);
//从指定位置开始打印字符串
void print_pstr(int x,int y,char*str,int len);


void initgrap();
//320*200
void point(int x,int y,int color);
/**
* 写入扇区
* data 要写入的数据
* start 开始的扇区
* size  扇区的个数
*/
int writeDisk(char*data,int start,char size);
/*
* 读取扇区
* data 要读取的buffer
* start 开始的扇区
* size 扇区的个数
*/
int readDisk(char*data,int start,char size);


#endif

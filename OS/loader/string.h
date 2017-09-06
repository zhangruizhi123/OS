#ifndef _SYS_STRING_H_
#define _SYS_STRING_H_
//求字符的长度
int strlen(char*str);
//拷贝字符串
int strcpy(char*dst,char*src);
//拼接字符串
int strcat(char*dst,char*src);
//格式化字符从
int sprintf(char*dst,char*src,...);
//将字符串转换成int型数字
int atoi(char*num);
//将数字转换成字符串
char*itoa(int value,char*dstBuf,int radix);

#endif

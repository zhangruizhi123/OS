#include "string.h"
#include "stdio.h"

//求字符的长度
int strlen(char*str)
{
	int result=0;
	char*p=str;
	while(*p!=0)
	{
		p++;
		result++;
	}
	return result;
}
//拷贝字符串
int strcpy(char*dst,char*src)
{
	char*p=src;
	while(*p!=0)
	{
		*dst=*p;
		dst++;
		p++;
	}
	dst=0;
	return 0;
}
//拼接字符串
int strcat(char*dst,char*src)
{
	char*p1=dst,*p2=src;
	while(*p1++);
	while(*p2++)
	{
		*p1=*p2;
		p1++;
	}
	
	return 0;
}
//格式化字符从
int sprintf(char*dst,char*src,...)
{
	char *dstT=dst,*srcT=src,temp=0,temp2=0,temp3=0,*tempStr=0;
	char buff[10]={0};
	int i=0,j=0,k=0,len=strlen(srcT),index=0,result=0;
	va_list v_list;
	va_start(v_list,src);
	for(i=0;i<len;i++)
	{
		temp=srcT[i];
		if(temp=='%'&&(i+1)<len)
		{
			temp2=srcT[i+1];
			if(temp2=='c'|temp2=='C')
			{
				temp3=va_arg(v_list,char);
				*dstT=temp3;
				dstT++;
				i++;
			}
			else if(temp2=='d'|temp2=='D')
			{
				result=va_arg(v_list,int);
				itoa(result,buff,10);
				for(k=0;k<strlen(buff);k++)
				{
					*dstT=buff[k];
					dstT++;
				}
				i++;
			}
			else if(temp2=='x'|temp2=='X')
			{
				result=va_arg(v_list,int);
				itoa(result,buff,16);
				for(k=0;k<strlen(buff);k++)
				{
					*dstT=buff[k];
					dstT++;
				}
				i++;
			}
			else if(temp2=='s'|temp2=='S')
			{
				tempStr=va_arg(v_list,char*);
				for(k=0;k<strlen(tempStr);k++)
				{
					*dstT=tempStr[k];
					dstT++;
				}
				i++;
			}
			else
			{
				*dstT=temp;
				dstT++;
			}
		}
		else
		{
			*dstT=temp;
			dstT++;
		}
		
	}
	dstT[index]=0;
	va_end(v_list);
}
//将字符串转换成int型数字
int atoi(char*num)
{
	char*p=num;
	int result=0;
	while(*p)
	{
		result=result*10+((*p-'0')&0x0f);
		p++;
	}
	return result;
}
//将数字转换成字符串
char*itoa(int value,char*dstBuf,int radix)
{
	char temp=0;
	int index=0,i=0,j=0;
	if(value==0)
	{
		dstBuf[index]='0';
		index++;
	}
	while(value)
	{
		temp=(char)(value%radix);
		value=value/radix;
		if(temp>=0&&temp<=9)
		{
			dstBuf[index]='0'+temp;
		}
		else
		{
			dstBuf[index]='A'+(temp-10);
		}
		index++;
	}
	//字符串最后的结尾符号
	dstBuf[index]=0;
	//对数据的顺序进行调整
	for(i=0;i<index;i++)
	{
		j=index-i-1;
		if(i<j)
		{
			temp=dstBuf[i];
			dstBuf[i]=dstBuf[j];
			dstBuf[j]=temp;
		}
		else
		{
			break;
		}
	}
	return dstBuf;
}

#include "elf.h"
#include "fs/ff.h"
#include "stdio.h"
#include "string.h"
typedef int (*MC)(int argc,char*argv[]);
typedef struct program_h_t {
	int h1;
	int h2;
	int h3;
	int h4;
	int h5;
	int h6;
	int h7;
	int h8;
} program_h_t;
char param[][40]={"name:qianzhi","version:1.0.0","date:2017/9/6","author:zhangruizhi"};
void loadK() {
	int result=0;
	char*str=(char*)(SRAM_START_ADDR);
	char no[]="Kernel.bin cannot be found in the root directory.\n";
	MC mc;
	FATFS FatFs;
	char*tempR;//设置加载到内存中的零时变量
	FIL fil; /* File object */
	FRESULT fr; /* FatFs return code */
	int br = 0;
	f_mount(&FatFs, "", 0);
	fr = f_open(&fil, "kernel.bin", FA_READ | FA_WRITE);
	if(fr==FR_OK)
	{
		char type[4];
		fr = f_read(&fil, type, 4, &br);
		if(fr!=FR_OK||br!=4){
			print_str("not read file.\n",15);
		}
		else
		{
			if(!(type[1]=='E'&&type[2]=='L'&&type[3]=='F'))
			{
				print_str("not find ELF file.\n",19);
			}
			else
			{
				int p_entry;
				f_lseek(&fil,0x18);
				f_read(&fil,&p_entry,sizeof(int), &br);
				mc=(MC)(p_entry);

				int p_start=0;
				f_lseek(&fil,0x1c);
				f_read(&fil,&p_start,sizeof(int), &br);

				short p_size=0;
				f_lseek(&fil,0x2a);
				f_read(&fil,&p_size,sizeof(short), &br);

				short p_number=0;
				f_lseek(&fil,0x2c);
				f_read(&fil,&p_number,sizeof(short), &br);

				int rel_addr=0;//获取每个节的首地址
				int i=0;
				program_h_t p_h;
				for(i=0;i<p_number;i++)
				{
					rel_addr=p_start+i*p_size;
					f_lseek(&fil,rel_addr);
					f_read(&fil,&p_h,sizeof(program_h_t), &br);
					if(p_h.h5==0)
					{
						continue;
					}

					f_lseek(&fil,p_h.h2);
					f_read(&fil,str,p_h.h5, &br);
					if(br==p_h.h5)
					{
						tempR=(char*)(p_h.h3);
						loadCode(tempR,str,p_h.h5);
					}
				}


			}
		}
		f_close(&fil);
	}
	else
	{
		setColor(0x0c);
		print_str(no, strlen(no));
	}
	mc(4,param);
}

void loadCode(char*code,char*content,int size)
{
	char*cd=code,*ct=content;
	int i=0;
	for(i=0;i<size;i++)
	{
		cd[i]=content[i];
	}
}

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>


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

void createImg();
//读取ELF文件 
void readELF(char*files, char*img);
//将启动文件写入镜像文件 
void readBOOT(char*files, char*img);

int main(int argc, char *argv[]) {

	//第一个参数是应用的名称
	if(argc==1){
		//默认情况下输出help帮助信息
		printf("说明：该应用用于创建 .img 软盘文件,和将boot,kernel写入 .img文件指定的位子.\n");
		printf("img -c name\t用于创建一个名称为name的镜像文件.\n");
		printf("img -b img boot\t将boot写入img中.\n");
		printf("img -k img kernel\t将kernel写入img中.\n");
		printf("img -a img boot kernel\t将boot和kernel同时写入img中.\n");
	}else if(argc==3){
		if(strcmp(argv[1],"-c")==0){
			//创建应用
			createImg(argv[2]);
		}else{
			printf("请检查参数是否正确.\n");
		}
	}else if(argc==4){
		if(strcmp(argv[1],"-b")==0){
			readBOOT(argv[3], argv[2]);
		}else if(strcmp(argv[1],"-k")==0){
			readELF(argv[3], argv[2]);
		}else{
			printf("请检查参数是否正确.\n");
		}
	}else if(argc==5){
		if(strcmp(argv[1],"-a")==0){
			createImg(argv[2]);
			readELF(argv[4], argv[2]);
			readBOOT(argv[3],argv[2]);
		}else{
			printf("请检查参数是否正确.\n");
		}
	}
	//createImg("abc.img");
	//readELF("kernel.bin", "abc.img");
	//readBOOT("boot", "abc.img");
	return 0;
}

void readBOOT(char*files, char*imgs) {
	int bootfd = open(files,O_RDWR);
	int imgfd = open(imgs,O_RDWR);
	size_t size;
	// 直接读取512个字节然后写入
	char buff[512];
	if(bootfd==-1){
		printf("打开boot文件失败\n");
		return;
	}
	if(imgfd==-1){
		printf("打开img文件失败\n");
		return;
	}
	size=read(bootfd,buff,512);
	if(size!=512){
		printf("读取boot文件失败\n");
		return;
	}
	size=write(imgfd,buff,512);
	if(size!=512){
		printf("写入img文件失败\n");
		return ;
	}

	printf("写入boot 成功\n");
	close(bootfd);
	close(imgfd);
}
void readELF(char*files, char*img) {
	int kernelfd = open(files,O_RDWR);
	int imgfd = open(img,O_RDWR);
	char type[4];
	if(kernelfd==-1){
		printf("打开kernel文件失败\n");
		return;
	}
	if(imgfd==-1){
		printf("打开img文件失败\n");
		return;
	}
	size_t size;
	size=read(kernelfd,type,4);
	if(size!=4)
	{
		printf("kernel读取失败\n");
	}
	if(!(type[1]=='E'&&type[2]=='L'&&type[3]=='F'))
	{
		printf("该文件不是ELF文件!\n");
		return;
	}
	int p_entry;
	lseek(kernelfd,0x18,SEEK_SET);
	read(kernelfd,&p_entry,sizeof(int));
	printf("程序入口地址：0x%x\n",p_entry);

	int p_start=0;
	lseek(kernelfd,0x1c,SEEK_SET);
	read(kernelfd,&p_start,sizeof(int));
	printf("节的开始地址：0x%x\n",p_start);

	//获取节的大小
	short p_size=0;
	lseek(kernelfd,0x2a,SEEK_SET);
	read(kernelfd,&p_size,sizeof(short));
	printf("节的大小：0x%x\n",p_size);

	//获取节的个数
	short p_number=0;
	lseek(kernelfd,0x2c,SEEK_SET);
	read(kernelfd,&p_number,sizeof(short));
	printf("节的个数：0x%x\n",p_number);
	printf("----------------------------------------\n");
	//循环读取每个节的信息
	int rel_addr=0;//获取每个节的首地址
	int i=0;
	//char*content;//文件中节的大小
	program_h_t p_h;
	for(i=0;i<p_number;i++)
	{
		rel_addr=p_start+i*p_size;
		printf("节%d的开始地址:0x%x\n",i+1,rel_addr);
		lseek(kernelfd,rel_addr,SEEK_SET);
		read(kernelfd,&p_h,sizeof(program_h_t));
		printf("在文件中偏移:0x%x\n",p_h.h2);
		printf("在内存中偏移:0x%x\n",p_h.h3);
		printf("在文件中长度:0x%x\n",p_h.h5);
		printf("在内存中长度:0x%x\n",p_h.h6);

		if(p_h.h5==0)
		{
			printf("无需读写.\n");
			printf("      ----------------\n");
			continue;
		}
		//创建文件中的长度大小
		char*content=(char*)malloc(p_h.h5);
		//设置文件中的偏移
		lseek(kernelfd,p_h.h2,SEEK_SET);
		//读取文件
		size=read(kernelfd,content,p_h.h5);
		if(size==p_h.h6)
		{
			lseek(imgfd,p_h.h3,SEEK_SET);
			size=write(imgfd,content,p_h.h5);
			if(!(size== p_h.h5))
			{
				printf("写入IMG文件失败!\n");
			}
			else
			{
				printf("写入IMG文件成功!\n");
			}
		}
		else
		{
			printf("读取文件失败%d，%d，%d\n",size,p_h.h5,size);
		}
		printf("      ----------------\n");

	}
	close(imgfd);
	close(kernelfd);
}
//创建一个镜像文件 
void createImg(char*name) {
	mode_t f_attrib;
	f_attrib = S_IRUSR | S_IWUSR | S_IRGRP | S_IWGRP | S_IROTH;
	int fd = open(name, O_CREAT | O_RDWR,f_attrib);
	size_t size;
	if (fd == -1) {
		printf("打开文件失败\n");
		return;
	}
	char buff[1024 * 1024] = { 0 };
	size = write(fd, buff, 1024 * 1024);
	if (size != 1024 * 1024) {
		printf("创建文件失败\n");
	} else {
		printf("创建文件 %s 成功\n", name);
	}
	close(fd);

}


 ;代码清单11-1
;文件名：c11_mbr.asm
 ;文件说明：硬盘主引导扇区代码 
;创建日期：2011-5-16 19:54
         ;设置堆栈段和栈指针 
	 call read
	 ;call model
         mov ax,cs      
         mov ss,ax
         mov sp,0x7c00
      
         ;计算GDT所在的逻辑段地址 
         mov ax,[cs:gdt_base+0x7c00]        ;低16位 
         mov dx,[cs:gdt_base+0x7c00+0x02]   ;高16位 
         mov bx,16        
         div bx            
         mov ds,ax                          ;令DS指向该段以进行操作
         mov bx,dx                          ;段内起始偏移地址 
      
         ;创建0#描述符，它是空描述符，这是处理器的要求
         mov dword [bx+0x00],0x00
         mov dword [bx+0x04],0x00  

         ;创建#1描述符，保护模式下的代码段描述符(4G)
         mov dword [bx+0x08],0x0000ffff    
         mov dword [bx+0x0c],0x00CF9E00   

         ;创建#2描述符，保护模式下的数据段描述符（文本模式下的显示缓冲区） 
         mov dword [bx+0x10],0x8000ffff     
         mov dword [bx+0x14],0x0040920b     

         ;创建#3描述符，保护模式下的堆栈段描述符
         mov dword [bx+0x18],0x7c007c00
         mov dword [bx+0x1c],0x00409600

	 ;创建#4描述符，保护模式下的数据段描述符（数据段 0-4G） 
         mov dword [bx+0x20],0x0000ffff     
         mov dword [bx+0x24],0x00CF9200  
	;创建#5描述符，保护模式下的数据段描述符（文本模式下的显示缓冲区） 
         mov dword [bx+0x28],0x0000ffff     
         mov dword [bx+0x2c],0x004f920a  

         ;初始化描述符表寄存器GDTR
         mov word [cs: gdt_size+0x7c00],47  ;描述符表的界限（总字节数减一）   
                                             
         lgdt [cs: gdt_size+0x7c00]
      
         in al,0x92                         ;南桥芯片内的端口 
         or al,0000_0010B
         out 0x92,al                        ;打开A20

         cli                                ;保护模式下中断机制尚未建立，应 
                                            ;禁止中断 
         mov eax,cr0
         or eax,1
         mov cr0,eax                        ;设置PE位
      
         ;以下进入保护模式... ...
         jmp dword 0x0008:0x7c00+flush             ;16位的描述符选择子：32位偏移
	[bits 16]                           ;清流水线并串行化处理器 
	read:
	push bx
	push cx
	push dx
	push es
	mov ax,0 
	mov es, ax
	mov bx, 0x8000   ; 1. es:bx 指向接受从扇区读入数据的内存区
	mov al, 60            ; 2. (al)=需要读取扇区的数         
	mov dl, 0            ; 3. (dl)=驱动器号 软驱从0开始， 0:软驱A，1:软驱B
		             ;    硬盘从80h开始，80h：C盘，81h：D盘
	mov dh, 1            ; 4. (dh)=磁头号(对于软盘即面号，一个面对应一个磁头)
	mov ch, 1           ; 5. (ch)=zhumian
	mov cl, 11           ; 6. (cl)=扇区号
	     
	mov ah, 2            ; 7. (ah)=int 13h的功能号(2表示读扇区)
	int 13h
	pop es
	pop dx
	pop cx
	pop bx
	ret
         [bits 32] 

    flush:
	 ;数据段，堆栈段的位子
         mov cx,0000000000100_000B         ;加载数据段选择子(0x10)
         mov ds,cx
	 mov es,cx
	 mov fs,cx
	mov ss,cx
	;mov esp,0x7b00;设置堆栈大小
	mov esp,0x500000;设置堆栈大小为（1-5M）4的大小
	;显存的位子
	 mov cx,00000000000_10_000B         ;加载数据段选择子(0x10)
         mov gs,cx
         ;以下在屏幕上显示"OK." 
         mov byte [gs:0x00],'O'  
         mov byte [gs:0x02],'K'
	 

	

         mov ebp,esp                        ;保存堆栈指针 
         push byte '.'                      ;压入立即数（字节）
         
         sub ebp,4
         cmp ebp,esp                        ;判断压入立即数时，ESP是否减4 
         jnz ghalt                          
         pop eax
         mov [gs:0x04],al                      ;显示句点 
      
  ghalt:     
	jmp dword 0x0008:0x8000
	;jmp ghalt
        hlt                                ;已经禁止中断，将不会被唤醒 

model:
	mov ah,0x00
	mov al,0x13
	int 10h
	ret
;-------------------------------------------------------------------------------
     
         gdt_size         dw 0
         gdt_base         dd 0x00007e00     ;GDT的物理地址 
                             
         times 510-($-$$) db 0
                          db 0x55,0xaa

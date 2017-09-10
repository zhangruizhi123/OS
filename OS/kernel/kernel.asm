[section .text]
;IDT描述符
abc:dw 0x00010000,0x00000000
ldtLen equ $-abc
ldtPtr dw ldtLen-1
		dd 0
global _start
global myprint
global in_byte
global in_word
global out_byte
global out_word
global os_point
global load_IDT

global _R8259AHandler
global hwd00

;以下是汇编函数的入口地在，当开启该功能时编译时可以不加入 -e参数
extern main
extern spurious_irq
extern hwint20
_start:
	;sti
	call main
	jmp _start

os_point:
	mov ecx,[esp+4]
	mov eax,[esp+8]
	mov [fs:ecx],al
	ret
myprint:
	mov ecx,[esp+4]
	mov edx,[esp+8]
	mov eax,[esp+12]
	mov byte [gs:ecx],dl
	mov byte [gs:ecx+1],al
	ret
in_byte:
	mov edx,[esp+4]
	in al,dx
	ret
in_word:
	mov edx,[esp+4]
	in ax,dx
	ret
out_byte:
	mov edx,[esp+4]
	mov eax,[esp+8]
	out dx,al
	ret
out_word:
	mov edx,[esp+4]
	mov eax,[esp+8]
	out dx,ax
	ret


load_IDT:
	mov eax,[esp+4]
	lidt [eax]
	;sti
	sti
	ret
;中断函数历程
_R8259AHandler:
	;mov ah,0ch
	;mov al,'!'
	;mov [gs:((80*15+15)*2)],ax
	mov al, 20h
	out 0xa0,al
    out 20h, al
    sti
    call hwint20
    cli
	iretd

%macro	hwint_master	1
	push	%1
	sti
	call	spurious_irq
	cli
	add	esp, 4
	hlt
%endmacro

hwd00:
	hwint_master 00





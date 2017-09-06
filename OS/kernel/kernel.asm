[section .text]
global _start
global myprint
global in_byte
global in_word
global out_byte
global out_word
global os_point
global getStack
;以下是汇编函数的入口地在，当开启该功能时编译时可以不加入 -e参数
extern main
_start:
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
getStack:
	mov eax,esp
	ret

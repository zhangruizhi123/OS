[section .text]
global _start
global myprint
global in_byte
global in_word
global out_byte
global out_word
global os_point
global getStack
extern main
_start:
	mov byte [gs:0x00],'s'  
        mov byte [gs:0x02],'t'
        mov byte [gs:0x04],'a'
        mov byte [gs:0x06],'r'
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

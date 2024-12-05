;(b+b+d)-(c+a)
;a-byte
;b-word
;c-double word
;d-qword
bits 32
global start
extern exit
import exit msvcrt.dll
segment data use32 class=data
a db 2
b dw 100
c dd 300
d dq 1000
segment code use32 class=code
start:
mov ax,[b];ax=b
add ax,[b];ax=b+b
cwd
cdq;edx:eax=b+b
mov ebx, dword[d]
mov ecx, dword[d+4]; ecx:ebx=d
add eax,ebx
adc edx,ecx; edx:eax=b+b+d
push edx
push eax
mov al, [a];al=a
cbw
cwd;dx:ax=a
add ax, word[c]
adc dx, word[c+2];dx:ax=a+c
cdq; edx:eax=a+c
mov ebx,eax;ebx=eax
mov ecx,edx;ecx=edx
pop eax
pop edx; edx:eax=b+b+d
sub eax, ebx
sbb edx, ecx;edx:eax=(b+b+d)-(c+a)

push dword 0
call[exit]
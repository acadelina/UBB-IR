;(c+d)-(a+d)+b
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
mov edx, 0 ;edx=0
mov eax, [c]; eax=c
add eax, [d] 
adc edx, [d+4];edx:eax=c+d
mov ecx, edx
mov ebx, eax; ecx:ebx=edx:eax
mov eax, 0; eax=0
mov edx, 0; edx=0
mov al, [a]; al=a
add eax,[d]
adc edx,[d+4]; edx:eax=a+d
sub ebx,eax
sbb ecx,edx; ebx:ecx=(c+d)-(a+d)
mov eax, 0; eax=0
mov ax, [b]; eax=b
mov edx, 0; edx=0
add ebx, eax
adc ecx, edx; ecx:ebx=(c+d)-(a+d)+b
mov eax,ebx
mov edx, ecx; edx:eax=(c+d)-(a+d)+b

push dword 0
call [exit]
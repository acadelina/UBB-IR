;(8-a*b*100+c)/d+x; 
;a,b,d-byte
;c-doubleword
;x-qword

bits 32
global start
extern exit
import exit msvcrt.dll
segment data use32 class=data
a db 2
b db 10
x dq 10000
c dd 300
d db 5
segment code use32 class=code
start:
mov al,[a];al=a
mul byte[b]; ax=a*b
mov bx, 100; bx=100
mul bx; dx:ax=a*b*100
push dx
push ax
pop eax; eax=a*b*100
mov edx,0; edx=0
add eax, dword[c]
adc edx, dword[c+4]; edx:eax=a*b*100+c
mov ecx,edx; ecx=edx
mov ebx,eax;ebx=eax
mov edx,0;edx=0
mov eax,0;eax=0
mov al,8;al=8
sub eax, ebx
sbb edx, ecx; edx:eax=8-a*b*100+c
div dword[d]; edx:eax=



push dword 0
call [exit]
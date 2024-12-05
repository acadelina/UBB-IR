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
x dq 1000
c dd 300
d db 2
segment code use32 class=code
start:
mov al,8;al=8
mov ah,0;ax=8
div byte[d];ax=8/d
push ax
mov al,[a];al=a
mul byte[b];ax=a*b
mov bx,ax;bx=ax=a*b
mov al,100;al=100
mov ah,0;ax=100
div byte[d];ax=100/d
mov ah,0;ah=0
mul bx;dx:ax=a*b*100/d
push dx
push ax
mov ax,word[c]
mov dx,word[c+2];dx:ax=c
div byte[d];dx:ax=c/d
pop bx
pop cx;cx:bx=a*b*100/d
add ax,bx
adc dx,cx;dx:ax=a*b*100/d+c/d
pop bx;bx=8/d
mov cx,0;cx=0
sub bx, ax
sbb cx, dx;cx:bx=(8-a*b*100+c)/d
push cx
push bx
mov edx,0
pop eax;edx:eax=(8-a*b*100+c)/d
add eax, dword[x]
adc edx, dword[x+4];edx:eax=(8-a*b*100+c)/d+x

push dword 0
call [exit]
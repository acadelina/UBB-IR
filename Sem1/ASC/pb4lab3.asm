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
cbw; ax=8
idiv byte[d]; ax=8/d
push ax
mov al,[a];al=a
imul byte[b]; ax=a*b
mov bx,ax;bx=ax=a*b
mov al,100;al=100
cbw;ax=100
idiv byte[d];ax=100/d
imul bx;dx:ax=a*b*100/d
push dx
push ax
mov al,[d];al=d
cbw; ax=d
mov bx,ax;bx=ax=d
mov ax,word[c];
mov dx,word[c+2];dx:ax=c

idiv bx;dx:ax=c/d
pop bx
pop cx;cx:bx=a*b*100/d
add ax,bx
adc dx,cx;dx:ax=c/d+a*b*100/d
pop bx;bx=8/d
cwd;cx:bx=8/d
sub bx, ax
sbb cx, dx;cx:bx=(8-a*b*100+c)/d
push cx
push bx
pop eax;eax=(8-a*b*100+c)/d
cdq;edx:eax=(8-a*b*100+c)/d
add eax, dword[x]
adc edx, dword[x+4];edx:eax=(8-a*b*100+c)/d+x

push dword 0
call [exit]
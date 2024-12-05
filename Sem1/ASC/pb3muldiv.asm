; 3.[-1+d-2*(b+1)]/a-d->word
bits 32
global start
extern exit
import exit msvcrt.dll
segment data use32 class=data
a db 5
b db 1
c db 3
d dw 40
segment data use32 class=code
start:
mov al,[b] ;al=b
mov ah, 0
add ax, 1  ;ax=b+1
mov ah, 2  ;ah=2
mul ah     ;ax=al*ah=2*(b+1)
mov bx, ax ;bx=ax=2*(b+1)
mov al, -1 ;al=-1
cbw
add ax, [d];ax=-1+d
sub ax,bx  ;ax=ax-bx=-1+d-2*(b+1)
div BYTE [a];al=ax/a=[-1+d-2*(b+1)]/a si ah=ax%a=[-1+d-2*(b+1)]%a
sub ax, [d];ax=[-1+d-2*(b+1)]/a-d
; ax=-33


push dword 0
call [exit]
; 3.(e+f)*g->word
bits 32
global start
extern exit
import exit msvcrt.dll
segment data use32 class=data
e dw 600
f dw 500
g dw 400

segment data use32 class=code
start:
mov ax,[e] ;ax=e
add ax,[f] ;ax=e+f
mul word[g];dx:ax=(e+f)*g


push dword 0
call [exit]
bits 32
global start

extern exit,printf
import exit msvcrt.dll
import printf msvcrt.dll
segment data use32 class=data
    sir dd 1234a678h,12345678h,1ac3b47dh,0xfedc9876
    len equ ($-sir)/4
    max_sir times len+1 db 0
    f1 db "%i ",0
    f2 db "%s ",0
    sir2 times len+1 db 0
    suma dw 0
segment code use32 class=code

start:
   
    mov ecx,len
    
    mov esi,sir
    mov edi,sir2
    repeta:
        push ecx
        mov ecx,3
        lodsb
        mov bl,al
        max_d:
            lodsb
            cmp al,bl
            jb mai_mic
            mov bl,al
            mai_mic:
            dec ecx
            jnz max_d
      mov ax,0
      mov al,bl
      mov bx,[suma]
      add bx,ax
      mov [suma],bx
      stosb
      pop ecx
      dec ecx
      jnz repeta
      
     mov edi,max_sir
     mov esi,sir2
     mov ecx,len
     repeta2:
        mov ebx,len
        sub ebx,ecx
        mov al,[esi+ebx]
        push ecx
        
        mov ebx,0
        mov cl,1
        repet:
            mov dl,[esi+ebx]
            cmp al,dl
            jae sari
            inc cl
            sari:
            inc ebx
            mov edx,len
            cmp ebx,edx
            jb repet
       mov al,cl
       add al,'0'
       stosb
       pop ecx
       dec ecx
       jnz repeta2
    
    
    push dword max_sir
    push dword f2
    call [printf]
    add esp,4*2
    
    
    mov ax,[suma]
    cwd
    push dword eax
    push dword f1
    call [printf]
    add esp,4*2
    
    push dword 0
    call [exit]
    
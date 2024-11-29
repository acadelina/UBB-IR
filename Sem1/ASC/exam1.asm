bits 32
global start
extern exit,scanf
import scanf msvcrt.dll
import exit  msvcrt.dll
segment data use32 class=data
n dd 0
format db "%d",0
sir times 10 dd 0
sume times 10 db 0
aux dd 0

segment code use32 class=code
start:
    push dword n
    push dword format
    call[scanf]
    add esp,4*2
    
    mov ecx,[n]
    mov esi,sir
    mov edi,sume
    jecxz final
    
    repeta:
        push ecx
        
        push dword aux
        push dword format
        call[scanf]
        add esp,4*2
        
        mov eax,[aux]
        mov [esi],eax
        add esi,4
        
        mov ecx,0
        rep_suma:
            cmp eax,0
            je gata
            
            mov edx,0
            mov ebx,10
            div ebx
            mov ebx,edx
            shr edx,1
            jc imp
            add ecx,ebx
            imp:
                jmp rep_suma
       gata:
            mov [edi],cl
            inc edi
            pop ecx
            dec ecx
            jnz repeta
       final:
       
       push dword 0
       call [exit]
        
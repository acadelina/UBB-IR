bits 32 ; assembling for the 32 bits architecture

; declare the EntryPoint (a label defining the very first instruction of the program)
global start        

; declare external functions needed by our program
extern exit,printf    
           ; tell nasm that exit exists even if we won't be defining it
import exit msvcrt.dll
import printf msvcrt.dll    ; exit is a function that ends the calling process. It is defined in msvcrt.dll
                          ; msvcrt.dll contains exit, printf and all the other important C-runtime specific functions

; our data is declared here (the variables needed by our program)
segment data use32 class=data
    sir dd -1,123456,0xabcdeff,0xabcdeff,0xcbcdeff,0xdbcdeff,0111010101b
    len1 equ ($-sir)/4
    rez times len1 db 0
    msj db "%x",0
    af db "%u",0
    hex dd 16

; our code starts here
segment code use32 class=code
    start:
        
        mov esi,sir
        mov edi,rez
        mov ecx,len1
        repeta:
        lodsd
        mov ebx,0
        suma1:
            mov edx,0
            div dword[hex]
            add bl,dl
            cmp eax,0
            jne suma1
        mov al,bl
        stosb
        dec ecx
        jnz repeta
        
        
        mov ecx,len1
        mov esi,rez
        repeta1:
            push ecx
            mov eax,0
            lodsb
            push eax
            push dword af
            call [printf]
            add esp,4*2
            pop ecx
            dec ecx
            jnz repeta1
        
        
        push    dword 0      ; push the parameter for exit onto the stack
        call    [exit]       ; call exit to terminate the program

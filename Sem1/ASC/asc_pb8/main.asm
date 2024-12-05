bits 32 ; assembling for the 32 bits architecture

; declare the EntryPoint (a label defining the very first instruction of the program)
global start        

; declare external functions needed by our program
extern exit ,printf 
extern vocale             ; tell nasm that exit exists even if we won't be defining it
import exit msvcrt.dll 
import printf msvcrt.dll   ; exit is a function that ends the calling process. It is defined in msvcrt.dll
                          ; msvcrt.dll contains exit, printf and all the other important C-runtime specific functions

; our data is declared here (the variables needed by our program)
segment data use32 class=data
    s1 dq 0xabcdeffaba92,0xabcdeffe322,0xaaabc12345,0x60016000e2aeef21
    len equ ($-s1)/8
    s2 times len dd 0
    msj db "%d"
; our code starts here
segment code use32 class=code
    start:
        mov ecx,len
        mov esi,s1
        mov edi,s2
        repeta:
            lodsd
            lodsw
            mov bx,ax
            lodsw
            cmp ax,bx
            jng mai_mic
            sub esi,4
            lodsd
            mov [edi],eax
            add edi,4
            mai_mic:
            dec ecx
            jnz repeta
            
        push dword s2
        call vocale
        
        push eax
        push msj
        call [printf]
        add esp,8 
        push    dword 0      ; push the parameter for exit onto the stack
        call    [exit]       ; call exit to terminate the program

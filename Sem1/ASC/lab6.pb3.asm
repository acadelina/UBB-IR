bits 32 ; assembling for the 32 bits architecture

; declare the EntryPoint (a label defining the very first instruction of the program)
global start        

; declare external functions needed by our program
extern exit               ; tell nasm that exit exists even if we won't be defining it
import exit msvcrt.dll    ; exit is a function that ends the calling process. It is defined in msvcrt.dll
                          ; msvcrt.dll contains exit, printf and all the other important C-runtime specific functions

; our data is declared here (the variables needed by our program)
segment data use32 class=data
    s dd 0702090ah,0b0c0304h,05060108h
    len equ ($-s)/4
    D times len db 0

; our code starts here
segment code use32 class=code
    start:
    
        mov ecx, len
        mov esi, s
        
        cld
        ;jecxz final
        ;repeta:
            lodsd
            ;shr eax,4
           ; mov ah,0
            
        
        ;loop repeta
        
        ;final:
        push    dword 0      ; push the parameter for exit onto the stack
        call    [exit]       ; call exit to terminate the program

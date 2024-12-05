bits 32 ; assembling for the 32 bits architecture

; declare the EntryPoint (a label defining the very first instruction of the program)
global start        

; declare external functions needed by our program
extern exit,fscanf,fprintf,fopen,fclose               ; tell nasm that exit exists even if we won't be defining it
import exit msvcrt.dll
import fopen msvcrt.dll
import fclose msvcrt.dll
import fprintf msvcrt.dll
import fscanf msvcrt.dll    ; exit is a function that ends the calling process. It is defined in msvcrt.dll
                          ; msvcrt.dll contains exit, printf and all the other important C-runtime specific functions

; our data is declared here (the variables needed by our program)
segment data use32 class=data
    nume_fis db "f27.txt",0
    desc_fis dd -1
    mod_acc db "r+",0
    format db "%d",0
    format2 db " %d",0
    n dd 0

; our code starts here
segment code use32 class=code
    start:
        push dword mod_acc
        push dword nume_fis
        call[fopen]
        add esp,4*2
        
        cmp eax,0
        je final
        mov [desc_fis],eax
        mov ebx,11111111h
        citire:
            
            push dword n
            push dword format
            push dword [desc_fis]
            call[fscanf]
            add esp,4*3
            
            cmp eax,1
            jne afisare
            
            cmp ebx,[n]
            jl not_min
            mov ebx,[n]
            
            not_min:
            jmp citire
            
        afisare:
            push ebx
            push dword format2
            push dword[desc_fis]
            call[fprintf]
            add esp,4*3
            
            push dword[desc_fis]
            call[fclose]
            add esp,4
        final:
        
        push    dword 0      ; push the parameter for exit onto the stack
        call    [exit]       ; call exit to terminate the program

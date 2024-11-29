bits 32 ; assembling for the 32 bits architecture

; declare the EntryPoint (a label defining the very first instruction of the program)
global start        

; declare external functions needed by our program
extern exit,fopen,fclose,scanf,getchar,gets,fprintf              ; tell nasm that exit exists even if we won't be defining it
import exit msvcrt.dll
import fopen msvcrt.dll
import fclose msvcrt.dll 
import scanf msvcrt.dll
import getchar msvcrt.dll
import gets msvcrt.dll
import fprintf msvcrt.dll   ; exit is a function that ends the calling process. It is defined in msvcrt.dll
                          ; msvcrt.dll contains exit, printf and all the other important C-runtime specific functions

; our data is declared here (the variables needed by our program)
segment data use32 class=data
    nume_fis resb 31
    text resb 121
    desc_fis dd -1
    mod_acc db "w",0
    format db "%s",0
    
; our code starts here
segment code use32 class=code
    start:
        push dword nume_fis
        push dword format
        call [scanf]
        add esp,4*2
        
        call[getchar]
        add esp,4
        
        
        push dword text
        call[gets]
        add esp,4
    
        push dword mod_acc
        push dword nume_fis
        call[fopen]
        add esp,4*2
        
        mov [desc_fis],eax
        cmp eax,0
        je final
        
        push dword text
        push dword[desc_fis]
        call[fprintf]
        add esp,4*2
        
        push dword [desc_fis]
        call[fclose]
        add esp,4
        
        final:
        push    dword 0      ; push the parameter for exit onto the stack
        call    [exit]       ; call exit to terminate the program

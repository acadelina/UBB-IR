bits 32 ; assembling for the 32 bits architecture

; declare the EntryPoint (a label defining the very first instruction of the program)
global start        

; declare external functions needed by our program
extern exit,fopen,fclose,fread,printf               ; tell nasm that exit exists even if we won't be defining it
import exit msvcrt.dll
import fopen msvcrt.dll
import fclose msvcrt.dll
import fread msvcrt.dll
import printf msvcrt.dll    ; exit is a function that ends the calling process. It is defined in msvcrt.dll
                          ; msvcrt.dll contains exit, printf and all the other important C-runtime specific functions

; our data is declared here (the variables needed by our program)
segment data use32 class=data
    nume_fis db "Fis.txt",0
    mod_acc db "r",0
    desc_fis dd -1
    text resb 201
    len equ 200
    prop resb 100

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
        
        push dword [desc_fis]
        push dword len
        push dword 1
        push dword text
        call[fread]
        add esp,4*4
        
        mov ecx,eax
        mov esi,text
        
        repeta:
            
            cmp ebx,0
            jne mai_dep
            cuvant1:
                mov al,[esi]
                inc ebx
                
        
        
        
        
        final:
        push    dword 0      ; push the parameter for exit onto the stack
        call    [exit]       ; call exit to terminate the program

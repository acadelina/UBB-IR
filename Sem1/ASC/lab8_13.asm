bits 32 ; assembling for the 32 bits architecture

; declare the EntryPoint (a label defining the very first instruction of the program)
global start        

; declare external functions needed by our program
extern exit,fopen,fclose,fprintf               ; tell nasm that exit exists even if we won't be defining it
import exit msvcrt.dll
import fopen msvcrt.dll
import fclose msvcrt.dll
import fprintf msvcrt.dll    ; exit is a function that ends the calling process. It is defined in msvcrt.dll
                          ; msvcrt.dll contains exit, printf and all the other important C-runtime specific functions

; our data is declared here (the variables needed by our program)
segment data use32 class=data
    nume_fis db "f13.txt",0
    text db "Ana are 7 mere si 5 pere!",0
    len equ $-text
    desc_fis dd -1
    mod_acc db "w",0
    

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
        
        mov esi,text
        mov ecx,len
        repeta:
            mov al,[esi]
            cmp al,'a'
            jl not_lit
            cmp al,'z'
            jg not_lit
            
            sub al,'a'
            add al,'A'
            mov byte[esi],al
            
            not_lit:
                inc esi
                dec ecx
                jnz repeta
                
        push dword text
        push dword [desc_fis]
        call[fprintf]
        add esp,4*2
        
        push dword[desc_fis]
        call[fclose]
        add esp,4
        
        
        final:
        
        push    dword 0      ; push the parameter for exit onto the stack
        call    [exit]       ; call exit to terminate the program

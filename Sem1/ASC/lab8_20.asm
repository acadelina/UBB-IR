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
    nume_fis db "f20.txt",0
    mod_acc db "w",0
    desc_fis dd -1
    text db "ana are mere",0
    len equ $-text

; our code starts here
segment code use32 class=code
    start:
        mov esi,text
        mov ecx,len
        mov ebx,0
        mov eax,0
        repeta:
            mov al,[esi+ebx]
            cmp al,'a'
            jl not_cif
            cmp al,'z'
            jg not_cif
            mov edx,ebx
            shr edx,1
            jc not_cif
            mov edx,ebx
            add edx,'0'
            mov byte[esi+ebx],dl
            
            not_cif:
            inc ebx
            cmp ebx,ecx
            jl repeta
            
        push dword mod_acc
        push dword nume_fis
        call [fopen]
        add esp,4*2
        
        cmp eax,0
        je final
        
        mov [desc_fis],eax
        
        push dword text
        push dword[desc_fis]
        call[fprintf]
        add esp,4*2
        
        push dword[desc_fis]
        call [fclose]
        add esp,4
        
        final:
        
        push    dword 0      ; push the parameter for exit onto the stack
        call    [exit]       ; call exit to terminate the program

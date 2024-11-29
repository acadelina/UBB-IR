bits 32 ; assembling for the 32 bits architecture

; declare the EntryPoint (a label defining the very first instruction of the program)
global start        

; declare external functions needed by our program
extern exit,scanf,fread,printf,fopen,fclose               ; tell nasm that exit exists even if we won't be defining it
import exit msvcrt.dll
import scanf msvcrt.dll
import fread msvcrt.dll
import printf msvcrt.dll
import fopen msvcrt.dll
import fclose msvcrt.dll
    ; exit is a function that ends the calling process. It is defined in msvcrt.dll
                          ; msvcrt.dll contains exit, printf and all the other important C-runtime specific functions

; our data is declared here (the variables needed by our program)
segment data use32 class=data
    nume_fis resb 50
    mod_acc db "r",0
    desc_fis dd -1
    text resb 101
    len equ 100
    format_nume_fis db "%s",0
    cuv resb 25
    msj db "%s ",0
segment code use32 class=code
    start:
        push dword nume_fis
        push dword format_nume_fis
        call [scanf]
        add esp,4*2
        
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
        mov ebx,0
        mov esi,text
        repeta:
            mov al,[esi+ebx]
            ;cmp al,' '
            je gata
            mov dl,[esi+ebx-1]
            cmp ebx,0
            je mai_departe
            
            cmp dl,' '
            jne not_poz
            mai_departe:
            
            mov edx,ebx
            mov edi,cuv
            repeta1:
                
                mov al,[esi+edx]
                cmp al,' '
                je gata
                mov [edi],al
                inc edi
                inc edx
                jmp repeta1
                gata:
                
           push dword cuv
           push dword msj
           call[printf]
           add esp,4*2
           
           not_poz:
           add ebx,4
           cmp ebx,ecx
           jl repeta
                
                
            
            
        
        final:
        push    dword 0      ; push the parameter for exit onto the stack
        call    [exit]       ; call exit to terminate the program

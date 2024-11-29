bits 32 ; assembling for the 32 bits architecture

; declare the EntryPoint (a label defining the very first instruction of the program)
global start        

; declare external functions needed by our program
extern exit,scanf,fprintf,fopen,fclose               ; tell nasm that exit exists even if we won't be defining it
import exit msvcrt.dll
import scanf msvcrt.dll
import fprintf msvcrt.dll
import fopen msvcrt.dll
import fclose msvcrt.dll    ; exit is a function that ends the calling process. It is defined in msvcrt.dll
                          ; msvcrt.dll contains exit, printf and all the other important C-runtime specific functions

; our data is declared here (the variables needed by our program)
segment data use32 class=data
    nume_fis db "f26.txt",0
    mod_acc db "w",0
    desc_fis dd -1
    cuv resb 50
    format db "%s",0
    msj db "%s",13,10,0
; our code starts here
segment code use32 class=code
    start:
        push dword mod_acc
        push dword nume_fis
        call [fopen]
        add esp,4*2
        
        cmp eax,0
        je final
        
        mov [desc_fis],eax
        
        repeta:
            push dword cuv
            push dword format
            call [scanf]
            add esp,4*2
            
            cmp byte[cuv],'$'
            je gata
            
            mov esi,cuv
            litera:
                mov al,[esi]
                cmp al,'A'
                jb not_lit
                cmp al,'Z'
                ja not_lit
                
                push dword cuv
                push dword msj
                push dword [desc_fis]
                call[fprintf]
                
                add esp,4*3
                jmp repeta
                not_lit:
                    inc esi
                    cmp byte[esi],''
                    jne litera
            jmp repeta
        gata:    
        push dword [desc_fis]
        call[fclose]
        add esp,4
       
        final:
        
        push    dword 0      ; push the parameter for exit onto the stack
        call    [exit]       ; call exit to terminate the program

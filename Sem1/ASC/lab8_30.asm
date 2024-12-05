bits 32 ; assembling for the 32 bits architecture

; declare the EntryPoint (a label defining the very first instruction of the program)
global start        

; declare external functions needed by our program
extern exit,fopen,fclose,scanf,fprintf               ; tell nasm that exit exists even if we won't be defining it
import exit msvcrt.dll
import fopen msvcrt.dll
import fclose msvcrt.dll
import fprintf msvcrt.dll
import scanf msvcrt.dll    ; exit is a function that ends the calling process. It is defined in msvcrt.dll
                          ; msvcrt.dll contains exit, printf and all the other important C-runtime specific functions

; our data is declared here (the variables needed by our program)
segment data use32 class=data
    nume_fis db "f30.txt",0
    des_fis dd -1
    mod_acc db "w",0
    format db "%s",0
    msj db "%s, ",0
    cuv resb 50
; our code starts here
segment code use32 class=code
    start:
        push dword mod_acc
        push dword nume_fis
        call [fopen]
        add esp,4*2
        
        cmp eax,0
        je final
        
        mov [des_fis],eax
        
        repeta:
            push dword cuv
            push dword format
            call [scanf]
            add esp,4*2
            
            cmp byte[cuv],'$'
            je gata
            
            mov esi,cuv
            cifre:
                mov al,[esi]
                cmp al,'0'
                jb not_cif
                cmp al,'9'
                ja not_cif
                
                push dword cuv
                push dword msj
                push dword[des_fis]
                call[fprintf]
                add esp,4*3
                
                jmp repeta
                
                not_cif:
                inc esi
                cmp byte[esi],''
                jne cifre
                jmp repeta
            
        gata:
            push dword[des_fis]
            call[fclose]
            add esp,4
        final:
        
        push    dword 0      ; push the parameter for exit onto the stack
        call    [exit]       ; call exit to terminate the program

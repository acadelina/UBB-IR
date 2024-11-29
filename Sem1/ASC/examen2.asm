bits 32 ; assembling for the 32 bits architecture

; declare the EntryPoint (a label defining the very first instruction of the program)
global start        

; declare external functions needed by our program
extern exit,scanf,fscanf,printf,fopen,fclose               ; tell nasm that exit exists even if we won't be defining it
import exit msvcrt.dll
import scanf msvcrt.dll
import fscanf msvcrt.dll
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
    format db "%s",0
    cuv resb 25
    msj db "%s ",0
segment code use32 class=code
    start:
        push dword nume_fis
        push dword format
        call [scanf]
        add esp,4*2
        
        push dword mod_acc
        push dword nume_fis
        call[fopen]
        add esp,4*2
        
        cmp eax,0
        je final
        
        mov [desc_fis],eax
        mov cx,0
        mov bx,4
        repeta: 
            pushad
            push dword cuv
            push dword format
           push dword [desc_fis]
            call[fscanf]
            add esp,4*3
            
            cmp eax,1
            jne gata
            popad
           
            mov ax,cx
            div bx
            cmp dx,0
            jne not_4
            pushad
            push dword cuv
            push dword msj
            call [printf]
            add esp,4*2
            popad
            not_4:
            
            mov dx,0
            inc cx
            jmp repeta
        gata:    
        push dword[desc_fis]
        call[fclose]
        add esp,4
        
        final:
        push    dword 0      ; push the parameter for exit onto the stack
        call    [exit]       ; call exit to terminate the program

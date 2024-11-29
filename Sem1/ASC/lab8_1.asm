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
    nume_fis db "f1.txt",0
    desc_fis dd -1
    text resb 101
    len equ 100
    mod_acces db "r",0
    msj db "Numarul de vocale: %d",0
    

; our code starts here
segment code use32 class=code
    start:
        push dword mod_acces
        push dword nume_fis
        call [fopen]
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
        
        mov esi,text
        mov ecx,eax
        mov ebx,0
        repeta:
            mov al,[esi]
            cmp al,'a'
            je adun
            cmp al,'e'
            je adun
            cmp al,'i'
            je adun
            cmp al,'o'
            je adun
            cmp al,'u'
            je adun
            cmp al,'A'
            je adun
            cmp al,'E'
            je adun
            cmp al,'I'
            je adun
            cmp al,'O'
            je adun
            cmp al,'U'
            je adun
            jmp nu_adun
            adun:
            inc ebx
            nu_adun:
            inc esi
            dec ecx
            jnz repeta
            
       push ebx
       push msj
       call[printf]
       add esp,4*2
       
       push dword [desc_fis]
       call[fclose]
       add esp,4
            
        final:
        push    dword 0      ; push the parameter for exit onto the stack
        call    [exit]       ; call exit to terminate the program

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
    nume_fis db "f16.txt",0
    des_fis dd -1
    text resb 101
    len equ 100
    mod_acc db "r",0
    msj db "Frecventa y: %d, frecventa z: %d",0

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
        
        push dword[des_fis]
        push dword len
        push dword 1
        push dword text
        call [fread]
        add esp,4*4
        
        mov ecx,eax
        mov esi,text
        mov ebx,0
        mov edx,0
        repeta:
            mov al,[esi]
            cmp al,'y'
            jne cmp_z
            inc ebx
            cmp_z:
            cmp al,'z'
            jne gata
            inc edx
            gata:
            inc esi
            dec ecx
            jnz repeta
            
        push edx
        push ebx
        push dword msj
        call [printf]
        add esp,4*3
        
        push dword[des_fis]
        call [fclose]
        add esp,4
        
        final:
        push    dword 0      ; push the parameter for exit onto the stack
        call    [exit]       ; call exit to terminate the program

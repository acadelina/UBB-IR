bits 32 ; assembling for the 32 bits architecture

; declare the EntryPoint (a label defining the very first instruction of the program)
global start        

; declare external functions needed by our program
extern exit,scanf,fprintf,fopen,fclose               ; tell nasm that exit exists even if we won't be defining it
import exit msvcrt.dll
import scanf msvcrt.dll
import fprintf msvcrt.dll 
import fopen msvcrt.dll
import fclose msvcrt.dll   ; exit is a function that ends the calling process. It is defined in msvcrt.dll
                          ; msvcrt.dll contains exit, printf and all the other important C-runtime specific functions

; our data is declared here (the variables needed by our program)
segment data use32 class=data
    nume_fis db "exprac7.txt",0
    mod_acc db "w",0
    desc_fis dd -1
    format db "%d",0
    msj1 db "baza 10: %d, baza 16: %x, nr de biti 1: %d",10,13,0
    numar resb 200

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
        
        push dword numar
        push dword format
        call[scanf]
        add esp,4*2
        
        repeta:
            mov eax,[numar]
            cmp eax,0
            je final2
            
            mov ebx,eax
            mov ecx,0
            bucla:
                cmp ebx,0
                je finalbucla
                shr ebx,1
                adc ecx,0
                jmp bucla
           finalbucla:
           
           push ecx
           push dword [numar]
           push dword [numar]
           push dword msj1
           push dword [desc_fis]
           call [fprintf]
           add esp,4*5
           
           push dword numar
           push dword format
           call[scanf]
           add esp,4*2
           
           jmp repeta
           
           final2:
           push dword[desc_fis]
           call [fclose]
        
        
        final:
        push    dword 0      ; push the parameter for exit onto the stack
        call    [exit]       ; call exit to terminate the program

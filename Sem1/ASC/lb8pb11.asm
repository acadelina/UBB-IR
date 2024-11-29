bits 32 ; assembling for the 32 bits architecture

; declare the EntryPoint (a label defining the very first instruction of the program)
global start        

; declare external functions needed by our program
extern exit,scanf,fprintf,fopen,fclose,getchar               ; tell nasm that exit exists even if we won't be defining it
import exit msvcrt.dll 
import scanf msvcrt.dll 
import fprintf msvcrt.dll 
import fopen msvcrt.dll
import fclose msvcrt.dll 
import getchar msvcrt.dll     ; exit is a function that ends the calling process. It is defined in msvcrt.dll
                          ; msvcrt.dll contains exit, printf and all the other important C-runtime specific functions

; our data is declared here (the variables needed by our program)
segment data use32 class=data
    nume_fis db "prob8.txt",0
    descr dd -1
    mod_acces db "w",0
    format db "%s",0
    cuvant resb 50

; our code starts here
segment code use32 class=code
    start:
        push dword mod_acces
        push dword nume_fis
        call [fopen]
        add esp,4*2
        
        mov [descr],eax
        cmp eax,0
        je final
        
        push dword cuvant
        push dword format
        call [scanf]
        add esp,4*2
        
        call [getchar]
        add esp,4
        
        mov eax,[cuvant]
        cmp eax,'$'
        je final2
        repeta:
            push dword cuvant
            push dword [descr]
            call [fprintf]
            add esp,4*2
            
            push dword cuvant
            push dword format
            call [scanf]
            add esp,4*2
            
            mov eax,[cuvant]
            cmp eax,'$'
            jne repeta
            
        final2:
            push dword [descr]
            call [fclose]
            add esp,4
        
        final:
        
        push    dword 0      ; push the parameter for exit onto the stack
        call    [exit]       ; call exit to terminate the program

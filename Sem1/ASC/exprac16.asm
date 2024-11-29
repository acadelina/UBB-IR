bits 32 ; assembling for the 32 bits architecture

; declare the EntryPoint (a label defining the very first instruction of the program)
global start        

; declare external functions needed by our program
extern exit,scanf,fopen,fclose,fprintf               ; tell nasm that exit exists even if we won't be defining it
import exit msvcrt.dll  
import scanf msvcrt.dll
import fopen msvcrt.dll
import fclose msvcrt.dll 
import fprintf msvcrt.dll ; exit is a function that ends the calling process. It is defined in msvcrt.dll
                          ; msvcrt.dll contains exit, printf and all the other important C-runtime specific functions

; our data is declared here (the variables needed by our program)
segment data use32 class=data
    n dd 0
    cuvant resb 50
    format_nr db "%d",0
    format_cuv db "%s",0
    nume_fis db "output.txt",0
    dec_fis dd -1
    mod_acc db "w",0
    msj db "%s ",0

; our code starts here
segment code use32 class=code
    start:
       
        push dword n 
        push dword format_nr
        call [scanf]
        add esp,4*2
        
        push dword mod_acc
        push dword nume_fis
        call[fopen]
        add esp,4*2
        
        mov [dec_fis],eax
        cmp eax,0
        je final
        
        repeta:
            
            push dword cuvant
            push dword format_cuv
            call [scanf]
            add esp,4*2
            
            
            mov eax,[cuvant]
            cmp byte[cuvant],'#'
            je final1
            
            mov esi,cuvant
            mov ebx,0
            vocale:
                mov al,[esi]
                cmp al,'a'
                je aduna
                cmp al,'e'
                je aduna
                cmp al,'i'
                je aduna
                cmp al,'o'
                je aduna
                cmp al,'u'
                je aduna
                jmp nu_aduna
                aduna:
                    inc ebx
                nu_aduna:
                    inc esi
                    cmp byte[esi],''
                    jne vocale
             cmp ebx,[n]
             jl repeta
             
             push dword cuvant
             push dword msj
             push dword [dec_fis]
             call [fprintf]
             add esp,4*2
             
             jmp repeta
       final1:      
             push dword[dec_fis]
             call [fclose]
             add esp,4
            
        final:
        push    dword 0      ; push the parameter for exit onto the stack
        call    [exit]       ; call exit to terminate the program

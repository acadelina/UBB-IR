bits 32 ; assembling for the 32 bits architecture

; declare the EntryPoint (a label defining the very first instruction of the program)
global start        

; declare external functions needed by our program
extern exit,printf,fscanf,fopen,fclose               ; tell nasm that exit exists even if we won't be defining it
import exit msvcrt.dll 
import printf msvcrt.dll
import fscanf msvcrt.dll
import fopen msvcrt.dll
import fclose msvcrt.dll   ; exit is a function that ends the calling process. It is defined in msvcrt.dll
                          ; msvcrt.dll contains exit, printf and all the other important C-runtime specific functions

; our data is declared here (the variables needed by our program)
segment data use32 class=data
    nume_fis db "input.txt",0
    mod_acces db "r",0
    format db "%x",0
    msj db "%x- %d",10,13,0
    desc_fis dd -1
    n dd 0
    
    
    
    

; our code starts here
segment code use32 class=code
    start:
        push dword mod_acces
        push dword nume_fis
        call[fopen]
        add esp,4*2
        
        cmp eax,0
        je final2
        mov [desc_fis],eax
        
        
        
        repeta:
            push dword n 
            push dword format
            push dword[desc_fis]
            call[fscanf]
            add esp,4*3
            
            cmp eax,1
            jne final
            
            mov eax,0
            mov al,[n]
            mov bl,al
            
            mov edx,0
            biti:
                shr bl,1
                adc edx,0
                cmp bl,0
                jne biti
            pushad
            push edx
            push eax
            push dword msj
            call [printf]
            add esp,4*3
            popad
            
            jmp repeta
           
        final:  
        push dword[desc_fis]
        call [fclose]
        add esp,4
        
        
        final2:
        
        push    dword 0      ; push the parameter for exit onto the stack
        call    [exit]       ; call exit to terminate the program

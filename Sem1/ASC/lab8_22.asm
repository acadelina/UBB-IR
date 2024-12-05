bits 32 ; assembling for the 32 bits architecture

; declare the EntryPoint (a label defining the very first instruction of the program)
global start        

; declare external functions needed by our program
extern exit,fopen,fclose,fprintf               ; tell nasm that exit exists even if we won't be defining it
import exit msvcrt.dll
import fopen msvcrt.dll
import fclose msvcrt.dll
import fprintf msvcrt.dll     ; exit is a function that ends the calling process. It is defined in msvcrt.dll
                          ; msvcrt.dll contains exit, printf and all the other important C-runtime specific functions

; our data is declared here (the variables needed by our program)
segment data use32 class=data
    nume_fis db "f22.txt",0
    nr dw 1234
    mod_acc db "w",0
    desc_fis dd -1
    msj db "%c",10,13,0

; our code starts here
segment code use32 class=code
    start:
        push dword mod_acc
        push dword nume_fis
        call [fopen]
        add esp ,4*2
        
        cmp eax,0
        je final
        
        mov [desc_fis],eax
        mov eax,0
        mov ax,[nr]
        repeta:
            mov bx,10
            div bx
            add edx,'0'
            pushad
            push edx
            push dword msj
            push dword [desc_fis]
            call [fprintf]
            add esp,4*3
            popad
            mov dx,0
           
            cmp ax,0
            jne repeta
            
        push dword [desc_fis]
        call [fclose]
        add esp,4
            
        
        final:
        
        push    dword 0      ; push the parameter for exit onto the stack
        call    [exit]       ; call exit to terminate the program

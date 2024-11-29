bits 32 ; assembling for the 32 bits architecture

; declare the EntryPoint (a label defining the very first instruction of the program)
global start        

; declare external functions needed by our program
extern exit,fopen,fclose,fread,printf               ; tell nasm that exit exists even if we won't be defining it
import exit msvcrt.dll 
import fopen msvcrt.dll
import fclose msvcrt.dll
import fread msvcrt.dll 
import printf msvcrt.dll  ; exit is a function that ends the calling process. It is defined in msvcrt.dll
                          ; msvcrt.dll contains exit, printf and all the other important C-runtime specific functions

; our data is declared here (the variables needed by our program)
segment data use32 class=data
    nume_fis db "r2.txt",0
    descr_fis dd -1
    mod_acc db "r",0
    msj resb 201
    msj2 resb 201
    len equ 100
    mesaj db "Text decodificat: %s",0
; our code starts here
segment code use32 class=code
    start:
        push dword mod_acc
        push dword nume_fis
        call [fopen]
        add esp, 4*2
        
        cmp eax,0
        je final
        
        mov [descr_fis],eax
        
        push dword [descr_fis]
        push dword len
        push dword 1
        push dword msj
        call [fread]
        add esp,4*4
        
        mov ecx,eax
        
        mov esi,msj
        mov edi,msj2
        repeta:
            mov al,[esi]
            cmp al,' '
            je modificat
            
            cmp al,'a'
            jb litera_mare
            cmp al,'z'
            ja modificat
            cmp al,'c'
            ja schimba
            add al,29
            jmp modificat
            litera_mare:
            cmp al,'A'
            jb modificat
            cmp al,'Z'
            ja modificat
            cmp al,'C'
            ja schimba
            add al,29
            schimba:
            sub al,3
            modificat:
            mov [edi],al
            inc edi
            inc esi
            dec ecx
            jnz repeta
            
        push dword msj2
        push dword mesaj
        call[printf]
        add esp,4*2
        
        push dword[descr_fis]
        call[fclose]
        add esp,4
        final:
        push    dword 0      ; push the parameter for exit onto the stack
        call    [exit]       ; call exit to terminate the program

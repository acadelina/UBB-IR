bits 32 ; assembling for the 32 bits architecture

; declare the EntryPoint (a label defining the very first instruction of the program)
global start        

; declare external functions needed by our program
extern exit,fopen,fclose,fread,printf               ; tell nasm that exit exists even if we won't be defining it
import exit msvcrt.dll
import fopen msvcrt.dll
import fclose msvcrt.dll
import fread msvcrt.dll
import printf msvcrt.dll
    ; exit is a function that ends the calling process. It is defined in msvcrt.dll
                          ; msvcrt.dll contains exit, printf and all the other important C-runtime specific functions

; our data is declared here (the variables needed by our program)
segment data use32 class=data
    nume_fis db "f6.txt",0
    desc_fis dd -1
    mod_acc db "r",0
    text resb 101
    len equ 100
    frec_cif resb 10
    cif_max dd -1
    msj db "Cifra: %d cu frecventa: %d",0
; our code starts here
segment code use32 class=code
    start:
        push dword mod_acc
        push dword nume_fis
        call[fopen]
        add esp,4*2
        
        cmp eax,0
        je final
        
        mov [desc_fis],eax
        
        push dword[desc_fis]
        push dword len
        push dword 1
        push dword text
        call[fread]
        add esp,4*4
        
        mov ecx,eax
        mov esi,text
        mov edi,frec_cif
        repeta:
            mov eax,0
            mov al,[esi]
            cmp al,'0'
            jl not_cif
            cmp al,'9'
            jg not_cif
            sub al,'0'
            mov bl,[edi+eax]
            inc bl
            mov [edi+eax],bl
            not_cif:
            inc esi
            dec ecx
            jnz repeta
            
        mov ecx,0
        mov esi,frec_cif
        mov ebx,0
        mov bl,0
        repeta1:
            mov al,[esi+ecx]
            cmp al,bl
            jl not_mx
            mov bl,al
            mov[cif_max],ecx
            not_mx:
            inc ecx
            cmp ecx,10
            jl repeta1
            
        push ebx
        push dword[cif_max]
        push dword msj
        call[printf]
        add esp,4*3
            
            
        
        
        
        final:
        push    dword 0      ; push the parameter for exit onto the stack
        call    [exit]       ; call exit to terminate the program

bits 32 ; assembling for the 32 bits architecture

; declare the EntryPoint (a label defining the very first instruction of the program)
global start        

; declare external functions needed by our program
extern exit,fopen,fclose,printf,fread              ; tell nasm that exit exists even if we won't be defining it
import exit msvcrt.dll
import fread msvcrt.dll
import printf msvcrt.dll
import fclose msvcrt.dll
import fopen msvcrt.dll
    ; exit is a function that ends the calling process. It is defined in msvcrt.dll
                          ; msvcrt.dll contains exit, printf and all the other important C-runtime specific functions

; our data is declared here (the variables needed by our program)
segment data use32 class=data
    nume_fis db "date.txt",0
    mod_acces db "r",0
    f_dir dd -1
    text resb 200
    len equ 200
    cuv resb 15
    propozitie resb 100
    msj db "Propozitia %d: %s Nr cuvinte: %d, Primul cuvant %s are %d litere",10,13,0
; our code starts here
segment code use32 class=code
    start:
        push dword mod_acces
        push dword nume_fis
        call [fopen]
        add esp,4*2
        
        cmp eax,0
        je final
        
        mov [f_dir],eax
        
        push dword [f_dir]
        push dword len
        push dword 1
        push dword text
        call [fread]
        
        mov ecx,eax
        mov esi,text
        
        mov eax,0
        push eax
        repeta2:
            ;inc esi
            mov edi,propozitie
            mov ebx,0
        repeta:
            cmp ebx,0
            jne mai_departe
            cuvant1:
                inc ebx
                mov al,[esi]
                mov[edi],al
                dec ecx
                inc edi
                inc esi
                cmp al,' '
                jne cuvant1
                
            mov edx,ebx
            dec edx
            dec esi
            dec esi
            push edi
            mov edi,cuv
            invers:
                mov al,[esi]
                mov [edi],al
                inc edi
                dec esi
                dec edx
                cmp edx,0
                jne invers
            pop edi
            inc ebx
            inc ecx
            add esi,ebx 
            sub ebx,2
            mov edx,1    
            mai_departe:
            mov al,[esi]
            dec ecx
            inc esi
            mov [edi],al
            inc edi
            cmp al,' '
            jne not_cuv
            inc edx
            not_cuv:
            cmp al,'.'
            jne prop
            
            
                inc edx
                pop eax
                inc eax
                push dword ebx
                push dword cuv
                push dword edx
                push dword propozitie
                push eax
                push dword msj
                call [printf]
                add esp,4*7
                cmp ecx,0
                inc esi
                jg repeta2
           prop:
           cmp ecx,0
           
           jg repeta
                
            
        final:
        push    dword 0      ; push the parameter for exit onto the stack
        call    [exit]       ; call exit to terminate the program

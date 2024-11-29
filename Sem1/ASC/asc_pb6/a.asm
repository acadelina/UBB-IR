bits 32 ; assembling for the 32 bits architecture

; declare the EntryPoint (a label defining the very first instruction of the program)
global start        

; declare external functions needed by our program
extern exit,printf    
extern suma           ; tell nasm that exit exists even if we won't be defining it
import exit msvcrt.dll
import printf msvcrt.dll    ; exit is a function that ends the calling process. It is defined in msvcrt.dll
                          ; msvcrt.dll contains exit, printf and all the other important C-runtime specific functions

; our data is declared here (the variables needed by our program)
segment data use32 class=data
    sir dd -1,123456,0xabcdeff,0xabcdeff,0xcbcdeff,0xdbcdeff,0111010101b
    len1 equ ($-sir)/4
    rez times len1 db 0
    msj db "0x%x, ",0
    af db "%u ",0
    final dd 0
    par1 db "(",0
    par2 db ")",0

; our code starts here
segment code use32 class=code
    start:
        push dword len1
        push dword rez
        push dword sir
        call suma
        
        mov ecx,len1
        mov esi,rez
        repeta:
            push ecx
            mov eax,0
            lodsb
            push eax
            push dword af
            call [printf]
            add esp,4*2
            pop ecx
            dec ecx
            jnz repeta
        
       mov esi,rez
       mov edi,rez
       mov dword[final],edi
       add dword[final],len1
       sub dword[final],1
       repeta1:
            cmp edi,[final]
            je gata
            mov al,[edi]
            mov bl,[edi+1]
            cmp al,bl
            jnb not_cresc
            inc edi
            jmp repeta1
            not_cresc:
                cmp edi,esi
                jne afisare
                add edi,1
                mov esi,edi
                cmp edi,[final]
                jl repeta1
            gata:
                cmp esi,edi
                je fina
            afisare:
                push dword par1
                call [printf]
                add esp,4
                push esi
                push edi
                mov ecx,esi
                sub ecx,rez
                
                aff:
                
                push ecx
                push dword[sir+4*ecx]
                push dword msj
                call[printf]
                add esp,8
                pop ecx
                inc ecx
                inc esi
                cmp esi,edi
                jle aff
                push dword par2
                call [printf]
                add esp,4
                pop edi
                mov esi,edi
                cmp edi,[final]
                jl repeta1
            
         fina:   
            
            
        
        push    dword 0      ; push the parameter for exit onto the stack
        call    [exit]       ; call exit to terminate the program

;Se dau cuvintele A si B. Sa se obtina dublucuvantul C:
;bitii 0-2 ai lui C coincid cu bitii 12-14 ai lui A
;bitii 3-8 ai lui C coincid cu bitii 0-5 ai lui B
;bitii 9-15 ai lui C coincid cu bitii 3-9 ai lui A
;bitii 16-31 ai lui C coincid cu bitii lui A

bits 32 ; assembling for the 32 bits architecture

; declare the EntryPoint (a label defining the very first instruction of the program)
global start        

; declare external functions needed by our program
extern exit               ; tell nasm that exit exists even if we won't be defining it
import exit msvcrt.dll    ; exit is a function that ends the calling process. It is defined in msvcrt.dll
                          ; msvcrt.dll contains exit, printf and all the other important C-runtime specific functions

; our data is declared here (the variables needed by our program)
segment data use32 class=data
   a dw 0111011101010111b
   b dw 1001101110111110b
   c dd 0

; our code starts here
segment code use32 class=code
    start:
    mov bx, 0
    mov cx, 0 ;registrele in care vom calcula rezultatele
    mov ax, [a]; ax=a
    and ax, 0011100000000000b;izolam bitii 12-14
    mov cl, 11
    ror ax, cl; rotim cu 11 pozitii spre dreapta
    or bx,ax;punem rezultatul in bx
    mov ax, [b]; ax=b
    and ax, 0000000000111111b; izolam bitii 0-5
    mov cl, 3
    rol ax,cl;rotim bitii spre stanga cu 3 pozitii
    or bx,ax; punem rezultatul in bx
    mov ax, [a];ax=a
    and ax, 0000111111111000b;izolam bitii 3-9
    mov cl, 6
    rol ax,cl;rotim spre stanga cu 6 pozitii
    or bx, ax;punem rezultatul in bx
    mov ax,[a];ax=a
    or cx,ax; punem rezultatul in cx
    mov [c],cx
    mov [c+2],bx; punem valorile din registrii in variabila rezultat
    
    
    push    dword 0      ; push the parameter for exit onto the stack
    call    [exit]       ; call exit to terminate the program

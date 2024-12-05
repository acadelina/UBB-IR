;Se dau cuvintele A, B si C. Sa se obtina octetul D ca suma a numerelor reprezentate de:
;biţii de pe poziţiile 0-4 ai lui A
;biţii de pe poziţiile 5-9 ai lui B
;Octetul E este numarul reprezentat de bitii 10-14 ai lui C. Sa se obtina octetul F ca rezultatul scaderii D-E.

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
    c dw 1000001110110110b
    d db 0
    e db 0
    f db 0

; our code starts here
segment code use32 class=code
    start:
    mov ax,[a]
    and ax,0000000000011111b;izolam bitii 0-4 ai lui a
    mov byte[d],al;punem bitii in rezultat
    mov ax,[b]; punem b in ax
    mov cl,5
    shr ax,cl; siftam cu 5 pozitii spre stanga
    and ax, 0000000000011111b; izolam bitii 0-4
    mov bl,al; mutam rezultatul in bl
    mov al,[d];mutam rezultatul din d in al
    add al,bl; adunam bitii extrasi din a cu cei extrasi din b
    mov byte[d],al;mutam rezultatul in d
    mov ax,[c];mutam c in ax
    mov cl,10
    shr ax,cl;siftam cu 10 pozitii spre dreapta
    and ax,0000000000011111b; izolam bitii 0-4
    mov byte[e],al; punem rezultatul in e
    mov al,[d];al=d
    mov bl,[e];bl=e
    sub al,bl;scadem din bitii lui d bitii lui e
    mov byte[f],al;punem rezultatul in f
        
    push    dword 0      ; push the parameter for exit onto the stack
    call    [exit]       ; call exit to terminate the program

;Se da dublucuvantul A. Sa se obtina numarul intreg n reprezentat de bitii 14-17 ai lui A. Sa se obtina apoi in B dublucuvantul rezultat prin rotirea spre stanga a lui A cu n pozitii. Sa se obtina apoi octet C astfel:
;bitii 0-5 ai lui C coincid cu bitii 1-6 ai lui B
;bitii 6-7 ai lui C coincid cu bitii 17-18 ai lui B

bits 32 ; assembling for the 32 bits architecture

; declare the EntryPoint (a label defining the very first instruction of the program)
global start        

; declare external functions needed by our program
extern exit               ; tell nasm that exit exists even if we won't be defining it
import exit msvcrt.dll    ; exit is a function that ends the calling process. It is defined in msvcrt.dll
                          ; msvcrt.dll contains exit, printf and all the other important C-runtime specific functions

; our data is declared here (the variables needed by our program)
segment data use32 class=data
   a dd 01110111010101110111011101010111b
   b dd 0
   c db 0

; our code starts here
segment code use32 class=code
    start:
        mov eax, dword[a];eax=a
        mov cl,14
        shr eax,cl; siftam bitii din eax cu 14 pozitii spre dreapta
        and eax, 00000000000000000000000000001111b; izolam bitii de pe pozitiile 28-31
        mov cl,al; mutam rezutatul in cl
        mov eax, dword[a]; eax=a
        rol eax, cl; rotim spre stanga cu cl pozitii
        mov dword[b], eax; punem rezultatul in b
        and eax, 00000000000000000000000001111110b;izolam bitii 1-6
        mov cl,1
        shr eax,cl; siftam cu o pozitie spre dreapta
        mov bl,al; punem rezultatul in bl
        mov eax, dword[b]
        and eax, 00000000000001100000000000000000b;izolam bitii 17-18
        mov cl,11
        shr eax,cl;siftam cu 11 pozitii spre dreapta
        or  bl,al;imbinam rezultatele
        mov byte [c], bl; punem rezultatul in c
        
     push    dword 0      ; push the parameter for exit onto the stack
     call    [exit]       ; call exit to terminate the program

;3.Se dau doua siruri de octeti S1 si S2. Sa se construiasca sirul D prin concatenarea elementelor din sirul S1 1uate de la stanga spre dreapta si a elementelor din sirul S2 luate de la dreapta spre stanga.

bits 32 ; assembling for the 32 bits architecture

; declare the EntryPoint (a label defining the very first instruction of the program)
global start        

; declare external functions needed by our program
extern exit               ; tell nasm that exit exists even if we won't be defining it
import exit msvcrt.dll    ; exit is a function that ends the calling process. It is defined in msvcrt.dll
                          ; msvcrt.dll contains exit, printf and all the other important C-runtime specific functions

; our data is declared here (the variables needed by our program)
segment data use32 class=data
    s1 db 1,2,3,4
    l1 equ $-s1; stabilim lungimea sirului s1
    s2 db 5,6,7
    l2 equ $-s2;stabilim lungimea sirului s2
    l equ $-s1; stabilim suma lungimilor sirurilor
    d times l db 0; rezervarea unu spatiu de dimensiune l pentru sirul destinatie

; our code starts here
segment code use32 class=code
    start:
        mov ecx, l1; punem in ecx lungimea primului sir pentru a putea realiza bucla loop de ecx ori
        mov esi,0; esi=0
        jecxz Sfarsit1
        Repeta1:
                mov al,[s1+esi]; punem in al elementul de pe pozitia esi din sirul s1
                mov [d+esi],al; punem pe pozitia esi din sirul d al
                inc esi; incrementam valoarea lui esi
        loop Repeta1
        Sfarsit1:; terminarea primei bucle
        
        mov ecx, l2; punem in ecx lungimea celui de-al doilea  sir pentru a putea realiza bucla loop de ecx ori
        mov edi, l2-1; setam edi pe indicele ultimului element din sir
        jecxz Sfarsit
        Repeta:
                mov al,[s2+edi];punem in al elementul de pe pozitia edi din sirul s2
                mov [d+esi],al; punem pe pozitia esi elemeuntul din al
                inc esi; encrementam valoarea lui esi
                dec edi;decrementam valoarea lui edi
        loop Repeta
        Sfarsit:; terminarea celei de-a doua bucle si a programului
                
        push    dword 0      ; push the parameter for exit onto the stack
        call    [exit]       ; call exit to terminate the program

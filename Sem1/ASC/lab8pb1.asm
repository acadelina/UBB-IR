;Se dau doua numere naturale a si b (a, b: dword, definite in segmentul de date). Sa se calculeze suma lor si sa se afiseze in urmatorul format: "<a> + <b> = <result>"
;Exemplu: "1 + 2 = 3"
;Valorile vor fi afisate in format decimal (baza 10) cu semn.
bits 32 ; assembling for the 32 bits architecture

; declare the EntryPoint (a label defining the very first instruction of the program)
global start        

; declare external functions needed by our program
extern exit,printf,scanf               ; tell nasm that exit exists even if we won't be defining it
import exit msvcrt.dll  
import printf msvcrt.dll
import scanf msvcrt.dll  ; exit is a function that ends the calling process. It is defined in msvcrt.dll
                          ; msvcrt.dll contains exit, printf and all the other important C-runtime specific functions

; our data is declared here (the variables needed by our program)
segment data use32 class=data
    a dd 0
    b dd 0
    m1 db "< %d >+< %d >=< %d >",0
    f1 db "%d",0
    f2 db "%d",0
    

; our code starts here
segment code use32 class=code
    start:
        ; vom apela scanf(f1,a)
        push dword a; punem offsetul lui a pe stiva
        push dword f1; punem offsetul lui f1 pe stiva
        call [scanf];apelam functia scanf pt citire
        add esp, 4*2; eliberam parametrii de pe stiva
        ; convertim a la dword pentru a pune valoarea pe stiva
        mov ebx,0
        mov bx,[a]
        ;vom apela scanf(f1,b)
        push dword b
        push dword f1
        call [scanf]
        add esp, 4*2;analog cu prima citire
        mov eax,0
        mov ax,[b];punem b in eax si il convertim la dword
        mov ecx,eax
        add ecx,ebx;facem suma a+b in ecx
        ; vom apela printf
        push ecx;punem ecx=a+b pe stiva
        push eax;punem eax=b pe stiva
        push ebx;punem ebx=a pe stiva
        push dword m1;punem m1 pe stiva
        call [printf];apelam functia printf
        add esp, 4*4; eliberam parametrii de pe stiva
        push    dword 0      ; push the parameter for exit onto the stack
        call    [exit]       ; call exit to terminate the program

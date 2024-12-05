;5.Se da un sir de caractere S. Sa se construiasca sirul D care sa contina toate literele mici din sirul S.
bits 32 ; assembling for the 32 bits architecture

; declare the EntryPoint (a label defining the very first instruction of the program)
global start        

; declare external functions needed by our program
extern exit               ; tell nasm that exit exists even if we won't be defining it
import exit msvcrt.dll    ; exit is a function that ends the calling process. It is defined in msvcrt.dll
                          ; msvcrt.dll contains exit, printf and all the other important C-runtime specific functions

; our data is declared here (the variables needed by our program)
segment data use32 class=data
   S db 'a','A','b','B','2','%','x'
   l equ $-S; stabilim lungimea sirului S
   d times l db 0; rezervam un spatiu de dimensiunea l pentru sirul destinatie
; our code starts here
segment code use32 class=code
    start:
        mov ecx,l;punem lungimea sirului in ecx pentru a putea realiza bucla loop de ecx ori
        mov esi,0
        mov edi,0
        jecxz Sfarsit
        Repeta:
            mov al,[S+esi]; mutam in al elementul de pe pozitia esi a sirului S
            mov bl,'a'
            cmp al,bl; compararea lui al cu 'a'
            jl not_lowercase; in cazul in care al<'a' programul sare la eticheta "not_lowercase"
            mov bl,'z'
            cmp al,bl; compararea lui al cu 'z'
            jg not_lowercase; in cazul in care al>'z' programul sare la eticheta "not_lowercase"
            
            mov [d+edi],al; daca al este cuprins intre 'a' si 'z' acesta este pus in sirul destinatie
            inc edi; incrementarea lui edi
           not_lowercase:
            inc esi;incrementarea lui esi
         loop Repeta
        Sfarsit:;terminarea programului    
        push    dword 0      ; push the parameter for exit onto the stack
        call    [exit]       ; call exit to terminate the program

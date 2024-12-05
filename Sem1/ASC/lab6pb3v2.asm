;Se da un sir de 3 dublucuvinte, fiecare dublucuvant continand 2 valori pe cuvant (despachetate, deci fiecare cifra hexa e precedata de un 0). Sa se creeze un sir de octeti care sa contina acele valori (impachetate deci pe un singur octet), ordonate crescator in memorie, acestea fiind considerate numere cu semn.
bits 32 ; assembling for the 32 bits architecture

; declare the EntryPoint (a label defining the very first instruction of the program)
global start        

; declare external functions needed by our program
extern exit               ; tell nasm that exit exists even if we won't be defining it
import exit msvcrt.dll    ; exit is a function that ends the calling process. It is defined in msvcrt.dll
                          ; msvcrt.dll contains exit, printf and all the other important C-runtime specific functions

; our data is declared here (the variables needed by our program)
segment data use32 class=data
    sir dd 0702090Ah, 0B0C0304h, 05060108h
    l equ ($-sir)/2
    d1 times l db 0
; our code starts here
segment code use32 class=code
    start:
        mov ecx, l;ecx=numarul de cuvinte ale sirului
        mov esi, 0;esi=0
        mov edi, 0;edi=0
        repeta:
            mov bx,[sir+esi];bx=elementul curent din sir
            inc esi;incrementarea lui esi
            mov ax,[sir+esi];ax= urmatorul element din sir
            
            shl ax, 4;siftarea bitiilor di ax cu patru pozitii spre stanga 
            or al,bl;alaturam cei doi octeti
            mov [d1+edi],al; mutam in sirul destinatie rezultatul obtinut
            inc edi;incrementarea lui edi
            inc esi;incrementarea lui esi
        loop repeta
    mov ebx,l-1; ebx=l-1
    mov ecx,l-1;ecx=l-1
    mov esi, d1;esi=offset de d1
    mov edi, d1+1;edi=offset de d1+1
    principal:
      push ecx;punem ecx pe stiva
        
     
    
        
        mov ecx,l-1;ecx=l-1
        mov esi, 0;esi=0
        mov edi, d1+1;edi=offset de d1+1
        repeta1:
            mov al,[d1+esi];al = elementul curent al sirului
            mov bl,[d1+esi+1];bl=elementul urmator
            cmp al,bl; comparam cu al cu bl
            jl mai_mic;daca aceste sunt ordonate se sare la eticheta mai_mic
            mov [d1+esi],bl
            mov [d1+esi+1],al;interschimbam valorile din sir
            mai_mic:
            inc esi;incrementarea lui esi
            
      loop repeta1
      
      pop ecx;scoatem ecx de pe stiva
      loop principal
      
            push dword 0 
            call [exit] 
     

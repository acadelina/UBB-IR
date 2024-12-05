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
        mov esi, sir;esi=offset sir
        mov edi,d1; edi=offset d1
        repeta:
            lodsb;al=elementul curent al sirului
            mov bl,al; bl=al
            lodsb;al=elementul urmator
            shl al, 4; shiftam la stanga cu patru pozitii bitii lui al ca sa scapam de 0
            or al,bl;al= valoarea impachetata pe un octet
            stosb; punem al in sirul d1
        loop repeta
    mov ebx,l-1; ebx=lungimea sirului-1
    mov ecx,l-1;ecx=lungimea sirului-1
    mov esi, d1;esi=offset d1
    mov edi, d1+1; edi=offset d1+1
    principal:
      push ecx;punem val ecx pe stiva
        
     
    
        cld; df=0 parcurgerea sirului de la stanga la dreapta
        mov ecx,l-1; ecx=l-1
        mov esi, d1;esi=offset d1
        mov edi, d1+1; edi=offset d1+1
        repeta1:
            lodsb ;al = elementul curent al sirului
            scasb; comparam cu edi, urm element
            jl mai_mic; salt in cazul in care cele doua elemente sunt deja ordonate
            dec edi; decrementarea lui edi
            push esi;punem esi pe stiva
            mov esi, edi; punem in esi offestul aflat in edi
            mov dl, al; dl=al
            lodsb ;al = edi
            push esi;punem esi pe stiva
            dec esi; decrementarea lui esi
            mov [esi],dl; punem elementul dl luat din al la adresa esi
            dec esi;decrementarea lui esi
            mov [esi],al; punem elementul al luat din dl la adresa esi
            pop edi; scoatem edi de pe stiva
            pop esi;scoatem esi de pe stiva
            mai_mic:
            
            
      loop repeta1
      
      pop ecx; scoatem ecx de pe stiva
      loop principal
            push dword 0 
            call [exit] 
    
        
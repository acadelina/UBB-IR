;Se da un fisier text. Sa se citeasca continutul fisierului, sa se contorizeze numarul de cifre pare si sa se afiseze aceasta valoare. Numele fisierului text este definit in segmentul de date.
bits 32
global start

extern exit,fopen,fread,fclose,printf
import exit msvcrt.dll
import fopen msvcrt.dll
import fread msvcrt.dll
import fclose msvcrt.dll
import printf msvcrt.dll

segment data use32 class=data
    nume_fisier db "text.txt", 0
    mod_acces db "r",0
    descriptor_fisier dd -1
    len equ 20
    text times 20 db 0
    format db "Cifre pare:%d",0

segment code use32 class=code
start:
    ;Deschidere fisier- eax=fopen(nume_fisier,mod_acces)
    push dword mod_acces; punem pe stiva mod_acces="r"
    push dword nume_fisier; punem pe stiva nume_fisier
    call [fopen]; apelam functia fopen care ne va pune in eax descriptorul de fisier
    add esp, 4*2;eliberam parametrii de pe stiva

    mov [descriptor_fisier], eax;salvam valoarea din eax in variabila descriptor_fisier

    cmp eax,0; comparam eax cu 0
    je finish; in cazul in care eax e 0 adica fisierul nu a fost creat se efectueaza un salt la finalul programului
    
    ; vom citi textul din fisier cu fread(text,1,len,descriptor_fisier)
    push dword [descriptor_fisier]; pune pe stiva descriptorul
    push dword len; punem pe stiva lungimea len
    push dword 1; punem pe stiva 1
    push dword text ; punem pe stiva text  
    call [fread];apelam functia fread- eax=nr caracterelor din fisier
    add esp, 4*4; eliberam parametrii de pe stiva
    
    mov ebx,0;ebx=0
    mov ecx,eax;ecx=eax=nr de caractere
    mov esi, text;esi=offset de text
    repeta:
        mov al,byte[esi];punem primul caracter din text in al
        cmp al,'0';comparam caracterul cu '0'
        jb notcif; daca acesta este mai mic se efectueaza un salt la eticheta notcif
        cmp al,'9';comparam caracterul cu '9'
        ja notcif; daca acesta este mai mare se efectueaza un salt la eticheta notcif
        shr al,1;siftam bitii lui al spre dreapta cu o pozitie cu scopul de a pastra in cf bitul ce determina paritatea nr
        jb notcif; daca cf=1 se sare la eticheta notcif
        inc ebx; daca cf=0 se incrementeaza ebx
        notcif:
        inc esi;esi=esi+1 trecerea la urmatorul caracter
    loop repeta
    
    ;afisam numarul de cifre pare
    push dword ebx;punem ebx pe stiva
    push dword format; punem format pe stiva
    call [printf];apelam functia pritf
    add esp, 4*2;eliberam parametrii de pe stiva


    finish:
        ;apelam functia fclose(descriptor) pt a inchide fisierul
        push dword [descriptor_fisier];punem descriptorul  pe stiva
        call [fclose];apelam fclose
        add esp, 4;eliberam parametrul de pe stiva
	    push dword 0 
	    call [exit] 
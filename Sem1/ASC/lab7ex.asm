; Ne propunem ca programul de mai jos sa citeasca de la tastatura un numar si sa afiseze pe ecran valoarea numarului citit impreuna cu un mesaj.
bits 32
global start        

; declararea functiilor externe folosite de program
extern exit, printf, scanf  ; adaugam printf si scanf ca functii externe           
import exit msvcrt.dll     
import printf msvcrt.dll     ; indicam asamblorului ca functia printf se gaseste in libraria msvcrt.dll
import scanf msvcrt.dll      ; similar pentru scanf
                          
segment  data use32 class=data
	n db 0,0,0,0      ; in aceasta variabila se va stoca valoarea citita de la tastatura
    m db 0,0,0,0
	message  db "Ana are %d mere si %d pere.", 0  
	format  db "%d %d", 0  ; %d <=> un numar decimal (baza 10)
    
segment  code use32 class=code
    start:
                                               
        ; vom apela scanf(format, n) => se va citi un numar in variabila n
        ; punem parametrii pe stiva de la dreapta la stanga
        push dword m
        push  dword n       ; ! adresa lui n, nu valoarea
        push  dword format
        call  [scanf]      ; apelam functia scanf pentru citire
        
        add  esp, 4 * 3    ; eliberam parametrii de pe stiva; 4 = dimensiunea unui dword; 2 = nr de parametri
        
        
       
        ;convertim n la dword pentru a pune valoarea pe stiva 
        mov  eax,0
        mov  al,[m]
        mov ebx,0
        mov bl,[n]
        ;afisam mesajul si valoarea lui n
        push eax
        push  ebx
        push  dword message 
        call  [printf]
        add  esp,4*3
        
        
        
        ; exit(0)
        push  dword 0     ; punem pe stiva parametrul pentru exit
        call  [exit]       ; apelam exit pentru a incheia programul
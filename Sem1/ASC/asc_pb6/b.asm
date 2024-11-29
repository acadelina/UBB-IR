bits 32
segment code use32 public code
global suma
hex dd 16
suma:
    mov esi,[esp+4]
    mov edi,[esp+8]
    mov ecx,[esp+12]
    repeta:
        lodsd
        mov ebx,0
        suma1:
            mov edx,0
            div dword[hex]
            add bl,dl
            cmp eax,0
            jne suma1
        mov al,bl
        stosb
        dec ecx
        jnz repeta
    ret 4
    
bits 32
segment code use32 public code
global vocale

vocale:
    mov esi,[esp+4]
    mov ebx,0
    lodsb
    lodsb
    cmp al,0
    je final
    repeta:
        cmp al,'a'
        je vocala
        cmp al,'e'
        je vocala
        cmp al,'i'
        je vocala
        cmp al,'o'
        je vocala
        cmp al,'u'
        je vocala
        jmp not_voc
        vocala:
        inc ebx
        not_voc:
        lodsw
        lodsb
        lodsb
        cmp al,0
        je final
        
    final:
        mov eax,ebx
        ret 4
from Repositories import get_s,get_tip,get_zi

def validare(cheltuiala,lista=None):
    """
    Functie care verifica daca cheltuiala introdusa este valida
    preconditii: cheltuiala: dictionar, lista: lista
    postconditii: False sau True daca este valida
    """
    tipuri=["mancare","intretinere","imbracaminte","telefon","altele"]
    tip=get_tip(cheltuiala).lower()
    s=get_s(cheltuiala)
    zi=get_zi(cheltuiala)
    x=31
    try:
        try:
            s= int(s)
        except ValueError:
            print("Suma nu a fost un numar valid")
            raise ValueError
        if lista is not None:
            for i in lista:
                if i[1]==zi and i[2]==tip:
                    print("Cheltuiala deja existenta. Incearca actualizarea ei.")
                    raise ValueError
        try:
            zi=int(zi)
        except ValueError:
            print("Ziua nu a fost un numar valid")
            raise ValueError
        
        if zi>x or zi<1:
            print("Ziua a fost un numar mai mare decat 31")
            raise ValueError
        ok=0
        for i in range(5):
            if tip==tipuri[i]:
                ok=1
        if(ok==0):
            print("Tipul de cheltuiala nu a fost valid")
            raise ValueError
    except ValueError:
        return False
    else:
        return True
    
def validarezi(zi):
    """
    Functie care verifica daca valoarea introdusa pentru zi este un numar cuprins intre 0 si 32
    preconditii: zi: int
    postconditii: False sau True daca a este o valoare valida
    """
    try:
        try:
            zi=int(zi)
        except ValueError:
            print("Numarul introdus pentru zi trebuie sa fie intreg")
            raise ValueError
        if(zi>31 or zi<1):
            print("Numarul introdus pentr zi trebuie sa fie mai mic decat 32 si mai mare decat 0")
            raise ValueError
    except ValueError:
        return False
    else:
        return True

def validaresum(a):
    """
    Functie care verifica daca valoarea introdusa pentru suma este un numar intreg
    preconditii: a: int
    postconditii: False sau True daca a este o valoare valida
    """
    try:
        try:
            a=int(a)
        except ValueError:
            print("Suma nu a fost un numar valid")
            raise ValueError
    except ValueError:
        return False
    else:
        return True

def validaretip(a):
    """
    Functie care verifica daca valoarea introdusa pentru tip este de tip string si face parte din tipurile posibile
    preconditii: a: string
    postconditii: False sau True daca a este valida
    """
    tipuri=["mancare","intretinere","imbracaminte","telefon","altele"]
    a=a.lower()
    try:
        ok=0
        for i in range(5):
            if a==tipuri[i]:
                ok=1
        if(ok==0):
            print("Tipul de cheltuiala nu a fost valid")
            raise ValueError
    except ValueError:
        return False
    else:
        return True    
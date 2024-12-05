

def afisare_cheltuieli(lista):
    print("AFISARE CHELTUIELI:")
    if type(lista)==list:
        for i in range(len(lista)):
            cheltuiala=lista[i]
            s=cheltuiala['s']
            zi=cheltuiala['zi']
            tip=cheltuiala['tip']
            print(i,". Suma ",s," din ziua ",zi," de tip ",tip)
    else:
        print("Nu exista cheltuieli")


def validare(cheltuiala,lista=None):
    tipuri=["mancare","intretinere","imbracaminte","telefon","altele"]
    x=31
    try:
        try:
            int(cheltuiala['s'])
        except ValueError:
            raise ValueError('Suma nu a fost un numar valid')
        if lista is not None:
            for i in lista:
                if i['zi']==cheltuiala['zi'] and i['tip']==cheltuiala['tip']:
                    raise ValueError('Cheltuiala deja existenta. Incearca actualizarea ei.')
        try:
            cheltuiala['zi']==int(cheltuiala['zi'])
        except ValueError:
            raise ValueError('Ziua nu a fost un numar valid')
        
        if  cheltuiala['zi']> x :
            raise ValueError('Ziua a fost un numar mai mare decat 31')
        ok=0
        for i in range(5):
            if cheltuiala['tip']==tipuri[i]:
                ok=1
        if(ok==0):
            raise ValueError('Tipul de cheltuiala nu a fost valid')
    except ValueError:
        return False
    else:
        return True

def verificare_cheltuiala(lista,cheltuiala):
    if validare(cheltuiala,lista):
        lista.append(cheltuiala)
    else:
        print("Invalid Input")

def creare_cheltuiala(lista):
    """
    citirea unei sume, a zilei curente si a tipului de suma
    """
    s=int(input("Dati suma cheltuielii:"))
    zi=int(input("Dati ziua cheltuielii:"))

    tip=input("Dati tipul de cheltuiala:").lower()
    cheltuiala={'s':s,
                'zi':zi,
                'tip':tip}
    verificare_cheltuiala(lista,cheltuiala)

def verificare_actualizare(lista,cheltuiala):
    try:
        ok=0
        if(validare(cheltuiala)):
            for i in range(len(lista)):
                if lista[i]['zi']==cheltuiala['zi'] and lista[i]['tip']==cheltuiala['tip']:
                    ok=1
                    lista[i]=cheltuiala
            if ok==0:
                raise ValueError("Cheltuiala invalida")
        else:
            raise ValueError("Invalid Input")
    except ValueError:
        return False
    else:
        return True
    

def actualizare_cheltuiala(lista):
    s=int(input("Dati suma cheltuielii:"))
    zi=int(input("Dati ziua cheltuielii:"))
    tip=input("Dati tipul de cheltuiala:").lower()
    cheltuiala={'s':s,
                'zi':zi,
                'tip':tip}
    verificare_actualizare(lista,cheltuiala)

def validarezi(a):
    try:
        try:
            int(a)
        except ValueError:
            raise ValueError("Numarul introdus pentru zi trebuie sa fie intreg")
        if(a>31):
            raise ValueError("Numarul introdus pentr zi trebuie sa fie mai mic decat 32")
    except ValueError:
        return False
    else:
        return True

def validaresum(a):
    try:
        try:
            int(a)
        except ValueError:
            raise ValueError("Suma nu a fost un numar valid")
    except ValueError:
        return False
    else:
        return True

def meniusterge_zi(lista):
    n=int(input("Introduceti ziua a caror cheltuieli vreti sa le stergeti:"))
    if(validarezi(n)):
        v=[]
        for i in range(len(lista)):
            if lista[i]['zi']==n:
                v.append(i)
        for i in range(len(v)):
            del lista[v[i]-i]
    else :
        print("Invalid Input")
    
def meniusterge_interval(lista):
    a=int(input("Introduceti ziua de inceput a intervalului"))
    b=int(input("Introduceti ziua de sfarsit a intervalului"))
    if(validarezi(a) and validarezi(b)):
        v=[]
        for i in range(len(lista)):
            if lista[i]['zi']>=a and lista[i]['zi']<=b:
                v.append(i)
        for i in range(len(v)):
            del lista[v[i]-i]
    else:
        print("Invalid Input")

def validaretip(a):
    tipuri=["mancare","intretinere","imbracaminte","telefon","altele"]
    try:
        ok=0
        for i in range(5):
            if a==tipuri[i]:
                ok=1
        if(ok==0):
            raise ValueError("Tipul de cheltuiala nu a fost valid")
    except ValueError:
        return False
    else:
        return True    

def meniusterge_tip(lista):
    a=str(input("Introduceti tipul cheltuielilor pe care vreti sa le eliminati: ")).lower
    if(validaretip(a)):
        v=[]
        for i in range(len(lista)):
            if lista[i]['tip']==a :
                v.append(i)
        for i in range(len(v)):
            del lista[v[i]-i]
    else:
        print("Invalid Input")



def meniucautari_suma(lista):
    a=int(input("Introduceti suma:"))
    if(validaresum(a)):
        ok=0
        for i in range(len(lista)):
            if lista[i]['s']>a:
                ok=1
        if(ok==1):
            print("CHELTUIELILE MAI MARI DECAT ",a,": ")
            for i in range(len(lista)):
                 if lista[i]['s']>a:
                    cheltuiala=lista[i]
                    s=cheltuiala['s']
                    zi=cheltuiala['zi']
                    tip=cheltuiala['tip']
                    print(i,". Suma ",s," din ziua ",zi," de tip ",tip)
        else:
            print("Nu exista cheltuieli mai mari decat ",a)
    else :
        print("Invalid Input")

def meniurap_sumtip(lista):
    a=str(input("Introduceti tipul de cheltuiala:"))
    if(validaretip(a)):
        s=0
        for i in range(len(lista)):
            if lista[i]['tip']==a:
                s+=lista[i]['s']
        if(s>0):
            print("Suma totala a cheltuielilor de tip ",a," este: ",s)
        else :
            print("Nu exista cheltuieli de acest tip")
    else :
        print("Invalid Input")

def meniufiltr_tip(lista):
    a=str(input("Introduceti tipul de cheltuiala: ")).lower
    if(validaretip(a)):
        v=[]
        for i in range(len(lista)):
            if lista[i]['tip']==a :
                v.append(i)
        for i in range(len(v)):
            del lista[v[i]-i]
    else :
        print("Invalid Input")



def printmeniu_principal():
    print("1. Adauga cheltuiala")
    print("2. Stergeri")
    print("3. Cautari")
    print("4. Rapoarte")
    print("5. Filtrare")
    #print("6. Undo")
    print("0. Iesire din aplicatie")

def printmeniu_cheltuieli():
    print("1. Adauga o noua cheltuiala")
    print("2. Actualizeaza cheltuiala")
    print("0. Iesire")

def printmeniu_stergeri():
    print("1. Sterge toate cheltuielile pentru ziua data")
    print("2. Sterge cheltuielile pentru un interval de timp(ziua de inceput-ziua de sfarsit)")
    print("3. Sterge toate cheltuielile de un anumit tip")
    print("0. Iesire")

def printmeniu_cautari():
    print("1. Tipareste toate cheltuielile mai mari decat o suma data")
    print("0. Iesire")

def printmeniu_rapoarte():
    print("1. Tipareswte suma totala pentru un anumit tip de cheltuiala")
    print("0. Iesire")

def printmeniu_filtrare():
    print("1. Elimina toate cheltuielile de un anumit tip")
    print("0. Iesire")

def meniu_cheltuieli(lista):
    """Meniul care creeaza cheltuielile
       lista-lista de cheltuieli"""
    printmeniu_cheltuieli()
    a=int(input())
    while a!=0:
        if a==1:
            creare_cheltuiala(lista)
            afisare_cheltuieli(lista)
        elif a==2:
            actualizare_cheltuiala(lista)
            afisare_cheltuieli(lista)
        else:
            print("Comanda invalida")
        printmeniu_cheltuieli()
        a=int(input())
    return lista

def meniu_stergeri(lista):
    printmeniu_stergeri()
    a=int(input())
    while a!=0:
        if a==1:
            meniusterge_zi(lista)
            afisare_cheltuieli(lista)
        elif a==2:
            meniusterge_interval(lista)
            afisare_cheltuieli(lista)
        elif a==3:
            meniusterge_tip(lista)
            afisare_cheltuieli(lista)
        else:
            print("Comanda invalida")
        printmeniu_stergeri()
        a=int(input())
    return lista

def meniu_cautari(lista):
    printmeniu_cautari()
    a=int(input())
    while a!=0:
        if a==1:
            meniucautari_suma(lista)
            afisare_cheltuieli(lista)
        else:
            print("Comanda invalida")
        printmeniu_cautari()
        a=int(input())
    return lista

def meniu_rapoarte(lista):
    printmeniu_rapoarte()
    a=int(input())
    while a!=0:
        if a==1:
            meniurap_sumtip(lista)
            afisare_cheltuieli(lista)
        else:
            print("Comanda invalida")
        printmeniu_rapoarte()
        a=int(input())
    return lista        

def meniu_filtrare(lista):
    printmeniu_filtrare()
    a=int(input())
    while a!=0:
        if a==1:
            meniufiltr_tip(lista)
            afisare_cheltuieli(lista)
        else:
            print("Comanda invalida")
        printmeniu_filtrare()
        a=int(input())
    return lista

def main(lista):
    lista=[]
    printmeniu_principal()
    a=int(input())
    while a!=0:
        if a==1:
            meniu_cheltuieli(lista)
        elif a==2:
            meniu_stergeri(lista)
        elif a==3:
            meniu_cautari(lista)
        elif a==4:
            meniu_rapoarte(lista)
        elif a==5:
            meniu_filtrare(lista)
        else:
            print("Comanda invalida")
        printmeniu_principal()
        a=int(input())
    
def run():
    lista=[]
    main(lista)
run()

def afisare_cheltuieli(lista):
    """
    Functie care afiseaza lista cheltuielilor
    preconditii: lista: de tip lista
    postconditii:
    """
    print("AFISARE CHELTUIELI:")
    if type(lista)==list:
        for i in range(len(lista)):
            cheltuiala=lista[i]
            s=get_s(cheltuiala)
            zi=get_zi(cheltuiala)
            tip=get_tip(cheltuiala)
            print(i,". Suma",s,"din ziua",zi,"de tip",tip)
    else:
        print("Nu exista cheltuieli")


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

def verificare_cheltuiala(lista,cheltuiala):
    """
    Functie care adauga o noua cheltuiala in lista
    preconditii: lista: lista, cheltuiala: dictionar
    postconditii: 
    """
    
    if validare(cheltuiala,lista):
        lista.append(cheltuiala)
    else:
        print("Invalid Input")

def creare_cheltuiala(lista,comenzi):
    """
    citirea unei sume, a zilei curente si a tipului de suma
    preconditii: lista: lista
    postconditii:
    """
    cheltuiala=[]
    cheltuiala.append(input("Dati suma cheltuielii:"))
    cheltuiala.append(input("Dati ziua cheltuielii:"))

    cheltuiala.append(input("Dati tipul de cheltuiala:").lower())
    comenzi.append([1,1,cheltuiala])
               
    verificare_cheltuiala(lista,cheltuiala)

def get_s(cheltuiala):
    """
    Functie care returneaza suma cheltuielii
    preconditii:cheltuiala:lista
    postcomditii: suma
    """
    return int(cheltuiala[0])

def get_zi(cheltuiala):
    """
    Functie care returneaza ziua cheltuielii
    preconditii: cheltuiala:lista
    postconditii: ziua
    """
    return int(cheltuiala[1])

def get_tip(cheltuiala):
    """
    Functie care returneaza tipul cheltuielii
    preconditii: cheltuiala:lista
    postconditii: tipul
    """
    return cheltuiala[2]

def verificare_actualizare(lista,cheltuiala):
    """
    Functie care verifica daca se poate realiza actualizarea si executa actualizarea
    preconditii: lista:lista, cheltuiala: dictionar care urmeaza sa fie actualizat
    postconditii: False sau True daca actualizarea este posibila
    """
    try:
        ok=0
        if(validare(cheltuiala)):
            for i in range(len(lista)):
                if get_zi(lista[i])==get_zi(cheltuiala) and get_tip(lista[i])==get_tip(cheltuiala):
                    ok=1
                    s=get_s(lista[i])
                    lista[i]=cheltuiala
            if ok==0:
                print("Cheltuiala invalida")
                raise ValueError
        else:
            raise ValueError("Invalid Input")
    except ValueError:
        return False
    else:
        return s
    

def actualizare_cheltuiala(lista,comenzi):
    """
    Functie care citeste cheltuiala ce urmeaza sa fie actualizata
    preconditii: lista: lista
    postconditii: 
    """
    cheltuiala=[]
    s=input("Dati suma cheltuielii:")
    zi=input("Dati ziua cheltuielii:")
    tip=input("Dati tipul de cheltuiala:").lower()
    cheltuiala.append(s)
    cheltuiala.append(zi)
    cheltuiala.append(tip)
    sum=verificare_actualizare(lista,cheltuiala)
    comenzi.append([1,2,sum,zi,tip])
    

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


def sterge_cheltuiala(lista,zi=None,a=None,b=None,tip=None):
    """
    Functie care efectueza stergeri
    preconditii: lista: lista
                 zi: int, daca exista se efectueaza stergerea cheltuielilor din acea zi
                 a,b: int, daca exista se efectueaza stergerea cheltuielilor din acel interval
                 tip: str, daca exista se efectueaza stergerea cheltuielilor de acel tip
    postconditii: lista modificata
    """
    if zi != None:
        v=[]
        for i in range(len(lista)):
            if get_zi(lista[i])==zi:
                v.append(i)
        for i in range(len(v)):
            del lista[v[i]-i]
    elif a!=None and b!=None:
        v=[]
        for i in range(len(lista)):
            if get_zi(lista[i])>=a and get_zi(lista[i])<=b:
                v.append(i)
        for i in range(len(v)):
            del lista[v[i]-i]
    elif tip!=None:
        v=[]
        for i in range(len(lista)):
            if get_tip(lista[i])==tip :
                v.append(i)
        for i in range(len(v)):
            del lista[v[i]-i]

    
def sterge(lista,zi,s,tip):
    
    for i in range(len(lista)):
        if get_zi(lista[i])==int(zi) and get_s(lista[i])==int(s) and get_tip(lista[i])==tip:
            v=i
            
    del lista[v]

    
def meniusterge_zi(lista,comenzi):
    """
    Functie care citeste ziua din care se vor sterge cheltuielile si modifica lista
    preconditii: lista: lista
    postconditii: lista modificata
    """
    n=int(input("Introduceti ziua a caror cheltuieli vreti sa le stergeti:"))
    undolist=lista.copy()
    comenzi.append([2,undolist])
    if(validarezi(n)):
       sterge_cheltuiala(lista,n)
    else :
        print("Invalid Input")
    
def meniusterge_interval(lista,comenzi):
    """
    Functie care citeste intervalul din care se vor sterge cheltuielile si modifica lista
    preconditii: lista: lista
    postconditii: lista modificata
    """
    a=int(input("Introduceti ziua de inceput a intervalului"))
    b=int(input("Introduceti ziua de sfarsit a intervalului"))
    undolist=lista.copy()
    comenzi.append([2,undolist])
    if(validarezi(a) and validarezi(b)):
        sterge_cheltuiala(lista,None,a,b)
    else:
        print("Invalid Input")

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

def meniusterge_tip(lista,comenzi):
    """
    Functia care citeste tipul cheltuielilor ce urmeaza sa fie sterse si modifica lista
    preconditii: lista: lista
    postconditii: lista modificata
    """
    a=input("Introduceti tipul cheltuielilor pe care vreti sa le eliminati:").lower()
    undolist=lista.copy()
    
    comenzi.append([2,undolist])
    print (comenzi)
    if(validaretip(a)):
        sterge_cheltuiala(lista,None,None,None,a)
    else:
        print("Invalid Input")


def cautari_suma(lista,s):
    """
    Functie care verifica daca exista suma mai mare decat cea data
    preconditii: lista: lista, s: int
    postconditii: False sau True daca exista suma mai mare
    """
    ok=0
    for i in range(len(lista)):
         if get_s(lista[i])>s:
                ok=1
    if(ok==1):
        return True
    else:
       
        return False

def creeaza_cautari_suma(lista,a):
    """
    Functie care creeaza o lista cu cheltuielile cu suma mai mare decat cea data
    preconditii: lista: lista, a: int
    postconditii: v:lista
    """
    v=[]
    for i in range(len(lista)):
        if get_s(lista[i])>a:
            v.append(lista[i])
    return (v)

def meniucautari_suma(lista):
    """
    Functie care citeste suma pentru afisare cheltuielilor mai mari decat ea
    preconditii: lista: lista
    postconditii: cheltuielile mai mari decat suma
    """
    a=int(input("Introduceti suma: "))
    if validaresum(a):
        if cautari_suma(lista,a):
            l=creeaza_cautari_suma(lista,a)
            afisare_cheltuieli(l)

        else:
           print("Nu exista cheltuieli mai mari decat ",a)
    else :
        print("Invalid Input")

def cautare_zisum(lista,zi,s):
     """
    Functie care creeaza o lista cu cheltuielile cu suma mai mica decat cea data si efectuate inainte de ziua data
    preconditii: lista: lista, zi: int, s: int
    postconditii: v:lista
    """
     v=[]
     for i in range(len(lista)):
        if get_s(lista[i])<s and get_zi(lista[i])<zi:
             v.append(lista[i])
     return (v)

def meniucautare_zisum(lista):
    """
    Functie care cisteste ziua si suma pentru afisarea cheltuielilor
    preconditii: lista: lista
    postconditii: afisarea cheltuielilor efectuate inainte de ziua data si cu suma mai mica decat cea data
    """
    a=int(input("Introduceti ziua: "))
    b=int(input("Introduceti suma: "))
    if validaresum(b) and validarezi(a):
        l=cautare_zisum(lista,a,b)
        if len(l)>0:
            afisare_cheltuieli(l)
        else:
            print("Nu exista cheltuieli efectuate inainte de ziua",a,"si cu suma mai mica decat",b)
    else:
        print("Invalid Input")

def cautare_tip(lista,a):
    """
    Functie care creaza o lista cu cheltuielile de tipul dat
    preconditii: lista: lista, a: str
    postconditii: v:lista
    """
    v=[]
    for i in range(len(lista)):
        if get_tip(lista[i])==a:
            v.append(lista[i])
    return (v)

def meniucautare_tip(lista):
    """
    Functie care citeste tipul chletuielilor care vor fi afisate
    preconditii:lista: lista
    postconditii: afisarea cheltuielilor de tipul dat
    """
    a=input("Introduceti tipul:").lower()
    if validaretip(a):
        l=cautare_tip(lista,a)
        if len(l)>0:
            afisare_cheltuieli(l)
        else:
            print("Nu exista cheltuieli de tipul:",a)
    else:
        print("Invalid Input")

def sumtip(lista,a):
    """
    Functie care calculeaza suma cheltuielilor de un anumit tip
    preconditii: lista: lista, a:str
    postconditii: s: suma
    """
    s=0
    for i in range(len(lista)):
        if get_tip(lista[i])==a:
            s+=get_s(lista[i])
    return s

def meniurap_sumtip(lista):
    """
    Functie care citeste tipul de cheltuiala a carei sume o va afisa
    preconditii: lista: lista
    postconditii: suma
    """
    a=input("Introduceti tipul de cheltuiala: ").lower()
    if(validaretip(a)):
        s=sumtip(lista,a)
        if(s>0):
            print("Suma totala a cheltuielilor de tip ",a," este: ",s)
        else :
            print("Nu exista cheltuieli de acest tip")
    else :
        print("Invalid Input")

def summax(lista):
    """
    Functie care cauta cheltuiala de suma maxima
    preconditii: lista: lista
    postconditii: d['zi']:int, ziua in care suma este maxima
    """
    max=0
    for i in range (len(lista)):
        if get_s(lista[i])>max:
            max=get_s(lista[i])
            d=lista[i]
    return (get_zi(d))

def meniurap_summax(lista):
    """
    Functie care afiseaza ziua in care cheltuiala este maxima
    preconditii: lista: lista
    postconditii: afisarea zilei
    """
    if len(lista)>0:
        d=summax(lista)
        print ("Ziua in care suma este maxima:",d)
    else:
        print("Lista este nula")

def rap_sum(lista,a):
    """
    Functie care creeaza o lista cu cheltuielile care au suma data
    preconditii: lista:lista, a:int
    postconditii: v:lista
    """
    v=[]
    for i in range(len(lista)):
        if lista[i][0]==a:
            v.append(lista[i])
    return (v)

def meniurap_sum(lista):
    """
    Functie care citeste suma a caror cheltuilei vor fi afisate
    preconditii: lista:lista
    postconditii: afisarea cheltuielilor
    """
    a=int(input("Dati suma: "))
    if validaresum(a):
        l=rap_sum(lista,a)
        if len(l)>0:
            afisare_cheltuieli(l)
        else:
            print("Nu exista cheltuieli cu suma ",a)
    else:
        print("Invalid Input")

def meniurap_tip(lista):
    """
    Functie care afiseaza cheltuielile sortate dupa tip
    preconditii: lista
    postconditii:
    """
    t=["mancare","intretinere","imbracaminte","telefon","altele"]
    for i in range(5):
        v=cautare_tip(lista,t[i])
        if len(v)>0:
            print(t[i].upper( ))
            afisare_cheltuieli(v)
        

def filtr_sum(lista,sum):
    """
    Functie care elimina din lista cheltuielile mai mici decat suma data
    preconditii: lista:lista
    postconditii: lista modificata
    """
    v=[]
    for i in range(len(lista)):
        if get_s(lista[i])<sum:
            v.append(i)
    for i in range(len(v)):
            del lista[v[i]-i]
    return lista
    
def meniu_undo(lista,comenzi):
    
    if len(comenzi)>0:
        comanda=comenzi.pop()
        
        if comanda[0]==1:
            
            
            if comanda[1]==1:
                cheltuiala=comanda[2].copy()
                sterge(lista,cheltuiala[1],cheltuiala[0],cheltuiala[2])
            else:
                cheltuiala=[]
                cheltuiala.append(comanda[2])
                cheltuiala.append(comanda[3])
                cheltuiala.append(comanda[4])
                verificare_actualizare(lista,cheltuiala)
        elif comanda[0]==2:
            lista=[]
            l=comanda[1].copy()
            for i in range (len(l)):
                lista.append(l[i])
        elif comanda[0]==5:
            lista=[]
            l=comanda[1].copy()
            for i in range (len(l)):
                lista.append(l[i])
        
    else:
        print("nu au fost efectuate comenzi")
            

                



def meniufiltr_sum(lista,comenzi):
    """
    Functie care elimina cheltuielile cu suma mai mica decat cea data
    preconditii: lista: lista
    postconditii: lista modificata
    """
    a=int(input("Introduceti suma cheltuielii: "))
    undolist=lista.copy()
    comenzi.append([5,undolist])
    if(validaresum(a)):
        filtr_sum(lista,a)
    else :
        print("Invalid Input")




def meniufiltr_tip(lista,comenzi):
    """
    Functie care elimina cheltuielile de un anumit tip
    preconditii: lista: lista
    postconditii: lista modificata
    """
    a=input("Introduceti tipul de cheltuiala: ").lower()
    undolist=lista.copy()
    comenzi.append([5,undolist])
    if(validaretip(a)):
        sterge_cheltuiala(lista,None,None,None,a)
    else :
        print("Invalid Input")



def printmeniu_principal():
    """
    Functia care afiseaza meniul principal
    """
    print('\n')
    print("MENIU PRINCIPAL:")
    print("1. Adauga cheltuiala")
    print("2. Stergeri")
    print("3. Cautari")
    print("4. Rapoarte")
    print("5. Filtrare")
    print("6. Undo")
    print("0. Iesire din aplicatie")

def printmeniu_cheltuieli():
    """
    Functia care afiseaza meniul CHELTUIELI
    """
    print('\n')
    print("MENIU CHELTUIELI:")
    print("1. Adauga o noua cheltuiala")
    print("2. Actualizeaza cheltuiala")
    print("0. Iesire")

def printmeniu_stergeri():
    """
    Functia care afiseaza meniul STERGERI
    """
    print('\n')
    print("MENIU STERGERI:")
    print("1. Sterge toate cheltuielile pentru ziua data")
    print("2. Sterge cheltuielile pentru un interval de timp(ziua de inceput-ziua de sfarsit)")
    print("3. Sterge toate cheltuielile de un anumit tip")
    print("0. Iesire")

def printmeniu_cautari():
    """
    Functia care afiseaza meniul CAUTARI
    """
    print('\n')
    print("MENIU CAUTARI:")
    print("1. Tipareste toate cheltuielile mai mari decat o suma data")
    print("2. Tipărește toate cheltuielile efectuate înainte de o zi dată și mai mici decât o sumă")
    print("3. Tipărește toate cheltuielile de un anumit tip")
    print("0. Iesire")

def printmeniu_rapoarte():
    """
    Functia care afiseaza meniul RAPOARTE
    """
    print('\n')
    print("MENIU RAPOARTE:")
    print("1. Tipareswte suma totala pentru un anumit tip de cheltuiala")
    print("2. Găsește ziua în care suma cheltuită e maximă")
    print("3. Tipărește toate cheltuielile ce au o anumită sumă")
    print("4. Tipărește cheltuielile sortate după tip")
    print("0. Iesire")

def printmeniu_filtrare():
    """
    Functia care afiseaza meniul FILTRARE
    """
    print('\n')
    print("MENIU FILTRARE:")
    print("1. Elimina toate cheltuielile de un anumit tip")
    print("2. Elimină toate cheltuielile mai mici decât o sumă dată")
    print("0. Iesire")

def meniu_cheltuieli(lista,comenzi):
    """
    Functia care creeaza cheltuielile
    preconditii: lista-lista de cheltuieli
    postconditii: lista modificata
    """
    printmeniu_cheltuieli()
    a=int(input())
    while a!=0:
        if a==1:
            
            creare_cheltuiala(lista,comenzi)
            afisare_cheltuieli(lista)
        elif a==2:
            
            actualizare_cheltuiala(lista,comenzi)
            afisare_cheltuieli(lista)
        else:
            print("Comanda invalida")
        printmeniu_cheltuieli()
        a=int(input())
    return lista

def meniu_stergeri(lista,comenzi):
    """
    Functia care executa stergerile cerute
    preconditii: lista: lista
    postconditii: lista modificata
    """
    printmeniu_stergeri()
    a=int(input())
    while a!=0:
        if a==1:
            
            meniusterge_zi(lista,comenzi)
            afisare_cheltuieli(lista)
            print(comenzi)
        elif a==2:
            
            meniusterge_interval(lista,comenzi)
            afisare_cheltuieli(lista)
            print(comenzi)
        elif a==3:
            
            meniusterge_tip(lista,comenzi)
            afisare_cheltuieli(lista)
            print(comenzi)
        else:
            print("Comanda invalida")
        printmeniu_stergeri()
        a=int(input())
    return lista

def meniu_cautari(lista):
    """
    Functia care efectueaza cautarile cerute
    preconditii: lista: lista
    postconditii: lista
    """
    printmeniu_cautari()
    a=int(input())
    while a!=0:
        if a==1:
            meniucautari_suma(lista)
            #afisare_cheltuieli(lista)
        elif a==2:
            meniucautare_zisum(lista)
        elif a==3:
            meniucautare_tip(lista)
        else:
            print("Comanda invalida")
        printmeniu_cautari()
        a=int(input())
    return lista

def meniu_rapoarte(lista):
    """
    Functia care executa rapoartele cerute
    preconditii: lista: lista
    postconditii: lista
    """
    printmeniu_rapoarte()
    a=int(input())
    while a!=0:
        if a==1:
            meniurap_sumtip(lista)
            #afisare_cheltuieli(lista)
        elif a==2:
            meniurap_summax(lista)
        elif a==3:
            meniurap_sum(lista)
        elif a==4:
            meniurap_tip(lista)
        else:
            print("Comanda invalida")
        printmeniu_rapoarte()
        a=int(input())
    return lista        

def meniu_filtrare(lista,comenzi):
    """
    Functia care executa filtrarile cerute
    preconditii: lista: lista
    postconditii: lista
    """
    printmeniu_filtrare()
    a=int(input())
    while a!=0:
        if a==1:
            
            meniufiltr_tip(lista,comenzi)
            afisare_cheltuieli(lista)
        elif a==2:
            
            meniufiltr_sum(lista,comenzi)
            afisare_cheltuieli(lista)
        else:
            print("Comanda invalida")
        printmeniu_filtrare()
        a=int(input())
    return lista

def main(lista):
    """
    Functia principala care acceseaza meniurile secundare in functie de alegerea utilizatorului
    preconditii: lista: lista
    postconditii:
    """
    lista=[]
    comenzi=[]
    printmeniu_principal()
    a=int(input())
    while a!=0:
        if a==1:
            meniu_cheltuieli(lista,comenzi)
        elif a==2:
            meniu_stergeri(lista,comenzi)
        elif a==3:
            meniu_cautari(lista)
        elif a==4:
            meniu_rapoarte(lista)
        elif a==5:
            meniu_filtrare(lista,comenzi)
        elif a==6:
            meniu_undo(lista,comenzi)
            print(lista)
            afisare_cheltuieli(lista)
        else:
            print("Comanda invalida")
        printmeniu_principal()
        a=int(input())


def test_validare():
    assert validare([30,28,"telefon"],[])==True    
    assert validare([30,40,"telefon"],[])==False
    assert validare([30,28,"haine"],[])==False

def test_validarezi():
    assert validarezi(30)==True
    assert validarezi(-4)==False
    assert validarezi(50)==False

def test_validaretip():
    assert validaretip("telefon")==True
    assert validaretip("intretinere")==True
    assert validaretip("tel")==False

def test_validaresum():
    assert validaresum(34)==True
    assert validaresum("a")==False
    
   
def test_verificareactualizare():
    l=[[36,14,"imbracaminte"],
       [380,17,"imbracaminte"]]
    assert verificare_actualizare(l,[80,14,"telefon"])==False
    assert verificare_actualizare(l,[90,14,"imbracaminte"])==36
    assert verificare_actualizare(l,[100,20,"telefon"])==False

def test_sterge_cheltuiala():
    l=[[36,14,"imbracaminte"],
       [380,17,"imbracaminte"]]
    
    sterge_cheltuiala(l,15)
    assert l==[[36,14,"imbracaminte"],[380,17,"imbracaminte"]]
    
    sterge_cheltuiala(l,None,13,15,None)
    assert l==[[380,17,"imbracaminte"]]

    sterge_cheltuiala(l,None,None,None,"telefon")
    assert l==[[380,17,"imbracaminte"]]

    sterge_cheltuiala(l,None,None,None,"imbracaminte")
    assert l==[]

def test_cautari_suma():
    assert cautari_suma([[36,14,"imbracaminte"],
       [380,17,"imbracaminte"]],40)==True
    
    assert cautari_suma([[36,14,"imbracaminte"],
       [380,17,"imbracaminte"]],400)==False
    
def test_sumtip():
    assert sumtip([[36,14,"imbracaminte"],
       [380,17,"imbracaminte"]],"imbracaminte")==416
    
    assert sumtip([[36,14,"imbracaminte"],
       [380,17,"altele"]],"imbracaminte")==36
    
    assert sumtip([[36,14,"imbracaminte"],
       [380,17,"imbracaminte"]],"telefon")==0
    
def test_verificare_cheltuiala():
    l=[[36,14,"imbracaminte"]]
    c=[380,17,"imbracaminte"]
    verificare_cheltuiala(l,c)
    assert l==[[36,14,"imbracaminte"],[380,17,"imbracaminte"]]
    c=[3,40,"telefon"]
    verificare_cheltuiala(l,c)
    assert l==[[36,14,"imbracaminte"],[380,17,"imbracaminte"]]
    
def test_cautare_zisum():
    assert cautare_zisum([[36,14,"imbracaminte"],
       [380,17,"imbracaminte"]],20,300)==[[36,14,"imbracaminte"]]

    assert cautare_zisum([[36,14,"imbracaminte"],
                          [380,17,"imbracaminte"]],10,400)==[]  

def test_cautare_tip():
    assert cautare_tip([[36,14,"imbracaminte"],
       [380,17,"imbracaminte"]],"imbracaminte")==[[36,14,"imbracaminte"],[380,17,"imbracaminte"]] 
    
    assert cautare_tip([[36,14,"imbracaminte"],
       [380,17,"imbracaminte"],[48,20,"telefon"],[500,16,"altele"]],"altele")==[[500,16,"altele"]]
    
    assert cautare_tip([[36,14,"imbracaminte"],
       [380,17,"imbracaminte"],[48,20,"telefon"],[500,16,"altele"]],"intertinere")==[]

def test_summax():
    assert summax([[36,14,"imbracaminte"],
       [380,17,"imbracaminte"],[48,20,"telefon"],[500,16,"altele"]])==16
    
    assert summax([[36,14,"imbracaminte"],
       [380,17,"imbracaminte"],[48,20,"telefon"],[50,16,"altele"]])==17
    
def test_rap_sum():
    assert rap_sum([[36,14,"imbracaminte"],
       [380,17,"imbracaminte"],[48,20,"telefon"],[36,16,"altele"]],36)==[[36,14,"imbracaminte"],[36,16,"altele"]]
    
    assert rap_sum([[36,14,"imbracaminte"],
       [380,17,"imbracaminte"],[48,20,"telefon"],[36,16,"altele"]],20)==[]
    
def test_filtr_sum():
    assert filtr_sum([[36,14,"imbracaminte"],[380,17,"imbracaminte"],[48,20,"telefon"],[20,16,"altele"]],40)==[[380,17,"imbracaminte"],[48,20,"telefon"]]
    
    assert filtr_sum([[39,14,"imbracaminte"],
       [380,17,"imbracaminte"],[48,20,"telefon"],[56,16,"altele"]],400)==[]
    
    assert filtr_sum([[36,14,"imbracaminte"],[380,17,"imbracaminte"],[48,20,"telefon"],[20,16,"altele"]],30)==[[36,14,"imbracaminte"],
       [380,17,"imbracaminte"],[48,20,"telefon"]]
 
def teste():
    test_sumtip()
    test_cautari_suma()
    test_sterge_cheltuiala()
    test_validare()
    test_validaretip()
    test_validarezi()
    test_validaresum()
    test_verificareactualizare()
    test_verificare_cheltuiala()
    test_cautare_zisum()
    test_cautare_tip()
    test_rap_sum()
    test_summax()
    test_filtr_sum()
    
def run():
    lista=[]
    main(lista)

teste()
run()
from Repositories import get_zi, get_s, get_tip
from Validari import validare

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
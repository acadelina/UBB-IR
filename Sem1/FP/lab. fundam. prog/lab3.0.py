

"""n=int()
lista=[]"""
def printMenu():
    #afisarea pe ecran a meniului aplicatiei
    print("Meniu:")
    print("      1-Citirea unei liste de numere intregi")
    print("      2-Gasirea secventelor de lungime maxima care au toate elementele egale")
    print("      3-Gasirea secventelor de lungime maxima care au suma elementelor egala cu 5")
    print("      4-Gasirea secventelor de lungime maxima care au toate elementele distincte intre ele")
    print("      5-Iesire din aplicatie")

def citire(lista):
    #citirea sirului de numere
    
    lista.clear()
    try:
        n = int(input('numar elemente = '))

        for i in range(n):
            lista.append(int(input('element %d = ' % i)))
    except ValueError:
        print("ValueError")
        return
    
    

def elemegale(lista):
    #cautarea secventei de lungime maxima care are toate elementele egale
    n=len(lista)
    l= 1
    lm=0
    dr=0
    nr=0
    v=[]
    if n>0:
        for x in range(n-1):
            if lista[x]==lista[x+1]:
                l+=1
                #daca elemenetele sunt egale se incremeteaza lungimea secventei curente
            else:
                if l>lm:
                    lm=l
                    dr=x
                
                """daca lungimea secventei curente este mai mare decat a celei
                    maxime se schimba valoarea lungimii maxime, slavand capatul din dreapta a secventei"""
                l=1

        if l>lm:
            lm=l
            dr=n-1
        x=0
        for i in range(dr-lm+1,dr+1):
            v.insert(x,lista[i])
            x+=1
        return (v)
    else: return(0)
    
    

def sum5(lista):
    #cautarea secventelor de lungime maxima care au suma elementelor 5
    n=len(lista)
    l= 1
    lm= 0
    sc=0
    dr=0
    v=[]
    if n>0:
        for a in range(n):
            sc=lista[a]
            l=1
            y=a+1
            while (sc<5 and y<n )or(sc>5 and lista[a+1]<0):
                sc+=lista[y]
                """se calculeaza suma secventelor incepand de pe fiecare pozitie a sirului
            pana cand suma este mai mare sau egala cu 5;"""
                l+=1
                y+=1
            if sc==5 and l>lm:
                lm=l
                dr=y-1
        
            
        """ in cazul in care suma este egala cu 5 si lungimea acesteia este mai
            mare decat lungimea maxima se salveaza noua lungime maxima si capatul din
            dreapta al secventei"""
                
        x=0
        if lm==0:
            v.clear()
        else:
            for i in range(dr-lm+1,dr+1):
                v.insert(x,lista[i])
                x+=1
        return (v)
    else:
        return(0)

    
        
def elemdiferite(lista):
    #cautarea secventelor de lungime maxima care au toate elementele egale
    n=len(lista)
    l= 0
    lm=0
    dr=0
    
    v=[]
    u=0
    if n>0:
        for x in range(n):
            ok=1
        
            for j in range(u,x):
                 if lista[x]==lista[j]:
                       ok=0
                
    
            if ok:
                l+=1
            else:
                u=x
                if l>lm:
                    lm=l
                    dr=x-1
                """daca lungimea secventei curente este mai mare decat a celei
                    maxime se schimba valoarea lungimii maxime, slavand
                    capatul din dreapta al secventei"""
                l=1

        if l>lm:
            lm=l
            dr=n-1
        
        x=0
        for i in range(dr-lm+1,dr+1):
            v.insert(x,lista[i])
            x+=1
        return (v)
    else:
        return(0)
   
  

def afisare(lista,v):
    
    if v==0:
        print("Introduceti 1 penru a citi sirul!")
    elif len(v)==0:
        print("Nu exista secventa cu suma 5")
    else:
        n=len(v)
        for i in range(n):
            print(v[i],end=' ')
    print('\n')
    
def test_elemegale():
    assert elemegale([1,1,1,2,3,3,3,0,0,0])==[1,1,1]
    assert elemegale([-2,-2,-3,-4,-4,-4,4,-5])==[-4,-4,-4]
    assert elemegale([11,12,13,14,15])==[11]

def test_elemdiferite():
    assert elemdiferite([1,1,1,2,3,3,3,0,0,0])==[1,2,3]
    assert elemdiferite([-2,-2,-3,-4,-4,-4,4,-5])==[-2,-3,-4]
    assert elemdiferite([11,11,11,11,11])==[11]
    
def test_sum5():
    assert sum5([1,1,1,2,3,0,0,0,0,0,5])==[0,0,0,0,0,5]
    print (sum5([5,-2,3,-4,3,0,4,4,1]))
    assert sum5([5,-2,3,-4,3,0,4,4,1])==[5,-2,3,-4,3,0]
    assert sum5([1,2,1,5,6,9,10,-1])=="Nu exista secventa cu suma 5"


def run():
    #implementarea interfatei tip utilizator
    stop=False
    lista=[]
    while not stop:
        
        printMenu()
        m=int(input())
        if m==5:
            stop=True
        elif m==1:
            citire(lista)
        elif m==2:
            afisare(lista,elemegale(lista))
        elif m==3:
            afisare(lista,sum5(lista))
        elif m==4:
            #elemdiferite(lista)
            afisare(lista,elemdiferite(lista))
        else:
            print("Comanda invalida")
        
    print("The end")
test_elemegale()
test_elemdiferite()
test_sum5()
run()


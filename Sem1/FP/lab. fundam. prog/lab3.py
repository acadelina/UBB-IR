

n=int()
lista=[]
def printMenu():
    #afisarea pe ecran a meniului aplicatiei
    print("Meniu:")
    print("      1-Citirea unei liste de numere intregi")
    print("      2-Gasirea secventelor de lungime maxima care au toate elementele egale")
    print("      3-Gasirea secventelor de lungime maxima care au suma elementelor egala cu 5")
    print("      4-Gasirea secventelor de lungime maxima care au toate elementele distincte intre ele")
    print("      5-Iesire din aplicatie")

def citire():
    #citirea sirului de numere
    global n
    global lista
    lista.clear()
    n= int(input("Numarul de elemente ale listei: "))
    print(" Dati elementele(intregi) ale listei:")
    for x in range(n):
        lista.append(int(input()))
    

def elemegale():
    #cautarea secventelor de lungime maxima care au toate elementele egale
    global n 
    global lista
    l= 1
    lm=0
    dr=0
    nr=0
    v=[]
    for x in range(n-1):
        if lista[x]==lista[x+1]:
            l+=1
            #daca elemenetele sunt egale se incremeteaza lungimea secventei curente
        else:
            if l>lm:
                lm=l
                dr=x
                v.clear()
                v.insert(0,dr)
                nr=1
                """daca lungimea secventei curente este mai mare decat a celei
                    maxime se schimba valoarea lungimii maxime, slavand in v
                    capetele noilor secvente de lungime maxima"""
                    
            else:
                if l==lm:
                    v.insert(nr,x)
                    nr+=1
                    """ daca lungimea curenta este egala cu cea maxima se salveaza
                        un nou element in v care indica capatul secventei curente"""
            l=1
    if l>lm:
        lm=l
        dr=n-1
        v.clear()
        v.insert(0,dr)
        nr=1
    else:
        if l==lm:
            dr=n-1
            v.insert(nr,dr)
            nr+=1
    print ("lungimea maxima: ", lm)
    print ("secventele de lungime maxima: ")
    for x in range(nr):
            for i in range(v[x]-lm+1,v[x]+1):
                print(lista[i], end=' ')
            print('\n')

def sum5():
    #cautarea secventelor de lungime maxima care au suma elementelor 5
    global n
    global lista
    l= 1
    lm= 0
    sc=0
    nr=0
    v=[]
    for a in range(n):
        
        sc=lista[a]
        l=1
        y=a+1
        while sc<5 and y<n:
            sc+=lista[y]
            l+=1
            y+=1
        """se calculeaza suma secventelor incepand de pe fiecare pozitie a sirului
            pana cand suma este mai mare sau egala cu 5;"""
            
        if sc==5 and l>lm :
            """ in cazul in care suma este egala cu 5 si lungimea acesteia este mai
            mare decat lungimea maxima se sterg elementele din v, se salveaza
            noua lungime maxima, iar prima valoare din v este capatul secventei"""
            lm=l
            v.clear()
            v.insert(0,y-1)
            nr=1
        else:
            if l==lm and sc==int(5):
                v.insert(nr,y-1)
                nr+=1
    

    if lm==0:
        print("nu exista nici o secventa cu suma elementelor egala cu 5")
    else:
        print ("lungimea maxima a unei secvente de suma 5:",lm)
        print ("secventele de lungime maxima: ")
        for x in range(nr):
            for i in range(v[x]-lm+1,v[x]+1):
                print(lista[i], end=' ')
            print('\n')
        
def elemdiferite():
    #cautarea secventelor de lungime maxima care au toate elementele egale
    global n 
    global lista
    l= 0
    lm=0
    dr=0
    nr=0
    v=[]
    u=0
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
                v.clear()
                v.insert(0,dr)
                nr=1
                """daca lungimea secventei curente este mai mare decat a celei
                    maxime se schimba valoarea lungimii maxime, slavand in v
                    capetele noilor secvente de lungime maxima"""
                    
            else:
                if l==lm and v[nr-1]!=x:
                    v.insert(nr,x-1)
                    nr+=1
                    """ daca lungimea curenta este egala cu cea maxima se salveaza
                        un nou element in v care indica capatul secventei curente"""
            l=1
    if l>lm:
        lm=l
        dr=n-1
        v.clear()
        v.insert(0,dr)
        nr=1
    else:
        if l==lm and v[nr-1]!=x-1:
            dr=n-1
            v.insert(nr,dr)
            nr+=1
    print ("lungimea maxima: ", lm)
    print ("secventele de lungime maxima: ")
    for x in range(nr):
            for i in range(v[x]-lm+1,v[x]+1):
                print(lista[i], end=' ')
            print('\n')





def run():
    #implementarea interfatei tip utilizator
    stop=False
    global lista=[]
    global n
    while not stop:
        
        printMenu()
        m=int(input())
        if m==5:
            stop=True
        elif m==1:
            citire()
        elif m==2:
            elemegale()
        elif m==3:
            sum5()
        elif m==4:
            elemdiferite()
        else:
            print("Comanda invalida")
        print(n, " ", lista)
    print("The end")

run()


from iterativ import backIter
from recursiv import backrec

def print_meniu():
    print("1.Citire date")
    print("2.Backtracking recursiv")
    print("3.Backtracking iterativ")
    print("0.Iesire")

def citire():
    
    n=input("Dati numarul n: ")
    try:
        n=int(n)
    except ValueError:
        raise ValueError("Numarul trebuie sa fie intreg.")
    if n<=0:
        raise ValueError("Numaruml de elemente trebuie sa fie natural.")
           
        
    v=[]
    for i in range (n):
        x=input("Dati elementul %d: "%i)
        v.append(x)
        
    for i in range (n):
        try:
            v[i]=int(v[i])
        except ValueError:
            raise ValueError("Elemntele trebuie sa fie numere intregi.")
    return v

def main():
    print_meniu()
    a=int(input("Dati optiunea: "))
    while a!=0:
        if a==1:
            try:
                v=citire()
            except ValueError as ve:
                print(ve)


        elif a==2:
            backrec([],v,len(v))
        elif a==3:
            backIter(v,len(v))
        elif a==0:
            return
        else:
            print("Optiune invalida")
        print_meniu()
        a=int(input("Dati optiunea: "))

main()

from Validari import validarezi, validaretip
from Afisari import afisare_cheltuieli
from Services import sterge_cheltuiala

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
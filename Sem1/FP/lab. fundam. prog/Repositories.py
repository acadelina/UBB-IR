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
               
    return (cheltuiala)

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
    return (cheltuiala[2])

def actualizare_cheltuiala(lista,comenzi):
    """
    Functie care citeste cheltuiala ce urmeaza sa fie actualizata
    preconditii: lista: lista
    postconditii: 
    """
    cheltuiala=[]
    l=lista[len(lista)-1]
    sum=l[0]
    s=input("Dati suma cheltuielii:")
    zi=input("Dati ziua cheltuielii:")
    tip=input("Dati tipul de cheltuiala:").lower()
    cheltuiala.append(s)
    cheltuiala.append(zi)
    cheltuiala.append(tip)
    comenzi.append([1,2,sum,zi,tip])
    return (cheltuiala)
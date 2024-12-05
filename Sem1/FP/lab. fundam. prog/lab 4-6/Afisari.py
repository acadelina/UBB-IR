from Repositories import get_s,get_zi,get_tip

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
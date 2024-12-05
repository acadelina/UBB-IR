def afisare(x,v):
    """
    Functie care afiseaza solutiile gasite
    preconditii: x:list,v:list
    postconditii: 
    """
    for i in range(len(x)):
        if v[i]>0:
            print(v[i],end=' ')
        else:
            print('(', v[i],')',end=' ')
        if x[i]==0:
            print('+',end=' ')
        else:
            print('-',end=' ')
    if v[len(v)-1]>0:
            print(v[len(v)-1],end=' ')
    else:
        print('(', v[len(v)-1],')',end=' ')
    print("\n")

def ok(x,v):
    """
    Functia verifica daca vectorul curent este o posibila solutie
    preconditii: x:list,v:list
    postconditii: True/False daca vectorul poate fi o solutie sau nu
    """
    s=v[0]
    if len(x)>=len(v):
        return False
    for i in range(len(x)):
        if x[i]==0:
            s+=v[i+1]
        else:
            s+=v[i+1]*(-1)
    s2=0
    for i in range(len(x),len(v)-1):
        s2+=v[i+1]
    
    
    if s-s2>=0 or s+s2>=0:
        return True
    return False

def sol(x,n):
    """
    Functie care verifica daca vectorul este o solutie
    preconditii: x:list,n:int
    postconditii: True/False
    """
    return len(x)==n-1

def backrec(x,v,n):
    x.append(0)
    for i in range(0,2):
        x[-1]=i
        if ok(x,v):
            if sol(x,n):
                afisare(x,v)
            backrec(x,v,n)
           
    x.pop()


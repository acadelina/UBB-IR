
def afisare(x,v):
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
def citire():
    n=int(input("Dati numarul n: "))
    v=[]
    for i in range (n):
        x=int(input("Dati elementul %d: "%i))
        v.append(x)
    return v
def ok(x,v):
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

def backIter(v,n):
    x=[-1]
    while len(x)>0:
        choosed = False
        while not choosed and x[-1]<1:
            x[-1] = x[-1]+1 
            choosed = ok(x,v)
        if choosed:
            if sol(x,n):
                afisare(x,v)
            x.append(-1) 
        else:
            x = x[:-1] 

def run():
    a=citire()
    print("Varianta recursiva:")
    backrec([],a,len(a))
    print("Varianta iterativa:")
    backIter(a,len(a))

run()



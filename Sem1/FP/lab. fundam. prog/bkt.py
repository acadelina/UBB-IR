
def afisare(x):
    for i in range(len(x)):
        print(x[i],end=',')
    print("\n")

def ok(x):
    
    for i in range(len(x)-1):
        if x[-1]==x[i]:
            return False
    ok=False
    if len(x)==1:
        ok=True
    for i in range(len(x)-1):
        if abs(x[-1]-x[i])==1:
            ok=True
    return ok

def sol(x,n):
    return len(x)==n

def backrec(x,n):
    x.append(1)
    for i in range(1,n+1):
        x[-1]=i
        if ok(x):
            if sol(x,n):
                afisare(x)
            backrec(x,n)
    x.pop()
print("Varianta recursiva: ")
backrec([],3)

def backIter(n):
    x=[0]
    while len(x)>0:
        choosed = False
        while not choosed and x[-1]<n:
            x[-1] = x[-1]+1 
            choosed = ok(x)
        if choosed:
            if sol(x,n):
                afisare(x)
            x.append(0) 
        else:
            x = x[:-1] 
print("Varianta iterativa: ")
backIter(3)
n=int(input("Dati n: "))
def prim(m):
    if m==1:
        return 0
    for i in range(2,m-1):
        if m%i==0:
            return 0
    return 1
    
if n==0:
    print(1)
else:
    a=2
    i=0
    while i<n:
        x=1
        if prim(a) :
            i+=1
            a+=1
            if i==n :
               print(a-1)
        else:
            b=a
            while b>1 and i<n:
                x+=1
                if b%x==0:
                    while b%x==0:
                        b/=x
                    i+=1
            if i==n:
                print (x)
            a+=1
    
    #n=0 => 1
    #n=3 => 2
    #n=9 => 3

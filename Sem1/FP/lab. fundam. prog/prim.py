n=int(input("Dati input"))
a=1
if n==1:
    print("numarul nu este prim")
else:
    for i in range(2, n-1):
        if n%i==0:
           a=0 
        
    if a==1:
        print("numarul este prim")
    
    else:
        print("numarul nu este prim")
    
    


    



from scipy.stats import expon,norm
import random
from matplotlib.pyplot import hist,show,plot
import numpy as np

T=expon.rvs(scale=2,size=1000)
hist(T,10,range=(0,10),density=True,edgecolor='black')
x=np.linspace(0,10,1000)
pdf=expon.pdf(x,2)
plot(x,pdf,'r-')
show()

N=[]

for t in T:
    n=random.randint(1,11)
    nf=n-np.floor(t)
    if nf< 1:
        nf=1
    N.append(nf)
    
p5=sum(1 for n in N if n>=5)/1000
print(p5)

succes=0
rez=[]
for i in range(0,10000):
    nr=0
    while True:
       p=norm.rvs(1.65,0.20)
       if p>1.90:
           break
       nr+=1
    rez.append(nr)   


hist(rez,10,density=True,edgecolor='black')
show()

p=sum(1 for r in rez if r>10)/10000
print(p)
           
    
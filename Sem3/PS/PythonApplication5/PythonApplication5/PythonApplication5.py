from collections import Counter
import random
from math import comb,sqrt
from matplotlib.pyplot import hist,show,plot
from scipy.stats import expon,norm,uniform
import numpy as np

urna=10*['r']+5*['n']+5*['a']

rez=[]
for i in range (0,1000):
    sim=random.sample(urna,3)
    rez.append(Counter(sim))

pa=sum(1 for r in rez if r['r']==3 or r['n']==3 or r['a']==3)/1000
pb=sum(1 for r in rez if r['r']==1 and r['a']==1 and r['n']==1)/1000
paa=1-pa
pc=sum(1 for r in rez if r['n']>=1)/1000

pta=(comb(10,3)+comb(5,3)+comb(5,3))/comb(20,3)
ptb=(comb(10,1)*comb(5,1)*comb(5,1))/comb(20,3)
paat=1-pta
ptc=1-(comb(5,0)*comb(15,3)/comb(20,3))

print(pa,pta)
print(paa,paat)
print(pb,ptb)
print(pc,ptc)

x=np.linspace(-2,5)
cdf=expon.cdf(x,1/2)
pdf=expon.pdf(x,1/2)
plot(x,cdf)
show()
plot(x,pdf)
show()

sim=expon.rvs(1/2,1,1000)
print(np.mean(sim),np.std(sim))

pe=sum(1 for r in sim if r>0.7)/1000
pt=1-expon.cdf(0.7,1/2)
print(pe,pt)

x=[-2,-1,1,2]
p=[0.1,0.4,0.3,0.2]

X=np.random.choice(x,500,p=p)
Y=uniform.rvs(loc=-1,scale=4,size=500)

U=(X**3)-(Y**3)
hist(U,bins=20,edgecolor='black')
show()
print(np.mean(U),np.var(U))
print(sum(1 for r in U if r<0)/500)

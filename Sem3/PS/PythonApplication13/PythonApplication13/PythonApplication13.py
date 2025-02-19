
from xml.sax.handler import feature_validation
from scipy.stats import hypergeom,binom,bernoulli,randint,geom,uniform,norm,expon
import random
import matplotlib.pyplot as mp
import numpy as np
from math import sqrt,comb

x=[-2,-1,0,1,2]
p=[0.2,0.15,0.25,0.14,0.26]

sim=random.choices(x,weights=p,k=1000)
bin_edges=([k+0.5 for k in range(-3,3)])
mp.hist(sim,bin_edges,range=(-2,2),density=True,edgecolor='black')
mp.show()

pe1=sum(1 for s in sim if s<=0)/1000
pe2=sum(1 for s in sim if s*s==4)/1000

print(pe1,pe2)

print(np.mean(x))
print(np.var(x))


x2=norm.rvs(loc=100,scale=sqrt(20),size=1000)
pae=sum(1 for r in x2 if r>80 and r<140)/1000
print(pae)
pat=norm.cdf(140,loc=100,scale=sqrt(20))-norm.cdf(80,loc=100,scale=sqrt(20))
print(pat)

mp.hist(x2,bins=13,density=True,edgecolor='black')
y=np.linspace(min(x2),max(x2),100)
pdf=norm.pdf(y,loc=100,scale=sqrt(20))
mp.plot(y,pdf,'-r')
mp.show()


x3=norm.rvs(loc=-1,scale=2,size=10000)
y3=norm.rvs(loc=1,scale=2,size=10000)
s=x3+y3
ls=np.linspace(min(s),max(s),100)
pdf3=norm.pdf(ls,loc=0,scale=sqrt(8))
mp.hist(s,bins=15,density=True,edgecolor='black')
mp.plot(ls,pdf3,'-r')
mp.show()

print(np.mean(s),np.var(s))

print(sum(1 for r in s if abs(r)<1)/10000)
print(norm.cdf(1,loc=0,scale=sqrt(8))-norm.cdf(-1,loc=0,scale=sqrt(8)))


x4=expon.rvs(scale=1,size=1000)
pt4=sum(1 for r in x4 if r>0.5 and r<1.5)/1000
pe4=expon.cdf(1.5,scale=1)-expon.cdf(0.5,scale=1)
print(pe4,pt4)

mp.hist(x4,bins=11,density=True,edgecolor='black')
y4=np.linspace(min(x4),max(x4),100)
pdf4=expon.pdf(y4,scale=1)
mp.plot(y4,pdf4,'-r')
mp.show()

urna=8*['n']+4*['a']
fa=0
fb=0
albe=[0]*5000
for i in range (0,5000):
    extr=random.sample(urna,3)
    nra=sum(1 for r in extr if r=='a')
    albe[i]=nra
    if nra==2:
        fa+=1
    if nra==0:
        fb+=1
print(fa/5000,fb/5000)
fat=comb(4,2)*8/comb(12,3)
fbt=comb(8,3)/comb(12,3)
print(fat,fbt)
mp.hist(albe,bins=4,range=(0,3),edgecolor='black')
mp.show()


z1=randint.rvs(3,19,size=10000)
y=hypergeom.rvs(10,4,3,size=10000)*(z1<12)+binom.rvs(3,4/10,size=10000)*(z1>=12)
bi_edges=[k+0.5 for k in range(-1,5)]
mp.hist(y,bi_edges,density=True,edgecolor='black')
print(sum(1 for i in y if i==2)/10000)
print(randint.cdf(12,3,19)*hypergeom.pmf(2,10,4,3)+(1-randint.cdf(12,3,19))*binom.pmf(2,3,4/10))
from collections import Counter
import numpy as np
import random
from math import comb
from scipy.stats import norm
from numpy._typing import _128Bit

acumulatori=3*['d']+7*['i']
rez=[]

for i in range(0,5000):
    rez.append(Counter(random.sample(acumulatori, 3)))

pA=sum(1 for r in rez if r['d']==1)/5000
pB=sum(1 for r in rez if r['d']==0)/5000

print(pA,pB)
pBT=comb(7,3)/comb(10,3)
print(pBT)

succes_a=0
succes_b=0
for i in range (0,1000):
    v=np.concatenate([np.random.normal(-1,1,2),np.random.normal(0,1,3)])
    inA=np.sum((v>=-2)&(v<=2))
    if inA>=3:
        succes_a+=1
    if inA==5:
        succes_b+=1
        
print(succes_a/1000)
print(succes_b/1000)

pn_1=norm.cdf(2,loc=-1,scale=1)-norm.cdf(-2,loc=-1,scale=1)
pn_0=norm.cdf(2,loc=0,scale=1)-norm.cdf(-2,loc=0,scale=1)

pTB=(pn_1**2)*(pn_0**3)

print(pTB)

acm=['d']*13+['i']*7
rez1=[]

for i in range(0,5000):
    rez1.append(Counter(random.sample(acm,4)))

pa=sum(1 for r in rez1 if r['d']==1)
pb=sum(1 for r in rez1 if r['d']==0)

ptb=comb(7,4)/comb(20,4)
print(pa,pb,ptb)


succesa=0
succesb=0
for i in range(0,1000):
    v=np.concatenate([np.random.normal(-1,1,2), np.random.normal(1,1,3)])
    inint=np.sum((v>-2)&(v<2))
    if inint>=2:
        succesa+=1
    if inint==5:
        succesb+=1
        
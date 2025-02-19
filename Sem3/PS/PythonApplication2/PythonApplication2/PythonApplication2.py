from collections import Counter
import numpy as np
from math import comb
import random
from scipy.stats import geom

urna=6*['1']+3*['2']+4*['3']
rez=[]
for i in range (0,2000):
    rez.append(Counter(random.sample(urna,3)))
 
pA=sum(1 for r in rez if r['1']==1 and r['2']==1 and r['3']==1)/2000
pB=sum(1 for r in rez if r['1']>=1)/2000
pC=sum(1 for r in rez if r['1']==1)/2000

print(pA,pB,pC)

pCT=comb(6,1)*comb(7,2)/comb(13,3)

print(pCT)

PA=0
PB=0

for i in range(0,1000):
    nr=0
    while True:
        d1=random.randint(1,6)
        d2=random.randint(1,6)
        if d1==d2:
            break
        nr+=1
    if nr < 5:
        PA+=1
    if nr>=7 and nr<=10:
        PB+=1

PA=PA/1000
PB=PB/1000

print( PA, PB)

fav=0
total=0

for i in range(1,7):
    for j in range(1,7):
        total+=1
        if(i==j):
            fav+=1
            
prob=fav/total
PTB=0
for k in range(7,11):
    PTB+=geom.pmf(k,prob)
    
print(PTB)
from collections import Counter
import random
import numpy as np
from math import comb
from scipy.stats import binom, uniform


urna=6*['a']+8*['n']
rez=[]
for i in range(0,5000):
    rez.append(Counter(random.sample(urna,4)))
pA=sum(1 for r in rez if r['a']==3)
pB=sum(1 for r in rez if r['n']>=2)

pTA=comb(6,3)*comb(8,1)/comb(14,4)
pTB=1-(comb(8,0)*comb(6,4)+comb(6,3)*comb(8,1))/comb(14,4)

print(pTA,pTB)

urna2=7*[1]+6*[0]
rez=[]
for i in range(0,10000):
    rez.append(sum(random.choices(urna2,k=8)))

P36=sum(1 for r in rez if r>3 and r<=6)/10000
print( sum(binom.pmf(k, 8, 7/13) for k in range(4, 7)))
PT=(comb(7,4)*comb(6,4)+comb(7,5)*comb(6,3)+comb(7,6)*comb(6,2))/comb(13,8)
print(P36,PT)

vec=uniform.rvs(1,2, size=6)
print(vec)
rez=[]
pa=0
for i in range(0,1000):
    y1,y2,y3=random.choices(vec,k=3)
    mg=(y1*y2*y3)**(1/3)
    rez.append(mg)
    if (y1+y3)/2>y2:
        pa+=1
        
med_geom=np.mean(rez)
pa=pa/1000

print(med_geom, pa)

p_in_int=(1.6-1.2)/(2-1)
pb=p_in_int**3

print(pb)

    

import random
from math import comb

urna=['r']*7+['a']*5+['v']*3

fa=0
fb=0
fc=0

for i in range(0,1000):
    extragere=random.sample(urna,3)
    if 'a' in extragere:
        fa+=1
    
    if len(set(extragere))==1:
        fb+=1
        
    if len(set(extragere))==1 and 'a' in extragere:
        fc+=1
        
print(fa/1000,fb/1000,fc/1000)

pba=comb(5,3)/comb(15,3)
pa=1-comb(10,3)/comb(15,3)
ptc=pba/pa
print(ptc)


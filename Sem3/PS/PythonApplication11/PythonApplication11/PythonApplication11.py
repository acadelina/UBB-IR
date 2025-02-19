
from xml.sax.handler import feature_validation
from scipy.stats import geom
import random

fa=0
fb=0
for i in range(0,10000):
    nr=0
    while True:
        z1=random.randint(1,6)
        z2=random.randint(1,6) 
        
        if z1+z2==6:
            break
        nr+=1
    if nr>4:
        fa+=1
    if nr>=7 and nr<=10:
        fb+=1

print(fa/10000,fb/10000)


x=geom.rvs(5/36,size=100000)-1

print(sum(1 for r in x if r>=7 and r<=10)/100000)

print(geom.pmf(8,5/36)+geom.pmf(9,5/36)+geom.pmf(10,5/36)+geom.pmf(11,5/36))
print(geom.cdf(11,5/36)-geom.cdf(7,5/36))
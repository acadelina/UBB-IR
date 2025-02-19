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
        if z1==z2:
            break
        nr+=1
    if nr<5:
        fa+=1
    if nr>=7 and nr<=10:
        fb+=1

print(fa/1000,fb/10000)




print(geom.pmf(8,1/6)+geom.pmf(9,1/6)+geom.pmf(10,1/6)+geom.pmf(11,1/6))

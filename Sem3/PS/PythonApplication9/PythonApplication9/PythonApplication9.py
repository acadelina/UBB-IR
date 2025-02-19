from scipy.stats import binom,hypergeom
from math import comb
import random

urna=7*[1]+6*[0]
cazf=0
for i in range(0,1000):
    bile=random.choices(urna,weights=[1]*13,k=8)
    x=0
    for j in range(0,8):
        x+=bile[j]
    if x>3 and x<=6:
        cazf+=1
print(cazf/1000)


pt=binom.pmf(4,8,(7/13))+binom.pmf(5,8,(7/13))+binom.pmf(6,8,(7/13))
print(hypergeom.pmf(6,13,7,8)+hypergeom.pmf(4,13,7,8)+hypergeom.pmf(5,13,7,8))
print(pt)
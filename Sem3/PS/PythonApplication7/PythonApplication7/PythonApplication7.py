from scipy.stats import norm
import numpy as np

afav=0
bfav=0
for i in range(0, 10000):
    n1=norm.rvs(-1,1,2)
    n2=norm.rvs(1,1,3)
    v=np.concatenate((n1,n2))
    nra=0
    for j in range(0,5):
        if v[j]>=-2 and v[j]<=2:
            nra+=1
    if nra>=2:
        afav+=1
    if nra==5:
        bfav+=1

print(afav/10000,bfav/10000)
help(norm)
ptb=((norm.cdf(2,-1,1)-norm.cdf(-2,-1,1))**2)*((norm.cdf(2,1,1)-norm.cdf(-2,1,1))**3)
print(ptb)
   
    

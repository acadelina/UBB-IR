
from scipy.stats import uniform
import random


w=uniform.rvs(1,1,6)
print(w)
sum=0
cazf=0

for i in range (0,1000):
    y1,y2,y3=random.choices(w,weights=[1,1,1,1,1,1],k=3)
    sum+=(y1*y2*y3)**(1/3)
    if (y1+y3)/2>y2:
        cazf+=1

print(sum/1000)
print(cazf/1000)

pt=(uniform.cdf(1.6,1,1)-uniform.cdf(1.2,1,1))**3
print(pt)
help(uniform)
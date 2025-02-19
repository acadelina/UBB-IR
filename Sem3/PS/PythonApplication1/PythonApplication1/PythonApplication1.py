from collections import Counter
from scipy.stats import expon,randint
from matplotlib.pyplot import hist,plot,show,axhline,grid,legend
from numpy import linspace, mean, floor,std
import random
from math import comb
import numpy as np

timp=expon.rvs(scale=2,size=10000)


print("P(N>=5) =", mean([randint.rvs(1,11)-floor(t)>=5 for t in timp ]))
print("P(N>=5) =", sum([randint.pmf(k,1,11)*expon.cdf(k-4,scale=2) for k in range (5,11)]))

urna=['r']*10+['n']*5+['a']*5
sol=[]
for i in range(0,1000):
    sol.append(Counter(random.sample(urna,3)))
probA=sum(1 for r in sol if r['r']==3 or r['a']==3 or r['n']==3)/1000
probB=sum(1 for r in sol if r['r']==1 and r['a']==1 and r['n']==1)/1000
probC=sum(1 for r in sol if r['n']>=1)/1000
prob_A=1-probA

print("A: ",probA,"B: ",probB,"C: ",probC,"A-: ",prob_A)

tA=(comb(10,3)+comb(5,3)+comb(5,3))/comb(20,3)
print(tA)
tB=(comb(10,1)*comb(5,1)*comb(5,1))/comb(20,3)
print(tB)
print(1-tA)
tAC=comb(5,3)/comb(20,3)
print(tAC)

x=np.linspace(-2,5,100)
pdf=expon.pdf(x,1/2)
cdf=expon.cdf(x,1/2)

plot(x,pdf,label="PDF",color="pink")
grid()
legend()
show()

plot(x,cdf,label="CDF",color="blue")
show()

#estimari prin simulari E(x) val medie si Std(x) abaterea standard)
simulari=expon.rvs(scale=1/2,size=1000)
print(mean(simulari),std(simulari))
sim=np.random.exponential(scale=1/2,size=1000)
print(mean(sim))

#probabilitatea P(X>0.7)
PSim=mean(simulari>0.7)
#teoretica
PTeo=1-expon.cdf(0.7,scale=1/2)

print(PSim,PTeo)


val=np.array([-2,-1,1,2])
prob=np.array([0.1,0.4,0.3,0.2])

x_sample=np.random.choice(val,size=500,p=prob)
y_sample=np.random.uniform(-1,4,size=500)

u_sample=x_sample**3-y_sample**3


hist(u_sample, bins=20, color='skyblue', edgecolor='black')
grid()
show()

PU=mean(u_sample<0)
VM=mean(u_sample)
VarU=std(u_sample)
print(PU,VM,VarU)

X3=val**3
medie=sum(X3*prob)
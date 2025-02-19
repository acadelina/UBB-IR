from random import choices, sample
from math import comb, perm
from random import randrange
from matplotlib.pyplot import bar, hist, grid, show, legend
from scipy.stats import binom



def cerinta_1a():
    lista = ["rosu","albastru","verde"]
    count_rosie = 0
    count_toate_rosii = 0
    repetitii = 10000
    for i in range(repetitii):
        extrase = sample(lista,counts=[5,3,2],k=3)
        if("rosu" in extrase):
            count_rosie +=1
            if(len(set(extrase)) == 1):
                count_toate_rosii += 1
    print((count_toate_rosii/count_rosie)*100)
    
def cerinta_1b():
    prob_ab=comb(5,3)/comb(10,3)
    prob_a=1-prob_ab
    prob_b_cond_a=prob_ab/prob_a
    print((prob_b_cond_a)*100)

def cerinta2():
    data = [randrange(1,7) for _ in range(1000)]
    bin_edges = [k+0.5 for k in range(1,7)]
    hist(data, bins=bin_edges, density = True, rwidth = 0.9, color = 'green', edgecolor = 'black',
    alpha = 0.5, label = 'frecvente relative')
    distribution = dict([(i,1/6) for i in range(1,7)])
    bar(distribution.keys(), distribution.values(), width = 0.85, color = 'red', edgecolor = 'black',
    alpha= 0.6, label = 'probabilitati')
    legend(loc = 'lower left')
    grid()
    show()

def cerinta3():
    #cerinta a
    x = binom.rvs(5, 0.6, size=1000)
    #cerinta b
    bin_edges = [k+0.5 for k in range(6)]
    hist(x, bin_edges, density = True, rwidth = 0.9, color = 'green', edgecolor = 'black', alpha = 0.5, label = 'frecvente relative')
    distribution = dict([(i, binom.pmf(i, 5, 0.6)) for i in range(6)])
    bar(distribution.keys(), distribution.values(), width = 0.85, color = 'red', edgecolor = 'black', alpha= 0.6, label = 'probabilitati')
    legend(loc = 'lower left')
    grid()
    show()
    
def main():
    cerinta_1a()
    cerinta_1b()
    cerinta2()
    cerinta3()
    
main()
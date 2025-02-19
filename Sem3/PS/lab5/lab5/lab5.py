import numpy as np
from scipy.stats import uniform
from matplotlib.pyplot import bar, show, hist, grid, legend, xticks


probabilitati = [0.46, 0.40, 0.04, 0.10]
grupe = ['0', 'A', 'AB', 'B']


def genereaza_o_valoare(probabilitati):
   
    u = uniform.rvs()
    
    suma_cdf = 0
    for idx, p in enumerate(probabilitati):
        suma_cdf += p
        if u < suma_cdf:
            return grupe[idx]


def cerinta1():
    N = 10000  
    observatii = [genereaza_o_valoare(probabilitati) for _ in range(N)]
    valori_unice, frecvente = np.unique(observatii, return_counts=True)
    frecvente_relative = frecvente / N
    xticks(range(len(grupe)), grupe)
    bar(range(len(grupe)), frecvente_relative, alpha=0.6, label='Frecvente relative (simulate)')
    bar(range(len(grupe)), probabilitati, alpha=0.6, label='Probabilitati teoretice', color='pink')
    grid(True)
    legend()
    show()
    

cerinta1()

from matplotlib.pyplot import show, hist, grid, legend, xticks, plot
from scipy.stats import expon

def cerinta2():
    N=1000
    alpha = 1/12
    data = np.random.exponential(1/alpha,N)
    hist(data, bins=12, density = True,range=(0,60))
    x = range(60)
    plot(x,expon.pdf(x,loc=0,scale=12),'r-')
    xticks(range(0,60,5))
    grid()
    show()
cerinta2()
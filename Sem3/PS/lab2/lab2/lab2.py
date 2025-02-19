import math
from random import randint
from matplotlib.pyplot import plot, grid, title, show, subplot
from random import random
from math import dist

def cerinta1_a(nr_pers,nr_sim):
    fav = 0
    for i in range(nr_sim):
        persoane = []
        for i in range(nr_pers):
            persoane.append(randint(1, 365))
        if len(set(persoane)) != nr_pers:
            fav+=1
    return fav/nr_sim



def cerinta1_b(nr_pers):
    if n>365:
        return 1
    p = 1 # prob ca nr de pers sa aiba zile de nastere diff
    for i in range(nr_pers):
         p=p*(365-i)/365

    return 1-p



def cerinta1_c(n,nr_sim):
    xs = range(50)
    ys1=[cerinta1_a(n,nr_sim) for n in xs]
    ys2=[cerinta1_b(n)for n in xs]
    subplot(1,2,1)
    plot(xs,ys2,'r*')
    grid()
    subplot(1,2,2)
    plot(xs,ys2,'r*')
    grid()
    show()


def patrat(nr_pct):
    E=[0.5,0.5]
    count = 0
    for i in range(nr_pct):
        F=[random(),random()]
        if dist(F,E) < 0.5:
            count+=1
            plot(F[0],F[1],"ro")
        else:
            plot(F[0],F[1],'bo')
    show()
    return count/nr_pct

def patrat2(nr_pct):
    count = 0
    A,B,C,D=[0,0],[1,0],[0,1],[1,1]
    E=[0.5,0.5]
    for i in range(nr_pct):
        F=[random(),random()]
        if dist(F,E) < min(dist(F,A),dist(F,B),dist(F,C),dist(F,D)):
            count+=1
            plot(F[0],F[1],"ro")
        else:
            plot(F[0],F[1],'bo')
    show()
    return count/nr_pct

def triunghi_ascutit(a, b, c):
   
    def squared_distance(p1, p2):
        return numpy.sum((p1 - p2) ** 2)
    
    ab2 = squared_distance(a, b)
    bc2 = squared_distance(b, c)
    ca2 = squared_distance(c, a)
    
    return (ab2 + bc2 > ca2) and (bc2 + ca2 > ab2) and (ca2 + ab2 > bc2)


def patrat3(nr_pct):
    
    
    
def main():
    print(cerinta1_a(700,1000))
    print(cerinta1_b(20))
    cerinta1_c(20,1000)
    print(patrat(1000))
    print(patrat2(1000))
   
main()
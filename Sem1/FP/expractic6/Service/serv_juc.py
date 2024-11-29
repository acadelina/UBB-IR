from Repository.repo_juc import*
from Domain.validator import *


class Service:
    def __init__(self,repo,val):
        self.__repo=repo
        self.__val=val
    def get_jucatori(self):
        """
        returneza o lista cu toti juctorii din fisier
        """
        return self.__repo.load_from_file()
    def adaugare(self,nume,prenume,inaltime,post):
        """
        Adauga un nou jucator validat in lista
        preconditii: nume->str
                     prenume->str
                     inaltime->int
                     post->str
        """
        jucator=Jucator(nume,prenume,inaltime,post)
        self.__val.validate(jucator)
        self.__repo.add(jucator)
    def modifica(self,nume,prenume,inaltime):
        """
        Functie care modifica inaltimea unui jucatore
        preconditii:nume->str
                    prenume->str
                    h->int
        postconditii:
        """
        l=self.get_jucatori()
        ind=self.__repo.find(nume,prenume)
        if ind==-1:
            raise ValueError("Jucatorul nu exista in lista!")
        l[ind].set_inaltime(inaltime)
        self.__repo.save_to_file(l)

    def echipa(self):
        """
        Functie care condtruieste o echipa
        """
        l=self.__repo.sort_h()
        rez=[]
        f=0
        e=0
        p=0
        for i in range(len(l)):
            if f<2 and l[i].get_post()=="fundas":
                rez.append(l[i])
                f+=1
            elif e<2 and l[i].get_post()=="extrema":
                rez.append(l[i])
                e+=1
            elif p<1 and l[i].get_post()=="pivot":
                rez.append(l[i])
                p+=1
        if f==2 and e==2 and p==1:
            return rez
        else:
            raise ValueError("Nu exista suficienti jucatori pentru o echipa!")
    def print_echipa(self):
        """
        Afiseaza echipa fromata
        """
        try:
            l=self.echipa()
        except ValueError as e:
            raise ValueError(e)
        print("Prenume    Nume    Post    Inaltime")
        for i in l:
            print(i.get_nume(),"  ",i.get_prenume(),"  ",i.get_post(),"  ",i.get_inaltime())
    def generare(self,filename):
        """
        Afiseaza numarul de jucatori importati
        preconditii: filename
        postconditii:
        """
        m=self.__repo.generate(filename)
        print("Numarul de jucatori importati: ",m)






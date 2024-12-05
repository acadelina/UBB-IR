from Domain.jucatori import*
import random
class Repository:
    def __init__(self,filename):
        self.__name=filename
    def load_from_file(self):
        """
        Functie care incarca datele din fisier intr-o lista
        preconditii:
        postconditii:l->list
        """
        l=[]
        f=open(self.__name,'r')
        text=f.read()
        lines=text.split('\n')
        for line in lines:
            if line!='':
                arg=line.split(',')
                jucator=Jucator(arg[0],arg[1],arg[2],arg[3])
                l.append(jucator)
        f.close()
        return l
    def save_to_file(self,l):
        """
        Salveaza in fisier lista data
        preconditii: l-> list of jucatori
        postconditii:
        """
        with open (self.__name,'w') as f:
            for j in l:
                str_j=str(j.get_nume())+','+str(j.get_prenume())+','+str(j.get_inaltime())+','+str(j.get_post())+'\n'
                f.write(str_j)
    def add (self,juc):
        """
        Adauga un nou jucator in fisier
        preconditii:juc->jucator
        postconditii
        """
        l=self.load_from_file()
        for j in l:
            if j.get_nume()==juc.get_nume() and j.get_prenume()==juc.get_prenume():
                raise ValueError("Jucatorul exista deja in lista")
        l.append(juc)
        self.save_to_file(l)
    def find(self,nume,prenume):
        """
        gaseste un jucator dupa nume si prenume
        preconditii:nume->str
                    prenume->str
        postconditii: i->indicele pozitiei jucatorului in lista
        """
        l=self.load_from_file()
        for i in range(len(l)):
            if l[i].get_nume()==nume and l[i].get_prenume()==prenume:
                return i
        return -1
    def sort_h(self):
        """
        Functie care sorteza lista jucatorilor dupa inaltime
        return: l->list
        """
        l=self.load_from_file()
        for i in range(len(l)-1):
            ind=i
            for j in range(i+1,len(l)):
                if l[j].get_inaltime()>l[i].get_inaltime():
                    ind=j
            if ind>i:
                l[ind],l[i]=l[i],l[ind]
        return l
    def load_nume_prenume(self,name):
        """
        Functie care incarca datele din fisier intr-o lista
        preconditii:name->str
        postconditii:n,p->lists
        """
        n=[]
        p=[]
        f=open(name,'r')
        text=f.read()
        lines=text.split('\n')
        for line in lines:
            if line!='':
                arg=line.split(',')
                n.append(arg[0])
                p.append(arg[1])
        f.close()
        return n,p
    def generate(self,name):
        """
        Genereaza inaltime si post pentru numele date si adauga juc valizi in fisier
        preconditii: name->str,nume fisier
        postconditii: m->int
        """
        n,p=self.load_nume_prenume(name)
        l=self.load_from_file()
        posturi=["fundas","extrema","pivot"]
        m=0
        for i in range (len(n)):
            ok=1
            for j in l:
                if j.get_nume()==n[i] and j.get_prenume()==p[i]:
                    ok=0
                    break
            if ok==1:
                h=random.randint(150,250)
                po=random.randint(0,2)
                juc=Jucator(n[i],p[i],h,posturi[po])
                l.append(juc)
                m+=1
        self.save_to_file(l)
        return m

            

        

from Domain.entitati import*
from datetime import datetime
class Repository:
    def __init__(self,filename):
        self.__filename=filename
    def load_from_file(self):
        """
        Incarca datele din fisier
        preconditii: 
        postconditii: l->list
        """
        f=open(self.__filename,'r')
        l=[]
        text=f.read()
        lines=text.split('\n')
        for line in lines:
            if line!='':
                arg=line.split(',')
                ev=Eveniment(arg[0],arg[1],arg[2])
                l.append(ev)
        f.close()
        return l
    def save_to_file(self,l):
        """
        Incarca lista l in fisier
        preconditii:l-> list
        postconditii:
        """
        with open(self.__filename,'w') as f:
            for e in l:
                str_e=str(e.get_data())+','+str(e.get_ora())+','+str(e.get_desc())+'\n'
                f.write(str_e)
    
    def get_day(self,day):
        """
        Furnizeaza o lista cu evenimentele din ziua data
        preconditii:day->data
        postconditii:rez->list
        """
        l=self.load_from_file()
        
        rez=[]
        for e in l:
            data=datetime.strptime(e.get_data(),"%d.%m.%Y")
            if data.day==day.day and data.month==day.month and data.year==day.year:
                rez.append(e)
        return rez

    def sort_ora(self,l):
        """
        Ordoneaza o lista de evenimente dupa ora
        preconditii:l->list
        postcondtii:l->list
        """
        for i in range(len(l)):
            for j in range(len(l)-i):
                if l[i+1].get_ora()<l[i].get_ora():
                    l[i],l[i+1]=l[i+1],l[i]
        return l
    
    def add(self,e):
        """
        Adauga un eveniment in fisier
        preconditii: e->eveniment
        postconditii:
        """
        l=self.load_from_file()
        ok=1
        for ev in l:
            if ev.get_data()==e.get_data() and ev.get_ora()==e.get_ora():
                ok=0
        if ok==0:
            raise ValueError("Evenimentul exista deja!")
        l.append(e)
        self.save_to_file(l)
    def get_sir(self,sir):
        """
        Furnizeaza o lista cu evenimentele ce contin sir in descriere
        preconditii: sir->str
        postconditii:l->list
        """
        l=self.load_from_file()
        rez=[]
        for e in l:
            if sir in e.get_desc():
                rez.append(e)
        
        return rez
    
    def sort_date_time(self,l):
        for i in range(len(l)):
            for j in range(len(l)-i):
                if l[i+1].get_data()<l[i].get_data() or  l[i+1].get_data()==l[i].get_data() and l[i+1].get_ora()<l[i].get_ora():
                    l[i],l[i+1]=l[i+1],l[i]
        return l

    def export(self,nume,l):
        """
        Exporta o lista intr-un fisier dat
        preconditii: nume->str
                     l->list
        postconditii:
        """
        with open(nume,'w') as f:
            for e in l:
                str_e=str(e.get_data())+','+str(e.get_ora())+','+str(e.get_desc())+'\n'
                f.write(str_e)

    def afisare(self,l):
        """
        Afiseaza lista l
        """
        for e in l:
            print("Data: ",e.get_data()," Ora: ",e.get_ora(),"Desc: ",e.get_desc())

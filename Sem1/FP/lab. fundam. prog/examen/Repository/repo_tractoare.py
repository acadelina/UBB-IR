from Domain.entitati import*
from datetime import datetime
class Repository:
    def __init__(self,filename):
        self.__filename=filename
        self.__undo=[]
    def load_from_file(self):
        """
        Functie care incarca datele din fisier intr-o lista
        preconditii:
        postconditii: l:list
        """
        f=open(self.__filename,'r')
        text=f.read()
        lines=text.split('\n')
        l=[]
        for line in lines:
            if line!='':
                arg=line.split(',')
                tr=Tractor(arg[0],arg[1],arg[2],arg[3],arg[4])
                l.append(tr)
        f.close()
        return l
    def save_to_file(self,l):
        """
        Salveaza lista data in fisier
        preconditii: l:list
        postconditii:
        """
        with open(self.__filename,'w') as f:
            for i in range(len(l)):
                str_tr=str(l[i].get_id())+','+str(l[i].get_denumire())+','+str(l[i].get_pret())+','+str(l[i].get_model())+','+str(l[i].get_data())+'\n'
                f.write(str_tr)
    def add(self,tractor):
        """
        Adauga un tractor nou in fisier
        preconditii: tractor:tractor
        postconditii:
        """
        l=self.load_from_file()
        for tr in l:
            if tr.get_id()==tractor.get_id():
                raise ValueError("Tractorul exista deja in lista!")
        self.update_undo()
        l.append(tractor)
        self.save_to_file(l)

    def delete(self,cif):
        """
        Sterge tractoarele care au cifra data in pret
        preconditii: cif:str
        potconditii: len(rez):int,nr tractoarelor sterse
        """
        l=self.load_from_file()
        
        rez=[tr for tr in l if cif not in tr.get_pret()]
        if len(rez)==len(l):
            raise ValueError("Nu exista tractoare cu cifra data in pret!")
        else:
            self.update_undo()
            self.save_to_file(rez)
            return len(l)-len(rez)

    def filtrare(self,denum,pret):
        """
        Creeaza o lista filtrata in functie de denumire si pret
        preconditii: denum:str
                     pret:int
        postconditii: rez:list
        """
        l=self.load_from_file()
        rez=[]
        if denum!='' and pret!=-1:
            for tr in l:
                if denum in tr.get_denumire() and tr.get_pret()<pret:
                    rez.append(tr)
        elif denum=='' and pret!=-1:
            for tr in l:
                if tr.get_pret()<pret:
                    rez.append(tr)
        elif pret==-1 and denum!='':
            for tr in l:
                if denum in tr.get_denumire():
                    rez.append(tr)
        else: rez=[]
        return rez
    
    def update_undo(self):
        """
        Functie care modifica undo-ul
        preconditii:
        postconditii:
        """
        l=self.load_from_file()
        self.__undo.append(l)
    def undo(self):
        """
        Functie care efectueaza undo-ul
        preconditii:
        postconditii:
        """
        if self.__undo!=[]:
            l=self.__undo.pop()
            self.save_to_file(l)
        else:
            raise ValueError("Nu exista operatii de adunare si stergere executate anterior!")

        




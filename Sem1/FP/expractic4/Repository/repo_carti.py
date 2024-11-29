from Domain.carti import*
class Repository:
    def __init__(self,filename):
        self.__file=filename
        self.__undolist=[]
    
    def load_from_file(self):
        """
        Functie care citeste datele din fisier si le pune intr o lista
        preconditii:
        postconditii: l->list
        """
        l=[]
        f=open(self.__file,'r')
        text=f.read()
        lines=text.split('\n')
        for line in lines:
            if line!='':
                arg=line.split(',')
                carte=Carte(arg[0],arg[1],arg[2],arg[3])
                l.append(carte)
        f.close()
        return l
    def save_to_file(self,lista):
        """
        Functie care salveaza datele dintr=o lista data in fisier
        preconditii: lista->list
        postconditii:
        """
        with open(self.__file,'w') as f:
            for c in lista:
                str_c=str(c.get_id())+','+str(c.get_titlu())+','+str(c.get_autor())+','+str(c.get_an())+'\n'
                f.write(str_c)


    def add_carte(self,carte):
        """
        Functie care adauga o carte noua in fisier
        preconditii: carte
        postconditii:
        raises: ValueError daca cartea exista deja
        """
        l=self.load_from_file()
        ok=1
        for c in l:
            if c.get_id()==carte.get_id():
                ok=0
        if ok==0:
            raise ValueError("Cartea exista deja in lista!")
        else:
            l.append(carte)
            self.save_to_file(l)
    def cif_an(self,cif):
        """
        Functie care creeaza o lista cu toate cartile a caror an de aparitie contine cifra data
        preconditii: cif->int
        postconditii: l->list
        """
        l=[]
        carti=self.load_from_file()
        for i  in range(len(carti)) :
            an=int(carti[i].get_an())
            ok=0
            while an!=0:
                c=an%10
                if c==cif:
                    ok=1
                an=an//10
            if ok==1:
                l.append(i)
        return l

    def del_carti(self,cifra):
        """
        Functie care sterge din fisier toate cartile a caror an de aparitie contine cifra data
        preconditii: cifra->int
        postconditii:
        """
        l=self.cif_an(cifra)
        carti=self.load_from_file()
        lista=[x for x in carti if cifra not in x.get_an()]
        self.update_undo(carti)
        for i in l:
            del carti[i]
        self.save_to_file(lista)
    
    def filtr(self,titlu,an):
        """
        Functie care creeaza o lista cu cartile ce sunt aparute inaintea anului dat si contin in titlu textul dat
        preconditii: titlu->str
                     an->str
        postconditii: l->list
        """
        lista=self.load_from_file()
        l=[]
        for carte in lista:
            if titlu in carte.get_titlu() and carte.get_an()<an:
                l.append(carte)
        return l
    
    def afisare(self,l):
        """
        Functie care afiseaza o lista data
        preconditii: l->list
        postconditii:
        """
        for i in l:
            print("Id: ",i.get_id(),", Titlu: ",i.get_titlu()," Autor: ",i.get_autor(),", An: ",i.get_an())
    
    def update_undo(self,l):
        """
        Functie care adauga o noua operatie la lista de undo
        """
        undo=self.__undolist
        new_l=[]
        for c in l:
            new_l.append(c)
        undo.append(new_l)
        self.__undolist=undo

    def undo(self):
        if len(self.__undolist)<=0:
            raise ValueError("Nu s au efectuat stergeri!")
        l=self.__undolist.pop()
        self.save_to_file(l)







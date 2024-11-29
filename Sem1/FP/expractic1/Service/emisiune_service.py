import random
class Service:
    def __init__(self,repository):
        self.__repo=repository

    def stergere_em(self,nume,tip):
        self.__repo.delete(nume,tip)
        
        
    def actualizare(self,nume,tip,durata,descriere):
        self.__repo.update(nume,tip,durata,descriere)
        
    def orar(self,ora1,ora2):
        l=self.__repo.load_from_file()
        nr_ore=ora2-ora1
        nr_curent=0
        nr_em=len(l)
        em=0
        lista=[]
        while   nr_curent<nr_ore and em!=nr_em:
            a=random.randint(0,nr_em-1)
            ok=1
            for i in range(len(lista)):
                if a==lista[i]:
                    ok=0
            if ok==1:
                em=em+1
                nr_curent=nr_curent+int(l[a].get_em_durata())
                lista.append(a)
        
        lista2=[]
        while nr_curent<nr_ore and em==nr_em:
            a=random.randint(0,nr_em-1)
            ok=1
            for i in range(len(lista2)):
                if a==lista2[i]:
                    ok=0
            if ok==1:
                em=em+1
                nr_curent=nr_curent+int(l[a].get_em_durata())
                lista2.append(a)

        return lista,lista2
    
    def creare_orar(self,o1,o2):
        l1,l2=self.orar(o1,o2)
        list=self.__repo.load_from_file()
        orar=[]
        for i in range (len(l1)):
            
                string=str(o1)+"   "+str(list[l1[i]].get_em_nume())+"  "+str(list[l1[i]].get_em_tip())+"  "+str(list[l1[i]].get_em_descriere())
                o1=o1+int(list[l1[i]].get_em_durata())
                orar.append(string)
        for i in range (len(l2)):
            
                string=str(o1)+"   "+str(list[l2[i]].get_em_nume())+"  "+str(list[l2[i]].get_em_tip())+"  ****"
                o1=o1+int(list[l2[i]].get_em_durata())
                orar.append(string)
        return orar


       


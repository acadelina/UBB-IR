from Domain.examene import*
from datetime import date

class Repository:
    def __init__(self,filename):
        self.__filename=filename
    def load_from_file(self):
        """
        Functie care incarca din fisier datele intr-o lista
        preconditii: 
        postconditii: lista->list
        """
        lista=[]
        f=open(self.__filename,'r')
        text=f.read()
        lines=text.split('\n')
        for line in lines:
            if line!='':
                arg=line.split(',')
                data=arg[0]
                ora=arg[1]
                materia=arg[2]
                tip=arg[3]
                exam=Examen(data,ora,materia,tip)
                lista.append(exam)
        f.close()
        return lista
    def save_to_file(self,lista):
        """
        Functie care salveaza in fisier o lista de date data
        preconditii: lista->list
        postconditii:
        """
        with open(self.__filename,'w') as f:
            for e in lista:
                str_e=str(e.get_data())+','+str(e.get_ora())+','+str(e.get_materia())+','+str(e.get_tip())+'\n'
                f.write(str_e)
        
    def next_day(self):
        """
        Functie care creeaza o lista cu examenele din ziua urmatoare
        preconditii:
        postconditii: lista->list
        """
        l=self.load_from_file()
        lista=[]
        zi=date.today().day
        luna=date.today().month
        if luna in [1,3,5,7,8,10,12] and zi==31:
            luna=luna+1
            zi=1
        elif luna==2 and zi==28:
            luna=luna+1
            zi=1
        elif luna in [4,6,9,11] and zi==30:
            luna=luna+1
            zi=1
        else:
            zi=zi+1
        for e in l:
            data=e.get_data()
            data=data.split('.')
            if int(data[0])==zi and int(data[1])==luna:
                lista.append(e)
        return lista
    
    def adauga(self,exam):
        l=self.load_from_file()
        for e in l:
            if e==exam:
                raise ValueError("Examenul este deja in lista!")
        l.append(exam)
        self.save_to_file(l)

    def next_3days(self,zi,luna):
        zi2=zi
        luna2=luna
        if luna in ['01','03','05','07','08','10','12'] and int(zi)+3>31:
            luna2=int(luna2)+1
            if luna2<10:
                luna2='0'+str(luna2)
            else: luna2=str(luna2)
            zi2=3-(31-int(zi2))
            if zi2<10:
                zi2='0'+str(zi2)
            else: zi2=str(zi2)
        elif luna=='02' and int(zi)+3>28:
            luna2=int(luna2)+1
            if luna2<10:
                luna2='0'+str(luna2)
            else: luna2=str(luna2)
            zi2=3-(28-int(zi2))
            if zi2<10:
                zi2='0'+str(zi2)
            else: zi2=str(zi2)
        elif luna in ['04','06','09','11'] and int(zi)>30:
            luna2=int(luna2)+1
            if luna2<10:
                luna2='0'+str(luna2)
            else: luna2=str(luna2)
            zi2=3-(30-int(zi2))
            if zi2<10:
                zi2='0'+str(zi2)
            else: zi2=str(zi2)
        else:
            zi2=int(zi2)+3
            if zi2<10:
                zi2='0'+str(zi2)
            else: zi2=str(zi2)
        l=self.load_from_file()
        
        lista=[]
        for e in l:
            data=e.get_data()
            data=data.split('.')
            if (data[1]==luna and data[0]>=zi and data[0]<zi2 and luna==luna2) or (data[1]==luna2 and data[0]<zi2)or(data[1]==luna and data[0]>=zi):
                lista.append(e)
        return lista
    
    def materie(self,mater):
        l=self.load_from_file()
        lista=[]
        for e in l:
            if e.get_materia()==mater:
                lista.append(e)
        return lista
    def greater_date(self,l1,l2):
        data1=l1.split('.')
        data2=l2.split('.')
        if data1[1]<data2[1]:
            return False
        if data1[1]==data2[1] and data1[0]<data2[0]:
            return False
        return True
        
    def sort (self,list):
        for i in range(len(list)-1):
            ind=i
            for j in range(i+1,len(list)):

                if self.greater_date(list[i].get_data(),list[j].get_data()) or list[i].get_data()==list[j].get_data() and list[i].get_ora()>list[j].get_ora():
                    ind=j
            if i<ind:
                list[i],list[ind]=list[ind],list[i]
        return list
    def export(self,name,materie):
        l=self.materie(materie)
        if len(l)>0:
            l=self.sort(l)
            with open(name,'w') as f:
                for e in l:
                    str_e=str(e.get_data())+','+str(e.get_ora())+','+str(e.get_materia())+','+str(e.get_tip())+'\n'
                    f.write(str_e)
        else:
            raise ValueError("Nu exista examene la materia data!")
    
    def afisare(self,lista):
        for e in lista:
            str_e=str(e.get_data())+','+str(e.get_ora())+','+str(e.get_materia())+','+str(e.get_tip())
            print(str_e)




        
        

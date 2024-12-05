from Domain.melodii import*
import random
class Repo_melodii:
    def __init__(self,filename):
        self.__filename=filename
    def load_from_file(self):
        """
        Functie care incarca datele din fisier sub forma unei liste cu melodii
        preconditii: 
        postconditii: l:list
        """
        l=[]
        f=open(self.__filename,'r')
        text=f.read()
        lines=text.split('\n')
        for line in lines:
            if line!='':
                arg=line.split(',')
                titlu=arg[0]
                artist=arg[1]
                gen=arg[2]
                durata=arg[3]
                mel=Melodie(titlu,artist,gen,durata)
                l.append(mel)
        f.close()
        return l
    
    def save_to_file(self,lista):
        """
        Functie care salveza in fisier o lista data
        preconditii: lista:list
        postconditii:
        """
        with open(self.__filename,'w') as f:
            for l in lista:
                str_mel=str(l.get_titlu())+','+str(l.get_artist())+','+str(l.get_gen())+','+str(l.get_durata())+'\n'
                f.write(str_mel)
        
    def update(self,melodie):
        """
        Functie care modifica o melodie existenta in lista
        preconditii: melodie
        postconditii:
        raises: ValueError daca melodia nu se afla in lista
        """
        l=self.load_from_file()
        titlu=melodie.get_titlu()
        artist=melodie.get_artist()
        ok=0
        for m in l:
            if m.get_titlu()==titlu and m.get_artist()==artist:
                m.set_gen(melodie.get_gen())
                m.set_durata(melodie.get_durata())
                ok=1
                break
        if ok==0:
            raise ValueError("Melodie inexistenta!")
        else:
            self.save_to_file(l)
    
    def adauga(self,melodie):
        """
        Functie care adauga o melodie nou in lista
        preconditii: melodie
        postconditii:
        raises: VslueError daca melodia deja exista in lista
        """
        ok=1
        l=self.load_from_file()
        for m in l:
            if m==melodie:
                ok=0
        if ok==0:
            raise ValueError("Melodia exista deja in lista!")
        else:
            l.append(melodie)
            self.save_to_file(l)
    
    def generate(self,s1,s2):
        """
        Functie care genereaza o melodie noua
        preconditii: s1,s2:str, sirurile cu artsti si titluri
        postconditii: melodie
        """
        l1=s1.split(',')
        l2=s2.split(',')
        genuri=["rock", "pop", "jazz", "altele"]
        a=random.randint(0,len(l1)-1)
        b=random.randint(0,len(l2)-1)
        c=random.randint(0,3)
        d=random.randint(100,420)
        melodie=Melodie(l1[a],l2[b],genuri[c],d)
        l=self.load_from_file()
        ok=1
        for i in l:
            if i.get_titlu()==l1[a] and i.get_artist()==l2[b]:
                ok=0
        if ok!=0:
            return melodie
        else: self.generate(s1,s2)

    def sort(self,l):
        """
        Functie care sorteza o lista dupa artist si titlu
        preconditii: l:list
        postconditii: l:list
         """
        for i in range(len(l)-1):
            ind=i
            for j in range(i+1,len(l)):
                if l[j].get_artist()<l[ind].get_artist() or (l[j].get_artist()==l[ind].get_artist() and l[j].get_titlu()<l[ind].get_titlu()):
                    ind=j
            if i<ind:
                l[ind],l[i]=l[ind],l[i]
        return l 
    
    def exp(self,name):
        """
        Functie car eexporta melodiile sortat
        preconditii: name:str
        postconditii:
        """
        l=self.load_from_file()
        l=self.sort(l)
        with open(name,'w') as f:
            for m in l:
                str_mel=str(m.get_titlu())+','+str(m.get_artist())+','+str(m.get_gen())+','+str(m.get_durata())+'\n'
                f.write(str_mel)








        


from Domain.piese import *
import random,string
class RepoPiese:
    def __init__(self,filename):
        self.__filename=filename

    def load_from_file(self):
        """
        Functie care incarca piesele din fisier
        preconditii: 
        postconditii: lista:list
        """
        f=open(self.__filename,'r')
        text=f.read()
        lines=text.split('\n')
        lista=[]
        for line in lines:
            if line!='':
                atr=line.split(',')
                titlu=atr[0]
                regizor=atr[1]
                gen=atr[2]
                durata=atr[3]
                piesa=Piese(titlu,regizor,gen,durata)
                lista.append(piesa)
        f.close()
        return lista
    
    def save_to_file(self,lista):
        """Functie care salveaza in fisier lista de piese
        preconditii: lista:list
        postconditii:
        """
        with open (self.__filename,'w') as f:
            for piesa in lista:
                str_piesa=str(piesa.get_titlu())+','+str(piesa.get_regizor())+','+str(piesa.get_gen())+','+str(piesa.get_durata())+'\n'
                f.write(str_piesa)
    
    def adauga_piesa(self,titlu,regizor,gen,durata):
        """
        Functie care adauga o noua piesa in fisier
        preconditii: titlu:str
                     regizor:str
                     gen:str
                     durata: int
        postconditii:
        """
        lista=self.load_from_file()
        piesa=Piese(titlu,regizor,gen,durata)
        ok=1
        for e in lista:
            if e==piesa:
                ok=0
        if ok==0:
            raise ValueError("Piesa exista deja in fisier!")
        lista.append(piesa)
        self.save_to_file(lista)

    def modifica_piesa(self,titlu,regizor,gen,durata):
        """
        Functie care modifica o piesa existenta in fisier
        preconditii: titlu:str
                     regizor:str
                     gen:str
                     durata: int
        postconditii:
        """
        lista=self.load_from_file()
        ok=0
        for piesa in lista:
            if piesa.get_titlu()==titlu and piesa.get_regizor()==regizor:
                piesa.set_durata(durata)
                piesa.set_gen(gen)
                ok=1
        if ok==0:
            raise ValueError("Piesa inexistenta!")
        else:
            self.save_to_file(lista)

    def random_titlu_reg(self):
         consonants = 'bcdfghjklmnpqrstvwxyz'
         vowels = 'aeiou'
         space = ' '

         length = random.randint(8, 12)
         start_with_consonant = random.choice([True, False])

         result = ''
         for i in range(length):
            if i == length // 2:
                result += space
            elif (i % 2 == 0 and start_with_consonant) or (i % 2 != 0 and not start_with_consonant):
                result += random.choice(consonants)
            else:
                result += random.choice(vowels)

         return result
    def random_gen(self):
        genuri=["Comedie", "Drama", "Satira", "Altele"]
        a=random.randint(0,3)
        return genuri[a]
    def random_durata(self):
        a=random.randint(3600,9000)
        return a
    

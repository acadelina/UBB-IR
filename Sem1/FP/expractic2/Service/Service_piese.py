from Repository.Repo import*
from Validators.Validare_piesa import*

class Service:
    def __init__(self,repo,val):
        self.__repo=repo
        self.__val=val
    def adauga(self,titlu,regizor,gen,durata):
        """
        Functie care adauga o noua piesa in fisier
        """
        self.__val.validare_durata(durata)
        self.__val.validare_gen(gen)
        self.__val.validare_regizor(regizor)
        self.__val.validare_titlu(titlu)
        self.__repo.adauga_piesa(titlu,regizor,gen,durata)

    def modifica(self,titlu,regizor,gen,durata):
        self.__val.validare_durata(durata)
        self.__val.validare_gen(gen)
        self.__val.validare_regizor(regizor)
        self.__val.validare_titlu(titlu)
        self.__repo.modifica_piesa(titlu,regizor,gen,durata)

    def generate(self,nr):
        lista=[]
        for i in range(nr):
            titlu=self.__repo.random_titlu_reg()
            reg=self.__repo.random_titlu_reg()
            durata=self.__repo.random_durata()
            gen=self.__repo.random_gen()
            self.__repo.adauga_piesa(titlu,reg,durata,gen)
            piesa=Piese(titlu,reg,durata,gen)
            lista.append(piesa)
        return lista
    
    def afisare(slef,lista):
        for i in range(len(lista)):
            print(lista[i].get_titlu()," ",lista[i].get_regizor()," ",lista[i].get_gen()," ",lista[i].get_durata())




from Repository.repo_melodii import*
from Validation.val_mel import*
class Service:
    def __init__(self,repo,val):
        self.__repo=repo
        self.__val=val
    def modificare(self,titlu,artist,gen,durata):
        """
        Functie care modifica o melodie
        preconditii:
                    titlu:str
                    artist:str
                    gen:str
                    durata:int
        postconditii:
        """
        melodie=Melodie(titlu,artist,gen,durata)
        self.__val.validare(melodie)
        self.__repo.update(melodie)
    def creare(self,n,s1,s2):
        """
        Functie care creaza n melodii in functie de stringurile date
        preconditii:
                    n:int
                    s1:str
                    s2:str
        postconditii:n:int
        """
        l=[]
        for i in range(n):
            m=self.__repo.generate(s1,s2)
            self.__repo.adauga(m)
        return n
    def export(self,filename):
        self.__repo.exp(filename)
from Domain.entitati import*
class Service:
    def __init__(self,repo,val):
        """Initializeaza clasa"""
        self.__repo=repo
        self.__val=val
    def adaugare(self,id,denumire,pret,model,data):
        """
        Valideaza datele si incarca un nou tractor in lista
        preconditii: id:int
                     denumire:str
                     pret:int
                     model:str
                     data:str
        postconditii:
        """
        self.__val.validare(id,denumire,pret,model,data)
        tractor=Tractor(id,denumire,pret,model,data)
        self.__repo.add(tractor)
    def stergere(self,cif):
        """
        Sterge din fisier tractoarele ce contin in pret o anumita cifra
        preconditii: cif:int
        potconditii:
        """
        nr=self.__repo.delete(cif)
        return nr
    def filtrare(self,denum,pret):
        """
        Returneaza tractoarele de au un anumit text in denumire si au pretul mai mic decat cel dat
        preconditii: denum:str
                     pret:int
        postconditii:
        """
        l=self.__repo.filtrare(denum,pret)
        
        return l
    def undo(self):
        """
        Efectueaza operatia de undo pt afisari/stergeri
        perconditii:
        potconditii:
        """
        self.__repo.undo()

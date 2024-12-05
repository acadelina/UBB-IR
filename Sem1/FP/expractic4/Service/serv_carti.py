from Repository.repo_carti import *

class Service:
    def __init__(self,repo):
        self.__repo=repo
    def adaugare(self,id,titlu,autor,an):
        """
        Functie care aduga o carte noua
        prec: id:
              titlu->str
              autor->str
              an->str
        postc:
        """
        carte=Carte(id,titlu,autor,an)
        self.__repo.add_carte(carte)
    def stergere(self,cifra):
        """
        Functie care sterge 
        prec: cifra->int
        postc:
        """
        self.__repo.del_carti(cifra)
    def filtrare(self,titlu,an):
        """
        Functie care afiseaza doar cartile care au un anumit text in titlu si sunt aprute inaintea unui an
        prec: titlu->str
              an->str
        postc: titlu->str
               an->str"""
        l=self.__repo.filtr(titlu,an)
        self.__repo.afisare(l)
        return titlu,an
    def undo(self):
        """
        Functie care face undo la ultima op de stergere
        """
        self.__repo.undo()

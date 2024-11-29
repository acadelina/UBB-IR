from Repository.repo_exam import*

class Service:
    def __init__(self,repo,val):
        self.__repo=repo
        self.__val=val
    def tipar_tomorrow(self):
        l=self.__repo.next_day()
        self.__repo.afisare(l)
    def add(self,data,ora,mat,tip):
        ex=Examen(data,ora,mat,tip)
        self.__val.validare(ex)
        self.__repo.adauga(ex)
    def set(self,data):
        zi,luna=data.split('.')
        l=self.__repo.next_3days(zi,luna)
        self.__repo.afisare(l)
    def export(self,name,materie):
        self.__repo.export(name,materie)
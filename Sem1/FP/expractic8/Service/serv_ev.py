from datetime import datetime
from Repository.repo_ev import*
class Service:
    def __init__(self,repo,val):
        self.__repo=repo
        self.__val=val
    def today(self):
        azi=datetime.today()
        l=self.__repo.get_day(azi)
        self.__repo.afisare(l)
    def adaugare(self,data,ora,desc):
        ev=Eveniment(data,ora,desc)
        self.__val.validare(ev)
        self.__repo.add(ev)
    def alta_data(self,data):
        l=self.__repo.get_day(data)
        self.__repo.afisare(l)
        
    def export(self,name,sir):
        l=self.__repo.get_sir(sir)
        self.__repo.export(name,l)

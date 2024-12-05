from Service.Service_piese import *
class Console:
    def __init__(self,serv):
        self.__serv=serv
    def meniu(self):
        print("Meniu: ")
        print("adauga_piesa")
        print("modifica_piesa")
        print("genereaza_piese")
        print("exit")
    def add(self):
        titlu=input("Dati titlu: ")
        regizor=input("Dati regizor: ")
        gen=input("Dati gen: ")
        durata=input("Dati durata(in secunde): ")
        try:
            self.__serv.adauga(titlu,regizor,gen,durata)
        except ValueError as e:
            print(str(e))
    def update(self):
        titlu=input("Dati titlu: ")
        regizor=input("Dati regizor: ")
        gen=input("Dati gen: ")
        durata=input("Dati durata(in secunde): ")
        try:
            self.__serv.modifica(titlu,regizor,gen,durata)
        except ValueError as e:
            print(str(e))
    def gen(self):
        nr=int(input("Dati numarul de piese generate: "))
        try:
           l= self.__serv.generate(nr)
           self.__serv.afisare(l)
        except ValueError as e:
            print(str(e))

    def run(self):
        
        while True:
            self.meniu()
            cmd=input(">").lower()
            cmd.strip()
            if cmd=="adauga_piesa":
                self.add()
            elif cmd=="modifica_piesa":
                self.update()
            elif cmd=="genereaza_piese":
                self.gen()
            elif cmd=="exit":
                break
            else :
                print("Comanda invalida")

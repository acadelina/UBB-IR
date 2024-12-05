
class Console:
    def __init__(self,serv):
        self.__serv=serv
    def print_meniu(self):
        print("MENIU")
        print("adauga")
        print("modifica")
        print("construieste_echipa")
        print("importa")
        print("exit")
    def adauga(self):
        nume=input("Dati nume:")
        prenume=input("Dati prenume")
        inaltime=input("Dati inaltime")
        post=input("Dati post:")
        try:
            self.__serv.adaugare(nume,prenume,inaltime,post)
        except ValueError as e:
            print(str(e))
    def modifica(self):
        nume=input("Dati nume:")
        prenume=input("Dati prenume")
        inaltime=input("Dati inaltime")
        try:
            self.__serv.modifica(nume,prenume,inaltime)
        except ValueError as e:
            print(str(e))
    def echipa(self):
        try:
            self.__serv.print_echipa()
        except ValueError as e:
            print(str(e))
    def importa(self):
        nume=input("Dati numele fisierului:")
        self.__serv.generare(nume)
    def run(self):
        while True:
            self.print_meniu()
            cmd=input(">")
            if cmd=="adauga":
                self.adauga()
            elif cmd=="modifica":
                self.modifica()
            elif cmd=="construieste_echipa":
                self.echipa()
            elif cmd=="importa":
                self.importa()
            elif cmd=="exit":
                break
            else:
                print("Comanda invalida!")
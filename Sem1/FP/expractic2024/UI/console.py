class Console:
    def __init__(self,serv):
        self.__serv=serv
    def print_meniu(self):
        print("MENIU:")
        print("adauga")
        print("seteaza_data")
        print("exporta")
        print("exit")
    def adauga(self):
        data=input("Dati data(format zi.luna):")
        ora=input("Dati ora(format ora:minut):")
        materie=input("Dati materie: ")
        tip=input("normal/restanta: ")
        try:
            self.__serv.add(data,ora,materie,tip)
        except ValueError as e:
            print(str(e))
    def seteaza(self):
        data=input("Dati data(format zi.luna): ")
        self.__serv.set(data)
        return data
    def exporta(self):
        nume=input("Dati nume fisier(format:nume.txt): ")
        materie=input("Dati materia: ")
        try:
            self.__serv.export(nume,materie)
        except ValueError as e:
            print(str(e))
    def run(self):
        self.__serv.tipar_tomorrow()
        data=''
        while True:
            self.print_meniu()
            if data!='':
                self.__serv.set(data)
            cmd=input(">")
            if cmd=="adauga":
                self.adauga()
            elif cmd=="seteaza":
                data=self.seteaza()
            elif cmd=="exporta":
                self.exporta()
            elif cmd=="exit":
                break
            else:
                print("Comanda invalida!")

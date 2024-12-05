from datetime import datetime
class Console:
    def __init__(self,serv):
        self.__serv=serv
    def print_meniu(self):
        print("MENIU:")
        print("adauga")
        print("stabileste_zi")
        print("exporta")
        print("exit")
    def adauga(self):
        data=input("DAti data:")
        ora=input("dati ora: ")
        desc=input("Dati descriere: ")
        try:
            self.__serv.adaugare(data,ora,desc)
        except ValueError as e:
            print(e)
    def stabileste(self):
        data=input("Dati data:")
        data=datetime.strptime(data,"%d.%m.%Y")
        self.__serv.alta_data(data)
        return data
    def exporta(self):
        num=input("Dati nume fisier:")
        sir=input("Dati sir de caractere: ")
        self.__serv.export(num,sir)
    def run(self):
        self.__serv.today()
        d=''
        while True:
            if d!='':
                self.__serv.alta_data(d)
            self.print_meniu()
            cmd=input("Dati comanda: ")
            if cmd=="adauga":
                self.adauga()
            elif cmd=="stabileste_zi":
                d=self.stabileste()
            elif cmd=="exporta":
                self.exporta()
            elif cmd=="exit":
                break
            else:
                print("Comanda invalida!")
        
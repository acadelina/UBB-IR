from Service.serv_carti import*

class Console:
    def __init__(self,serv):
        self.__serv=serv
    def print_meniu(self):
        print("MENIU:")
        print("adauga")
        print("sterge")
        print("filtreaza")
        print("undo")
        print("exit")
    def adauga(self):
        id=input("Dati id:")
        titlu=input("Dati titlu:")
        autor=input("Dati autor:")
        an=input("Dati an aparitie:")
        try:
            self.__serv.adaugare(id,titlu,autor,an)
        except ValueError as e:
            print(str(e))

    def sterge(self):
        cif=input("Dati cifra care apare in anul aparitiei: ")
        self.__serv.stergere(cif)
    def filtreaza(self):
        titlu=input("Dati text din titlu:")
        an=input("Dati an:")
        self.__serv.filtrare(titlu,an)
        return titlu,an
    def undo(self):
        try:
            self.__serv.undo()
        except ValueError as e:
            print(str(e))
    def run(self):
        titl=''
        an=''
        while True:
            self.print_meniu()
            if titl!='' and an!='':
                self.__serv.filtrare(titl,an)
            
            cmd=input(">")
            if cmd=="adauga":
                self.adauga()
            elif cmd=="sterge":
                self.sterge()
            elif cmd=="filtreaza":
                titl,an=self.filtreaza()
            elif cmd=="undo":
                self.undo()
            elif cmd=="exit":
                break
            else:
                print("Comanda invalida!")

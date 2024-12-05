from Service.service import*

class Console:
    def __init__(self,serv):
        self.__serv=serv
    def print_meniu(self):
        print("MENIU:")
        print("modifica")
        print("creeaza")
        print("exporta")
        print("exit")
    def modifica(self):
        titlu=input("Dati titlu: ")
        artist=input("Dati artist: ")
        gen=input("Dati gen: ")
        durata=input("Dati durata: ")
        try:
            self.__serv.modificare(titlu,artist,gen,durata)
            print("Modificare incheiata cu succes!")
        except ValueError as ve:
            print(str(ve))
    def creeaza(self):
        n=int(input("Dati numarul de melodii: "))
        s1=input("Dati artistii separati doar prin virgula: ")
        s2=input("Dati titlurile separate doar prin virgula: ")
        a=self.__serv.creare(n,s2,s1)
        print(a)
    def exporta(self):
        name=input("Dati numele fisierului(nume.txt): ")
        self.__serv.export(name)
    def run(self):
        while True:
            self.print_meniu()
            cmd=(input(">")).lower()
            cmd.strip()
            if cmd=="modifica":
                self.modifica()
            elif cmd=="creeaza":
                self.creeaza()
            elif cmd=="exporta":
                self.exporta()
            elif cmd=="exit":
                break
            else:
                print("Comanda invalida!")


from Service.emisiune_service import *
class Console:
    def __init__(self,service):
        self.__service=service
    def print_commands(self):
        print("sterge_emisiune")
        print("modifica_emisiune")
        print ("exit")

    def delete_em(self):
        try:
            nume=input("Introduceti numele emisiunii: ")
            tip=input("Introduceti tipul emisiunii: ")
            self.__service.stergere_em(nume,tip)
            print("Emisiune stearsa cu succes!")
        except ValueError as e:
            print("EROARE:"+str(e))

    def update_em(self):
        try:
            nume=input("Introduceti numele emisiunii: ")
            tip=input("Introduceti tipul emisiunii: ")
            durata=input("introduceti durata emisiunii: ")
            descriere=input("Introduceti descrierea emisiunii: ")
            self.__service.actualizare(nume,tip,durata,descriere)
            print("Emisiune modificata cu succes!")
        except ValueError as e:
            print("EROARE: "+str(e))
    def afisare_orar(self,l):

        print("Ora   Nume   Tip    Descriere")
        for i in range(len(l)):
            print(l[i])
    def orar(self):
        o1=int(input("Dati ora de inceput:"))
        o2=int(input("Dati ora de final: "))
        l=self.__service.creare_orar(o1,o2)
        self.afisare_orar(l)            
    def run(self):
        self.print_commands()
        while True:
            cmd=input(">").lower().strip(' ')
            if cmd=="sterge_emisiune":
                self.delete_em()
            elif cmd=="modifica_emisiune":
                self.update_em()
            elif cmd=="exit":
                break
            elif cmd=="orar":
                self.orar()
            else:
                print("Comanda invalida!")



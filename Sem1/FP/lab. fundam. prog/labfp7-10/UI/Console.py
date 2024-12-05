from Exceptions.Exc import *

class Console:
    def __init__(self,serv_filme,serv_clienti,serv_inchirieri):
        self.__serv_filme=serv_filme
        self.__serv_clienti=serv_clienti
        self.__serv_inchirieri=serv_inchirieri
        

    def __print_menu(self):
        print("1. Adauga client")
        print("2. Adauga film")
        print("3. Sterge client")
        print("4. Sterge film")
        print("5. Modifica client")
        print("6. Modifica film")
        print("7. Cauta client dupa id")
        print("8. Cauta film dupa id")
        print("9. Inchiriaza film")
        print("10. Returneaza film")
        print("11. Genereaza clienti")
        print("12. Genereaza filme")
        print("13. Clienti cu filme inchiriate ordonati dupa nume")
        print("14. Clienti cu filme inchiriate ordonati dupa numarul de filme inchiriate")
        print("15. Cele mai inchiriate filme")
        print("16. Primii 30 la suta clienti cu cele mai multe filme")
        print("17. Filmele cu un anumit gen ordonate dupa inchirieri si titlu")
        print("18. Afisare filme")
        print("19. Afisare clienti")
        print("0. Exit") 

    def __print_clienti(self,listac):
        if len(listac)==0:
            print("Nu exista clienti in lista.")
        else:
            print("Lista clienti: ")
            for client in listac:
                print('ID: ', client.getId(),'Nume: ', client.getNume(), 'CNP: ', client.getCnp(),'Filme: ',client.getFilme())
    
    def __add_client(self):
        id=int(input("ID client: "))
        nume=input("Nume client: ")
        try:
            cnp=input("CNP: ")
            added_client=self.__serv_clienti.add_client(id,nume,cnp)
            print("Clientul "+added_client.getNume()+' cu cnp '+ added_client.getCnp()+ 'a fost adaugat cu succes.')
        except ValidationException as ve:
            print(str(ve))
        except DuplicateIDException as e:
            print(str(e))
    def print_client(self,client):
        print("Client: "+str(client.getId())+';'+str(client.getNume())+';'+str(client.getCnp())+';'+str(client.getFilme()))
    def cauta_client(self):
        id=int(input("ID-ul clientului cautat: "))
        if self.__serv_clienti.cauta_client(id)==None:
            print("Client not found")
        else:
            self.print_client(self.__serv_clienti.cauta_client(id))
    def print_film(self,film):
        print("Film: "+str(film.getId())+";"+str(film.getTitlu())+";"+str(film.getDesc())+";"+str(film.getGen()))        
    def cauta_film(self):
        id=int(input("ID-ul filmului cautat: "))
        if self.__serv_filme.cauta_film(id)==None:
            print("Film not found")
        else:
            self.print_film(self.__serv_filme.cauta_film(id))

    def __delete_client(self):
        id=int(input("ID-ul clientului de sters: "))
        try:
            del_client=self.__serv_clienti.delete_client(id)
            print("Client sters cu succes!")
        except ClientNotFoundException as e:
            print(str(e))

    def __update_client(self):
        id=int(input("ID client: "))
        nume=input("Nume client: ")
        try:
            cnp=input("CNP: ")
            mod_client=self.__serv_clienti.update_client(id,nume,cnp)
            print('Clientul '+mod_client.getNume()+'cu cnp '+ mod_client.getCnp()+ 'a fost modificat cu succes.')
        except ValidationException as ve:
            print(str(ve))
        except DuplicateIDException as e:
            print(str(e))

    def __print_filme(self,listaf):
        if len(listaf)==0:
            print("Nu exista filme in lista.")
        else:
            print("Lista filme: ")
            for film in listaf:
                print('ID: ', film.getId(),'Titlu: ', film.getTitlu(), 'Descriere: ', film.getDesc(),'Gen: ', film.getGen())

    def __add_film(self):
        id=int(input("Dati id: "))
        titlu=input("Dati titlu: ")
        descriere=input("Dati descriere: ")
        gen=input("Dati gen: ")
        try:
            added_film=self.__serv_filme.add_Film(id,titlu,descriere,gen,0)
            print("Film adaugat cu succes!")
        except ValidationException as ve:
            print(str(ve))
        except DuplicateIDException as  e:
            print(str(e))
    
    def __delete_film(self):
        id=int(input("Dati id-ul filmului de sters"))
        try:
            del_film=self.__serv_filme.delete_Film(id)
            print("Film sters cu succes!")
        except FilmNotFoundException as e:
            print(str(e))
        
    def __update_film(self):
        id=int(input("Dati id: "))
        titlu=input("Dati titlu: ")
        descriere=input("Dati descriere: ")
        gen=input("Dati gen: ")
        try:
            mod_film=self.__serv_filme.update_Film(id,titlu,descriere,gen)
            print("Film modificat cu succes!")
        except ValidationException as ve:
            print(str(ve))
        except DuplicateIDException as  e:
            print(str(e))    
        
    def __print_inchirieri(self,listai):
        if len(listai)==0:
            print("Nu exista inchirieri in lista")
        else:
            print("Lista inchirieri: ")
            for inchiriere in listai:
                print('Client: ', str(inchiriere.getCl()), 'Film: ', str(inchiriere.getFl()))

    def __inchiriaza(self):
        idc=int(input("ID client: "))
        idf=int(input("ID film: "))
        try:
            inch=self.__serv_inchirieri.create_Inchiriere(idf,idc)
            print("Inchiriere incheiata cu succes!")
        except FilmNotFoundException as e:
            print(str(e))
        except ClientNotFoundException as e:
            print(str(e))
        except RentalAlreadyAssignedException as e:
            print(str(e))
    
    def __returneaza(self):
        idc=int(input("ID client: "))
        idf=int(input("ID film: "))
        try:
            inch=self.__serv_inchirieri.returnare(idc,idf)
            print("Returnare incheiata cu succes!")
        except FilmNotFoundException as e:
            print(str(e))
        except ClientNotFoundException as e:
            print(str(e))
        except RentalNotFoundException as e:
            print(str(e))

    def __genereaza_clienti(self):
        n=int(input("Dati numarul de clienti generati: "))
        self.__serv_clienti.genereaza_clienti(n)

    def __genereaza_filme(self):
        n=int(input("Dati numarul de filme generate: "))
        self.__serv_filme.genereaza_filme(n)

    def __cl_ord_nume(self):
        a=self.__serv_inchirieri.sort_nume()
        self.__print_clienti(a)
    def __cl_ord_inch(self):
        a=self.__serv_inchirieri.sort_inch()
        self.__print_clienti(a)

    def __top_filme(self):
        a=self.__serv_inchirieri.get_top_films()
        self.__print_filme(a)

    def __per30(self):
        a=self.__serv_inchirieri.per30()
        self.__print_clienti(a)

    def __filme_gen(self):
        try:
            gen=input("Dati genul filmelor: ")
            a=self.__serv_inchirieri.ord_gen(gen)
            self.__print_filme(a)
        except GenException as e:
            print(str(e))
        
    def afis_filme(self):
        self.__print_filme(self.__serv_filme.get_all())

    def afis_clienti(self):
        self.__print_clienti(self.__serv_clienti.get_all_clients())
    def ui(self):
            self.__print_menu()
            cmd=int(input("Comanda: "))
            if cmd==0:
                return
            if cmd==1:
                self.__add_client()
            elif cmd==3:
                self.__delete_client()
            elif cmd==2:
                self.__add_film()
            elif cmd==4:
                self.__delete_film()
            elif cmd==5:
                self.__update_client()
            elif cmd==6:
                self.__update_film()
            elif cmd==7:
                self.cauta_client()
            elif cmd==8:
                self.cauta_film()
            elif cmd==9:
                self.__inchiriaza()
            elif cmd==10:
                self.__returneaza()
            elif cmd==11:
                self.__genereaza_clienti()
            elif cmd==12:
                self.__genereaza_filme()
            elif cmd==13:
                self.__cl_ord_nume()
            elif cmd==14:
                self.__cl_ord_inch()
            elif cmd==15:
                self.__top_filme()
            elif cmd==16:
                self.__per30()
            elif cmd==17:
                self.__filme_gen()
            elif cmd==18:
                self.afis_filme()
            elif cmd==19:
                self.afis_clienti()
            else:
                print("Comanda invalida!")
            self.ui()
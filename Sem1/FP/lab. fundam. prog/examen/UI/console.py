from datetime import datetime
class Console:
    def __init__(self,serv):
        self.__serv=serv
    def print_meniu(self):
        """
        Functie care afiseaza meniul
        """
        print("MENIU:")
        print("adauga")
        print("sterge")
        print("filtreaza")
        print("undo")
        print("exit")
    def afisare_filtru(self,l):
        """
        Afiseaza tractoarele dupa aplicarea filtrarii
        preconditii: l:list
        postconditii:
        
        """
        print("Tractoare filtrate:")
        today=datetime.today()
        for tr in l:
            data=datetime.strptime(tr.get_data(),"%d.%m.%Y")
            if int(data.year) <int(today.year) or (int(data.year)==int(today.year) and int(data.month)<int(today.month)) or (int(data.year)==int(today.year) and int(data.month)==int(today.month) and int(data.day)<int(today.day)) :
                data="*"
            else: data=tr.get_data()
            #str_tr=str(tr.get_id())+','+str(tr.get_denumire())+','+str(tr.get_pret())+','+str(tr.get_model())+','+str(data)+'\n'
            print("ID: ",tr.get_id(),", denumire: ",tr.get_denumire(),", pret: ",tr.get_pret(),", model: ",tr.get_model(),", data: ",data)
    def adauga(self):
        """
        Functie care citeste datele necesare pt adaugare si efectueaza adauggarea
        """
        id=input("Dati id: ")
        denumire=input("Dati denumire: ")
        pret=input("Dati pret: ")
        model=input("Dati model: ")
        data=input("Dati data(zi.luna.an): ")
        try:
            self.__serv.adaugare(id,denumire,pret,model,data)
        except ValueError as e:
            print(str(e))
    def sterge(self):
        """
        Functie care citeste datele necesare pt stergere si efectueaza stergerea
        """
        cif=input("Dati cifra: ")
        try:
            nr=self.__serv.stergere(cif)
            print("Numarul de tractoare sterse: ",nr)
        except ValueError as e:
            print(str(e))
    def filtreaza(self):
        """
        Functie care citeste datele necesare pt filtrare si efectueaza filtrarea
        """
        denum=input("Dati textul ce se afla in denumire: ")
        pret=input("Dati pretul maxim: ")
        l=self.__serv.filtrare(denum,pret)
        self.afisare_filtru(l)
        return denum,pret
    def undo(self):
        """
        Functie care efectueaza undo-ul
        raises: ValueError daca nu se pot efectua operatii de undo
        """
        try:
            self.__serv.undo()
        except ValueError as e:
            print(str(e))
    def run(self):
        """
        Meniul principal
        """
        denum=''
        pret=-1
        while True:
            self.print_meniu()
            self.__serv.filtrare(denum,pret)
            cmd=input(">")
            if cmd=="adauga":
                self.adauga()
            elif cmd=="sterge":
                self.sterge()
            elif cmd=="filtreaza":
                denum,pret=self.filtreaza()
            elif cmd=="undo":
                self.undo()
            elif cmd=="exit":
                break
            else :
                print("Comanda invalida!")
            
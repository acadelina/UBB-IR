from Domain.Inchiriere import Inchiriere
from Exceptions.Exc import *
from Repsitory.Inchirieri import*
from Repsitory.Client import*
from Repsitory.Film import*
from Service.Sortari import*


class InchiriereService:
    def __init__(self, Inchiriere_repo, film_repo, client_repo):
        self.__Inchiriere_repo = Inchiriere_repo
        self.__film_repo = film_repo
        self.__client_repo = client_repo
        

    def create_Inchiriere(self, film_id, client_id):
        """
        Creeaza un Inchiriere
        :param film_id: id-ul film-ului evaluat
        :type film_id: str
        :param client_id: id-ul clientului care evalueaza
        :type client_id: str
        :param no_stars: numarul de stele acordate serialului (1-5)
        :type no_stars: float
        :return: Inchirierea creata cu datele date
        :rtype: Inchiriere
        :raises: filmNotFoundException
                 ClientNotFoundException
                 ValidationException
                 InchiriereAlreadyAssignedException
        """
        film = self.__film_repo.find(film_id)
        if film is None:
            raise FilmNotFoundException()

        client = self.__client_repo.find(client_id)

        if client is None:
            raise ClientNotFoundException()
        
        inchiriere = Inchiriere(client_id, film_id)
        inc=self.__Inchiriere_repo.find(inchiriere)
        if inc is not None:
            raise RentalAlreadyAssignedException()
        self.__Inchiriere_repo.store(inchiriere)
        self.__film_repo.inc_inchirieri(film)
        return inchiriere
    
    def returnare(self,client_id, film_id):
        """
        Fucntie care efectueaza returnarea unui film
        preconsitii: client_id: int, film_id:int
        postconditii: 
        """
        film = self.__film_repo.find(film_id)
        if film is None:
            raise FilmNotFoundException()
        client = self.__client_repo.find(client_id)
        if client is None:
            raise ClientNotFoundException()
        inchiriere = Inchiriere(client_id,film_id)
        inc=self.__Inchiriere_repo.find(inchiriere)
        if inc is None:
            raise RentalNotFoundException()
        self.__Inchiriere_repo.delete(inchiriere)
        

    def get_all(self):
        """
        Functie care returneza lista inchirierilor
        """
        return self.__Inchiriere_repo.get_all()

    def get_top_films(self):
        """
        Returneaza filmele cu cele mai multe Inchirieri
        preconditii:
        postconditii: v:list
        """
        filme=self.__film_repo.get_all()
        max=0
        v=[]
        for film in filme:
            nr=film.getInc()
            if nr > max:
                max=nr
        for film in filme:
            nr=film.getInc()
            if nr == max:
                v.append(film)
        
        return v
        
    def lfilme_gen(self,gen):
        """
        Returneaza lista cu filmele de un anumit gen care au fost inchiriate
        preconditii: gen
        postconditii: lista filme
        """
        v=[]
        filme=self.__film_repo.get_all()
        for film in filme:
            if film.getGen()==gen and film.getInc()>0:
                v.append(film)
        return v
    
    def swap(self,l, a, b):
        """
        Interschimba_2_clienti
        preconditii: l:lista, a:, b:
        postconditii: lista modificata
        """
        l[a], l[b] = l[b], l[a]
        return l

    def ord_gen(self,gen):
        """
        Functie care ordoneaza filmele de un anumit gen dupa nume si inchirieri
        preconditii: gen
        postconditii: lista filme
        """
        
        gen_ok = ["Comedy","Thriller","Horror","Action","Animation","Drama","Musical","Romance","Fantasy","SF","altele"]
        if gen not in gen_ok:
            raise GenException
        
        v=self.lfilme_gen(gen)
        v=merge_sort(v,key=lambda x:x.getTitlu(),key2=lambda x:x.getInc())
        """for i in range(len(v)):
            for j in range(len(v)-1):
                if v[j].getInc()>v[j+1].getInc():
                    self.swap(v,j,j+1)
                elif v[j].getInc()==v[j+1].getInc() and v[j].getTitlu()>v[j+1].getTitlu():
                    self.swap(v,j,j+1)"""
        return v

    def lclienti_inch(self):
        """
        Functie care returneaza lista cu clientii care au filme inchiriate
        preconditii:
        postconditii: lista
        """
        v=[]
        inchiriere=self.get_all()
        for i in range( len(inchiriere)):
            ok=1
            for j in range (len(v)):
                if int(v[j].getId())==int(inchiriere[i].getCl()):
                    ok=0
            if ok==1:
                v.append(self.__client_repo.find(inchiriere[i].getCl()))
        return v
    
    def sort_nume(self):
        """
        Functie care ordoneaza clientii cu filme inchiriate dupa nume
        preconditii:
        postconditii: lista sortata
        """
        v=self.lclienti_inch()
        if len(v)>0:
            v=bingoSort(v,key=lambda x:x.getNume())
        """for i in range (len(v)):
            for j in range (len(v)-1):
                c=self.__client_repo.find(v[j])
                c1=self.__client_repo.find(v[j+1])
                if v[j].getNume()>v[j+1].getNume():
                    self.swap(v,j,j+1)"""
        return v

    def nr_filme(self,v):
        """
        Functie care creeaza o lista cu nr de inchirieri ale clientilor
        preconditii: v:list
        postconditii: a:list
        """
        a=[]
        b=self.get_all()
        for i in range(len(v)):
            nr=0
            for j in range(len(b)):
                if v[i].getId()==b[j].getCl():
                    nr+=1
            v[i].setFilme(nr)
            a.append(nr)
        return a    

    def sort_inch(self):
        """
        Functie care sorteaza o lista de clienti in functie de numarul de inchirieri
        preconditii: listac:lista
        postconditii: lista sortata
        """
        
        v=self.lclienti_inch()
        z=self.nr_filme(v)
        v=bingoSort(v,key=lambda x:x.getFilme())
        
        """for i in range(len(z)):
            for j in range(len(z)-1):
                if z[j]>z[j+1]:
                    self.swap(z,j,j+1)
                    self.swap(v,j,j+1)"""
        return v
    
    def per30(self):
        """
        Functie care creeaza o lista cu primii 30% clienti cu cele mai multe inchirieri
        preconditii:
        postconditii: f:list
        """
        v=self.__client_repo.get_all()
        z=self.nr_filme(v)
        #for i in range(len(v)):
           # print('ID: ', v[i].getId(),'Nume: ', v[i].getNume(), 'CNP: ', v[i].getCnp(),'Filme: ',v[i].getFilme())
        v=bingoSort(v,key=lambda x:x.getFilme())
        #for i in range(len(v)):
            #print('ID: ', v[i].getId(),'Nume: ', v[i].getNume(), 'CNP: ', v[i].getCnp(),'Filme: ',v[i].getFilme())
        """for i in range(len(v)):
            for j in range(len(v)-1):
                if z[j]<z[j+1]:
                    self.swap(z,j,j+1)
                    self.swap(v,j,j+1)"""
        l=len(v)
        nr=int(0.3*l)
        f=[]
        
        for i in range(nr):
            f.append(v[l-i-1])
        return f

   
def test_create_Inchiriere():
    irepo=InchirieriInMemoryRepo()
    crepo=ClientInMemoryRepo()
    frepo=filmInMemoryRepo()
    test_serv=InchiriereService(irepo,frepo,crepo)
    crepo.store(Client(1,"Nume","1260406160861"))
    frepo.store(Film(234,"Cinderella","najje jed","Fantasy",0))
    test_serv.create_Inchiriere(234,1)
    assert len(test_serv.get_all())==1
    try:
        test_serv.create_Inchiriere(234,1)
        assert False
    except RentalAlreadyAssignedException:
        assert True

def test_returnare():
    irepo=InchirieriInMemoryRepo()
    crepo=ClientInMemoryRepo()
    frepo=filmInMemoryRepo()
    test_serv=InchiriereService(irepo,frepo,crepo)
    crepo.store(Client(1,"Nume","1260406160861"))
    frepo.store(Film(234,"Cinderella","najje jed","Fantasy",0))
    test_serv.create_Inchiriere(234,1)
    assert len(test_serv.get_all())==1
    test_serv.returnare(1,234)
    assert len(test_serv.get_all())==0
    try:
        test_serv.returnare(1,23)
        assert False
    except FilmNotFoundException:
        assert True

    try:
        test_serv.returnare(1,234)
        assert False
    except RentalNotFoundException:
        assert True
    
def test_get_top_films():
    irepo=InchirieriInMemoryRepo()
    crepo=ClientInMemoryRepo()
    frepo=filmInMemoryRepo()
    test_serv=InchiriereService(irepo,frepo,crepo)
    crepo.store(Client(1,"Nume","1260406160861"))
    assert test_serv.get_top_films()==[]
    frepo.store(Film(234,"Cinderella","najje jed","Fantasy",0))
    frepo.store(Film(2,"Cila","najje jed","Fantasy",0))
    frepo.store(Film(3,"Cila","najje jed","Fantasy",0))
    
    test_serv.create_Inchiriere(234,1)
    test_serv.create_Inchiriere(2,1)
    assert test_serv.get_top_films()==[Film(234,"Cinderella","najje jed","Fantasy",0),Film(2,"Cila","najje jed","Fantasy",0)]
    test_serv.create_Inchiriere(3,1)
    assert test_serv.get_top_films()==[Film(234,"Cinderella","najje jed","Fantasy",0),Film(2,"Cila","najje jed","Fantasy",0),Film(3,"Cila","najje jed","Fantasy",0)]
    
def test_lfilme_gen():
    irepo=InchirieriInMemoryRepo()
    crepo=ClientInMemoryRepo()
    frepo=filmInMemoryRepo()
    test_serv=InchiriereService(irepo,frepo,crepo)
    crepo.store(Client(1,"Nume","1260406160861"))
    frepo.store(Film(234,"Cinderella","najje jed","Action",0))
    frepo.store(Film(2,"Cila","najje jed","Fantasy",0))
    frepo.store(Film(3,"Cila","najje jed","Fantasy",0))
    assert test_serv.lfilme_gen("Action")==[]
    test_serv.create_Inchiriere(234,1)
    test_serv.create_Inchiriere(2,1)
    test_serv.create_Inchiriere(3,1)
    assert test_serv.lfilme_gen("Action")==[Film(234,"Cinderella","najje jed","Action",0)]
    assert test_serv.lfilme_gen("altele")==[]
    assert test_serv.lfilme_gen("Fantasy")==[Film(2,"Cila","najje jed","Fantasy",0),Film(3,"Cila","najje jed","Fantasy",0)]

def test_ord_gen():
    irepo=InchirieriInMemoryRepo()
    crepo=ClientInMemoryRepo()
    frepo=filmInMemoryRepo()
    test_serv=InchiriereService(irepo,frepo,crepo)
    crepo.store(Client(1,"Nume","1260406160861"))
    frepo.store(Film(234,"Cinderella","najje jed","Action",0))
    frepo.store(Film(2,"Cilb","najje jed","Fantasy",0))
    frepo.store(Film(3,"Cila","najje jed","Fantasy",0))
    
    test_serv.create_Inchiriere(234,1)
    test_serv.create_Inchiriere(2,1)
    test_serv.create_Inchiriere(3,1)
    assert test_serv.ord_gen("Fantasy")==[Film(3,"Cila","najje jed","Fantasy",1),Film(2,"Cilb","najje jed","Fantasy",1)]
    assert test_serv.ord_gen("altele")==[]
    
def test_lclienti_inch():
    irepo=InchirieriInMemoryRepo()
    crepo=ClientInMemoryRepo()
    frepo=filmInMemoryRepo()
    test_serv=InchiriereService(irepo,frepo,crepo)
    crepo.store(Client(1,"Nume","1260406160861"))
    crepo.store(Client(2,"Adi","1260406160863"))
    frepo.store(Film(234,"Cinderella","najje jed","Action",0))
    frepo.store(Film(2,"Cilb","najje jed","Fantasy",0))
    frepo.store(Film(3,"Cila","najje jed","Fantasy",0))
    test_serv.create_Inchiriere(234,1)
    test_serv.create_Inchiriere(2,1)
    assert len(test_serv.lclienti_inch())==1
    test_serv.create_Inchiriere(3,2)
    assert len(test_serv.lclienti_inch())==2

def test_sort_nume():
    irepo=InchirieriInMemoryRepo()
    crepo=ClientInMemoryRepo()
    frepo=filmInMemoryRepo()
    test_serv=InchiriereService(irepo,frepo,crepo)
    crepo.store(Client(1,"Nume","1260406160861"))
    crepo.store(Client(2,"Adi","1260406160863"))
    frepo.store(Film(234,"Cinderella","najje jed","Action",0))
    frepo.store(Film(2,"Cilb","najje jed","Fantasy",0))
    frepo.store(Film(3,"Cila","najje jed","Fantasy",0))
    assert test_serv.sort_nume()==[]
    test_serv.create_Inchiriere(234,1)
    test_serv.create_Inchiriere(2,1)
    test_serv.create_Inchiriere(3,2)
    #assert test_serv.sort_nume()==[Client(2,"Adi","1260406160863"),Client(1,"Nume","1260406160861")]

def test_nr_filme():
    irepo=InchirieriInMemoryRepo()
    crepo=ClientInMemoryRepo()
    frepo=filmInMemoryRepo()
    test_serv=InchiriereService(irepo,frepo,crepo)
    crepo.store(Client(1,"Nume","1260406160861"))
    crepo.store(Client(2,"Adi","1260406160863"))
    frepo.store(Film(234,"Cinderella","najje jed","Action",0))
    frepo.store(Film(2,"Cilb","najje jed","Fantasy",0))
    frepo.store(Film(3,"Cila","najje jed","Fantasy",0))
    v=test_serv.lclienti_inch()
    assert test_serv.nr_filme(v)==[]
    test_serv.create_Inchiriere(234,1)
    v=test_serv.lclienti_inch()
    assert test_serv.nr_filme(v)==[1]
    test_serv.create_Inchiriere(2,1)
    v=test_serv.lclienti_inch()
    assert test_serv.nr_filme(v)==[2]
    test_serv.create_Inchiriere(3,2)
    v=test_serv.lclienti_inch()
    assert test_serv.nr_filme(v)==[2,1]

def test_per30():
    irepo=InchirieriInMemoryRepo()
    crepo=ClientInMemoryRepo()
    frepo=filmInMemoryRepo()
    test_serv=InchiriereService(irepo,frepo,crepo)
    crepo.store(Client(1,"Nume","1260406160861"))
    crepo.store(Client(2,"Adi","1260406160863"))
    crepo.store(Client(3,"Ade","1260406160862"))
    crepo.store(Client(4,"Ale","1260406160864"))
    frepo.store(Film(234,"Cinderella","najje jed","Action",0))
    frepo.store(Film(2,"Cilb","najje jed","Fantasy",0))
    frepo.store(Film(3,"Cila","najje jed","Fantasy",0))
    frepo.store(Film(4,"Cila","najje jed","Fantasy",0))
    assert test_serv.sort_nume()==[]
    test_serv.create_Inchiriere(234,1)
    test_serv.create_Inchiriere(2,4)
    test_serv.create_Inchiriere(3,2)
    test_serv.create_Inchiriere(4,4)
    assert len(test_serv.per30())==1


test_create_Inchiriere()
test_returnare()
test_get_top_films()
test_lfilme_gen()
test_ord_gen()
test_lclienti_inch()
test_sort_nume()
test_nr_filme()
test_per30()

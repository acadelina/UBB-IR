from Domain.dtos import ClientFilmInc
from Domain.Inchiriere import Inchiriere
from Exceptions.Exc import *
class InchirieriInMemoryRepo:
    def __init__(self):
        self.__inchirieri = []

    def find(self, r):
        """
        Cauta inchiriere in lista de evaluari
        preconditii: inchirierea cautata, r: inchiriere
        postconditii: inchirierea cautata daca exista in lista, None altfel
        
        """
        for inchiriere in self.__inchirieri:
            if r == inchiriere:
                return inchiriere
        return None
    
    def delete(self,r):
        """
        Functie care sterge o inchiriere data
        preconditii: r: Inchiriere
        postconditii: 
        """
        i=self.find(r)
        if i is None:
            raise RentalNotFoundException()
        for j in range(len(self.__inchirieri)):
            if self.__inchirieri[j]==i:
                m=j
        del self.__inchirieri[m]



    def store(self, inchiriere):
        """
        Adauga o evaluare
        preconditii: inchiriere: 
        postconditii: se adauga inchiriere la lista 
        """
        r = self.find(inchiriere)
        if r is not None:
            raise RentalAlreadyAssignedException()
        self.__inchirieri.append(inchiriere)

    def get_all(self):
        """
        Returneaza o lista cu toate evaluarile disponibile
        postconditii: lista cu evaluarile disponibile
        
        """
        return self.__inchirieri

    def delete_all(self):
        self.__inchirieri = []

def setup_test_repo():
    inchiriere1 = Inchiriere('1','2')
    inchiriere2 = Inchiriere('2','5')
    inchiriere3 = Inchiriere('3','4')
    inchiriere4 = Inchiriere('5','10')
    
    
    test_repo = InchirieriInMemoryRepo()
    test_repo.store(inchiriere1)
    test_repo.store(inchiriere2)
    test_repo.store(inchiriere3)
    test_repo.store(inchiriere4)
    
    return test_repo


def test_find():
    test_repo = setup_test_repo()

    p = test_repo.find(Inchiriere('1','2'))
    assert (p.getCl() == 1)
    assert (p.getFl() == 2)
   

    p1 = test_repo.find(Inchiriere('100','7'))
    assert (p1 is None)


def test_get_all():
    test_repo1 = setup_test_repo()
    crt_inchirierei = test_repo1.get_all()
    assert (type(crt_inchirierei) == list)
    assert (len(crt_inchirierei) == 4)

    test_repo1.delete(Inchiriere('1','2'))
    test_repo1.delete(Inchiriere('2','5'))

    crt_inchirierei = test_repo1.get_all()
    assert (len(crt_inchirierei) == 2)

    test_repo1.store(Inchiriere('6','9'))
    assert (len(test_repo1.get_all()) == 3)

    
    assert (test_repo1.get_all()[-1].getCl() ==6)
    assert (test_repo1.get_all()[-1].getFl() ==9)

    


def test_store():
    test_repo = InchirieriInMemoryRepo()
    inchiriere1 = Inchiriere('1','2')
    test_repo.store(inchiriere1)

    assert (len(test_repo.get_all()) == 1)
    inchiriere2 = Inchiriere('2','8')
    test_repo.store(inchiriere2)
    assert (len(test_repo.get_all()) == 2)

    try:
        
        test_repo.store(inchiriere2)
        assert False
    except RentalAlreadyAssignedException:
        assert True


def test_delete():
    test_repo = InchirieriInMemoryRepo()
    inchiriere1 = Inchiriere('1','2')
    test_repo.store(inchiriere1)
    inchiriere2 = Inchiriere('2','8')
    test_repo.store(inchiriere2)
    

    test_repo.delete(inchiriere1)
    
    assert (len(test_repo.get_all() )== 1)

    
    try:
        test_repo.delete(Inchiriere('4','8'))
        assert False
    except RentalNotFoundException:
        assert True



test_delete()
test_find()
test_get_all()
test_store()


class inchiriereRepoFile:
    def __init__(self, filename):
        self.__filename = filename
        

    def __load_from_file(self):
        """
        Incarca din fisier inchirierile
        preconditii:
        postconditii:

        """
        
        try:
            f = open(self.__filename, 'r')
           
        except IOError:
            raise CorruptedFileException()

        lines = f.readlines()
        
        inch=[]
        for line in lines:
            
            idc,idf= [token.strip() for token in line.split(';')]
            a = Inchiriere(idc, idf)
            inch.append(a)
        f.close()
        return inch

    def __save_to_file(self,list):
        """
        Salveaza lista inchirierilor in fisier
        preconditii:
        postconditii: fisierul schimbat
        """
        inchirieri_list = list
        with open(self.__filename, 'w') as f:
            for inchiriere in inchirieri_list:
                inchiriere_string = str(inchiriere.getCl()) + ';' + str(inchiriere.getFl()) + '\n'
                f.write(inchiriere_string)

    def find(self, r):
        """
        Cauta inchiriere in lista
        preconditii: inchirierea cautat
        postconditii: inchirierea cautat daca exista in lista, None altfel
        """
        all_inch=self.__load_from_file()
        for i in range(len(all_inch)):
            if r==all_inch[i]:
                return r
        return None

    def store(self, inchiriere):
        """
        Adauga o inchiriere
        preconditii: inchiriere:inchiriere de adaugat
        postconditii: se adauga inchiriere la lista
        """
        all_inch=self.__load_from_file()
        if self.find(inchiriere) is None:
            all_inch.append(inchiriere)
            self.__save_to_file(all_inch)
        else:
            raise RentalAlreadyAssignedException

    def get_all(self):
        """
        Returneaza o lista cu toate inchirierile 
        postconditii: lista cu inchirierile 
        
        """
        return self.__load_from_file()

    def delete_all(self):
        """
        Functie care sterge toate inchirierile din fisier
        """
        self.__save_to_file([])

    def delete(self,r):
        """
        Functie care sterge inchirierea data
        preconditii: r:Inchiriere
        postconditii:
        """
        all_inch=self.__load_from_file()
        if self.find(r) is None:
            raise RentalNotFoundException
        for i in range(len(all_inch)):
            if all_inch[i]==r:
                m=i
        del all_inch[m]
        self.__save_to_file(all_inch)

    def get_all_for_client(self, client_id):
        """
        Gaseste toate inchirierile aferente unui client dat
        :param client_id: id-ul clientului
        :type client_id:str
        postconditii: lista cu obiecte inchirierile clientului)
        :rtype: list 
        """
        all_inchirieri = self.get_all()
        client_inchirieri = []

        for inchiriere in all_inchirieri:
            if inchiriere.getCl() == client_id:
                client_inchiriere =ClientFilmInc(inchiriere.getCl(), inchiriere.getFl())
                client_inchirieri.append(client_inchiriere)

        return client_inchirieri

    
def test_read_from_file():
    
    test_repo = inchiriereRepoFile("data/test_inchirieri.txt")
    test_repo.delete_all()
    assert (len(test_repo.get_all()) == 0)


def test_store_repo_file():
    
    test_repo = inchiriereRepoFile("data/test_inchirieri.txt")
    test_repo.delete_all()
    
    inchiriere1 = Inchiriere('1','2')
    test_repo.store(inchiriere1)
    assert (len(test_repo.get_all()) == 1)
    inchiriere2 = Inchiriere('2','8')
    test_repo.store(inchiriere2)
    assert (len(test_repo.get_all()) == 2)
   

    try:
        
        test_repo.store(inchiriere1)
        assert False
    except RentalAlreadyAssignedException:
        assert True



def test_find_repo_file():
    
    test_repo = inchiriereRepoFile("data/test_inchirieri.txt")

    assert (len(test_repo.get_all()) == 2)

    

    assert (test_repo.find(Inchiriere('1','2')) is not None)
    assert (test_repo.find(Inchiriere('2','8')) is not None)
    assert (test_repo.find(Inchiriere('1','20')) is  None)
    assert (test_repo.find(Inchiriere('1','4')) is None)


def test_delete_repo_file():
    
    test_repo = inchiriereRepoFile("data/test_inchirieri.txt")
    
    assert (len(test_repo.get_all()) == 2)

    deleted_film = test_repo.delete(Inchiriere('1','2'))
    assert (len(test_repo.get_all()) == 1)
    assert (test_repo.find(Inchiriere('1','2')) is None)
    

    

    test_repo.store(Inchiriere('3','7'))
    assert (len(test_repo.get_all()) == 2)

    deleted_film = test_repo.delete(Inchiriere('3','7'))
    assert (len(test_repo.get_all()) == 1)
    assert (test_repo.find(Inchiriere('3','7')) is None)
    

    try:
        test_repo.delete(Inchiriere('3','7'))
        assert False
    except RentalNotFoundException:
        assert True

test_read_from_file()
test_store_repo_file()
test_find_repo_file()
test_delete_repo_file()

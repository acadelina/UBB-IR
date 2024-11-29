from Domain.Client import Client
from Domain.Validators import *
from Repsitory.Client import*
from Service.Utils import*
import random,string



class ClientService:
    def __init__(self, repo, validator):
        """
        Initializeaza service
        :param repo: obiect de tip repo care ne ajuta sa gestionam multimea de clienti
        :type repo: ClientRepo
        :param validator: validator pentru verificarea clientilor
        :type validator: ClientValidator
        """
        self.__repo = repo
        self.__validator = validator

    def add_client(self, id, nume, cnp):
        """
        Adauga client
        :param id: id-ul clientului
        :type id: str
        :param nume: numele clientului
        :type nume: str
        :param varsta: varsta clientului
        :type varsta: int
        :return: Clientul adaugat
        :rtype: Client
        :raises: ValidationException daca datele pentru client nu sunt valide
                 DuplicateIDException daca exista deja client cu id dat
        """
        c = Client(id, nume, cnp)
        self.__validator.validate(c)
        self.__repo.store(c)
        return c

    def get_all_clients(self):
        """
        Returneaza o lista cu toti clientii disponibili
        :return: lista de clienti disponibili
        :rtype: list of objects de tip Client
        """
        return self.__repo.get_all()

    def delete_client(self, id):
        """
        Sterge clientul cu id dat din lista
        :param id: id-ul dat
        :type id: str
        :return: clientul sters
        :rtype: Client
        :raises: ClientNotFoundException daca nu exista client cu id-ul dat
        """
        return self.__repo.delete(id)

    def update_client(self, id, nume, cnp):
        """
        Modifica datele clientului cu id dat
        :param id: id-ul clientului de modificat
        :type id: str
        :param nume: noul nume al clientului
        :type nume: str
        :param varsta: noua varsta a clientului
        :type varsta: int
        :return: clientul modificat
        :rtype:Client
        :raises: ValidationException daca datele nu sunt valide
                 ClientNotFoundException daca nu exista client cu id-ul dat
        """
        c = Client(id, nume, cnp)

        self.__validator.validate(c)
        return self.__repo.update(id, c)
    
    def create_random_string(self,l):
        letters = string.ascii_lowercase
        result = ''.join(random.choice(letters) for i in range(l))
        return result
    
    
    def genereaza_clienti(self,n):
        for i in range(n):
            id=random.randint(1,999)
            nume=self.create_random_string(9)
            cnp=str(''.join([str(random.randint(1,9)) for _ in range(13)]))
            self.add_client(id,nume,cnp)

    def cauta_client(self,id):
        """
        Functie care cauta un client in lista dupa id-ul sau
        preconditii: listac:lista, id:int
        postconditii: clientul
        """
        return self.__repo.find(id)
        
def test_adaugare_client():
    repo=ClientInMemoryRepo()
    val=ValidatorClient()
    test_serv=ClientService(repo,val)
    
    
    test_serv.add_client(1,"nume","1260406160861")
    assert len(test_serv.get_all_clients())==1
    try:
        test_serv.add_client(1,"Nume","1260406160861")
        assert False
    except DuplicateIDException:
        assert True
    
def test_delete_client():
    repo=ClientInMemoryRepo()
    val=ValidatorClient()
    test_serv=ClientService(repo,val)

    test_serv.add_client(1,'Mara',"1260406160861" )
    test_serv.add_client(2, 'Matei',"1330722122555")
    test_serv.add_client(3, 'Carmen',"6661029751557")

    assert (len(test_serv.get_all_clients()) == 3)
    deleted_person = test_serv.delete_client(1)
    assert (len(test_serv.get_all_clients()) == 2)
    assert (deleted_person.getNume() == 'Mara')

    deleted_person = test_serv.delete_client(3)
    assert (len(test_serv.get_all_clients()) == 1)
    assert (deleted_person.getNume() == 'Carmen')

    try:
        deleted_person = test_serv.delete_client(3)
        assert False
    except ClientNotFoundException:
        assert True
       
def test_modify_client():
    repo=ClientInMemoryRepo()
    val=ValidatorClient()
    test_serv=ClientService(repo,val)

    test_serv.add_client(1,'Mara',"1260406160861" )
    test_serv.add_client(2, 'Matei',"1330722122555")
    test_serv.add_client(3, 'Carmen',"6661029751557")

    assert (len(test_serv.get_all_clients()) == 3)
    person_before_modif = test_serv.cauta_client(1)
    
    assert(person_before_modif.getNume()=='Mara')

    test_serv.update_client(1,'Maya',"1260406160861")
    person_after_modif = test_serv.cauta_client(1)
    assert(person_after_modif.getNume()=='Maya')

    try:
        test_serv.update_client(4,'Maya',"1260406160861")
        assert False
    except ClientNotFoundException:
        assert True
test_adaugare_client()
test_delete_client()
test_modify_client()

def test_adaugare_client_file():
    repo=ClientFileRepo("data/test_clienti.txt")
    val=ValidatorClient()
    test_serv=ClientService(repo,val)
    
    clear_file_content("data/test_clienti.txt")
    test_serv.add_client(1,"nume","1260406160861")
    assert len(test_serv.get_all_clients())==1
    try:
        test_serv.add_client(1,"Nume","1260406160861")
        assert False
    except DuplicateIDException:
        assert True
    
def test_delete_client_file():
    repo=ClientFileRepo("data/test_clienti.txt")
    val=ValidatorClient()
    test_serv=ClientService(repo,val)
    
    clear_file_content("data/test_clienti.txt")

    test_serv.add_client(1,'Mara',"1260406160861" )
    test_serv.add_client(2, 'Matei',"1330722122555")
    test_serv.add_client(3, 'Carmen',"6661029751557")

    assert (len(test_serv.get_all_clients()) == 3)
    deleted_person = test_serv.delete_client(1)
    assert (len(test_serv.get_all_clients()) == 2)
    assert (deleted_person.getNume() == 'Mara')

    deleted_person = test_serv.delete_client(3)
    assert (len(test_serv.get_all_clients()) == 1)
    assert (deleted_person.getNume() == 'Carmen')

    try:
        deleted_person = test_serv.delete_client(3)
        assert False
    except ClientNotFoundException:
        assert True
       
def test_modify_client_file():
    repo=ClientFileRepo("data/test_clienti.txt")
    val=ValidatorClient()
    test_serv=ClientService(repo,val)
    
    clear_file_content("data/test_clienti.txt")

    test_serv.add_client(1,'Mara',"1260406160861" )
    test_serv.add_client(2, 'Matei',"1330722122555")
    test_serv.add_client(3, 'Carmen',"6661029751557")

    assert (len(test_serv.get_all_clients()) == 3)
    person_before_modif = test_serv.cauta_client(1)
    print (person_before_modif)
    assert(person_before_modif.getNume()=='Mara')

    test_serv.update_client(1,'Maya',"1260406160861")
    person_after_modif = test_serv.cauta_client(1)
    assert(person_after_modif.getNume()=='Maya')

    try:
        test_serv.update_client(4,'Maya',"1260406160861")
        assert False
    except ClientNotFoundException:
        assert True

test_adaugare_client_file()
test_delete_client_file()
test_modify_client_file()
from Domain.Film import Film
from Domain.Validators import *
from Exceptions.Exc import *
from Repsitory.Film import *
from Service.Utils import *
import random,string

class FilmService:
    def __init__(self, repo, validator):
        """
        Initializeaza service
        :param repo: obiect de tip repo care ne ajuta sa gestionam multimea de Filme
        :type repo: FilmInMemoryRepo
        :param validator: validator pentru verificarea Filmelor
        :type validator: FilmValidator
        """
        self.__repo = repo
        self.__validator = validator
    def get_all(self):
        return self.__repo.get_all()
    def add_Film(self, id, titlu, desc, gen,inc):
        """
        Adauga Film
        :param titlu: titlul Filmului
        :type titlu:str
        :param an_aparitie: anul de aparitie al Filmului
        :type an_aparitie:int
        :param eps:numarul de episoade al Filmului
        :type eps:int
        :return: obiectul de tip Film creat
        :rtype:-; Filmul s-a adaugat in lista
        :raises: ValidationException daca Filmul are date invalide
                 DuplicateIDException daca id-ul exista deja in lista
        """
        s = Film(id, titlu, desc, gen,inc)

        self.__validator.validate(s)

        self.__repo.store(s)
        return s

    def get_all_Films(self):
        """
        Returneaza o lista cu toate Filmele disponibile
        :return: lista de Filme disponibile
        :rtype: list of objects de tip Film
        """
        return self.__repo.get_all()

    def delete_Film(self, id):
        """
        Sterge Filmul cu id dat din lista
        :param id: id-ul dat
        :type id: str
        :return: Filmul sters
        :rtype: Film
        :raises: FilmNotFoundException daca nu exista Film cu id-ul dat
        """
        return self.__repo.delete(id)

    def update_Film(self, id, titlu, descriere, gen,inc):
        """
        Modifica datele Filmului cu id dat
        :param id: id-ul Filmului de modificat
        :type id: str
        :param titlu: noul titlu al Filmului
        :type titlu: str
        :param an_aparitie: noul an de aparitie al Filmului
        :type an_aparitie: int
        :param eps: noul numar de episoade pentru Film
        :type eps: int
        :return: Filmul modificat
        :rtype:Film
        :raises: ValidationException daca noile date nu sunt valide
                 FilmNotFoundException daca nu exista Film cu id dat
        """
        s = Film(id, titlu, descriere, gen,inc)

        self.__validator.validate(s)
        return self.__repo.update(id, s)

    def cauta_film(self,id):
        """
        Functie care cauta un film in lista dupa id-ul sau
        preconditii: listaf:lista, id:int
        postconditii: filmul
        """
        return self.__repo.find(id)
        
        
            
    def create_random_string(self,l):
        """
        Functie care creeaza un cuvant
        preconditii: l:int
        postconditii: cuvantul
        """
        letters = string.ascii_lowercase
        result = ''.join(random.choice(letters) for i in range(l))
        return result

    
    def genereaza_filme(self,n):
        """
        Functie care genereaza n filme
        preconditii: listaf:lista, n:int
        postconditii:
        """
        genuri=["Comedy","Thriller","Horror","Action","Animation","Drama","Musical","Romance","Fantasy","SF","altele"]
       
        for i in range(n):
            
            id=random.randint(1,999)
            titlu=self.create_random_string(10)
            desc=''.join(random.sample(string.ascii_lowercase + ' ',15))
            gen=random.choice(genuri)
            inc=0
            self.add_Film(id,titlu,desc,gen,inc)

def test_adaugare_film():
    repo=filmInMemoryRepo()
    val=ValidatorFilm()
    test_serv=FilmService(repo,val)
    
    
    test_serv.add_Film(234,"Cinderella","najje jed","altele",0)
    assert len(test_serv.get_all_Films())==1
    try:
        test_serv.add_Film(234,"Cin","najje jed","Action",0)
        assert False
    except DuplicateIDException:
        assert True
    
def test_delete_film():
    repo=filmInMemoryRepo()
    val=ValidatorFilm()
    test_serv=FilmService(repo,val)

    test_serv.add_Film(234,"Cinderella","najje jed","Fantasy",0)
    test_serv.add_Film(214,"H2o","najje jed","Action",0)
    test_serv.add_Film(1,"Dumbo","sla","Action",0)

    assert (len(test_serv.get_all_Films()) == 3)
    deleted_film = test_serv.delete_Film(1)
    assert (len(test_serv.get_all_Films()) == 2)
    assert (deleted_film.getTitlu() == 'Dumbo')

    deleted_film = test_serv.delete_Film(234)
    assert (len(test_serv.get_all_Films()) == 1)
    assert (deleted_film.getTitlu() == 'Cinderella')

    try:
        deleted_film= test_serv.delete_Film(234)
        assert False
    except FilmNotFoundException:
        assert True
       
def test_modify_film():
    repo=filmInMemoryRepo()
    val=ValidatorFilm()
    test_serv=FilmService(repo,val)

    test_serv.add_Film(234,"Cinderella","najje jed","Fantasy",0)
    test_serv.add_Film(214,"H2o","najje jed","Action",0)
    test_serv.add_Film(1,"Dumbo","sla","Action",0)

    assert (len(test_serv.get_all_Films()) == 3)
    film_before_modif = test_serv.cauta_film(1)
    assert(film_before_modif.getTitlu()=='Dumbo')

    test_serv.update_Film(1,"Dumbo2","sla","Action",1)
    film_after_modif = test_serv.cauta_film(1)
    assert(film_after_modif.getTitlu()=='Dumbo2')

    try:
        test_serv.update_Film(4,"Dumbo2","sla","Action",0)
        assert False
    except FilmNotFoundException:
        assert True
test_adaugare_film()
test_delete_film()
test_modify_film()

def test_adaugare_film_file():
    repo=filmFileRepo("test_filme.txt")
    val=ValidatorFilm()
    test_serv=FilmService(repo,val)
    clear_file_content("test_filme.txt")
    
    test_serv.add_Film(234,"Cinderella","najje jed","altele",0)
    assert len(test_serv.get_all_Films())==1
    try:
        test_serv.add_Film(234,"Cin","najje jed","Action",0)
        assert False
    except DuplicateIDException:
        assert True
    
def test_delete_film_file():
    repo=filmFileRepo("test_filme.txt")
    val=ValidatorFilm()
    test_serv=FilmService(repo,val)
    clear_file_content("test_filme.txt")

    test_serv.add_Film(234,"Cinderella","najje jed","Fantasy",0)
    test_serv.add_Film(214,"H2o","najje jed","Action",0)
    test_serv.add_Film(1,"Dumbo","sla","Action",0)

    assert (len(test_serv.get_all_Films()) == 3)
    deleted_film = test_serv.delete_Film(1)
    assert (len(test_serv.get_all_Films()) == 2)
    assert (deleted_film.getTitlu() == 'Dumbo')

    deleted_film = test_serv.delete_Film(234)
    assert (len(test_serv.get_all_Films()) == 1)
    assert (deleted_film.getTitlu() == 'Cinderella')

    try:
        deleted_film= test_serv.delete_Film(234)
        assert False
    except FilmNotFoundException:
        assert True
       
def test_modify_film_file():
    repo=filmFileRepo("test_filme.txt")
    val=ValidatorFilm()
    test_serv=FilmService(repo,val)
    clear_file_content("test_filme.txt")

    test_serv.add_Film(234,"Cinderella","najje jed","Fantasy",0)
    test_serv.add_Film(214,"H2o","najje jed","Action",0)
    test_serv.add_Film(1,"Dumbo","sla","Action",0)

    assert (len(test_serv.get_all_Films()) == 3)
    film_before_modif = test_serv.cauta_film(1)
    assert(film_before_modif.getTitlu()=='Dumbo')

    test_serv.update_Film(1,"Dumbo2","sla","Action",1)
    film_after_modif = test_serv.cauta_film(1)
    assert(film_after_modif.getTitlu()=='Dumbo2')

    try:
        test_serv.update_Film(4,"Dumbo2","sla","Action",0)
        assert False
    except FilmNotFoundException:
        assert True
test_adaugare_film_file()
test_delete_film_file()
test_modify_film_file()
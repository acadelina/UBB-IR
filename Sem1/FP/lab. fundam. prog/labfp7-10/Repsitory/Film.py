from Domain.Film import Film
from Exceptions.Exc import *


class filmInMemoryRepo:
    def __init__(self):
        
        self.__filme = {}

    def find(self, id):
        """
        Cauta Filmul cu id dat
        :param id: id dat
        :type id: str
        :return: Filmul cu id dat, None daca nu exista Film cu id dat
        :rtype: Film
        """
        if id in self.__filme:
            return self.__filme[id]
        return None

    def store(self, film):
        """
       Adauga un Film in lista
       :param film: Filmul care se adauga
       :type film: Film
       :return: -; lista de Filme se modifica prin adaugarea Filmului dat
        :rtype:
        :raises: DuplicateIDException daca Filmul exista deja
        """
        
        if film.getId() in self.__filme:
            raise DuplicateIDException()

        self.__filme[film.getId()] = film

    def get_all(self):
        """
        Returneaza o lista cu toate film-urile existente
        :rtype: list of objects de tip Film
        """
        return list(self.__filme.values())

    def size(self):
        """
        Returneaza numarul de Filme din multime
        :return: numar Filme existente
        :rtype:int
        """
        return len(self.__filme)

    def delete(self, id):
        """
        Sterge Film dupa id
        :param id: id-ul dat
        :type id: str
        :return: Filmul sters
        :rtype: Film
        :raises: filmNotFoundException daca id-ul nu exista
        """
        if id not in self.__filme:
            raise FilmNotFoundException()

        deleted_film = self.__filme[id]
        del self.__filme[id]
        return deleted_film

    def update(self, id, modified_film):
        """
        Modifica datele Filmului cu id dat
        :param id: id dat
        :type id: str
        :param modified_film: film-ul cu datele noi
        :type modified_film: Film
        :return: film-ul modificat
        :rtype: Film
        """

        if id not in self.__filme:
            raise FilmNotFoundException()

        old_film = self.__filme[id]
        self.__filme[id] = modified_film
        return modified_film

    def delete_all(self):
        self.__filme = {}
    
    def inc_inchirieri(self,film):
        a=film.getInc()
        film.setInc(a+1)

def setup_test_repo():
    Film1 = Film('1001', "Superstore", "-","Action","0" )
    Film2 = Film('1002', "Arrow", "-", "Action","0")
    Film3 = Film('1003', 'Modern Family', "-", "Comedy","0")
    Film4 = Film('1000', 'Squid Game', "-", "Action","0")
    Film5 = Film('1005', 'See', " ", "altele","0")
    Film6 = Film('1854', 'Grey\'s Anatomy', "a", "altele","0")
    Film7 = Film('2638', 'The Magicians', "-", "Thriller","0")
    Film8 = Film('1211', 'Atypical', "-", "Drama","0")
    
    test_repo = filmInMemoryRepo()
    test_repo.store(Film1)
    test_repo.store(Film2)
    test_repo.store(Film3)
    test_repo.store(Film4)
    test_repo.store(Film5)
    test_repo.store(Film6)
    test_repo.store(Film7)
    test_repo.store(Film8)
   
    return test_repo


def test_find():
    test_repo = setup_test_repo()

    p = test_repo.find('1005')
    assert (p.getTitlu() == "See")
    assert (p.getDesc() == " ")
    assert (p.getGen() == "altele")

    p1 = test_repo.find('1645')
    assert (p1 is None)


def test_size():
    test_repo1 = setup_test_repo()
    assert (test_repo1.size() == 8)
    test_repo1.delete('1001')
    test_repo1.delete('2638')

    assert (test_repo1.size() == 6)

    test_repo1.store(Film('2384', 'The Crown', "-", "Fantasy","0"))
    assert (test_repo1.size() == 7)
    test_repo1.update('2384', Film('2384', 'The Crown', "-", "Comedy","0"))
    assert (test_repo1.size() == 7)


def test_get_all():
    test_repo1 = setup_test_repo()
    crt_shows = test_repo1.get_all()
    assert (type(crt_shows) == list)
    assert (len(crt_shows) == 8)

    test_repo1.delete('1001')
    test_repo1.delete('2638')

    crt_shows = test_repo1.get_all()
    assert (len(crt_shows) == 6)

    test_repo1.store(Film('2384', 'The Crown', "-", "Fantasy","0"))
    assert (test_repo1.size() == 7)

    
    assert (test_repo1.get_all()[-1].getTitlu() == 'The Crown')
    assert (test_repo1.get_all()[-1].getGen() == "Fantasy")

    test_repo1.update('2384', Film('2384', 'The Crown', "as", "Fantasy","0"))

   

    assert (test_repo1.get_all()[-1].getDesc() == "as")
    assert (test_repo1.size() == 7)


def test_store():
    test_repo = filmInMemoryRepo()
    show1 = Film('23', 'See', "-", "Fantasy","0")
    test_repo.store(show1)

    assert (test_repo.size() == 1)
    show2 = Film('234', 'Kim\'s Convenience', "-", "Fantasy","0")
    test_repo.store(show2)
    assert (test_repo.size() == 2)

    try:
        
        test_repo.store(show2)
        assert False
    except DuplicateIDException:
        assert True


def test_delete():
    test_repo = filmInMemoryRepo()
    show1 = Film('23', 'See', "-", "Fantasy","0")
    test_repo.store(show1)
    show2 = Film('234', 'Kim\'s Convenience', "-", "Fantasy","0")
    test_repo.store(show2)

    deleted_film = test_repo.delete('234')
    assert (deleted_film.getTitlu() == 'Kim\'s Convenience')
    assert (test_repo.size() == 1)

    film_left = test_repo.find('23')
    assert (film_left.getTitlu() == 'See')

    try:
        test_repo.delete('0')
        assert False
    except FilmNotFoundException:
        assert True


def test_update():
    test_repo = filmInMemoryRepo()
    show1 = Film('23', 'See', "-", "Fantasy","0")
    test_repo.store(show1)
    show2 = Film('234', 'Kim\'s Convenience', "-", "Fantasy","0")
    test_repo.store(show2)
    show3 = Film('234', 'Kim', "-", "Fantasy","1")

    modified_show = test_repo.update('234', show3)
    assert (modified_show.getTitlu() == 'Kim')
    assert (modified_show.getDesc() == "-")
    assert (modified_show.getGen() == "Fantasy")

    try:
        test_repo.update('243545', Film('234', 'Kim', "-", "Fantasy","0"))
        assert False
    except FilmNotFoundException:
        assert True

test_delete()
test_find()
test_get_all()
test_size()
test_store()
test_update()

class filmFileRepo:
    def __init__(self, filename):
        self.__filename = filename

    def __load_from_file(self):
        """
        Incarca datele din fisier
        :return: lista de Filme din fisier
        :rtype: list of Film objects
        :raises: ...
        """
        try:
            f = open(self.__filename, 'r')
            
        except IOError:
            return

        lines = f.readlines()
        
        all_filme = []
        for line in lines:
            film_id, film_titlu, film_desc, film_gen,film_inc = [token.strip() for token in line.split(';')]
            

            s = Film(int(film_id), film_titlu, film_desc, film_gen,int(film_inc))
            all_filme.append(s)

        f.close()
        return all_filme

    def __save_to_file(self, all_filme):
        """
        Salveaza Filmele in fisier
        """
        with open(self.__filename, 'w') as f:
            for film in all_filme:
                film_string = str(film.getId()) + ';' + str(film.getTitlu()) + ';' + str(
                    film.getDesc()) + ';' + str(film.getGen()) +';'+ str(film.getInc())+ '\n'
                f.write(film_string)

    def find(self, id):
        """
        Cauta Filmul cu id dat
        :param id: id dat
        :type id: str
        :return: Filmul cu id dat, None daca nu exista Film cu id dat
        :rtype: Film
        """
        all_filme = self.__load_from_file()
        for film in all_filme:
            
            
            if int(film.getId()) == int(id):
                return film
        return None

    def store(self, film):
        """
       Adauga un Film in lista
       :param film: Filmul care se adauga
       :type film: Film
       :return: -; lista de Filme se modifica prin adaugarea Filmului dat
        :rtype:
        :raises: DuplicateIDException daca Filmul exista deja
        """
        all_filme = self.__load_from_file()

        for i in range(len(all_filme)):
            
            if int(all_filme[i].getId())==int(film.getId()):
                raise DuplicateIDException()

        all_filme.append(film)
        self.__save_to_file(all_filme)

    def get_all(self):
        """
        Returneaza o lista cu toate film-urile existente
        :rtype: list of objects de tip Film
        """
        return self.__load_from_file()

    def size(self):
        """
        Returneaza numarul de Filme din multime
        :return: numar Filme existente
        :rtype:int
        """
        return len(self.__load_from_file())

    def __find_index(self, all_filme, id):
        """
        Gaseste pozitia in lista a Filmului cu id dat
        :param all_filme: lista cu toate Filmele
        :type all_filme: list of Film objects
        :param id: id-ul cautat
        :type id: str
        :return: pozitia in lista a Filmului dat, -1 daca Filmul nu se regaseste in lista
        :rtype: int, >=0, <repo.size()
        """
        index = -1
        for i in range(len(all_filme)):
            if all_filme[i].getId() == id:
                index = i

        return index

    def delete(self, id):
        """
        Sterge Film dupa id
        :param id: id-ul dat
        :type id: str
        :return: Filmul sters
        :rtype: Film
        :raises: filmNotFoundException daca id-ul nu exista
        """
        all_filme = self.__load_from_file()
        index = self.__find_index(all_filme, id)
        if index == -1:
            raise FilmNotFoundException()

        deleted_film = all_filme.pop(index)

        self.__save_to_file(all_filme)
        return deleted_film

    def update(self, id, modified_film):
        """
        Modifica datele Filmului cu id dat
        :param id: id dat
        :type id: str
        :param modified_film: film-ul cu datele noi
        :type modified_film: Film
        :return: film-ul modificat
        :rtype: Film
        :raises: filmNotFoundException daca nu exista Film cu id dat
        """

        all_filme = self.__load_from_file()
        index = self.__find_index(all_filme, id)
        if index == -1:
            raise FilmNotFoundException()

        all_filme[index] = modified_film

        self.__save_to_file(all_filme)
        return modified_film

    def delete_all(self):
        self.__save_to_file([])
    
    def inc_inchirieri(self,film):
        a=film.getInc()
        film.setInc(a+1)
        self.update(film.getId(),film)


def test_read_from_file():
    
    test_repo = filmFileRepo("data/test_filme.txt")
    test_repo.delete_all()
    assert (test_repo.size() == 0)


def test_store_repo_file():
    
    test_repo = filmFileRepo("data/test_filme.txt")
    test_repo.delete_all()
    
    show1 = Film('23', 'See', "-", "Fantasy","0")
    test_repo.store(show1)

    assert (test_repo.size() == 1)
    show2 = Film('234', 'Kim\'s Convenience', "-", "Fantasy","0")
    test_repo.store(show2)
    assert (test_repo.size() == 2)

    try:
        
        test_repo.store(Film('234', 'Kim\'s Convenience', "-", "Fantasy","0"))
        assert False
    except DuplicateIDException:
        assert True






def test_update_repo_file():
    test_repo = filmFileRepo("data/test_filme.txt")
    
    show3 = Film('234', 'Kim', "-", "Fantasy","0")

    modified_show = test_repo.update(234, show3)
    assert (modified_show.getTitlu() == 'Kim')
    assert (modified_show.getDesc() == "-")
    assert (modified_show.getGen() == "Fantasy")

    try:
        test_repo.update(243545, Film('234', 'Kim', "-", "Fantasy","0"))
        assert False
    except FilmNotFoundException:
        assert True

def test_find_repo_file():
    
    test_repo = filmFileRepo("data/test_filme.txt")

    assert (test_repo.size() == 2)

    

    assert (test_repo.find(23) is not None)
    assert (test_repo.find(234) is not None)
    assert (test_repo.find(3) is  None)
    assert (test_repo.find(10) is None)


def test_delete_repo_file():
    
    test_repo = filmFileRepo("data/test_filme.txt")
    
    assert (test_repo.size() == 2)

    deleted_film = test_repo.delete(23)
    assert (test_repo.size() == 1)
    assert (test_repo.find(23) is None)
    assert (deleted_film.getDesc() == "-")

    

    test_repo.store(Film('1001', "Superstore", "-","Action","0" ))
    assert (test_repo.size() == 2)

    deleted_film = test_repo.delete(1001)
    assert (test_repo.size() == 1)
    assert (test_repo.find(1001) is None)
    assert (deleted_film.getDesc() == "-")

    try:
        test_repo.delete(111)
        assert False
    except FilmNotFoundException:
        assert True

test_read_from_file()
test_store_repo_file()
test_update_repo_file()
test_find_repo_file()
test_delete_repo_file()





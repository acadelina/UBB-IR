from Domain.Client import Client
from Exceptions.Exc import CorruptedFileException, DuplicateIDException, ClientNotFoundException


class ClientInMemoryRepo:
    def __init__(self):
        self.__clients = {}

    def find(self, id):
        """
        Cauta clientul cu id dat
        :param id: id dat
        :type id: str
        :return: clientul cu id dat, None daca nu exista client cu id dat
        :rtype: Client
        """
        if id in self.__clients:
            return self.__clients[id]
        return None

    def store(self, client):
        """
       Adauga un client in lista
       :param client: clientul care se adauga
       :type client: Client
       :return: -; lista de cliente se modifica prin adaugarea clientului dat
        :rtype:
        :raises: DuplicateIDException daca clientul exista deja
        """
        # verificare id duplicat
        if client.getId() in self.__clients:
            raise DuplicateIDException()

        self.__clients[client.getId()] = client

    def get_all(self):
        """
        Returneaza o lista cu toate client-urile existente
        :rtype: list of objects de tip Client
        """
        return list(self.__clients.values())

    def size(self):
        """
        Returneaza numarul de cliente din multime
        :return: numar cliente existente
        :rtype:int
        """
        return len(self.__clients)

    def delete(self, id):
        """
        Sterge client dupa id
        :param id: id-ul dat
        :type id: str
        :return: clientul sters
        :rtype: Client
        :raises: ClientNotFoundException daca id-ul nu exista
        """
        if id not in self.__clients:
            raise ClientNotFoundException()

        deleted_client = self.__clients[id]
        del self.__clients[id]
        return deleted_client

    def update(self, id, modified_client):
        """
        Modifica datele clientului cu id dat
        :param id: id dat
        :type id: str
        :param modified_client: clientul cu datele noi
        :type modified_client: Client
        :return: clientul modificat
        :rtype: Client
        :raises: ClientNotFoundException daca id-ul nu exista
        """

        if id not in self.__clients:
            raise ClientNotFoundException()

        old_client = self.__clients[id]
        self.__clients[id] = modified_client
        return modified_client

    def delete_all(self):
        self.__clients = {}

def setup_test_repo():
    client1 = Client('1',"Adrian","1260406160861")
    client2 = Client('2',"Naomi","1330722122555")
    client3 = Client('3',"May","6661029751557")
    client4 = Client('5',"Ardelia","1680427620727")
    
    
    test_repo = ClientInMemoryRepo()
    test_repo.store(client1)
    test_repo.store(client2)
    test_repo.store(client3)
    test_repo.store(client4)
    
    return test_repo


def test_find():
    test_repo = setup_test_repo()

    p = test_repo.find('1')
    assert (p.getNume() == "Adrian")
    assert (p.getCnp() == "1260406160861")
   

    p1 = test_repo.find('1645')
    assert (p1 is None)


def test_size():
    test_repo1 = setup_test_repo()
    assert (test_repo1.size() == 4)
    test_repo1.delete('1')
    test_repo1.delete('2')

    assert (test_repo1.size() == 2)

    test_repo1.store(Client('1',"ada","1360406160861"))
    assert (test_repo1.size() == 3)
    test_repo1.update('1', Client('1','Adelina',"1360406160861"))
    assert (test_repo1.size() == 3)


def test_get_all():
    test_repo1 = setup_test_repo()
    crt_clienti = test_repo1.get_all()
    assert (type(crt_clienti) == list)
    assert (len(crt_clienti) == 4)

    test_repo1.delete('1')
    test_repo1.delete('2')

    crt_clienti = test_repo1.get_all()
    assert (len(crt_clienti) == 2)

    test_repo1.store(Client('1','Adelina',"1360406160861"))
    assert (test_repo1.size() == 3)

    
    assert (test_repo1.get_all()[-1].getNume() == "Adelina")
    assert (test_repo1.get_all()[-1].getCnp() == "1360406160861")

    


def test_store():
    test_repo = ClientInMemoryRepo()
    client1 = Client('1','Adelina',"1360406160861")
    test_repo.store(client1)

    assert (test_repo.size() == 1)
    client2 = Client('2',"Naomi","1330722122555")
    test_repo.store(client2)
    assert (test_repo.size() == 2)

    try:
        
        test_repo.store(client2)
        assert False
    except DuplicateIDException:
        assert True


def test_delete():
    test_repo = ClientInMemoryRepo()
    client1 = Client('1','Adelina',"1360406160861")
    test_repo.store(client1)
    client2 = Client('2',"Naomi","1330722122555")
    test_repo.store(client2)
    

    deleted_Client = test_repo.delete('2')
    assert (deleted_Client.getNume() == "Naomi")
    assert (test_repo.size() == 1)

    Client_left = test_repo.find('1')
    assert (Client_left.getNume() == 'Adelina')

    try:
        test_repo.delete('0')
        assert False
    except ClientNotFoundException:
        assert True


def test_update():
    test_repo = ClientInMemoryRepo()
    client1 = Client('1','Adelina',"1360406160861")
    test_repo.store(client1)
    client2 = Client('2',"Naomi","1330722122555")
    test_repo.store(client2)
    client3 = Client('2',"Naomi Sara","1330722122555")

    modified_client = test_repo.update('2', client3)
    assert (modified_client.getNume() == 'Naomi Sara')
    assert (modified_client.getCnp() == "1330722122555")
   

    try:
        test_repo.update('243545', Client('2',"Naomi Sara","1330722122555"))
        assert False
    except ClientNotFoundException:
        assert True

test_delete()
test_find()
test_get_all()
test_size()
test_store()
test_update()

class ClientFileRepo:
    def __init__(self, filename):
        self.__filename = filename
        
    
    
    
    def __load_from_file(self):
        """
        Incarca datele din fisier
        :return: lista cu clientii din fisier
        :rtype: list of Clients
        """

        try:
            f = open(self.__filename, 'r')
            
        except IOError:
            raise CorruptedFileException()

        clients = []
        lines = f.readlines()
        for line in lines:
            client_id, client_name, client_cnp = [token.strip() for token in line.split(';')]
            a = Client(int(client_id), client_name, client_cnp)
            clients.append(a)
        f.close()
        return clients

    def __save_to_file(self, client_list):
        """
        Salveaza in fisier clientii dati
        :param client_list: lista de clienti
        :type client_list: list of Clients
        :return: -
        :rtype: -
        """
        with open(self.__filename, 'w') as f:
            for client in client_list:
                client_string = str(client.getId()) + ';' + str(client.getNume()) + ';' + str(
                    client.getCnp()) + '\n'
                f.write(client_string)

    def store(self, client):
        """
        Adauga client in lista
        :param client: clientul de adaugat
        :type client: Client
        :return: -; lista de clienti se modifica prin adaugarea clientului
        :rtype: -; clientul este adaugat
        :raises: DuplicateIDException daca exista deja clientul
        """
        all_clients = self.__load_from_file()
        for i in range (len(all_clients)):
            if int(all_clients[i].getId())==int(client.getId()):
                raise DuplicateIDException()
        all_clients.append(client)
        self.__save_to_file(all_clients)

    def find(self, id):
        """
        Cauta clientul cu id dat
        :param id: id dat
        :type id: str
        :return: clientul cu id dat, None daca nu exista client cu id dat
        :rtype: Client
        """
        all_clients = self.__load_from_file()
        for i in range(len(all_clients)):
            if all_clients[i].getId() == id:
                return all_clients[i]
        return None

    def get_all(self):
        """
        Returneaza o lista cu toti clientii existenti
        :rtype: list of objects de tip Client
        """
        return self.__load_from_file()

    def size(self):
        """
        Returneaza numarul de clienti din multime
        :return: numar clienti existenti
        :rtype:int
        """
        return len(self.__load_from_file())

    def __find_index(self, all_clients, id):
        """
        Gaseste pozitia in lista all_clients a clientului cu id id
        :param all_clients: lista de clienti
        :type all_clients: list of Clients
        :param id: id-ul dat
        :type id: str
        :return: pozitia Clientului cu id id in lista data, -1 daca nu exista
        :rtype: int, >0, <len(all_clients)
        """
        index = -1
        for i in range(len(all_clients)):
            if all_clients[i].getId() == id:
                index = i
                break
        return index

    def delete(self, id):
        """
        Sterge client dupa id
        :param id: id-ul dat
        :type id: str
        :return: clientul sters
        :rtype: Client
        :raises: ClientNotFoundException daca id-ul nu exista
        """
        all_clients = self.__load_from_file()
        index = self.__find_index(all_clients, id)
        if index == -1:
            raise ClientNotFoundException()

        deleted_client = all_clients.pop(index)
        self.__save_to_file(all_clients)
        return deleted_client

    def update(self, id, modified_client):
        """
        Modifica datele clientului cu id dat
        :param id: id dat
        :type id: str
        :param modified_client: clientul cu datele noi
        :type modified_client: Client
        :return: clientul modificat
        :rtype: Client
        :raises: ClientNotFoundException daca nu exista client cu id dat
        """
        all_clients = self.__load_from_file()
        index = self.__find_index(all_clients, id)
        if index == -1:
            raise ClientNotFoundException()

        all_clients[index] = modified_client
        self.__save_to_file(all_clients)

        return modified_client

    def delete_all(self):
        self.__save_to_file([])


def test_read_from_file():
    
    test_repo = ClientFileRepo("data/test_clienti.txt")
    test_repo.delete_all()
    assert (test_repo.size() == 0)


def test_store_repo_file():
    
    test_repo = ClientFileRepo("data/test_clienti.txt")
    test_repo.delete_all()
    
    client1 = Client('1','Adelina',"1360406160861")
    test_repo.store(client1)

    assert (test_repo.size() == 1)
    client2 = Client('2',"Naomi Sara","1330722122555")
    test_repo.store(client2)
    assert (test_repo.size() == 2)

    try:
        
        test_repo.store(Client('2',"Naomi Sara","1330722122555"))
        assert False
    except DuplicateIDException:
        assert True






def test_update_repo_file():
    test_repo = ClientFileRepo("data/test_clienti.txt")
    
    client3 = Client('2',"Naomi","1330722122555")

    modified_client = test_repo.update(2, client3)
    assert (modified_client.getNume() == 'Naomi')
    assert (modified_client.getCnp() == "1330722122555")
    

    try:
        test_repo.update(243545, Client('1','Adelina',"1360406160861"))
        assert False
    except ClientNotFoundException:
        assert True

def test_find_repo_file():
    
    test_repo = ClientFileRepo("data/test_clienti.txt")

    assert (test_repo.size() == 2)

    

    assert (test_repo.find(2) is not None)
    assert (test_repo.find(1) is not None)
    assert (test_repo.find(3) is  None)
    assert (test_repo.find(10) is None)


def test_delete_repo_file():
    
    test_repo = ClientFileRepo("data/test_clienti.txt")
    
    assert (test_repo.size() == 2)

    deleted_client = test_repo.delete(2)
    assert (test_repo.size() == 1)
    assert (test_repo.find(2) is None)
    assert (deleted_client.getNume() == "Naomi")

    

    test_repo.store(Client('3',"May","6661029751557"))
    assert (test_repo.size() == 2)

    deleted_film = test_repo.delete(1)
    assert (test_repo.size() == 1)
    assert (test_repo.find(1) is None)
    assert (deleted_film.getNume() == "Adelina")

    try:
        test_repo.delete(111)
        assert False
    except ClientNotFoundException:
        assert True

test_read_from_file()
test_store_repo_file()
test_update_repo_file()
test_find_repo_file()
test_delete_repo_file()


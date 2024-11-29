import unittest
from Repsitory.Client import*
from Repsitory.Film import *
from Repsitory.Inchirieri import*
from Exceptions.Exc import*

class TesteRepo(unittest.TestCase):
    def setUp(self):
        self.repo_filme = filmInMemoryRepo()
        self.repo_clienti = ClientInMemoryRepo()
        self.repo_inchirieri = InchirieriInMemoryRepo()
        self.repo_filme_f = filmFileRepo('data/test_filme.txt')
        self.repo_clienti_f = ClientFileRepo('data/test_clienti.txt')
        self.repo_inchirieri_f = inchiriereRepoFile('data/test_inchirieri.txt')

    def setup_film_repo(self):
        
        Film1 = Film('1001', "Superstore", "-","Action","0" )
        Film2 = Film('1002', "Arrow", "-", "Action","0")
        Film3 = Film('1003', 'Modern Family', "-", "Comedy","0")
        Film4 = Film('1000', 'Squid Game', "-", "Action","0")
        Film5 = Film('1005', 'See', " ", "altele","0")
        Film6 = Film('1854', 'Grey\'s Anatomy', "a", "altele","0")
        Film7 = Film('2638', 'The Magicians', "-", "Thriller","0")
        Film8 = Film('1211', 'Atypical', "-", "Drama","0")
    
        
        self.repo_filme.store(Film1)
        self.repo_filme.store(Film2)
        self.repo_filme.store(Film3)
        self.repo_filme.store(Film4)
        self.repo_filme.store(Film5)
        self.repo_filme.store(Film6)
        self.repo_filme.store(Film7)
        self.repo_filme.store(Film8)
    def test_film_in_memory(self):
        
        self.assertTrue(self.repo_filme.find('2')==None)
        film3 = Film('2',"bruce almighty","abcd","Comedy","0")
        self.repo_filme.store(film3)
        self.repo_filme.update('2',film3)
        film_gasit = self.repo_filme.find('2')
        self.assertTrue(film_gasit.getTitlu()=="bruce almighty")
        self.assertTrue(len(self.repo_filme.get_all())==1)
        with self.assertRaises(FilmNotFoundException) as re:
            self.repo_filme.delete('3')
        self.assertEqual(str(re.exception), 'Repository Exception: Filmul nu a fost gasit.')
        self.repo_filme.delete('2')
        self.assertTrue(len(self.repo_filme.get_all())==0)

    def setup_test_repo(self):
        client1 = Client('1',"Adrian","1260406160861")
        client2 = Client('2',"Naomi","1330722122555")
        client3 = Client('3',"May","6661029751557")
        client4 = Client('5',"Ardelia","1680427620727")
    
    
    
        self.repo_clienti.store(client1)
        self.repo_clienti.store(client2)
        self.repo_clienti.store(client3)
        self.repo_clienti.store(client4)
    
        return self.repo_clienti


    def test_find(self):
        test_repo = self.setup_test_repo()

        p = test_repo.find('1')
        self.assertTrue(p.getNume() == "Adrian")
        self.assertTrue(p.getCnp() == "1260406160861")
   

        p1 = test_repo.find('1645')
        self.assertTrue(p1 is None)
        self.assertEqual (test_repo.size(),4)
        test_repo.delete('1')
        test_repo.delete('2')

        self.assertEqual(test_repo.size(), 2)

        test_repo.store(Client('1',"ada","1360406160861"))
        self.assertTrue(test_repo.size() == 3)
        test_repo.update('1', Client('1','Adelina',"1360406160861"))
        self.assertEqual (test_repo.size(),3)


    def test_size(self):
        test_repo1 = self.setup_test_repo()
        self.assertEqual (test_repo1.size(),4)
        test_repo1.delete('1')
        test_repo1.delete('2')

        self.assertTrue (test_repo1.size() == 2)

        test_repo1.store(Client('1',"ada","1360406160861"))
        self.assertEqual (test_repo1.size(), 3)
        test_repo1.update('1', Client('1','Adelina',"1360406160861"))
        self.assertTrue (test_repo1.size() == 3)


    def test_get_all(self):
        test_repo1 = self.setup_test_repo()
        crt_clienti = test_repo1.get_all()
        self.assertEqual (type(crt_clienti), list)
        self.assertTrue (len(crt_clienti) == 4)

        test_repo1.delete('1')
        test_repo1.delete('2')

        crt_clienti = test_repo1.get_all()
        self.assertTrue (len(crt_clienti) == 2)

        test_repo1.store(Client('1','Adelina',"1360406160861"))
        self.assertTrue (test_repo1.size() == 3)

    
        self.assertTrue(test_repo1.get_all()[-1].getNume() == "Adelina")
        self.assertTrue (test_repo1.get_all()[-1].getCnp() == "1360406160861")

    


    def test_store(self):
        test_repo = ClientInMemoryRepo()
        client1 = Client('1','Adelina',"1360406160861")
        test_repo.store(client1)

        self.assertEqual (test_repo.size() , 1)
        client2 = Client('2',"Naomi","1330722122555")
        test_repo.store(client2)
        self.assertTrue(test_repo.size() == 2)




    def test_delete(self):
        test_repo = ClientInMemoryRepo()
        client1 = Client('1','Adelina',"1360406160861")
        test_repo.store(client1)
        client2 = Client('2',"Naomi","1330722122555")
        test_repo.store(client2)
    

        deleted_Client = test_repo.delete('2')
        self.assertTrue(deleted_Client.getNume() == "Naomi")
        self.assertTrue(test_repo.size() == 1)

        Client_left = test_repo.find('1')
        self.assertTrue(Client_left.getNume() == 'Adelina')

    


    def test_update(self):
        test_repo = ClientInMemoryRepo()
        client1 = Client('1','Adelina',"1360406160861")
        test_repo.store(client1)
        client2 = Client('2',"Naomi","1330722122555")
        test_repo.store(client2)
        client3 = Client('2',"Naomi Sara","1330722122555")

        modified_client = test_repo.update('2', client3)
        self.assertTrue (modified_client.getNume() == 'Naomi Sara')
        self.assertTrue (modified_client.getCnp() == "1330722122555")
    
    def setup_test_repo_inch(self):
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


    def test_find_inch(self):
        test_repo = self.setup_test_repo_inch()

        p = test_repo.find(Inchiriere('1','2'))
        self.assertTrue (p.getCl() == 1)
        self.assertTrue(p.getFl() == 2)
   

        p1 = test_repo.find(Inchiriere('100','7'))
        self.assertTrue (p1 is None)


    def test_get_all_inch(self):
        test_repo1 = self.setup_test_repo_inch()
        crt_inchirierei = test_repo1.get_all()
        self.assertTrue (type(crt_inchirierei) == list)
        self.assertTrue (len(crt_inchirierei) == 4)

        test_repo1.delete(Inchiriere('1','2'))
        test_repo1.delete(Inchiriere('2','5'))

        crt_inchirierei = test_repo1.get_all()
        self.assertTrue (len(crt_inchirierei) == 2)

        test_repo1.store(Inchiriere('6','9'))
        self.assertTrue (len(test_repo1.get_all()) == 3)

    
        self.assertTrue(test_repo1.get_all()[-1].getCl() ==6)
        self.assertTrue (test_repo1.get_all()[-1].getFl() ==9)

    


    def test_store_inch(self):
        test_repo = InchirieriInMemoryRepo()
        inchiriere1 = Inchiriere('1','2')
        test_repo.store(inchiriere1)

        self.assertTrue (len(test_repo.get_all()) == 1)
        inchiriere2 = Inchiriere('2','8')
        test_repo.store(inchiriere2)
        self.assertTrue (len(test_repo.get_all()) == 2)

        


    def test_delete_inch(self):
        test_repo = InchirieriInMemoryRepo()
        inchiriere1 = Inchiriere('1','2')
        test_repo.store(inchiriere1)
        inchiriere2 = Inchiriere('2','8')
        test_repo.store(inchiriere2)
    

        test_repo.delete(inchiriere1)
    
        self.assertTrue (len(test_repo.get_all() )== 1)

    
   

   

    

if __name__ == '__main__':
    unittest.main()  
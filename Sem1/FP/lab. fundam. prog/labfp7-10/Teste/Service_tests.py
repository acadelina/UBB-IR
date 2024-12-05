import unittest
from Service.Client import *
from Service.Film import *
from Service.Inchirieri import *
from Repsitory.Client import *
from Repsitory.Film import *
from Repsitory.Inchirieri import *

class TesteService(unittest.TestCase):
    def test_adaugare_film(self):
        repo=filmInMemoryRepo()
        val=ValidatorFilm()
        test_serv=FilmService(repo,val)
    
    
        test_serv.add_Film(234,"Cinderella","najje jed","altele",0)
        self.assertTrue( len(test_serv.get_all_Films())==1)
        
    
    def test_delete_film(self):
        repo=filmInMemoryRepo()
        val=ValidatorFilm()
        test_serv=FilmService(repo,val)

        test_serv.add_Film(234,"Cinderella","najje jed","Fantasy",0)
        test_serv.add_Film(214,"H2o","najje jed","Action",0)
        test_serv.add_Film(1,"Dumbo","sla","Action",0)

        self.assertTrue (len(test_serv.get_all_Films()) == 3)
        deleted_film = test_serv.delete_Film(1)
        self.assertTrue (len(test_serv.get_all_Films()) == 2)
        self.assertTrue (deleted_film.getTitlu() == 'Dumbo')

        deleted_film = test_serv.delete_Film(234)
        self.assertTrue (len(test_serv.get_all_Films()) == 1)
        self.assertTrue (deleted_film.getTitlu() == 'Cinderella')

        
       
    def test_modify_film(self):
        repo=filmInMemoryRepo()
        val=ValidatorFilm()
        test_serv=FilmService(repo,val)

        test_serv.add_Film(234,"Cinderella","najje jed","Fantasy",0)
        test_serv.add_Film(214,"H2o","najje jed","Action",0)
        test_serv.add_Film(1,"Dumbo","sla","Action",0)

        self.assertTrue (len(test_serv.get_all_Films()) == 3)
        film_before_modif = test_serv.cauta_film(1)
        self.assertTrue(film_before_modif.getTitlu()=='Dumbo')

        test_serv.update_Film(1,"Dumbo2","sla","Action",1)
        film_after_modif = test_serv.cauta_film(1)
        self.assertTrue(film_after_modif.getTitlu()=='Dumbo2')

    def test_adaugare_client(self):
        repo=ClientInMemoryRepo()
        val=ValidatorClient()
        test_serv=ClientService(repo,val)
    
    
        test_serv.add_client(1,"nume","1260406160861")
        self.assertTrue( len(test_serv.get_all_clients())==1)
        
    
    def test_delete_client(self):
        repo=ClientInMemoryRepo()
        val=ValidatorClient()
        test_serv=ClientService(repo,val)

        test_serv.add_client(1,'Mara',"1260406160861" )
        test_serv.add_client(2, 'Matei',"1330722122555")
        test_serv.add_client(3, 'Carmen',"6661029751557")

        self.assertTrue (len(test_serv.get_all_clients()) == 3)
        deleted_person = test_serv.delete_client(1)
        self.assertTrue (len(test_serv.get_all_clients()) == 2)
        self.assertTrue (deleted_person.getNume() == 'Mara')

        deleted_person = test_serv.delete_client(3)
        self.assertTrue (len(test_serv.get_all_clients()) == 1)
        self.assertTrue (deleted_person.getNume() == 'Carmen')

   
       
    def test_modify_client(self):
        repo=ClientInMemoryRepo()
        val=ValidatorClient()
        test_serv=ClientService(repo,val)

        test_serv.add_client(1,'Mara',"1260406160861" )
        test_serv.add_client(2, 'Matei',"1330722122555")
        test_serv.add_client(3, 'Carmen',"6661029751557")

        self.assertTrue(len(test_serv.get_all_clients()) == 3)
        person_before_modif = test_serv.cauta_client(1)
    
        self.assertTrue(person_before_modif.getNume()=='Mara')

        test_serv.update_client(1,'Maya',"1260406160861")
        person_after_modif = test_serv.cauta_client(1)
        self.assertTrue(person_after_modif.getNume()=='Maya')

    
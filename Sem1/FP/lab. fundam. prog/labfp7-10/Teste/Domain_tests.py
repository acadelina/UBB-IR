
from Domain.Client import*
from Domain.Film import*
from Domain.Inchiriere import*
import unittest

class TesteDomain(unittest.TestCase):
    def test_Getters(self):
        film = Film(1, "Interstellar", "abcd", "SF",0)
        client = Client(1, "Andrei", "1111111123456")
        inchiriere = Inchiriere( 1, 1)

        self.assertTrue(film.getId()==1)
        self.assertTrue(film.getTitlu() == "Interstellar")
        self.assertTrue(film.getDesc() == "abcd")
        self.assertTrue(film.getGen() == "SF")


        self.assertTrue(client.getId() == 1)
        self.assertTrue(client.getNume() == "Andrei")
        self.assertTrue(client.getCnp() == "1111111123456")

       
        self.assertTrue(inchiriere.getCl() == 1)
        self.assertTrue(inchiriere.getFl() == 1)

    def test_Equals(self):
        film = Film(1, "Interstellar", "abcd", "SF",0)
        film2 = Film(2,"Inception","abcd","Action",0)
        self.assertFalse(film.__eq__(film2))
        self.assertTrue(film.__eq__(film))

        

        inchiriere = Inchiriere( 1, 1)
        inchiriere2 = Inchiriere( 1, 2)
        self.assertFalse(inchiriere.__eq__(inchiriere2))
        self.assertTrue(inchiriere.__eq__(inchiriere))

if __name__ == '__main__':
    unittest.main()    
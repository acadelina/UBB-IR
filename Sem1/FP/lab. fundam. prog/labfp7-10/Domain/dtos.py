class ClientFilmInc:
    def __init__(self, id_client, id_film):
        
        self.__client_id = id_client
        self.__film_id = id_film
        self.__nume_client = None
        self.__nume_film = None
        

    def getClientId(self):
        return self.__client_id

    def getShowId(self):
        return self.__film_id

    def getNumeClient(self):
        return self.__nume_client

    def getTitlufilm(self):
        return self.__nume_film


    def setNumeClient(self, value):
        self.__nume_client = value

    def setTitlufilm(self, value):
        self.__nume_film = value

    

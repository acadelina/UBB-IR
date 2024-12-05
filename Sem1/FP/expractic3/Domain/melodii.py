class Melodie:
    def __init__(self,titlu,artist,gen,durata):
        self.__titlu=titlu
        self.__artist=artist
        self.__gen=gen
        self.__durata=durata
    
    def get_titlu(self):
        return self.__titlu
    def get_artist(self):
        return self.__artist
    def get_gen(self):
        return self.__gen
    def get_durata(self):
        return self.__durata
    def set_durata(self,nou):
        self.__durata=nou
    def set_titlu(self,nou):
        self.__titlu=nou
    def set_artist(self,nou):
        self.__artist=nou
    def set_gen(self,nou):
        self.__gen=nou
    def __equ__(self,other):
        return self.__artist==other.get_artist() and self.__titlu==other.get_titlu()
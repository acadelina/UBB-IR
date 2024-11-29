class Carte:
    def __init__(self,id,titlu,autor,an):
        self.__id=id
        self.__titlu=titlu
        self.__autor=autor
        self.__an=an
    def get_id(self):
        return self.__id
    def get_titlu(self):
        return self.__titlu
    def get_autor(self):
        return self.__autor
    def get_an(self):
        return self.__an
    def set_id(self,nou):
        self.__id=nou
    def set_titlu(self,nou):
        self.__titlu=nou
    def set_autor(self,nou):
        self.__autor=nou
    def set_an(self,nou):
        self.__an=nou
    def __equ__(self,other):
        return self.__id==other.get_id()
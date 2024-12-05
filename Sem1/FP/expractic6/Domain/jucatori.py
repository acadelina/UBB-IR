class Jucator:

    def __init__(self,nume,prenume,inaltime,post):
        self.__nume=nume
        self.__prenume=prenume
        self.__inaltime=inaltime
        self.__post=post
    def get_nume(self):
        return self.__nume
    def get_prenume(self):
        return self.__prenume
    def get_inaltime(self):
        return self.__inaltime
    def get_post(self):
        return self.__post
    def set_nume(self,nou):
        self.__nume=nou
    def set_prenume(self,nou):
        self.__prenume=nou
    def set_inaltime(self,nou):
        self.__inaltime=nou
    def set_post(self,nou):
        self.__post=nou
    def __equ__(self,other):
        return self.__nume==other.get_nume() and self.__prenume==other.get_prenume()
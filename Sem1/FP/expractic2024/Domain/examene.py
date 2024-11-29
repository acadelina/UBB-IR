class Examen:
    def __init__(self,data,ora,materia,tip):
        self.__data=data
        self.__ora=ora
        self.__materia=materia
        self.__tip=tip
    def get_data(self):
        return self.__data
    def get_ora(self):
        return self.__ora
    def get_materia(self):
        return self.__materia
    def get_tip(self):
        return self.__tip
    def set_data(self,nou):
        self.__data=nou
    def set_ora(self,nou):
        self.__ora=nou
    def set_materia(self,nou):
        self.__materia=nou
    def set_tip(self,nou):
        self.__tip=nou
    def __equ__(self,other):
        return self.__materia==other.get_materia() and self.__tip==other.get_tip()
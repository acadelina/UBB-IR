class Piese:
    def __init__(self,titlu,regizor,gen,durata):
        self.__titlu=titlu
        self.__regizor=regizor
        self.__gen=gen
        self.__durata=durata

    def get_titlu(self):
        return self.__titlu
    def get_regizor(self):
        return self.__regizor
    def get_gen(self):
        return self.__gen
    def get_durata(self):
        return self.__durata
    def set_titlu(self,nou):
        self.__titlu=nou
    def set_regizor(self,nou):
        self.__regizor=nou
    def set_gen(self,nou):
        self.__gen=nou
    def set_durata(self,nou):
        self.__durata=nou
    
    def __equ__(self,other):
        return self.__titlu==other.get_titlu() and self.__regizor==other.get_durata()


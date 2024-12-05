class Tractor:
    def __init__(self,id,denumire,pret,model,data):
        self.__id=id
        self.__denumire=denumire
        self.__pret=pret
        self.__model=model
        self.__data=data
    def get_id(self):
        return self.__id
    def get_denumire(self):
        return self.__denumire
    def get_pret(self):
        return self.__pret
    def get_model(self):
        return self.__model
    def get_data(self):
        return self.__data
    def set_id(self,nou):
        self.__id=nou
    def set_denumire(self,nou):
        self.__denumire=nou
    def set_pret(self,nou):
        self.__pret=nou
    def set_model(self,nou):
        self.__model=nou
    def set_data(self,nou):
        self.__data=nou
    
    
    
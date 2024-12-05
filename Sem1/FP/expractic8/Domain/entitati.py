class Eveniment:
    def __init__(self,data,ora,desc):
        self.__data=data
        self.__ora=ora
        self.__desc=desc
    def get_data(self):
        return self.__data
    def get_ora(self):
        return self.__ora
    def get_desc(self):
        return self.__desc
    def set_data(self,nou):
        self.__data=nou
    def set_ora(self,nou):
        self.__ora=nou
    def set_desc(self,nou):
        self.__desc=nou
  
    
class Client():
    def __init__(self,id,nume,cnp):
        self.__id=id
        self.__nume=nume
        self.__cnp=cnp
        self.__filme=0
        
    def getId(self):
        return self.__id
    
    def setId(self,idnou):
        self.__id=idnou
   
    def getNume(self):
        return self.__nume
    
    def setNume(self,numenou):
        self.__nume=numenou
    
    def getCnp(self):
        return self.__cnp
   
    def setCnp(self,cnpnou):
        self.__cnp=cnpnou
    
    def getFilme(self):
        return self.__filme
   
    def setFilme(self,innou):
        self.__filme=innou
    
    """ def __eq__(self, other):
        if self.__id == other.__id:
            return True
        return False
    """
    def __lessthan__(self,other):
        if self.__getFilme<other.__getFilme:
            return True
        return False
    def __str__(self):
        return 'ID: ' + str(self.__id) + '; Nume: ' + str(self.__nume) + '; Cnp: ' + str(self.__cnp)+';Filme: '+str(self.__filme)
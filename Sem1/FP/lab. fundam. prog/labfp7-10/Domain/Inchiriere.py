class Inchiriere():
    def __init__(self,id_client,id_film):
        self.__cl=int(id_client)
        self.__fl=int(id_film)
    
    def getCl(self):
        return self.__cl
   
    def setCl(self,clnou):
        self.__cl=clnou

    def getFl(self):
        return self.__fl
   
    def setFl(self,flnou):
        self.__fl=flnou
    
    def __eq__(self, other):
        if self.__cl== other.__cl and self.__fl == other.__fl:
            return True
        return False

    def __str__(self):
        return 'Film: [' + str(self.__fl) + ']; ' + \
               'Client: [' + str(self.__cl) + '];'
        
class Film():
    def __init__(self,id,titlu,descriere,gen,inc):
        self.__id=id
        self.__titlu=titlu
        self.__descriere=descriere
        self.__gen=gen
       # self.__disponibilitate=True
        self.__inchirieri=inc
    def getId(self):
        return self.__id

    def getTitlu(self):
        return self.__titlu

    def getDesc(self):
        return self.__descriere

    def getGen(self):
        return self.__gen

    def getInc(self):
        return self.__inchirieri

    def setTitlu(self, value):
        self.__titlu = value

    def setDesc(self, value):
        self.__descriere = value

    def setGen(self, value):
        self.__gen = value

    def setId(self, value):
        self.__id = value

    def setInc(self,value):
        self.__inchirieri=value

    def __eq__(self, other):
        
        """Verifica egalitatea intre serialul curent si serialul other
        :param other:
        :type other: Serial
        :return: True daca serialele sunt egale (au acelasi id), False altfel
        :rtype: bool"""
        
        if self.__id == other.getId():
            return True
        return False

    def __str__(self):
        return "ID:" + str(self.getId()) + "; Titlu: " + self.__titlu + '; Descriere: ' + str(
            self.__descriere) + '; Gen: ' + str(self.__gen) +'; Inchirieri: ' + str(
            self.__inchirieri)

    def inc_inchirieri(self):
        self.__inchirieri=self.__inchirieri+1


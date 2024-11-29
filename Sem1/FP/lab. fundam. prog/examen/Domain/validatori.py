from Repository.repo_tractoare import *
from datetime import datetime

class Validate:
    def validare(self,id,denumire,pret,model,data):
        """
        Valideaza datele unui tractor
        preconditii: id:int
                     denumire:str
                     pret:int
                     model:str
                     data:str
        postconditii:
        raises: ValueError daca exista date invalide
        """
        erori=''
        try:
            id=int(id)
        except ValueError:
            erori+="Id-ul trebuie sa fie un numar intreg \n"
        try:
            pret=int(pret)
        except ValueError:
            erori+="Pretul trebuie sa fie un nr intreg \n"
        if denumire=='':
            erori+="Denumirea tractorului trebuie precizata \n"
        try:
            data=datetime.strptime(data,"%d.%m.%Y")
        except ValueError:
            erori+="Data este invalida \n"
        if model=='':
            erori+="Modelul trebuie precizat!"
        if len(erori)>0:
            raise ValueError(erori)
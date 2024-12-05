class Validate:
    def __init__(self,repo):
        self.__repo=repo

    def val_titlu(self,titlu):
        """
        Validare titlu
        preconditii: titlu: str
        postconditii:
        """
        if titlu=='':
            raise ValueError("Titlul trebuie precizat!")
    def val_artist(self,artist):
        """
        Validare artist
        preconditii: titlu: str
        postconditii:
        """
        if artist=='':
            raise ValueError("Artistul trebuie precizat!")
    def val_gen(self,gen):
        """
        Validare gen
        preconditii: gen:str
        postconditii:
        raises: ValueError daca nu face parte din genurile valide
        """
        genuri=["rock", "pop", "jazz", "altele"]
        ok=0
        for g in genuri:
            if g==gen:
                ok=1
        if ok==0:
            raise ValueError("Gen invalid!")
    def val_durata(self,durata):
        try:
            durata=int(durata)
           
        except: raise ValueError("Durata trebuie sa fie un numar intreg pozitiv")
        if durata<0:
             raise ValueError("Durata pozitiva")
    def validare(self,melodie):
        erori=''
        try:
            self.val_artist(melodie.get_artist())
        except ValueError as e:
            erori=erori+str(e)+'\n'
        try:
            self.val_titlu(melodie.get_titlu())
        except ValueError as e:
            erori=erori+str(e)+'\n'
        try:
            self.val_gen(melodie.get_gen())
        except ValueError as e:
            erori=erori+str(e)+'\n'
        try:
            self.val_durata(melodie.get_durata())
        except ValueError as e:
            erori=erori+str(e)+'\n'
        if len(erori)>0:
            raise ValueError(erori)
        
        

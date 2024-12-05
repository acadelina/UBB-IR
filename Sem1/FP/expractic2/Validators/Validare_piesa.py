
class Validare:
    
    def validare_gen(self,gen):
        genuri=["Comedie", "Drama", "Satira", "Altele"]
        ok=0
        for i in genuri:
            if i==gen:
                ok=1
        if ok==0:
            raise ValueError("Genul dat este incorect!")
    def validare_titlu(self,titlu):
        if titlu=='':
            raise ValueError("Titlu invalid!")
    def validare_regizor(self,regizor):
        if regizor=='':
            raise ValueError("Regizor invalid!")
    def validare_durata(self,durata):
        try:
            durata=int(durata)
        except:
            raise ValueError("Durata trebuie sa fie un numar intreg!")
        if durata<0:
            raise ValueError("Durata trebuie sa fie un numar pozitiv!")
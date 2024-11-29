class Validators:
   
    def validate(self,jucator):
        """
        Validarea unui jucator
        preconditii: jucator
        postconditii:
        raises: ValuError-> jucator invalid
        """
        erori=''
        if jucator.get_nume()=='':
            erori+="Numele jucatorului trebuie precizat! \n"
        if jucator.get_prenume()=='':
            erori+="Prenume jucatorului trebuie precizat! \n"
        if jucator.get_post() not in ["fundas","pivot","extrema"]:
            erori+="Postul jucatorului este invalid! \n"
        h=jucator.get_inaltime()
        try:
            h=int(h)
        except ValueError:
            erori+="Inaltimea trebuie sa fie un numar intreg! \n"
        if h<0:
            erori+="Inaltimea trebuie sa fie un numar pozitiv! "
        
        if len(erori)>0:
            raise ValueError(erori)
        
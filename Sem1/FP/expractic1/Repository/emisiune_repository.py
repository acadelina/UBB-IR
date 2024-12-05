from Data.emisiune import*
class FileRepoEmisiune:
    def __init__(self,file_name):
        self.__file=file_name

    def load_from_file(self):
        try:
            f=open(self.__file,'r')
        except IOError:
            raise IOError
        emisiuni=[]
        content=f.read()
        lines=content.split('\n')
        for line in lines:
            if line!='':
                line.strip()
                atribute=line.split(',')
                nume=str(atribute[0])
                tip=str(atribute[1])
                durata=str(atribute[2])
                descriere=str(atribute[3])
           
                e=Emisiune(nume,tip,durata,descriere)
                emisiuni.append(e)
        
        f.close()
        return emisiuni
    
    def save_to_file(self,lista):
        with open(self.__file,'w') as f:
            for emisiune in lista:
                str_emisiune=str(emisiune.get_em_nume())+','+str(emisiune.get_em_tip())+','+str(emisiune.get_em_durata())+','+str(emisiune.get_em_descriere())+'\n'
                f.write(str_emisiune)

    def find(self,nume,tip):
        lista=self.load_from_file()
        for e in lista:
            if e.get_em_nume()==nume and e.get_em_tip()==tip:
                return e
        return None  
    
    def delete(self,nume,tip):
        lista=self.load_from_file()
        emisiune=self.find(nume,tip)
        if emisiune is None:
            raise ValueError("Emisiune inexistenta!")
       
        lista = [el for el in lista if el.get_em_nume() != nume and el.get_em_tip() != tip]
        
        
        self.save_to_file(lista)

    def update(self,nume,tip,durata,descriere):
        lista=self.load_from_file()
        ok=0
        for e in lista:
            if e.get_em_nume()==nume and e.get_em_tip()==tip:
                e.set_em_descriere(descriere)
                e.set_em_durata(durata)
                ok=1
        if ok==1:
            self.save_to_file(lista)
        else:
            raise ValueError("Emisiune inexistenta!")

    
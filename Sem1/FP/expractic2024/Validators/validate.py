class Validate:
    def __init__(self,repo):
        self.__repo=repo
    def val_data(self,data):
        data=data.split('.')
        if data[1] in ['01','03','05','07','08','10','12'] and data[0]>'31' or data[0]<'0':
            raise ValueError("Data invalida!")
        if data[1] in ['04','06','09','11'] and data[0]>'30' or data[0]<'0':
            raise ValueError("Data invalida!")
        if data[1]=='02' and data[0]>'28' or data[0]<'0':
            raise ValueError("Data invalida!")
    def val_ora(self,ora):
        ora=ora.split(':')
        if ora[0]<'00' or ora[0]>'23':
            raise ValueError("Ora invalida!")
        if ora[1]<'00' or ora[1]>'59':
            raise ValueError("Ora invalida!")
    def val_materie(self,mat):
        if mat=='':
            raise ValueError("Materia trebuie precizata!")
    def val_tip(self,tip):
        if tip!="normal" and tip!="restanta":
            raise ValueError("Tip invalid!")
    def validare(self,exam):
        erori=''
        try:
            self.val_data(exam.get_data())
        except ValueError as e:
            erori=erori+str(e)+'\n'
        try:
            self.val_materie(exam.get_materia())
        except ValueError as e:
            erori=erori+str(e)+'\n'
        try:
            self.val_ora(exam.get_ora())
        except ValueError as e:
            erori=erori+str(e)+'\n'
        try:
            self.val_tip(exam.get_tip())
        except ValueError as e:
            erori=erori+str(e)+'\n'
        if len(erori)>0:
            raise ValueError(erori)
        



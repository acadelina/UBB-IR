from datetime import datetime
class Validate:
    def validare(self,eveniment):
        data=eveniment.get_data()
        ora=eveniment.get_ora()
        er=''
        try:
            data=datetime.strptime(data,"%d.%m.%Y")
        except ValueError:
            er+="Data nu este valida!\n"
        try:
            ora=datetime.strptime(ora,"%H:%M")
        except ValueError:
            er+="Ora este invalida!"

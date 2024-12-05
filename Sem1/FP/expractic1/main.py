from Service.emisiune_service import*
from Ui.Console import *
from Data.emisiune import*
from Repository.emisiune_repository import *

repo=FileRepoEmisiune("emisiuni.txt")
serv=Service(repo)
ui=Console(serv)
ui.run()

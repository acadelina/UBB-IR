from Service.Service_piese import *
from Repository.Repo import *
from UI.Console import*

repo=RepoPiese("piese.txt")
val=Validare()
serv=Service(repo,val)
ui=Console(serv)
ui.run()
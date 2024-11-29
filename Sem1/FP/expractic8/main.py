from Domain.entitati import*
from Domain.validator import*
from Repository.repo_ev import*
from Service.serv_ev import*
from UI.Console import*
val=Validate()
repo=Repository("evenimente.txt")
serv=Service(repo,val)
ui=Console(serv)
ui.run()
from Domain.carti import*
from Repository.repo_carti import*
from Service.serv_carti import*
from UI.console import*

repo=Repository("carti.txt")
serv=Service(repo)
ui=Console(serv)
ui.run()
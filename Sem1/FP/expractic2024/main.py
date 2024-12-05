from Domain.examene import*
from Repository.repo_exam import*
from Service.service import*
from Validators.validate import *
from UI.console import*

repo=Repository("examene.txt")
val=Validate(repo)
serv=Service(repo,val)
ui=Console(serv)
ui.run()
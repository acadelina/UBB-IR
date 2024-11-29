from Domain.melodii import*
from Repository.repo_melodii import*
from Service.service import*
from Validation.val_mel import*
from UI.console import*

repo=Repo_melodii("melodii.txt")
val=Validate(repo)
serv=Service(repo,val)
ui=Console(serv)
ui.run()

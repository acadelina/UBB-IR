from Domain.entitati import*
from Repository.repo_tractoare import*
from Service.serv_tractoare import*
from UI.console import *
from Domain.validatori import*
from Teste.domain_tests import*
from Teste.repo_tests import *
from Teste.serv_tests import*

repo=Repository("tractoare.txt")
val=Validate()
serv=Service(repo,val)
ui=Console(serv)
test_domain()
test_repo()
test_serv()
ui.run()
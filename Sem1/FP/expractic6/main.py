from Domain.validator import*
from Repository.repo_juc import*
from Service.serv_juc import *
from UI.console import*
from Teste.domain_tests import*
from Teste.repo_tests import*
from Teste.serv_tests import *

repo=Repository("data/jucatori.txt")
val=Validators()
serv=Service(repo,val)
ui=Console(serv)
repo_tests()
domain_tests()
test_service()
ui.run()
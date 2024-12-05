from Domain.jucatori import *
from Repository.repo_juc import*
from Teste.file_utils import *
from Service.serv_juc import*

def test_service():
    clear_file_content("data/test.txt")
    repo=Repository("data/test.txt")
    val=Validators()
    serv=Service(repo,val)
    juc=Jucator("Nume1","Prenume1",178,"pivot")
    repo.add(juc)
    try :
        serv.adaugare("Nume1","Prenume1",165,"pivot")
        assert False
    except ValueError :
        assert True
    
    serv.adaugare("Nume2","Prenume2",190,"extrema")
    l=repo.load_from_file()
    assert len(l)==2

    try:
        serv.modifica("Nume3","Prenume3",200)
        assert False
    except ValueError:
        assert True
    serv.modifica("Nume1","Prenume1",200)
    m=repo.find("Nume1","Prenume1")
    l=repo.load_from_file()
    assert l[m].get_inaltime()=='200'

    

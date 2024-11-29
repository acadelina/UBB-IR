from Domain.entitati import*
from Domain.validatori import*
from Repository.repo_tractoare import *
from Service.serv_tractoare import*

def clear_fis(nume):
    with open(nume,'w') as f:
        pass
def test_serv():
    repo=Repository("Teste/test.txt")
    val=Validate()
    serv=Service(repo,val)
    clear_fis("Teste/test.txt")

    try:
        serv.adaugare("s","asd",234,"v4","12.05.2024")
        assert False
    except ValueError:
        assert True


    try:
        serv.undo()
        assert False
    except ValueError:
        assert True


    serv.adaugare("1","asd",234,"v4","12.05.2024")
    l=repo.load_from_file()
    assert len(l)==1


    serv.adaugare("2","aad",211,"v5","12.05.2024")
    assert serv.stergere('1')==1

    
    try:
        serv.stergere('0')
        assert False
    except ValueError:
        assert True


    serv.undo()
    l=repo.load_from_file()
    assert len(l)==2


    l=serv.filtrare("a","300")
    assert len(l)==2


    l=serv.filtrare("b","300")
    assert len(l)==0

    





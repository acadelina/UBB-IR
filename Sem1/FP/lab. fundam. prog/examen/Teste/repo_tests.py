from Domain.entitati import*
from Repository.repo_tractoare import *

def clear_fis(nume):
    with open(nume,'w') as f:
        pass
def test_repo():
    repo=Repository("Teste/test.txt")
    clear_fis("Teste/test.txt")

    l=repo.load_from_file()
    assert len(l)==0

    tr1=Tractor('1',"asd",'234',"v4","12.05.2024")
    tr2=Tractor('2',"tr2",'194',"v8","12.05.2024")
    l=[tr1,tr2]

    repo.save_to_file(l)
    try:
        repo.add(tr1)
        assert False
    except ValueError:
        assert True

    tr3=Tractor(3,"tr3",534,"v0","12.12.2023")

    try:
        repo.undo()
        assert False
    except ValueError:
        assert True
    
    repo.add(tr3)
    l=repo.load_from_file()
    assert len(l)==3

    repo.delete('1')
    l=repo.load_from_file()
    assert len(l)==2

    repo.undo()
    l=repo.load_from_file()
    assert len(l)==3
    
    v=repo.filtrare("tr","600")
    assert len(v)==2
    



    


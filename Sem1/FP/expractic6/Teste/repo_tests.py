from Domain.jucatori import *
from Repository.repo_juc import*
from Teste.file_utils import *

def test_add():
    clear_file_content("data/test.txt")
    repo=Repository("data/test.txt")
    juc=Jucator("Nume1","Prenume1","178","Pivot")
    repo.add(juc)
    l=repo.load_from_file()
    assert len(l)==1
def test_find():
    clear_file_content("data/test.txt")
    repo=Repository("data/test.txt")
    juc=Jucator("Nume1","Prenume1",178,"Pivot")
    repo.add(juc)
    m=repo.find("Nume1","Prenume1")
    assert m!=-1
    m=repo.find("N","Prenume1")
    assert m==-1

def test_sort_h():
    clear_file_content("data/test.txt")
    repo=Repository("data/test.txt")
    juc=Jucator("Nume1","Prenume1",178,"Pivot")
    juc1=Jucator("Nume2","Prenume2",190,"Pivot")
    repo.add(juc)
    repo.add(juc1)
    l=repo.sort_h()
    assert l[0].__equ__(juc1)
    assert l[1].__equ__(juc)

def test_generate():
    clear_file_content("data/test.txt")
    repo=Repository("data/test.txt")
    m=repo.generate("data/nume_test.txt")
    assert m>0


def repo_tests():
    test_add()
    test_find()
    test_sort_h()
    test_generate() 


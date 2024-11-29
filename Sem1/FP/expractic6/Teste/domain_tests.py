from Domain.jucatori import *
from Domain.validator import *

def test_create_jucator():
    juc=Jucator("Nume1","Prenume1",178,"Pivot")
    assert juc.get_nume()=="Nume1"
    assert juc.get_prenume()=="Prenume1"
    assert juc.get_inaltime()==178
    assert juc.get_post()=="Pivot"
    juc.set_nume("Nume2")
    assert juc.get_nume()=="Nume2"

def test_validare():
    val=Validators()
    juc=Jucator("","Prenume1",178,"Pivot")
    try:
        val.validate(juc)
        assert False
    except ValueError:
        assert True
    juc=Jucator("Nume1","Prenume1",-178,"Pivot")
    try:
        val.validate(juc)
        assert False
    except ValueError:
        assert True    
    juc=Jucator("Nume","Prenume1",178,"altceva")
    try:
        val.validate(juc)
        assert False
    except ValueError:
        assert True

def domain_tests():
    test_create_jucator()
    test_validare()    
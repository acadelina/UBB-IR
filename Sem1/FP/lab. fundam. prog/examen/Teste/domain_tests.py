from Domain.entitati import*
from Domain.validatori import*

def test_domain():
    val=Validate()
    tractor=Tractor(1,"asd",234,"v4","12.05.2024")
    assert tractor.get_id()==1
    assert tractor.get_denumire()=="asd"
    assert tractor.get_pret()==234
    assert tractor.get_model()=="v4"
    assert tractor.get_data()=="12.05.2024"
    tractor.set_id(4)
    assert tractor.get_id()==4

    try:
        val.validare("s","asd",234,"v4","12.05.2024")
        assert False
    except ValueError:
        assert True
    
    try:
        val.validare(1,"",234,"v4","12.05.2024")
        assert False
    except ValueError:
        assert True

test_domain()
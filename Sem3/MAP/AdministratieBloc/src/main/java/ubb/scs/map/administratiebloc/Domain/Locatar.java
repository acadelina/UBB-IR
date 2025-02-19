package ubb.scs.map.administratiebloc.Domain;

import java.util.Date;

public class Locatar extends Persoana{
    Long apartament;
    public Locatar(String nume, String prenume, Date dataNasterii,Long apartament) {
        super(nume, prenume, dataNasterii);
        this.apartament = apartament;
    }

    public Long getApartament() {
        return apartament;
    }

    public void setApartament(Long apartament) {
        this.apartament = apartament;
    }
}

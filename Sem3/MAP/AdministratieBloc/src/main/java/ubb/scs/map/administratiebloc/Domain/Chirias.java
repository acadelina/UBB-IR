package ubb.scs.map.administratiebloc.Domain;

import java.util.Date;

public class Chirias extends Locatar{
    Long chirie;
    public Chirias(String nume, String prenume, Date dataNasterii, Long apartament,Long chirie) {
        super(nume, prenume, dataNasterii, apartament);
        this.chirie = chirie;
    }
    public Long getChirie() {
        return chirie;
    }
    public void setChirie(Long chirie) {
        this.chirie = chirie;
    }
}

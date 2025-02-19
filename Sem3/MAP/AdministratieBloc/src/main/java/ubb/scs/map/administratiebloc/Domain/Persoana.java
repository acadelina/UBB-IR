package ubb.scs.map.administratiebloc.Domain;

import java.util.Date;

public class Persoana extends Entity<Long>{
    String nume;
    String prenume;
    Date dataNasterii;

    public Persoana(String nume, String prenume, Date dataNasterii) {
        this.nume = nume;
        this.prenume = prenume;
        this.dataNasterii = dataNasterii;
    }

    public String getNume() {
        return nume;
    }

    public void setNume(String nume) {
        this.nume = nume;
    }

    public String getPrenume() {
        return prenume;
    }

    public void setPrenume(String prenume) {
        this.prenume = prenume;
    }

    public Date getDataNasterii() {
        return dataNasterii;
    }

    public void setDataNasterii(Date dataNasterii) {
        this.dataNasterii = dataNasterii;
    }
}

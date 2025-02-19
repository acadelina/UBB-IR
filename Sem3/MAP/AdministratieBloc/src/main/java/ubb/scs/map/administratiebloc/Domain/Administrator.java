package ubb.scs.map.administratiebloc.Domain;

import java.util.ArrayList;
import java.util.Date;

public class Administrator extends Persoana{
    Long apartament;
    ArrayList<Bloc> bloc;

    public Long getApartament() {
        return apartament;
    }

    public void setApartament(Long apartament) {
        this.apartament = apartament;
    }

    public ArrayList<Bloc> getBloc() {
        return bloc;
    }

    public void setBloc(ArrayList<Bloc> bloc) {
        this.bloc = bloc;
    }

    public Administrator(String nume, String prenume, Date dataNasterii, Long apartament, ArrayList<Bloc> bloc) {
        super(nume, prenume, dataNasterii);
        this.apartament = apartament;
        this.bloc = bloc;
    }
}

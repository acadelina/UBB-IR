package ubb.scs.map.administratiebloc.Domain;

public class Apartament extends Entity<Long> {
    Long bloc;
    Integer nr_apartamente;
    Integer nr_camere;
    TipApartament tipApartament;
    Integer suprafata;

    public Apartament(Long bloc, Integer nr_apartamente, Integer nr_camere, TipApartament tipApartament, Integer suprafata) {
        this.bloc = bloc;
        this.nr_apartamente = nr_apartamente;
        this.nr_camere = nr_camere;
        this.tipApartament = tipApartament;
        this.suprafata = suprafata;
    }

    public Long getBloc() {
        return bloc;
    }

    public void setBloc(Long bloc) {
        this.bloc = bloc;
    }

    public Integer getNr_apartamente() {
        return nr_apartamente;
    }

    public void setNr_apartamente(Integer nr_apartamente) {
        this.nr_apartamente = nr_apartamente;
    }

    public Integer getNr_camere() {
        return nr_camere;
    }

    public void setNr_camere(Integer nr_camere) {
        this.nr_camere = nr_camere;
    }

    public TipApartament getTipApartament() {
        return tipApartament;
    }

    public void setTipApartament(TipApartament tipApartament) {
        this.tipApartament = tipApartament;
    }

    public Integer getSuprafata() {
        return suprafata;
    }

    public void setSuprafata(Integer suprafata) {
        this.suprafata = suprafata;
    }
}

package ubb.scs.map.administratiebloc.Domain;

import java.util.ArrayList;

public class Bloc extends Entity<Long> {
    Long adresa;
    Integer etaje;
    Long administrator;
    ArrayList<Apartament> apartamente;

    public Bloc() {}
    public Bloc(Long adresa, Integer etaje, Long administrator, ArrayList<Apartament> apartamente) {
        this.adresa = adresa;
        this.etaje = etaje;
        this.administrator = administrator;
        this.apartamente = apartamente;
    }

    public Long getAdresa() {
        return adresa;
    }

    public void setAdresa(Long adresa) {
        this.adresa = adresa;
    }

    public Integer getEtaje() {
        return etaje;
    }

    public void setEtaje(Integer etaje) {
        this.etaje = etaje;
    }

    public Long getAdministrator() {
        return administrator;
    }

    public void setAdministrator(Long administrator) {
        this.administrator = administrator;
    }

    public ArrayList<Apartament> getApartamente() {
        return apartamente;
    }

    public void setApartamente(ArrayList<Apartament> apartamente) {
        this.apartamente = apartamente;
    }
}

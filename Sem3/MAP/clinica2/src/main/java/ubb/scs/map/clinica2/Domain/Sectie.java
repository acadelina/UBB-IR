package ubb.scs.map.clinica2.Domain;

public class Sectie extends Entity<Long>{
    String nume;
    Long idsef;
    Integer pret;
    Integer durataMax;

    public Sectie(String nume, Long idsef, Integer pret, Integer durataMax) {
        this.nume = nume;
        this.idsef = idsef;
        this.pret = pret;
        this.durataMax = durataMax;
    }

    public String getNume() {
        return nume;
    }

    public void setNume(String nume) {
        this.nume = nume;
    }

    public Long getIdsef() {
        return idsef;
    }

    public void setIdsef(Long idsef) {
        this.idsef = idsef;
    }

    public Integer getPret() {
        return pret;
    }

    public void setPret(Integer pret) {
        this.pret = pret;
    }

    public Integer getDurataMax() {
        return durataMax;
    }

    public void setDurataMax(Integer durataMax) {
        this.durataMax = durataMax;
    }
}

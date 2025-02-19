package ubb.scs.map.anar.Domain;

public class Localitate extends  Entity <Integer>{
    String nume;
    Integer rau;
    Float cotamin;
    Float cotamax;

    public String getNume() {
        return nume;
    }

    public void setNume(String nume) {
        this.nume = nume;
    }

    public Integer getRau() {
        return rau;
    }

    public void setRau(Integer rau) {
        this.rau = rau;
    }

    public Float getCotamin() {
        return cotamin;
    }

    public void setCotamin(Float cotamin) {
        this.cotamin = cotamin;
    }

    public Float getCotamax() {
        return cotamax;
    }

    public void setCotamax(Float cotamax) {
        this.cotamax = cotamax;
    }

    public Localitate(String nume, Integer rau, Float cotamin, Float cotamax) {
        this.nume = nume;
        this.rau = rau;
        this.cotamin = cotamin;
        this.cotamax = cotamax;
    }
}

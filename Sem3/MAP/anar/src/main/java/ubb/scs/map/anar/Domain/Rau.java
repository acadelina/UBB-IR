package ubb.scs.map.anar.Domain;

public class Rau extends Entity <Integer> {
    String nume;
    Float cotamedie;

    public String getNume() {
        return nume;
    }

    public void setNume(String nume) {
        this.nume = nume;
    }

    public Float getCotamedie() {
        return cotamedie;
    }

    public void setCotamedie(Float cotamedie) {
        this.cotamedie = cotamedie;
    }

    public Rau(String nume, Float cotamedie) {
        this.nume = nume;
        this.cotamedie = cotamedie;
    }
}

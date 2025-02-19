package ubb.scs.map.administratiebloc.Domain;

public class Adresa extends Entity<Long>{
    String strada;
    String numar;

    public Adresa(String numar, String strada) {
        this.numar = numar;
        this.strada = strada;
    }

    public String getStrada() {
        return strada;
    }

    public void setStrada(String strada) {
        this.strada = strada;
    }

    public String getNumar() {
        return numar;
    }

    public void setNumar(String numar) {
        this.numar = numar;
    }
}

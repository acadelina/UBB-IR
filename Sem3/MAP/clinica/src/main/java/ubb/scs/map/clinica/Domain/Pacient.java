package ubb.scs.map.clinica.Domain;

public class Pacient extends Entity<Integer> {
    Integer varsta;
    String prematur;
    String diagnostic;
    Integer gravitate;

    public Pacient(Integer varsta, String prematur, String diagnostic, Integer gravitate) {
        this.varsta = varsta;
        this.prematur = prematur;
        this.diagnostic = diagnostic;
        this.gravitate = gravitate;
    }

    @Override
    public String toString() {
        return "Pacient{" +
                "varsta=" + varsta +
                ", prematur='" + prematur + '\'' +
                ", diagnostic='" + diagnostic + '\'' +
                ", gravitate=" + gravitate +
                '}';
    }

    public Integer getVarsta() {
        return varsta;
    }

    public void setVarsta(Integer varsta) {
        this.varsta = varsta;
    }

    public String getPrematur() {
        return prematur;
    }

    public void setPrematur(String prematur) {
        this.prematur = prematur;
    }

    public String getDiagnostic() {
        return diagnostic;
    }

    public void setDiagnostic(String diagnostic) {
        this.diagnostic = diagnostic;
    }

    public Integer getGravitate() {
        return gravitate;
    }

    public void setGravitate(Integer gravitate) {
        this.gravitate = gravitate;
    }


}

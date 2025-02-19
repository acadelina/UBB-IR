package ubb.scs.map.clinica.Domain;

public class Pat extends Entity<Integer> {
    TipPat tipPat;
    String ventilatie;
    Integer pacient;

    public Pat(TipPat tipPat, String ventilatie, Integer pacient) {
        this.tipPat = tipPat;
        this.ventilatie = ventilatie;
        this.pacient = pacient;
    }

    public Pat(TipPat tipPat, String ventilatie) {
        this.tipPat = tipPat;
        this.ventilatie = ventilatie;
        this.pacient = null;
    }

    @Override
    public String toString() {
        return "Pat{" +
                "tipPat=" + tipPat +
                ", ventilatie='" + ventilatie + '\'' +
                ", pacient=" + pacient +
                '}';
    }

    public TipPat getTipPat() {
        return tipPat;
    }

    public void setTipPat(TipPat tipPat) {
        this.tipPat = tipPat;
    }

    public String getVentilatie() {
        return ventilatie;
    }

    public void setVentilatie(String ventilatie) {
        this.ventilatie = ventilatie;
    }

    public Integer getPacient() {
        return pacient;
    }

    public void setPacient(Integer pacient) {
        this.pacient = pacient;
    }
}

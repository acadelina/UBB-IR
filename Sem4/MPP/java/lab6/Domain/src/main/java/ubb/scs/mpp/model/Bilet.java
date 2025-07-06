package ubb.scs.mpp.model;



public class Bilet extends Entity<Long> {
    private String buyer;
    private Integer seats_number;
    private Spectacol spectacol;

    public String getBuyer() {
        return buyer;
    }

    public void setBuyer(String buyer) {
        this.buyer = buyer;
    }

    public Integer getSeats_number() {
        return seats_number;
    }

    public void setSeats_number(Integer seats_number) {
        this.seats_number = seats_number;
    }

    public Spectacol getSpectacol() {
        return spectacol;
    }

    public void setSpectacol(Spectacol spectacol) {
        this.spectacol = spectacol;
    }

    public Bilet(String buyer, Integer seats_number, Spectacol spectacol) {
        this.buyer = buyer;
        this.seats_number = seats_number;
        this.spectacol = spectacol;
    }

    @Override
    public String toString() {
        return "Bilet [buyer=" + buyer + ", seats_number="+seats_number+", spectacol="+spectacol.toString()+"]";
    }
}

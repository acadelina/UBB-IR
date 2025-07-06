package ubb.scs.mpp.model;

import jakarta.persistence.*;
import jakarta.persistence.Entity;


@Entity
@Table(name="bilete")
public class Bilet extends ubb.scs.mpp.model.Entity<Long>  {

    @Id
    @GeneratedValue(generator = "increment")
    @Column(name = "id")
    Long id;
    private String buyer;
    private Integer seats;
    @ManyToOne
    @JoinColumn(name="spectacol")
    private Spectacol spectacol;

    public Bilet() {
        buyer="default";
        seats=0;
        spectacol=null;
    }

    @Column(name="buyer")
    public String getBuyer() {
        return buyer;
    }

    public void setBuyer(String buyer) {
        this.buyer = buyer;
    }

    @Column(name="seats")
    public Integer getSeats_number() {
        return seats;
    }

    public void setSeats_number(Integer seats_number) {
        this.seats= seats_number;
    }

    public Spectacol getSpectacol() {
        return spectacol;
    }

    public void setSpectacol(Spectacol spectacol) {
        this.spectacol = spectacol;
    }


    public Bilet(String buyer, Integer seats_number, Spectacol spectacol) {
        this.buyer = buyer;
        this.seats = seats_number;
        this.spectacol = spectacol;
    }



    @Override
    public String toString() {
        return "Bilet [buyer=" + buyer + ", seats_number="+seats+", spectacol="+spectacol.toString()+"]";
    }


    @Override
    public Long getId() {
        return id;
    }

    @Override
    public void setId(Long aLong) {
        this.id = aLong;
    }
}

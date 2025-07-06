package ubb.scs.mpp.model;
import jakarta.persistence.Table;

import jakarta.persistence.*;
import java.time.LocalDateTime;
import jakarta.persistence.Entity;

@Entity
@Table(name = "spectacole")
public class Spectacol extends ubb.scs.mpp.model.Entity<Long> {

    @Id
    @GeneratedValue(generator = "increment")
    @Column(name = "id")
    private Long id;
    private String artist;
    private LocalDateTime data;
    private String location;
    private Integer avseats;
    private Integer soseats;

    public Spectacol(String artist, LocalDateTime date, String location, Integer available_seats, Integer sold_seats) {
        this.artist = artist;
        this.data = date;
        this.location = location;
        this.avseats = available_seats;
        this.soseats = sold_seats;
    }

    public Spectacol() {

        this.artist = this.location ="default";
        this.data = LocalDateTime.now();
        this.avseats = 0;
        this.soseats = 0;
    }

    @Column(name="artist")
    public String getArtist() {
        return artist;
    }

    public void setArtist(String artist) {
        this.artist = artist;
    }

    @Column(name="data")
    public LocalDateTime getDate() {
        return data;
    }

    public void setDate(LocalDateTime date) {
        this.data = date;
    }

    @Column(name="location")
    public String getLocation() {
        return location;
    }

    public void setLocation(String location) {
        this.location = location;
    }

    @Column(name="avseats")
    public Integer getAvailable_seats() {
        return avseats;
    }

    public void setAvailable_seats(Integer available_seats) {
        this.avseats = available_seats;
    }

    @Column(name="soseats")
    public Integer getSold_seats() {
        return soseats;
    }

    public void setSold_seats(Integer sold_seats) {
        this.soseats = sold_seats;
    }

    @Override
    public String toString() {
        return "Spectacol [artist=" + artist + ", date=" + data + ", location=" + location+ ", available_seats=" + avseats+ ", sold_seats=" + soseats + "]";
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

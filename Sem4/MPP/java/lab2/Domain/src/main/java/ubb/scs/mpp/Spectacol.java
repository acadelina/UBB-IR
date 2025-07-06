package ubb.scs.mpp;

import java.util.Date;

public class Spectacol extends Entity<Long>{
    String artist;
    Date date;
    String location;
    Integer available_seats;
    Integer sold_seats;

    public Spectacol(String artist, Date date, String location, Integer available_seats, Integer sold_seats) {
        this.artist = artist;
        this.date = date;
        this.location = location;
        this.available_seats = available_seats;
        this.sold_seats = sold_seats;
    }

    public String getArtist() {
        return artist;
    }

    public void setArtist(String artist) {
        this.artist = artist;
    }

    public Date getDate() {
        return date;
    }

    public void setDate(Date date) {
        this.date = date;
    }

    public String getLocation() {
        return location;
    }

    public void setLocation(String location) {
        this.location = location;
    }

    public Integer getAvailable_seats() {
        return available_seats;
    }

    public void setAvailable_seats(Integer available_seats) {
        this.available_seats = available_seats;
    }

    public Integer getSold_seats() {
        return sold_seats;
    }

    public void setSold_seats(Integer sold_seats) {
        this.sold_seats = sold_seats;
    }
}

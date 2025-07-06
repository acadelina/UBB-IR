package ubb.scs.mpp.model;
import java.time.LocalDateTime;

public class Spectacol extends Entity<Long> {
    private String artist;
    private LocalDateTime date;
    private String location;
    private Integer available_seats;
    private Integer sold_seats;

    public Spectacol(String artist, LocalDateTime date, String location, Integer available_seats, Integer sold_seats) {
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

    public LocalDateTime getDate() {
        return date;
    }

    public void setDate(LocalDateTime date) {
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

    @Override
    public String toString() {
        return "Spectacol [artist=" + artist + ", date=" + date + ", location=" + location+ ", available_seats=" + available_seats+ ", sold_seats=" + sold_seats + "]";
    }
}

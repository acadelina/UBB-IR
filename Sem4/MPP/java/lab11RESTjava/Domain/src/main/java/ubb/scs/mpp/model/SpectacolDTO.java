package ubb.scs.mpp.model;

import com.fasterxml.jackson.annotation.JsonFormat;

import java.time.LocalDateTime;

public class SpectacolDTO {
    private String id;
    private String artist;
    private String data;
    private String location;
    private String avseats;
    private String soseats;



    public String getId() {
        return id;
    }

    public void setId(String id) {
        this.id = id;
    }

    public String getArtist() {
        return artist;
    }

    public void setArtist(String artist) {
        this.artist = artist;
    }

    public String getData() {
        return data;
    }

    public void setData(String data) {
        this.data = data;
    }

    public String getLocation() {
        return location;
    }

    public void setLocation(String location) {
        this.location = location;
    }

    public String getAvailable_seats() {
        return avseats;
    }

    public void setAvailable_seats(String avseats) {
        this.avseats = avseats;
    }

    public String getSold_seats() {
        return soseats;
    }

    public void setSold_seats(String soseats) {
        this.soseats = soseats;
    }

    @Override
    public String toString() {
        return "SpectacolDTO [id=" + id + ", artist=" + artist + ", data=" + data + ", location=" + location+ ", avseats=" + avseats+ ", soseats=" + soseats + "]";
    }

    @Override
    public boolean equals(Object o) {
        if (this == o) return true;
        if (!(o instanceof Spectacol)) return false;
        SpectacolDTO trip = (SpectacolDTO) o;
        return artist.equals(trip.artist) &&
                data.equals(trip.data) &&
                location.equals(trip.location)&&
                avseats.equals(trip.avseats)
                && soseats.equals(trip.soseats);

    }

    @Override
    public int hashCode() {
        int result = artist.hashCode();
        result = 31 * result + data.hashCode();
        result = 31 * result + location.hashCode();
        result = 31 * result + avseats.hashCode();
        result = 31 * result + soseats.hashCode();
        return result;
    }
}

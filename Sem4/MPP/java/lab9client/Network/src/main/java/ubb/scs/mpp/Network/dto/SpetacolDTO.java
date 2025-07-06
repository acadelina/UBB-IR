package ubb.scs.mpp.Network.dto;

import ubb.scs.mpp.model.Spectacol;

import java.time.LocalDateTime;

public class SpetacolDTO extends EntityDTO{
    private final String artist;
    private final LocalDateTime date;
    private final String location;
    private final int avseats;
    private final int soseats;

    public SpetacolDTO(String artist, LocalDateTime date, String location, int avseats, int soseats) {
        this.artist = artist;
        this.date = date;
        this.location = location;
        this.avseats = avseats;
        this.soseats = soseats;
    }
    public String getArtist() {
        return artist;
    }
    public LocalDateTime getDate() {
        return date;
    }
    public String getLocation() {
        return location;
    }
    public int getAvseats() {
        return avseats;
    }
    public int getSoseats() {
        return soseats;
    }

    public static SpetacolDTO fromSpectacol(Spectacol entity) {
        var s=new SpetacolDTO(entity.getArtist(),entity.getDate(),entity.getLocation(),entity.getAvailable_seats(), entity.getSold_seats());
        s.setId(entity.getId());
        return s;
    }

    public Spectacol toSpectacol() {
        var s=new Spectacol(artist,date,location,avseats,soseats);
        s.setId(getId());
        return s;
    }
}

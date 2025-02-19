package ubb.scs.map.vacanta.Domain;

public class Hotel extends Entity <Double> {
    Double location;
    String name;
    Integer rooms;
    Double price;
    HotelType hotelType;

    public Hotel(Double location, String name, Integer rooms, Double price, HotelType hotelType) {
        this.location = location;
        this.name = name;
        this.rooms = rooms;
        this.price = price;
        this.hotelType = hotelType;
    }

    public Double getLocation() {
        return location;
    }

    public void setLocation(Double location) {
        this.location = location;
    }

    public String getName() {
        return name;
    }

    public void setName(String name) {
        this.name = name;
    }

    public Integer getRooms() {
        return rooms;
    }

    public void setRooms(Integer rooms) {
        this.rooms = rooms;
    }

    public Double getPrice() {
        return price;
    }

    public void setPrice(Double price) {
        this.price = price;
    }

    public HotelType getHotelType() {
        return hotelType;
    }

    public void setHotelType(HotelType hotelType) {
        this.hotelType = hotelType;
    }
}

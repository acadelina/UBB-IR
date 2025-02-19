package ubb.scs.map.vacanta.Domain;

public class Location extends Entity<Double> {
    String locatione;

    public Location(String location) {
        this.locatione = location;
    }

    public String getLocation() {
        return locatione;
    }

    public void setLocation(String location) {
        this.locatione = location;
    }
}

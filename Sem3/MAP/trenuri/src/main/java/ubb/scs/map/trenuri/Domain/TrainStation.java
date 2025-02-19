package ubb.scs.map.trenuri.Domain;

public class TrainStation extends Entity <String> {
    String departureCityId;
    String destinationCityId;

    public TrainStation(String departure, String destination) {
        this.departureCityId = departure;
        this.destinationCityId = destination;
    }

    public String getDeparture() {
        return departureCityId;
    }

    public void setDeparture(String departure) {
        this.departureCityId = departure;
    }

    public String getDestination() {
        return destinationCityId;
    }

    public void setDestination(String destination) {
        this.destinationCityId = destination;
    }
}

package ubb.scs.map.zboruri2024.Domain;

import java.time.LocalDateTime;

public class Flight extends Entity<Long>{
    String from;
    String to;
    LocalDateTime departure;
    LocalDateTime arrival;
    Integer seats;

    public Flight(String from, String to, LocalDateTime departure, LocalDateTime arrival, Integer seats) {
        this.from = from;
        this.to = to;
        this.departure = departure;
        this.arrival = arrival;
        this.seats = seats;
    }

    public Integer getSeats() {
        return seats;
    }

    public void setSeats(Integer seats) {
        this.seats = seats;
    }

    public LocalDateTime getArrival() {
        return arrival;
    }

    public void setArrival(LocalDateTime arrival) {
        this.arrival = arrival;
    }

    public LocalDateTime getDeparture() {
        return departure;
    }

    public void setDeparture(LocalDateTime departure) {
        this.departure = departure;
    }

    public String getTo() {
        return to;
    }

    public void setTo(String to) {
        this.to = to;
    }

    public String getFrom() {
        return from;
    }

    public void setFrom(String from) {
        this.from = from;
    }
}

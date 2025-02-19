package ubb.scs.map.vacanta.Domain;

import java.util.Date;

public class Reservation extends Entity <Double> {
    Long clientid;
    Double hotelid;
    Date startdate;
    Integer nights;

    public Reservation(Long clientid, Double hotelid, Date startdate, Integer nights) {
        this.clientid = clientid;
        this.hotelid = hotelid;
        this.startdate = startdate;
        this.nights = nights;
    }

    public Long getClientid() {
        return clientid;
    }

    public void setClientid(Long clientid) {
        this.clientid = clientid;
    }

    public Double getHotelid() {
        return hotelid;
    }

    public void setHotelid(Double hotelid) {
        this.hotelid = hotelid;
    }

    public Date getStartdate() {
        return startdate;
    }

    public void setStartdate(Date startdate) {
        this.startdate = startdate;
    }

    public Integer getNights() {
        return nights;
    }

    public void setNights(Integer nights) {
        this.nights = nights;
    }
}

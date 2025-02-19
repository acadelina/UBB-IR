package ubb.scs.map.vacanta.Domain;

import java.util.Date;

public class SpecialOffer extends Entity <Double>{
    Double hotelid;
    Date startDate;
    Date endDate;
    Integer percents;

    public Double getHotelid() {
        return hotelid;
    }

    public void setHotelid(Double hotelid) {
        this.hotelid = hotelid;
    }

    public Date getStartDate() {
        return startDate;
    }

    public void setStartDate(Date startDate) {
        this.startDate = startDate;
    }

    public Date getEndDate() {
        return endDate;
    }

    public void setEndDate(Date endDate) {
        this.endDate = endDate;
    }

    public Integer getPercents() {
        return percents;
    }

    public void setPercents(Integer percents) {
        this.percents = percents;
    }

    public SpecialOffer(Double hotelid, Date startDate, Date endDate, Integer percents) {
        this.hotelid = hotelid;
        this.startDate = startDate;
        this.endDate = endDate;
        this.percents = percents;
    }
}

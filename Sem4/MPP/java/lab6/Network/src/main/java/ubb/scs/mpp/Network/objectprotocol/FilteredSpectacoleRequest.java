package ubb.scs.mpp.Network.objectprotocol;

import java.time.LocalDateTime;
import java.util.Date;

public class FilteredSpectacoleRequest implements Request {
    Date day;

    public FilteredSpectacoleRequest(final Date day) {
        this.day = day;
    }
    public Date getDay() {
        return day;
    }
}

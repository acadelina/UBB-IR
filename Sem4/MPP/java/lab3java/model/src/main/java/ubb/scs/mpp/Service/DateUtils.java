package ubb.scs.mpp.Service;

import java.time.LocalDate;
import java.time.LocalDateTime;
import java.time.ZoneId;
import java.util.Date;

public class DateUtils {
    public static Date getStartOfDay(Date d) {
        LocalDate localDate = d.toInstant().atZone(ZoneId.systemDefault()).toLocalDate();
        LocalDateTime startOfDay = localDate.atStartOfDay();
        return Date.from(startOfDay.atZone(ZoneId.systemDefault()).toInstant());
    }

    public static Date getEndOfDay(Date d) {
        LocalDate localDate = d.toInstant().atZone(ZoneId.systemDefault()).toLocalDate();
        LocalDateTime endOfDay = localDate.atTime(23, 59, 59, 999_999_999);
        return Date.from(endOfDay.atZone(ZoneId.systemDefault()).toInstant());
    }
}

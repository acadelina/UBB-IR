package ubb.scs.map.vacanta.Repository;

import ubb.scs.map.vacanta.Domain.SpecialOffer;

import java.sql.ResultSet;
import java.sql.SQLException;
import java.util.Date;

public class RepoSpecialOffer extends AbstractBDRepo<Double, SpecialOffer> {
    public RepoSpecialOffer(String url, String username, String password) {
        super(url, username, password);
    }

    @Override
    protected SpecialOffer extractEntity(ResultSet resultSet) throws SQLException {
        Double id = resultSet.getDouble("id");
        Double hotelid = resultSet.getDouble("hotelid");
        Date startdate=resultSet.getDate("startdate");
        Date enddate=resultSet.getDate("enddate");
        Integer percents=resultSet.getInt("percents");
        SpecialOffer specialOffer=new SpecialOffer(hotelid, startdate, enddate, percents);
        specialOffer.setId(id);
        return specialOffer;
    }

    @Override
    protected String getTableName() {
        return "specialoffers";
    }
}

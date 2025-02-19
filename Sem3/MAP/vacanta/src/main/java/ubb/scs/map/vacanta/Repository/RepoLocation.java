package ubb.scs.map.vacanta.Repository;

import ubb.scs.map.vacanta.Domain.Location;

import java.sql.ResultSet;
import java.sql.SQLException;

public class RepoLocation extends AbstractBDRepo<Double, Location> {
    public RepoLocation(String url, String username, String password) {
        super(url, username, password);
    }

    @Override
    protected Location extractEntity(ResultSet resultSet) throws SQLException {
        Double id=resultSet.getDouble("id");
        String location=resultSet.getString("location");
        Location loc=new Location(location);
        loc.setId(id);
        return loc;
    }

    @Override
    protected String getTableName() {
        return "locations";
    }
}

package ubb.scs.map.trenuri.Repository;

import ubb.scs.map.trenuri.Domain.TrainStation;

import java.sql.ResultSet;
import java.sql.SQLException;

public class RepoStation extends AbstractBDRepo<String, TrainStation> {
    public RepoStation(String url, String username, String password) {
        super(url, username, password);
    }

    @Override
    protected TrainStation extractEntity(ResultSet resultSet) throws SQLException {
        String id = resultSet.getString("id");
        String departure = resultSet.getString("departure");
        String destination = resultSet.getString("destination");
        TrainStation trainStation=new TrainStation(departure, destination);
        trainStation.setId(id);
        return trainStation;
    }

    @Override
    protected String getTableName() {
        return "stations";
    }
}

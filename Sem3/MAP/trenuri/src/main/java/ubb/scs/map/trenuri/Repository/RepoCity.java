package ubb.scs.map.trenuri.Repository;

import ubb.scs.map.trenuri.Domain.City;

import java.sql.ResultSet;
import java.sql.SQLException;

public class RepoCity extends AbstractBDRepo<String, City>{
    public RepoCity(String url, String username, String password) {
        super(url, username, password);
    }

    @Override
    protected City extractEntity(ResultSet resultSet) throws SQLException {
        String id = resultSet.getString("id");
        String name = resultSet.getString("name");
        City city=new City(name);
        city.setId(id);
        return city;
    }

    @Override
    protected String getTableName() {
        return "cities";
    }
}

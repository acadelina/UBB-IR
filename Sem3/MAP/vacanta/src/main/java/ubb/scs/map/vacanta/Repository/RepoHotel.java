package ubb.scs.map.vacanta.Repository;

import ubb.scs.map.vacanta.Domain.Hotel;
import ubb.scs.map.vacanta.Domain.HotelType;

import java.sql.ResultSet;
import java.sql.SQLException;

public class RepoHotel extends AbstractBDRepo<Double, Hotel> {
    public RepoHotel(String url, String username, String password) {
        super(url, username, password);
    }

    @Override
    protected Hotel extractEntity(ResultSet resultSet) throws SQLException {
        Double id = resultSet.getDouble("id");
        String name = resultSet.getString("name");
        Double location = resultSet.getDouble("location");
        Integer rooms = resultSet.getInt("rooms");
        Double price = resultSet.getDouble("price");
        HotelType type = HotelType.valueOf(resultSet.getString("type"));
        Hotel hotel=new Hotel(location, name, rooms, price, type);
        hotel.setId(id);
        return hotel;
    }

    @Override
    protected String getTableName() {
        return "hoteluri";
    }
}

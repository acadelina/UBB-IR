package ubb.scs.map.zboruri2024.Repository;

import ubb.scs.map.zboruri2024.Domain.Flight;

import java.sql.ResultSet;
import java.sql.SQLException;
import java.time.LocalDate;
import java.time.LocalDateTime;

public class RepoFlight extends AbstractBDRepo<Long, Flight> {
    public RepoFlight(String url, String username, String password) {
        super(url, username, password);
    }

    @Override
    protected Flight extractEntity(ResultSet resultSet) throws SQLException {
        Long id = resultSet.getLong("id");
        String from = resultSet.getString("from");
        String to = resultSet.getString("to");
        LocalDateTime departuure= resultSet.getTimestamp("departure").toLocalDateTime();
        LocalDateTime arrival= resultSet.getTimestamp("arrival").toLocalDateTime();
        Integer seats = resultSet.getInt("seats");
        Flight flight=new Flight(from,to,departuure,arrival,seats);
        flight.setId(id);
        return flight;
    }

    @Override
    protected String getTableName() {
        return "flights";
    }
}

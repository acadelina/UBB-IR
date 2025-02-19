package ubb.scs.map.zboruri2024.Repository;

import ubb.scs.map.zboruri2024.Domain.Ticket;

import java.sql.*;
import java.time.LocalDateTime;

public class RepoTicket extends AbstractBDRepo<Long,Ticket>{
    public RepoTicket(String url, String username, String password) {
        super(url, username, password);
    }

    @Override
    protected Ticket extractEntity(ResultSet resultSet) throws SQLException {
        Long id = resultSet.getLong("id");
        String username = resultSet.getString("username");
        Long flightid = resultSet.getLong("flightid");
        LocalDateTime purchasetime = resultSet.getTimestamp("purchasetime").toLocalDateTime();

        Ticket ticket=new Ticket(username,flightid,purchasetime);
        ticket.setId(id);
        return ticket;
    }

    @Override
    protected String getTableName() {
        return "tickets";
    }

    public void addTicket(Ticket ticket) {
        String query = "INSERT INTO " + getTableName() + " (username, flightid, purchasetime) VALUES (?, ?, ?)";
        try (Connection connection = DriverManager.getConnection(url, username, password);
             PreparedStatement statement = connection.prepareStatement(query, Statement.RETURN_GENERATED_KEYS)) {

            statement.setString(1, ticket.getUsername());
            statement.setLong(2, ticket.getIdflight());
            statement.setTimestamp(3, Timestamp.valueOf(ticket.getPurchaseTime()));

            int rowsAffected = statement.executeUpdate();

            if (rowsAffected > 0) {

                try (ResultSet generatedKeys = statement.getGeneratedKeys()) {
                    if (generatedKeys.next()) {
                        ticket.setId(generatedKeys.getLong(1));
                    }
                }
            }
        } catch (SQLException e) {
            e.printStackTrace();
        }
    }
}

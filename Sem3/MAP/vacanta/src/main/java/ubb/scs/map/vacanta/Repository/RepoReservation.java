package ubb.scs.map.vacanta.Repository;

import ubb.scs.map.vacanta.Domain.Reservation;

import java.sql.DriverManager;
import java.sql.ResultSet;
import java.sql.SQLException;
import java.util.Date;

public class RepoReservation extends AbstractBDRepo<Double, Reservation> {

    public RepoReservation(String url, String username, String password) {
        super(url, username, password);
    }

    @Override
    protected Reservation extractEntity(ResultSet resultSet) throws SQLException {
        Double id = resultSet.getDouble("id");
        Long idclient= resultSet.getLong("idclient");
        Double idhotel= resultSet.getDouble("idhotel");
        Date startDate= resultSet.getDate("startdate");
        Integer nights= resultSet.getInt("nights");

        Reservation reservation=new Reservation(idclient,idhotel,startDate,nights);
        reservation.setId(id);
        return reservation;
    }

    @Override
    protected String getTableName() {
        return "resrevations";
    }
    public void addReservation(Reservation reservation) {
        String sql = "INSERT INTO resrevations (idclient, idhotel, startdate, nights) VALUES (?, ?, ?, ?)";

        try (var connection = DriverManager.getConnection(url, username, password);
             var statement = connection.prepareStatement(sql)) {

           // statement.setDouble(1, reservation.getId()); // ID-ul rezervării
            statement.setLong(1, reservation.getClientid()); // ID-ul clientului
            statement.setDouble(2, reservation.getHotelid()); // ID-ul hotelului
            statement.setDate(3, new java.sql.Date(reservation.getStartdate().getTime())); // Data de început
            statement.setInt(4, reservation.getNights()); // Numărul de nopți

            statement.executeUpdate();
        } catch (SQLException e) {
            throw new RuntimeException("Eroare la adăugarea rezervării: " + e.getMessage(), e);
        }
    }

}

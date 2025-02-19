package ubb.scs.map.faptebune.Repository;

import ubb.scs.map.faptebune.Domain.Nevoie;

import java.sql.ResultSet;
import java.sql.SQLException;
import java.time.LocalDateTime;

import static java.sql.DriverManager.getConnection;

public class NevoieRepo extends AbstractBDRepo<Long, Nevoie> {

    public NevoieRepo(String url, String username, String password) {
        super(url, username, password);
    }

    @Override
    protected Nevoie extractEntity(ResultSet resultSet) throws SQLException {

        Long id = resultSet.getLong("id");
        String titlu= resultSet.getString("titlu");
        String descriere= resultSet.getString("descriere");
        LocalDateTime deadline= resultSet.getTimestamp("deadline").toLocalDateTime();
        Long omInNevoie= resultSet.getLong("omInNevoie");
        Long omSalvator= resultSet.getLong("omSalvator");
        String status= resultSet.getString("status");

        Nevoie nevoie=new Nevoie(titlu,descriere,deadline,omInNevoie,omSalvator,status);
        nevoie.setId(id);
        return nevoie;
    }

    @Override
    protected String getTableName() {
        return "nevoi";
    }

    public void addNeoie(Nevoie nevoie) {
        String sql = "INSERT INTO nevoi (titlu, descriere, deadline, omInNevoie, omSalvator, status) VALUES (?, ?, ?, ?, ?, ?)";
        try (var connection = getConnection(url, username, password);
             var preparedStatement = connection.prepareStatement(sql)) {

            preparedStatement.setString(1, nevoie.getTitlu());
            preparedStatement.setString(2, nevoie.getDescriere());
            preparedStatement.setTimestamp(3, java.sql.Timestamp.valueOf(nevoie.getDeadline()));
            preparedStatement.setLong(4, nevoie.getOmInNevoie());
            if (nevoie.getOmSalvator() != null) {
                preparedStatement.setLong(5, nevoie.getOmSalvator());
            } else {
                preparedStatement.setNull(5, java.sql.Types.BIGINT);
            }
            preparedStatement.setString(6, nevoie.getStatus());

            preparedStatement.executeUpdate();
        } catch (SQLException e) {
            throw new RuntimeException("Error while adding a need: " + e.getMessage(), e);
        }
    }

    public void update(Nevoie nevoie) {
        String sql = "UPDATE nevoi SET titlu = ?, descriere = ?, deadline = ?, omInNevoie = ?, omSalvator = ?, status = ? WHERE id = ?";

        try (var connection = getConnection(url, username, password);
             var preparedStatement = connection.prepareStatement(sql)) {


            preparedStatement.setString(1, nevoie.getTitlu());
            preparedStatement.setString(2, nevoie.getDescriere());
            preparedStatement.setTimestamp(3, java.sql.Timestamp.valueOf(nevoie.getDeadline()));
            preparedStatement.setLong(4, nevoie.getOmInNevoie());

            if (nevoie.getOmSalvator() != null) {
                preparedStatement.setLong(5, nevoie.getOmSalvator());
            } else {
                preparedStatement.setNull(5, java.sql.Types.BIGINT);
            }

            preparedStatement.setString(6, nevoie.getStatus());
            preparedStatement.setLong(7, nevoie.getId());


            preparedStatement.executeUpdate();
        } catch (SQLException e) {
            throw new RuntimeException("Error while updating a need: " + e.getMessage(), e);
        }
    }

}

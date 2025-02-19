package ubb.scs.map.clinica2.Repository;

import ubb.scs.map.clinica2.Domain.Consultatie;
import ubb.scs.map.clinica2.Domain.Entity;

import java.sql.ResultSet;
import java.sql.SQLException;
import java.time.LocalDateTime;

import static java.sql.DriverManager.getConnection;

public class RepoConsultatie extends AbstractBDRepo<Long, Consultatie> {
    public RepoConsultatie(String url, String username, String password) {
        super(url, username, password);
    }

    @Override
    protected Consultatie extractEntity(ResultSet resultSet) throws SQLException {
        Long id = resultSet.getLong("id");
        Long idmedic= resultSet.getLong("medic");
        Long cnppacient= resultSet.getLong("cnppacient");
        String numepacient= resultSet.getString("numepacient");
        LocalDateTime data= resultSet.getTimestamp("data").toLocalDateTime();
        Consultatie consultatie=new Consultatie(idmedic,cnppacient,numepacient,data);
        consultatie.setId(id);
        return consultatie;
    }

    public void add(Consultatie consultatie) {
        String sql = "INSERT INTO consultatii (medic, cnppacient, numepacient, data) VALUES (?, ?, ?, ?)";
        try (var connection = getConnection(url, username, password);
             var preparedStatement = connection.prepareStatement(sql, java.sql.Statement.RETURN_GENERATED_KEYS)) {

            preparedStatement.setLong(1, consultatie.getIdmedic());
            preparedStatement.setLong(2, consultatie.getCnppacient());
            preparedStatement.setString(3, consultatie.getNumepacient());
            preparedStatement.setTimestamp(4, java.sql.Timestamp.valueOf(consultatie.getData()));

            int rowsAffected = preparedStatement.executeUpdate();

            if (rowsAffected == 0) {
                throw new SQLException("Adding the consultation failed, no rows affected.");
            }

            // Retrieve the generated ID
            try (ResultSet generatedKeys = preparedStatement.getGeneratedKeys()) {
                if (generatedKeys.next()) {
                    consultatie.setId(generatedKeys.getLong(1));
                } else {
                    throw new SQLException("Adding the consultation failed, no ID obtained.");
                }
            }

        } catch (SQLException e) {
            throw new RuntimeException("Error while adding the consultation: " + e.getMessage(), e);
        }
    }


    @Override
    protected String getTableName() {
        return "consultatii";
    }
}

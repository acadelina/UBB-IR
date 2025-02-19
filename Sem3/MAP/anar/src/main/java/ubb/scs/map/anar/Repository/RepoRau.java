package ubb.scs.map.anar.Repository;

import ubb.scs.map.anar.Domain.Rau;

import java.sql.ResultSet;
import java.sql.SQLException;

import static java.sql.DriverManager.getConnection;

public class RepoRau extends AbstractBDRepo<Integer, Rau>{
    public RepoRau(String url, String username, String password) {
        super(url, username, password);
    }

    @Override
    protected Rau extractEntity(ResultSet resultSet) throws SQLException {
        Integer id = resultSet.getInt("id");
        String name = resultSet.getString("nume");
        Float cota = resultSet.getFloat("cota");
        Rau rau=new Rau(name, cota);
        rau.setId(id);
        return rau;
    }

    @Override
    protected String getTableName() {
        return "rauri";
    }

    public void update(Rau rau) {
        String sql = "UPDATE " + getTableName() + " SET nume = ?, cota = ? WHERE id = ?";
        try (var connection = getConnection(url, username, password);
             var preparedStatement = connection.prepareStatement(sql)) {
            preparedStatement.setString(1, rau.getNume()); // Setează numele râului
            preparedStatement.setFloat(2, rau.getCotamedie()); // Setează cota râului
            preparedStatement.setInt(3, rau.getId());     // Setează id-ul râului

            int rowsUpdated = preparedStatement.executeUpdate(); // Execută comanda SQL
            if (rowsUpdated == 0) {
                throw new RuntimeException("No row found with id: " + rau.getId());
            }
        } catch (SQLException e) {
            throw new RuntimeException("Error while updating river with id: " + rau.getId(), e);
        }
    }

}

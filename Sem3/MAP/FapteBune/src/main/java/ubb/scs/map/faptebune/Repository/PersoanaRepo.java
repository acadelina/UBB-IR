package ubb.scs.map.faptebune.Repository;

import ubb.scs.map.faptebune.Domain.Oras;
import ubb.scs.map.faptebune.Domain.Persoana;

import java.sql.ResultSet;
import java.sql.SQLException;

import static java.sql.DriverManager.getConnection;

public class PersoanaRepo extends AbstractBDRepo<Long, Persoana> {
    public PersoanaRepo(String url, String username, String password) {
        super(url, username, password);
    }

    @Override
    protected Persoana extractEntity(ResultSet resultSet) throws SQLException {
        Long id = resultSet.getLong("id");
        String nume=resultSet.getString("nume");
        String prenume=resultSet.getString("prenume");
        String username=resultSet.getString("username");
        String parola=resultSet.getString("parola");
        Oras oras=Oras.valueOf(resultSet.getString("oras"));
        String strada=resultSet.getString("strada");
        String numarStrada=resultSet.getString("numarStrada");
        String telefon=resultSet.getString("telefon");
        Persoana persoana=new Persoana(nume,prenume,username,parola,oras,strada,numarStrada,telefon);
        persoana.setId(id);
        return persoana;
    }

    @Override
    protected String getTableName() {
        return "persoane";
    }

    public void addPersoana(Persoana persoana)
    {
        String sql = "INSERT INTO persoane (nume, prenume, username, parola, oras, strada, numarStrada, telefon) VALUES (?, ?, ?, ?, ?, ?, ?, ?)";
        try (var connection = getConnection(url, username, password);
             var preparedStatement = connection.prepareStatement(sql)) {

            preparedStatement.setString(1, persoana.getNume());
            preparedStatement.setString(2, persoana.getPrenume());
            preparedStatement.setString(3, persoana.getUsername());
            preparedStatement.setString(4, persoana.getParola());
            preparedStatement.setString(5, persoana.getOras().toString());
            preparedStatement.setString(6, persoana.getStrada());
            preparedStatement.setString(7, persoana.getNumarStrada());
            preparedStatement.setString(8, persoana.getTelefon());

            preparedStatement.executeUpdate();
        } catch (SQLException e) {
            throw new RuntimeException("Error while adding a person: " + e.getMessage(), e);
        }
    }
}

package ubb.scs.map.clinica.Repository;

import ubb.scs.map.clinica.Domain.Pat;
import ubb.scs.map.clinica.Domain.TipPat;

import java.sql.Connection;
import java.sql.PreparedStatement;
import java.sql.ResultSet;
import java.sql.SQLException;

import static java.sql.DriverManager.getConnection;

public class RepoPat extends AbstractBDRepo<Integer, Pat> {

    public RepoPat(String url, String username, String password) {
        super(url, username, password);
    }

    @Override
    protected Pat extractEntity(ResultSet resultSet) throws SQLException {
        Integer id = resultSet.getInt("id");
        TipPat tip=TipPat.valueOf(resultSet.getString("tip"));
        String ventilatie=resultSet.getString("ventilatie");
        Integer pacient=resultSet.getInt("pacient");
        Pat pat=new Pat(tip,ventilatie,pacient);
        pat.setId(id);
        return pat;
    }

    @Override
    protected String getTableName() {
        return "paturi";
    }
    public void update(Pat pat) throws SQLException {
        String query = "UPDATE paturi SET tip = ?, ventilatie = ?, pacient = ? WHERE id = ?";

        try (Connection connection = getConnection(url, username, password);
             PreparedStatement stmt = connection.prepareStatement(query)) {

            // Setează valorile parametrilor în interogare
            stmt.setObject(1, pat.getTipPat().toString());  // Setează tipul patului
            stmt.setString(2, pat.getVentilatie());  // Setează ventilarea
            stmt.setInt(3, pat.getPacient());  // Setează pacientul
            stmt.setInt(4, pat.getId());  // Setează ID-ul patului

            // Execută update-ul
            stmt.executeUpdate();
        }
    }

}

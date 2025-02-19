package ubb.scs.map.clinica.Repository;

import ubb.scs.map.clinica.Domain.Pacient;

import java.sql.ResultSet;
import java.sql.SQLException;

public class RepoPacient extends AbstractBDRepo<Integer,Pacient> {
    public RepoPacient(String url, String username, String password) {
        super(url, username, password);
    }

    @Override
    protected Pacient extractEntity(ResultSet resultSet) throws SQLException {
        Integer id = resultSet.getInt("id");
        Integer varsta = resultSet.getInt("varsta");
        String prematur= resultSet.getString("prematur");
        String dianostic= resultSet.getString("diagnostic");
        Integer gravitate= resultSet.getInt("gravitate");
        Pacient pacient=new Pacient(varsta,prematur,dianostic,gravitate);
        pacient.setId(id);
        return pacient;
        }

    @Override
    protected String getTableName() {
        return "pacienti";
    }
}

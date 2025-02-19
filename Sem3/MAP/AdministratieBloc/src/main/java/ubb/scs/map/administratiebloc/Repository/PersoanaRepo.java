package ubb.scs.map.administratiebloc.Repository;

import ubb.scs.map.administratiebloc.Domain.Entity;
import ubb.scs.map.administratiebloc.Domain.Persoana;

import java.sql.Date;
import java.sql.ResultSet;
import java.sql.SQLException;

public class PersoanaRepo extends AbstractBDRepo{
    public PersoanaRepo(String url, String username, String password) {
        super(url, username, password);
    }

    @Override
    protected Entity extractEntity(ResultSet resultSet) throws SQLException {
        Long id = resultSet.getLong("id");
        String nume=resultSet.getString("nume");
        String prenume=resultSet.getString("prenume");
        Date date=resultSet.getDate("data");
        Persoana persoana=new Persoana(nume,prenume,date);
        persoana.setId(id);

        return persoana;
    }

    @Override
    protected String getTableName() {
        return "persoane";
    }
}

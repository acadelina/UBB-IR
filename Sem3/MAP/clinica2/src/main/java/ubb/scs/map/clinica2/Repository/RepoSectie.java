package ubb.scs.map.clinica2.Repository;

import ubb.scs.map.clinica2.Domain.Sectie;

import java.sql.ResultSet;
import java.sql.SQLException;

public class RepoSectie extends AbstractBDRepo<Long, Sectie>{
    public RepoSectie(String url, String username, String password) {
        super(url, username, password);
    }

    @Override
    protected Sectie extractEntity(ResultSet resultSet) throws SQLException {
        Long id = resultSet.getLong("id");
        String nume=resultSet.getString("nume");
        Long sef=resultSet.getLong("sef");
        Integer pret=resultSet.getInt("pret");
        Integer durataMax=resultSet.getInt("duratamax");
        Sectie sectie=new Sectie(nume,sef,pret,durataMax);
        sectie.setId(id);
        return sectie;
    }

    @Override
    protected String getTableName() {
        return "sectii";
    }
}

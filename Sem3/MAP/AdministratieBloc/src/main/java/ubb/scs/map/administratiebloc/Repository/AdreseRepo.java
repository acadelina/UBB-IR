package ubb.scs.map.administratiebloc.Repository;

import ubb.scs.map.administratiebloc.Domain.Adresa;

import java.sql.ResultSet;
import java.sql.SQLException;

public class AdreseRepo extends AbstractBDRepo<Long, Adresa>{
    public AdreseRepo(String url, String username, String password) {
        super(url, username, password);
    }

    @Override
    protected Adresa extractEntity(ResultSet resultSet) throws SQLException {
        Long id = resultSet.getLong("id");
        String strada= resultSet.getString("adresa");
        String numar= resultSet.getString("numar");
        Adresa adresa=new Adresa(strada, numar);
        adresa.setId(id);
        return adresa;
    }

    @Override
    protected String getTableName() {
        return "adrese";
    }
}

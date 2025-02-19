package ubb.scs.map.anar.Repository;

import ubb.scs.map.anar.Domain.Localitate;

import java.sql.ResultSet;
import java.sql.SQLException;

public class RepoLocalitate extends AbstractBDRepo<Integer, Localitate> {

    public RepoLocalitate(String url, String username, String password) {
        super(url, username, password);
    }

    @Override
    protected Localitate extractEntity(ResultSet resultSet) throws SQLException {
        Integer id = resultSet.getInt("id");
        String nume=resultSet.getString("nume");
        Float cotamin=resultSet.getFloat("cotamin");
        Float ctamax=resultSet.getFloat("ctamax");
        Integer rau=resultSet.getInt("rau");
        Localitate localitate=new Localitate(nume,rau,cotamin,ctamax);
        localitate.setId(id);
        return localitate;
    }

    @Override
    protected String getTableName() {
        return "localitati";
    }
}

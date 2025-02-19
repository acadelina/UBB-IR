package ubb.scs.map.clinica2.Repository;

import ubb.scs.map.clinica2.Domain.Medic;

import java.sql.ResultSet;
import java.sql.SQLException;

public class RepoMedic extends AbstractBDRepo<Long, Medic>{
    public RepoMedic(String url, String username, String password) {
        super(url, username, password);
    }

    @Override
    protected Medic extractEntity(ResultSet resultSet) throws SQLException {
        Long id = resultSet.getLong("id");
        Long idsectie= resultSet.getLong("idsectie");
        String nume= resultSet.getString("nume");
        Integer vechime= resultSet.getInt("vechime");
        String rezident= resultSet.getString("rezident");
        Medic medic=new Medic(idsectie,nume,vechime,rezident);
        medic.setId(id);
        return medic;
    }

    @Override
    protected String getTableName() {
        return "medici";
    }
}

package ubb.scs.map.administratiebloc.Repository;

import ubb.scs.map.administratiebloc.Domain.Apartament;
import ubb.scs.map.administratiebloc.Domain.TipApartament;

import java.sql.ResultSet;
import java.sql.SQLException;

public class ApartamenteRepo extends AbstractBDRepo<Long, Apartament>{


    public ApartamenteRepo(String url, String username, String password) {
        super(url, username, password);
    }



    @Override
    protected Apartament extractEntity(ResultSet resultSet) throws SQLException {
        Long id=resultSet.getLong("id");
        Long idbloc=resultSet.getLong("idbloc");
        Integer nrapartamnt=resultSet.getInt("nrapartament");
        Integer nrcamere=resultSet.getInt("nrcamere");
        String tip=resultSet.getString("tip");
        Integer suprafata=resultSet.getInt("suprafata");
        TipApartament tipApartament=TipApartament.valueOf(tip);

        Apartament apartament=new Apartament(idbloc,nrapartamnt,nrcamere,tipApartament,suprafata);

        apartament.setId(id);
        return apartament;
    }

    @Override
    protected String getTableName() {
        return "apartamente";
    }
}

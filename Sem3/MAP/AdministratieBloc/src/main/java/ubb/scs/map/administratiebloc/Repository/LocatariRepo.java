package ubb.scs.map.administratiebloc.Repository;

import ubb.scs.map.administratiebloc.Domain.Apartament;
import ubb.scs.map.administratiebloc.Domain.Locatar;
import ubb.scs.map.administratiebloc.Domain.Persoana;
import ubb.scs.map.administratiebloc.Domain.TipApartament;

import java.sql.*;
import java.util.Optional;

public class LocatariRepo extends AbstractBDRepo<Long, Locatar> {
    PersoanaRepo repoPersoana;
    public LocatariRepo(String url, String username, String password,PersoanaRepo persoanaRepo) {
        super(url, username, password);
        this.repoPersoana = persoanaRepo;
    }


    @Override
    protected Locatar extractEntity(ResultSet resultSet) throws SQLException {
        Long id = resultSet.getLong("id");
        Long idapartament = resultSet.getLong("apartament");
        Optional<Persoana> persoana=repoPersoana.findOne(id);
        Persoana persoanaAux=persoana.isPresent()?persoana.get():null;

        Locatar locatar=new Locatar(persoanaAux.getNume(),persoanaAux.getPrenume(),persoanaAux.getDataNasterii(),idapartament);
        locatar.setId(id);
        return locatar;
    }

    @Override
    protected String getTableName() {
        return "locatari";
    }
}

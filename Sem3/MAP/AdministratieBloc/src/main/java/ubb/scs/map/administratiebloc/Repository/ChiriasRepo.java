package ubb.scs.map.administratiebloc.Repository;

import ubb.scs.map.administratiebloc.Domain.Chirias;
import ubb.scs.map.administratiebloc.Domain.Locatar;
import ubb.scs.map.administratiebloc.Domain.Persoana;

import java.sql.ResultSet;
import java.sql.SQLException;
import java.util.Optional;

public class ChiriasRepo extends AbstractBDRepo<Long, Chirias> {
    PersoanaRepo persoanaRepo;
    public ChiriasRepo(String url, String username, String password,PersoanaRepo persoanaRepo) {
        super(url, username, password);
        this.persoanaRepo = persoanaRepo;
    }

    @Override
    protected Chirias extractEntity(ResultSet resultSet) throws SQLException {
        Long id = resultSet.getLong("id");
        Long idapartament= resultSet.getLong("apartament");
        Long chirie = resultSet.getLong("chirie");
        Optional<Persoana> persoana=persoanaRepo.findOne(id);
        Persoana persoanaAux=persoana.isPresent()?persoana.get():null;

        Chirias locatar=new Chirias(persoanaAux.getNume(),persoanaAux.getPrenume(),persoanaAux.getDataNasterii(),idapartament,chirie);
        locatar.setId(id);
        return locatar;
    }

    @Override
    protected String getTableName() {
        return "chiriasi";
    }
}

package ubb.scs.mpp.Repository;

import ubb.scs.mpp.model.Angajat;



import java.sql.SQLException;

public interface AngajatRepository extends Repository<Long, Angajat> {
    Angajat findByUsernamePassword(String username, String password) throws SQLException, RepoException;
    Angajat findByUsername(String username) throws SQLException, RepoException;
}

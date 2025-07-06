package ubb.scs.mpp.Repository;

import org.apache.logging.log4j.LogManager;
import org.apache.logging.log4j.Logger;
import org.springframework.stereotype.Component;
import ubb.scs.mpp.model.Angajat;


import java.sql.ResultSet;
import java.sql.SQLException;
import java.util.Properties;
@Component
public class DbAngajatRepo extends DbRepoUtils<Long, Angajat> implements AngajatRepository{
    private static final Logger logger= LogManager.getLogger(DbAngajatRepo.class);

    public DbAngajatRepo(Properties prop) {
        super(prop);
        logger.info("Initializing DbAngajatRepo with properties: {}", prop);
    }

    @Override
    public Angajat decodeResult(ResultSet resultSet) throws SQLException {
        Long id = resultSet.getLong("id");
        String username = resultSet.getString("username");
        String password = resultSet.getString("password");
        String email = resultSet.getString("mail");
        Angajat angajat=new Angajat(username,password,email);
        angajat.setId(id);
        return angajat;
    }

    @Override
    public Angajat findByUsernamePassword(String username, String password) throws RepoException {
        return selectFirst("select * from angajati where username = ? and password = ?", username,password);

    }

    public Angajat findByUsername(String username) throws RepoException {
        return selectFirst("select * from angajati where username = ?", username);
    }

    @Override
    public Angajat findOne(Long aLong) throws RepoException {
        return selectFirst("select * from angajati where id=?",aLong);
    }

    @Override
    public Iterable<Angajat> findAll() throws RepoException {
        return select("select * from angajati");
    }

    @Override
    public Angajat save(Angajat entity) throws RepoException {
        logger.trace("Saving angajat: {}", entity);
        executeNonQuery("insert into angajati (username,password,mail) values (?,?,?)",entity.getUsername(),entity.getPassword(),entity.getMail());
        logger.info("Saved angajat: {}", entity);
        logger.traceExit();
        return entity;
    }

    @Override
    public Angajat delete(Long aLong) throws RepoException {
        logger.trace("Deleting angajat: {}", findOne(aLong));
        executeNonQuery("delete from angajati where id=?",aLong);
        logger.info("Deleted angajat: {}", findOne(aLong));
        logger.traceExit();
        return findOne(aLong);
    }

    @Override
    public Angajat update(Angajat entity) throws RepoException {
        logger.trace("Updating angajat: {}", entity);
        executeNonQuery("update angajati set mail=? where id=? ",entity.getMail(),entity.getId());
        logger.info("Updated angajat: {}", entity);
        logger.traceExit();
        return entity;
    }
}

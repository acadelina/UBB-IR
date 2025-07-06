package ubb.scs.mpp.Repository;


import org.apache.logging.log4j.LogManager;
import org.apache.logging.log4j.Logger;
import ubb.scs.mpp.model.Spectacol;


import java.sql.ResultSet;
import java.sql.SQLException;
import java.time.LocalDateTime;
import java.time.ZoneId;
import java.util.Date;
import java.util.Properties;

public class DbSpectacolRepository extends DbRepoUtils<Long, Spectacol> implements SpectacolRepository {
    private static final Logger logger= LogManager.getLogger(DbSpectacolRepository.class);

    public DbSpectacolRepository(Properties props) {
        super(props);
        logger.info("Initializing DbSpectacolRepository with properties {}",props);
    }

    @Override
    public Spectacol decodeResult(ResultSet resultSet) throws SQLException {
        String artist=resultSet.getString("artist");
        LocalDateTime data=resultSet.getTimestamp("data").toLocalDateTime();
        String location=resultSet.getString("location");
        int avseats=resultSet.getInt("avseats");
        int soseats=resultSet.getInt("soseats");
        Long id=resultSet.getLong("id");

        Spectacol spectacol=new Spectacol(artist,data,location,avseats,soseats);
        spectacol.setId(id);
        return spectacol;
    }

    @Override
    public Iterable<Spectacol> findOnDate(Date sdate,Date edate) throws RepoException {
        long startTimestamp =  sdate.getTime();
        long endTimestamp = edate.getTime();

        return select("select * from spectacole where data between ? and ?", startTimestamp,endTimestamp);
    }

    @Override
    public Spectacol findOne(Long aLong) throws RepoException {
        return selectFirst("select * from spectacole where id=?", aLong);
    }

    @Override
    public Iterable<Spectacol> findAll() throws RepoException {
        return select("select * from spectacole");
    }

    @Override
    public Spectacol save(Spectacol entity) throws RepoException {
        logger.trace("Saving spectacol {}", entity);
        executeNonQuery("insert into spectacole (artist,data,location,avseats,soseats) values (?,?,?,?,?)", entity.getArtist(),entity.getDate(),entity.getLocation(),entity.getAvailable_seats(),entity.getSold_seats());
        logger.info("Saved spectacol {}", entity);
        logger.traceExit();
        return entity;
    }

    @Override
    public Spectacol delete(Long aLong) throws RepoException {
        logger.trace("Deleting spectacol {}", findOne(aLong));
        executeNonQuery("delete from spectacole where id=?", aLong);
        logger.info("Deleted spectacol {}", findOne(aLong));
        logger.traceExit();
        return findOne(aLong);
    }

    @Override
    public Spectacol update(Spectacol entity) throws RepoException {
        logger.trace("Updating spectacol {}", entity);

        executeNonQuery("update spectacole set artist=?, data=?, location=?, avseats=?, soseats=? where id=?",entity.getArtist(),entity.getDate().atZone(ZoneId.of("UTC")).toInstant().toEpochMilli(),entity.getLocation(),entity.getAvailable_seats(),entity.getSold_seats(),entity.getId());
        logger.info("Updated spectacol {}", entity);
        logger.traceExit();
        return entity;
    }
}

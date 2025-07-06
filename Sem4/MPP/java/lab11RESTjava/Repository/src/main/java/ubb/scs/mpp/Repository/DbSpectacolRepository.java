package ubb.scs.mpp.Repository;


import org.apache.logging.log4j.LogManager;
import org.apache.logging.log4j.Logger;
import org.springframework.stereotype.Component;
import ubb.scs.mpp.model.Spectacol;


import java.sql.*;
import java.time.LocalDateTime;
import java.time.ZoneId;
import java.time.format.DateTimeFormatter;
import java.time.temporal.ChronoUnit;
import java.util.Date;
import java.util.Properties;

@Component
public class DbSpectacolRepository extends DbRepoUtils<Long, Spectacol> implements SpectacolRepository {
    private static final Logger logger= LogManager.getLogger(DbSpectacolRepository.class);
    private JdbcUtils dbUtils;

    public DbSpectacolRepository(Properties props) {
        super(props);
        dbUtils = new JdbcUtils(props);
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

        String sql = "INSERT INTO spectacole (artist, data, location, avseats, soseats) VALUES (?, ?, ?, ?, ?)";
        String idQuery = "SELECT last_insert_rowid()";

        try (Connection connection = dbUtils.getConnection();
             PreparedStatement ps = connection.prepareStatement(sql, Statement.RETURN_GENERATED_KEYS)) {

            ps.setString(1, entity.getArtist());
            ps.setLong(2, entity.getData().truncatedTo(ChronoUnit.SECONDS).atZone(ZoneId.of("UTC")).toInstant().toEpochMilli());
            ps.setString(3, entity.getLocation());
            ps.setInt(4, entity.getAvailable_seats());
            ps.setInt(5, entity.getSold_seats());

            int affectedRows = ps.executeUpdate();

            if (affectedRows == 0) {
                throw new RepoException("Inserting spectacol failed, no rows affected.");
            }

            try (Statement idStmt = connection.createStatement();
                 ResultSet rs = idStmt.executeQuery(idQuery)) {
                if (rs.next()) {
                    long generatedId = rs.getLong(1);
                    entity.setId(generatedId);
                    logger.info("Saved spectacol with generated id {}", generatedId);
                } else {
                    throw new RepoException("Inserting spectacol failed, no ID obtained.");
                }
            }
        } catch (SQLException e) {
            logger.error("Error saving spectacol", e);
            throw new RepoException("Database error: " + e.getMessage());
        }

        logger.traceExit(entity);
        return entity;
    }

    @Override
    public Spectacol delete(Long aLong) throws RepoException {
        Spectacol spectacol=findOne(aLong);
        logger.trace("Deleting spectacol {}", spectacol);
        executeNonQuery("delete from spectacole where id=?", aLong);
        logger.info("Deleted spectacol {}", spectacol);
        logger.traceExit();
        return spectacol;
    }

    @Override
    public Spectacol update(Spectacol entity) throws RepoException {
        logger.trace("Updating spectacol {}", entity);

        executeNonQuery("update spectacole set artist=?, data=?, location=?, avseats=?, soseats=? where id=?",entity.getArtist(),entity.getData().truncatedTo(ChronoUnit.SECONDS).atZone(ZoneId.of("UTC")).toInstant().toEpochMilli(),entity.getLocation(),entity.getAvailable_seats(),entity.getSold_seats(),entity.getId());
        logger.info("Updated spectacol {}", entity);
        logger.traceExit();
        return entity;
    }
}

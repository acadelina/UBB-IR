package ubb.scs.mpp.Repository;

import org.apache.logging.log4j.LogManager;
import org.apache.logging.log4j.Logger;
import ubb.scs.mpp.Domain.Bilet;
import ubb.scs.mpp.Domain.Spectacol;


import java.sql.ResultSet;
import java.sql.SQLException;
import java.util.Properties;

public class DbBiletRepository extends DbRepoUtils<Long, Bilet> implements BiletRepository {
    private static final Logger logger= LogManager.getLogger(DbSpectacolRepository.class);
    SpectacolRepository spectacolRepository;

    public DbBiletRepository(Properties props, SpectacolRepository spectacolRepository) {
        super(props);
        this.spectacolRepository=spectacolRepository;
        logger.info("DbBiletRepository initialized {}",props);
    }


    @Override
    public Iterable<Bilet> findBiletBySpectacol(Spectacol spectacol) throws RepoException {
        return select("select * from bilete where spectacol=?",spectacol.getId());
    }

    @Override
    protected Bilet decodeResult(ResultSet resultSet) throws SQLException, RepoException {
        Long id = resultSet.getLong("id");
        String buyer = resultSet.getString("buyer");
        int seats = resultSet.getInt("seats");
        Long spectacolId = resultSet.getLong("spectacol");
        Spectacol spectacol=spectacolRepository.findOne(spectacolId);
        Bilet bilet=new Bilet(buyer,seats,spectacol);
        bilet.setId(id);
        return bilet;
    }

    @Override
    public Bilet findOne(Long aLong) throws RepoException {
        return selectFirst("select * from bilete where id=?",aLong);
    }

    @Override
    public Iterable<Bilet> findAll() throws RepoException {
        return select("select * from bilete");
    }

    @Override
    public Bilet save(Bilet entity) throws RepoException {
        logger.trace("save bilet {}",entity);
        executeNonQuery("insert into bilete (buyer,spectacol,seats) values (?,?,?)",entity.getBuyer(),entity.getSpectacol().getId(),entity.getSeats_number());
        logger.info("saved bilet");
        logger.traceExit();
        return entity;
    }

    @Override
    public Bilet delete(Long aLong) throws RepoException {
        logger.trace("delete bilet {}",aLong);
        executeNonQuery("delete from bilete where id=?",aLong);
        logger.info("deleted bilet");
        logger.traceExit();
        return findOne(aLong);
    }

    @Override
    public Bilet update(Bilet entity) throws RepoException {
        logger.trace("update bilet {}",entity);
        executeNonQuery("update bilete set buyer=?,spectacol=?,seats=? where id=?",entity.getBuyer(),entity.getSpectacol(),entity.getSeats_number(),entity.getId());
        logger.info("updated bilet");
        logger.traceExit();
        return entity;
    }
}

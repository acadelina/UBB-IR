package ubb.scs.mpp.Server;

import org.apache.logging.log4j.LogManager;
import org.apache.logging.log4j.Logger;
import ubb.scs.mpp.Service.ServiceException;
import ubb.scs.mpp.model.Spectacol;
import ubb.scs.mpp.Repository.RepoException;
import ubb.scs.mpp.Repository.SpectacolRepository;

import java.util.Date;



public class SpectacolService {
    private static final Logger logger= LogManager.getLogger(SpectacolService.class);
    SpectacolRepository repo;
    public SpectacolService(SpectacolRepository repo) {
        this.repo = repo;
        logger.info("SpectacolService created");
    }

    public Iterable<Spectacol> findAll() throws ServiceException {
        try {
            logger.info("Searching all the spectacols");
            return repo.findAll();
        }
        catch (RepoException e) {
            throw new ServiceException(e.getMessage());
        }
    }

    public Iterable<Spectacol> findOnDate(Date d) throws ServiceException
    {
        try {
            logger.info("Searching on the spectacols for date :{}", d);
            Date start = DateUtils.getStartOfDay(d);
            Date end = DateUtils.getEndOfDay(d);
            return repo.findOnDate(start, end);
        }
        catch (RepoException e) {
            throw new ServiceException(e.getMessage());
        }
    }

    public Spectacol findById(long id) throws ServiceException {
        try {
            return repo.findOne(id);
        } catch (RepoException e) {
            throw new ServiceException(e.getMessage());
        }
    }

    public void delete(long id) throws ServiceException {
        try{
            repo.delete(id);
        }catch (RepoException e) {
            throw new ServiceException(e.getMessage());
        }
    }



}

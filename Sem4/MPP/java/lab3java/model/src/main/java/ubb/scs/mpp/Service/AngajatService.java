package ubb.scs.mpp.Service;

import org.apache.logging.log4j.LogManager;
import org.apache.logging.log4j.Logger;
import ubb.scs.mpp.Domain.Angajat;
import ubb.scs.mpp.Repository.AngajatRepository;
import ubb.scs.mpp.Repository.DbAngajatRepo;

public class AngajatService{
    private static final Logger logger= LogManager.getLogger(AngajatService.class);
    private AngajatRepository repo;
    public AngajatService(AngajatRepository repo){
        this.repo = repo;
        logger.info("AngajatService created");
    }

    public Angajat connectAngajat(String username, String password) throws ServiceException {
        try {
            logger.info("Angajat trying to connect");
            return repo.findByUsernamePassword(username, password);
        }
        catch (Exception e) {
            throw new ServiceException(e.getMessage());
        }

    }
}

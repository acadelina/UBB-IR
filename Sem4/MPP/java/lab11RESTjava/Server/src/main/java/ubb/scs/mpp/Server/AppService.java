package ubb.scs.mpp.Server;

import org.apache.logging.log4j.LogManager;
import org.apache.logging.log4j.Logger;
import ubb.scs.mpp.Service.IAppService;
import ubb.scs.mpp.Service.ServiceException;
import ubb.scs.mpp.Service.observer.Observer;
import ubb.scs.mpp.model.Angajat;
import ubb.scs.mpp.model.Spectacol;

import java.util.Date;

public class AppService implements IAppService {
    private static final Logger logger= LogManager.getLogger(AppService.class);
    AngajatService angajatService;
    BiletService biletService;
    SpectacolService spectacolService;

    public AppService(AngajatService angajatService, BiletService biletService, SpectacolService spectacolService) {
        this.angajatService = angajatService;
        this.biletService = biletService;
        this.spectacolService = spectacolService;
        logger.info("AppService created");
    }

    public Angajat login(Angajat ang, Observer observer) throws ServiceException {
        try {
            logger.info("Login attempt");
            return angajatService.connectAngajat(ang.getUsername(), ang.getPassword());
        }catch (ServiceException e){
            throw new ServiceException(e.getMessage());
        }
    }

    public Iterable<Spectacol> allSpectacol() throws ServiceException {
            logger.info("All Spectacols in app service");
            return spectacolService.findAll();
    }

    public Iterable<Spectacol> getFilteredSpectacol(Date day) throws ServiceException {
        logger.info("Get Spectacols in app service");
        return spectacolService.findOnDate(day);
    }

    public void addBilet(String buyer,Spectacol spec,int seats) throws ServiceException {
        logger.info("Add Bilet in app service");
        biletService.AddBilet(buyer, spec.getId(), seats);
    }

    @Override
    public void logout(Angajat a) {

    }

    public Spectacol findSpectacol(long id) throws ServiceException {
        return spectacolService.findById(id);
    }
}

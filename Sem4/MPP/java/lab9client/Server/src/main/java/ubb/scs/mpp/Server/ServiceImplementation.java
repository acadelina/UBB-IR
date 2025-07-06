package ubb.scs.mpp.Server;

import org.apache.logging.log4j.LogManager;
import org.apache.logging.log4j.Logger;
import ubb.scs.mpp.Network.objectprotocol.ServiceObjectProxy;
import ubb.scs.mpp.Service.IAppService;
import ubb.scs.mpp.Service.ServiceException;
import ubb.scs.mpp.Service.observer.Observer;
import ubb.scs.mpp.model.Angajat;
import ubb.scs.mpp.model.Spectacol;
import java.util.Date;
import java.util.concurrent.ConcurrentHashMap;

public class ServiceImplementation implements IAppService {
    private final IAppService appService;
    private static Logger logger = LogManager.getLogger(ServiceObjectProxy.class);
    ConcurrentHashMap<String, Observer> angajatiObs ;


    public ServiceImplementation(IAppService appService) {
        this.appService = appService;
        logger.info("Service implementation created");
        angajatiObs = new ConcurrentHashMap<>();
    }
    @Override
    public Angajat login(Angajat ang, Observer observer) throws ServiceException {
        try {

            var a = appService.login(ang, observer);
            logger.info("Login angajat");
            if(a==null)
                logger.warn("Login angajat failed");
            if(observer==null)
                logger.warn("Login observer failed");
            
            if (angajatiObs.containsKey(ang.getUsername())) {
                logger.error("Login angajat is already logged in");
                throw new ServiceException("User already logged in.");
            }

            if (a != null && observer != null) {
                angajatiObs.put(ang.getUsername(), observer);
            }else
                throw new ServiceException("Login angajat failed");
            return a;
        }
        catch (ServiceException e) {
            logger.error(e.getMessage());
            throw e;
        }


    }


    @Override
    public Iterable<Spectacol> allSpectacol() throws ServiceException {
       return appService.allSpectacol();
    }

    @Override
    public Iterable<Spectacol> getFilteredSpectacol(Date day) throws ServiceException {
        return appService.getFilteredSpectacol(day);
    }

    @Override
    public void addBilet(String buyer, Spectacol spec, int seats) throws ServiceException {
        appService.addBilet(buyer, spec, seats);
        logger.info("Added bilet");
        new Thread(() -> {
            angajatiObs.values().forEach(observer -> observer.updatedSpectacol(spec));
        }).start();
    }

    @Override
    public void logout(Angajat a) throws ServiceException {
        Observer o=angajatiObs.remove(a.getUsername());
        if(o==null)
        {
            throw new ServiceException("User not logged out");
        }
        appService.logout(a);
    }

    @Override
    public void deleteSpectacol(long id) throws ServiceException {
        appService.deleteSpectacol(id);
    }
}

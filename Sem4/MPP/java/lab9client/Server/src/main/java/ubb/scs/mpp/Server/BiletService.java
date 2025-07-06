package ubb.scs.mpp.Server;

import org.apache.logging.log4j.LogManager;
import org.apache.logging.log4j.Logger;
import ubb.scs.mpp.Service.ServiceException;
import ubb.scs.mpp.model.Bilet;
import ubb.scs.mpp.model.Spectacol;
import ubb.scs.mpp.Repository.BiletRepository;
import ubb.scs.mpp.Repository.RepoException;
import ubb.scs.mpp.Repository.SpectacolRepository;

public class BiletService {
    private static final Logger logger= LogManager.getLogger(BiletService.class);
    private BiletRepository repo;
    private SpectacolRepository srepo;
    public BiletService(BiletRepository repo,SpectacolRepository srepo) {
        this.repo = repo;
        this.srepo = srepo;
        logger.info("BiletService created");
    }
    public void AddBilet(String buyer,Long spectacol,Integer seats) throws ServiceException {
        try {
            Spectacol s;
            s= srepo.findOne(spectacol);
            if(s.getAvailable_seats() < seats)
                throw new ServiceException("Not enough available seats");
            s.setAvailable_seats(s.getAvailable_seats() - seats);
            s.setSold_seats(s.getSold_seats()+seats);

            srepo.update(s);
            Bilet bilet = new Bilet(buyer,seats,s);
            repo.save(bilet);
            logger.info("Bilet added");
        }catch(RepoException e) {
            throw new ServiceException(e.getMessage());
        }
    }
}

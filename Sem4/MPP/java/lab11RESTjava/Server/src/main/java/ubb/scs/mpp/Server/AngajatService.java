package ubb.scs.mpp.Server;
import org.springframework.security.crypto.bcrypt.BCryptPasswordEncoder;
import org.apache.logging.log4j.LogManager;
import org.apache.logging.log4j.Logger;
import ubb.scs.mpp.Repository.RepoException;
import ubb.scs.mpp.Service.ServiceException;
import ubb.scs.mpp.model.Angajat;
import ubb.scs.mpp.Repository.AngajatRepository;

import java.util.Objects;
import java.util.Optional;
import java.util.stream.StreamSupport;

public class AngajatService{
    private static BCryptPasswordEncoder encoder = new BCryptPasswordEncoder();

    private static final Logger logger= LogManager.getLogger(AngajatService.class);
    private AngajatRepository repo;
    public AngajatService(AngajatRepository repo){
        this.repo = repo;
        logger.info("AngajatService created");
    }

    public void addAngajat(String username, String password,String mail) throws RepoException {
        Angajat angajat = new Angajat(username,encoder.encode(password),mail);
        repo.save(angajat);
    }
    public Angajat connectAngajat(String username, String password) throws ServiceException {
        try {
            logger.info("Angajat trying to connect");
            Optional<Angajat> user = StreamSupport.stream(repo.findAll().spliterator(), false)
                    .filter(it -> Objects.equals(it.getUsername(), username) && encoder.matches(password, it.getPassword()))
                    .findFirst();
            if(user.isEmpty())
            {
                throw new ServiceException("Angajat not found");
            }
            return user.get();

        }
        catch (Exception e) {
            throw new ServiceException(e.getMessage());
        }

    }
}

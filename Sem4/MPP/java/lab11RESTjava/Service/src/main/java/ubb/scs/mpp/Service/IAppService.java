package ubb.scs.mpp.Service;

import ubb.scs.mpp.Service.observer.Observer;
import ubb.scs.mpp.model.Angajat;
import ubb.scs.mpp.model.Spectacol;

import java.util.Date;

public interface IAppService {

    public Angajat login(Angajat angajat, Observer observer) throws ServiceException;
    public Iterable<Spectacol> allSpectacol() throws ServiceException;
    public Iterable<Spectacol> getFilteredSpectacol(Date day) throws ServiceException ;
    public void addBilet(String buyer,Spectacol spec,int seats) throws ServiceException;
    public void logout(Angajat angajat) throws ServiceException;



}

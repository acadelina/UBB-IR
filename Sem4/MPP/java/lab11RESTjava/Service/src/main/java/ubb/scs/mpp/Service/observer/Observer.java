package ubb.scs.mpp.Service.observer;

import ubb.scs.mpp.model.Angajat;
import ubb.scs.mpp.model.Spectacol;

public interface Observer {
    void updatedSpectacol(Spectacol s);
}

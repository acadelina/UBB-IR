package ubb.scs.mpp.Network.objectprotocol;

import ubb.scs.mpp.Network.dto.AngajatDTO;

public class LogoutRequest implements Request {
    AngajatDTO angajat;
    public AngajatDTO getAngajat() {
        return angajat;
    }

    public LogoutRequest(AngajatDTO angajat) {
        this.angajat = angajat;
    }
}
